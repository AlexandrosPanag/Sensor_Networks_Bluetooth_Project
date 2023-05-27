//Credits: Alexandros Panagiotakopoulos, Christos Koutsos  & The Autonomous Systems Laboratory, University of Ioannina
//MIT LICENSE
//code for Arduino BLE 
//central device
#include <ArduinoBLE.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup() {
    Serial.begin(9600); //serial start   
    
    BLE.begin();  //starts the bluetooth module
    Serial.println("Bluetooth® Low Energy central ");
    
    BLE.setLocalName("DIT_WSN_CENTRAL_1"); // sets the central's name
    BLE.scanForName("DIT_WSN_1"); // starts scanning for specific peripherals
    // initialize LCD
  lcd.init();
  lcd.backlight();
}
    
void loop() {
  
  BLEDevice peripheral = BLE.available(); // check if a peripheral has been discovered

  // if a central is connected to peripheral:
  if (peripheral) {
    Serial.print("Found ");
    Serial.println(peripheral.address());
    Serial.println(peripheral.localName());
    BLE.stopScan();
     Serial.println("connecting...");
  if (peripheral.connect()) {
      Serial.println("connected");  
      }
  else{
    
    Serial.println("failed to connect");
    return;
      }
      
  while(peripheral.connected()){
    
        Serial.print("peripheral RSSI: ");
        Serial.println(peripheral.rssi());
        Serial.print("MY RSSI IS : ");
        Serial.println(BLE.rssi());
        
        //LCD print RSSI
     // set cursor to first column, second row
     lcd.setCursor(0,0);
     lcd.print("central device" );
     lcd.setCursor(0,1);
     lcd.print("my rssi is");
     lcd.setCursor(11,1);
     lcd.print(peripheral.rssi());
     delay(500);
     
  }
  Serial.println("peripheral disconnected");
  return;

  }
}
