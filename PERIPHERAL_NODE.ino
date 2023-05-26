//code for Arduino IoT
// it is the peripheral device
// provides information and the characteristics
// provides the info for the central devices

#include <ArduinoBLE.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int time_count_second=0; //Declaring a time counter for each second
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup() {
    // initialize LCD
    lcd.init();
    // turn on LCD backlight                      
   lcd.backlight();
    Serial.begin(9600); //serial start  

    Serial.println("Bluetooth® Low Energy Peripheral ");
    
    
   if(!BLE.begin()) { //starts the bluetooth module
   Serial.println("starting Bluetooth® Low Energy module failed!");
   while (1);
   }  
    BLE.setLocalName("DIT_WSN_1"); // sets the peripheral's name
    BLE.advertise(); //starts to advertise its name     
    Serial.println("my name is: DIT_WSN "); //print its name
  
}

void loop() {
    BLEDevice central = BLE.central();
      if (central){
        Serial.println("Connected to central: "); 
        Serial.println(central.address()); //print the central address *needs debug*
         while (central.connected()) 
         { //establishes connection
                 // set cursor to first column, second row
          lcd.setCursor(0,0);
          lcd.print("peripheral device" );
          lcd.setCursor(0,1);
          lcd.print("my rssi is");
          lcd.setCursor(11,1);
          lcd.print(central.rssi());
          delay(500);
         // distance(central); //calls the distance function
      }
       Serial.print(F("Disconnected from central: "));
       Serial.println(central.address()); 

   } 
}