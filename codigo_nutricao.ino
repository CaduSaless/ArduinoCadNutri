#include <HardwareSerial.h>
#include <TFMPlus.h> // Biblioteca oficial do TF-Luna

// ==========================================
// 1. CONFIGURAÇÕES DO HARDWARE E VARIÁVEIS
// ==========================================
HardwareSerial lidarSerial(2); // Instancia a porta UART2 do ESP32
TFMPlus tfmP;                  // Cria o objeto principal do sensor

#define RXD2 16                // Pino RX2 do ESP32 (Ligar no TX do sensor)
#define TXD2 17                // Pino TX2 do ESP32 (Ligar no RX do sensor)

#define numeroDeLeitura 300    // Quantidade de leituras para o filtro de média
float alturaFixa = 213.0;      // Variável que guarda a distância do teto ao chão vazio (em cm)

// ==========================================
// 2. CONFIGURAÇÃO INICIAL (SETUP)
// ==========================================
void setup() {
  // Inicia a comunicação com o computador (para o Monitor Serial)
  Serial.begin(115200);
  delay(20);
  
  // Inicia a comunicação com o sensor TF-Luna nos pinos 16 e 17
  lidarSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  // Entrega o controle dessa porta serial para a biblioteca TFMPlus
  tfmP.begin(&lidarSerial); 
  
  // Imprime o menu de instruções no Monitor Serial
  Serial.println("\n--- SISTEMA LIDAR: MODO MANUAL ---");
  Serial.println("Digite 'C' e aperte Enter para CALIBRAR (medir o chao vazio)");
  Serial.println("Digite 'M' e aperte Enter para MEDIR (altura de um objeto)");
  Serial.println("----------------------------------\n");
}

// ==========================================
// 3. FUNÇÃO BASE DE LEITURA DO SENSOR
// ==========================================
uint16_t getLidarDistance() {
  int16_t tfDist = 0;    // Variável para guardar a distância lida
  int16_t tfFlux = 0;    // Força do sinal do laser (obrigatório para a biblioteca)
  int16_t tfTemp = 0;    // Temperatura do chip (obrigatório para a biblioteca)

  // A função getData() tenta conversar com o sensor. 
  // Se receber um pacote válido e sem erros, retorna "true".
  if (tfmP.getData(tfDist, tfFlux, tfTemp)) {
    return (uint16_t)tfDist; // Devolve a distância em centímetros
  } else {
    return 0; // Se deu erro de leitura, devolve 0
  }
}

// ==========================================
// 4. FUNÇÃO DE CALIBRAGEM (ACHAR O CHÃO)
// ==========================================
void calibrateHeight() {
  Serial.println("\n[STATUS] Iniciando calibragem da altura fixa...");
  Serial.println("[STATUS] Por favor, deixe o espaco livre debaixo do sensor.");

  uint32_t sum = 0;               // Variável para somar todas as leituras
  uint16_t collected = 0;         // Contador de quantas leituras deram certo
  unsigned long start = millis(); // Marca o tempo inicial para evitar travamentos
  const unsigned long timeoutMs = 15000; // Tempo máximo de espera: 15 segundos

  // Fica em loop até coletar 300 amostras OU estourar o tempo de 15 segundos
  while (collected < numeroDeLeitura && (millis() - start) < timeoutMs) {
    
    uint16_t d = getLidarDistance(); // Pede uma leitura ao sensor
    
    if ((d > 0) && (d<250)) { // Se a leitura foi válida (maior que zero)
      sum += d;  // Adiciona a distância na soma total
      collected++; // Aumenta o contador de sucesso
      
      // Imprime o progresso no console a cada 10% (30 leituras)
      if (collected % (numeroDeLeitura / 10) == 0) {
        int percentual = (collected * 100) / numeroDeLeitura;
        Serial.print("Progresso: ");
        Serial.print(percentual);
        Serial.println("%");
      }
    }
  }

  // Se o loop terminou mas não coletou nada, avisa que deu erro
  if (collected == 0) {
    Serial.println("[ERRO] Calibragem falhou: Nenhuma amostra valida coletada. Verifique os fios!");
    return; // Interrompe a função
  }

  // Calcula a média das 300 leituras e salva na variável global
  alturaFixa = (float)sum / (float)collected;

  Serial.println("[SUCESSO] Calibragem concluida!");
  Serial.print("Nova altura do chao: ");
  Serial.print(alturaFixa);
  Serial.println(" cm\n");
}

// ==========================================
// 5. FUNÇÃO DE MEDIÇÃO (ACHAR O OBJETO)
// ==========================================
void medirAltura() {
  Serial.println("\n[STATUS] Iniciando medicao do objeto...");

  uint32_t somaDistancias = 0;
  int distanciasColetadas = 0;
  unsigned long start = millis();
  const unsigned long timeoutMs = 10000; // Tempo máximo de espera: 10 segundos

  // Repete a mesma lógica de loop da calibragem para tirar a média de 300 leituras
  while (distanciasColetadas < numeroDeLeitura && (millis() - start) < timeoutMs) {
    
    uint16_t d = getLidarDistance();
    
    if ((d > 0) && (d < 250)) {
      somaDistancias += d;
      distanciasColetadas++;
      
      if (distanciasColetadas % (numeroDeLeitura / 10) == 0) {
        int percentual = (distanciasColetadas * 100) / numeroDeLeitura;
        Serial.print("Lendo objeto: ");
        Serial.print(percentual);
        Serial.println("%");
      }
    }
  }

  if (distanciasColetadas == 0) {
    Serial.println("[ERRO] Nenhuma amostra valida coletada (timeout).");
    return;
  }

  // Calcula a distância média lida do teto até a cabeça do objeto
  float media = (float)(somaDistancias) / (float)(distanciasColetadas);
  
  // Matemática final: Subtrai a distância lida agora do chão que foi calibrado antes
  float distancia = alturaFixa - media;
  
  // Arredonda o valor para um número inteiro
  uint16_t alturaFinal = (uint16_t)(distancia + 0.5f); 
  
  Serial.println("[SUCESSO] Medicao concluida!");
  Serial.print("-> Altura calculada da pessoa/objeto: ");
  Serial.print(alturaFinal);
  Serial.println(" cm\n");
}

// ==========================================
// 6. LOOP PRINCIPAL (ESCUTANDO O TECLADO)
// ==========================================
void loop() {
  // Verifica se o usuário digitou algo no Monitor Serial
  if (Serial.available() > 0) {
    
    // Lê o que foi digitado e converte para letra maiúscula
    char comando = toupper(Serial.read()); 

    // Se o usuário digitou 'C', roda a função de calibragem
    if (comando == 'C') {
      calibrateHeight();
    }
    // Se o usuário digitou 'M', roda a função de medição
    else if (comando == 'M') {
      medirAltura();
    }
  }
  
  delay(50); // Pequeno atraso para não sobrecarregar o processador do ESP32
}