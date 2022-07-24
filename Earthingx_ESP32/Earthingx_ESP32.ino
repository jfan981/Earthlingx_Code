#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)           //error catching
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; //declares the Bluetooth object

void setup() {
  
  Serial1.begin(115200);
  SerialBT.begin("ESP32_Earthlingx");  //begins Bluetooth Serial connection
 // Serial.println("Started successfully.");

}

char readIn;

void loop() {

  if (SerialBT.available()) { //if there are bytes available in the buffer
    readIn = char(SerialBT.read()); //read in one and store it in readIn
    Serial1.print(readIn);
  }
  delay(20);

}
