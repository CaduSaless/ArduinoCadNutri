import os
from dotenv import load_dotenv
from google import genai
from PIL import Image

# 1. Carrega as configurações do arquivo .env
load_dotenv()

# 2. Pega a chave da variável de ambiente que criamos
CHAVE_API = os.getenv("GEMINI_API_KEY")

# Verifica se a chave foi carregada corretamente (opcional, mas recomendado)
if not CHAVE_API:
    raise ValueError("Chave da API não encontrada. Verifique seu arquivo .env")

# 3. Inicializa o cliente com a chave segura
client = genai.Client(api_key=CHAVE_API)

# ... (Daqui para baixo, o código da imagem continua exatamente igual) ...
caminho_da_imagem = 'numeros.jpg'
imagem = Image.open(caminho_da_imagem)

print("Analisando a imagem com a API protegida...")
resposta = client.models.generate_content(
    model='gemini-2.5-flash',
    contents=[
        """Você é um sistema de leitura automatizada. 
        Esta imagem mostra o display digital de uma balança. 
        Por favor, leia atentamente os números que aparecem no visor.
        Retorne ÚNICA E EXCLUSIVAMENTE o valor numérico final.
        A resposta nao poderá ser mais de um numero, e deve ser apenas o número, sem unidades ou texto adicional.""",
        imagem
    ]
)

print("\n--- Resultado ---")
print(resposta.text)