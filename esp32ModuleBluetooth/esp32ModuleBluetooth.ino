#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32BT");
  Serial.println("Iniciado");
}

void loop() {
  if(Serial.available()) {
    char palavra = Serial.read();
    Serial.println(palavra);
    SerialBT.write(palavra);
  }
  if(SerialBT.available()) {
    char recebido = SerialBT.read();
    Serial.println(recebido);

    Serial.write(recebido);
  }
  delay(20);
}
