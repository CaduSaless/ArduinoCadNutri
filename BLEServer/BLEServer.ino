#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Variáveis de controle
BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;

void envia_Tamanho();

// UUIDs padrão para o serviço UART (Compatível com a maioria dos apps BLE)
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// Callback para gerenciar a conexão
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println(">>> Dispositivo Conectado");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println(">>> Dispositivo Desconectado");
    }
};

// Callback para processar o que o celular envia para o ESP32
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.print("Recebido do FLASK: ");
        for (int i = 0; i < rxValue.length(); i++) {
          if(rxValue == "M") {
            envia_Tamanho();
          }
          Serial.print(rxValue[i]);
        }
        Serial.println();
      }
    }
};

void setup() {
  Serial.begin(115200);

  // Inicializa o dispositivo BLE
  BLEDevice::init("ESP32_BLE");

  // Cria o Servidor BLE
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Cria o Serviço UART
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Cria a Característica de Transmissão (TX) - Envia do ESP para o Celular
  pTxCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_TX,
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
  pTxCharacteristic->addDescriptor(new BLE2902());

  // Cria a Característica de Recebimento (RX) - Celular escreve aqui
  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID_RX,
                                           BLECharacteristic::PROPERTY_WRITE
                                         );
  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Inicia o serviço
  pService->start();

  // Inicia o anúncio (Advertising) para o celular encontrar o ESP32
  pServer->getAdvertising()->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  
  Serial.println("Aguardando conexao BLE no app...");
}

void envia_Tamanho () {
  String input = "124.5";

  pTxCharacteristic->setValue(input);
  pTxCharacteristic->notify();
};

void loop() {
    // Se houver algo digitado no Monitor Serial do PC, envia para o Bluetooth
    if (deviceConnected && Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        Serial.print("Enviado para o Celular: ");
        Serial.println(input);
        
        pTxCharacteristic->setValue(input);
        pTxCharacteristic->notify(); // Notifica o celular que há um novo dado
    }

    // Gerenciamento de reconexão automática
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); 
        pServer->startAdvertising(); // Reinicia o anúncio ao desconectar
        Serial.println("Reiniciando anúncio (Advertising)...");
        oldDeviceConnected = deviceConnected;
    }
    
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
    }
}