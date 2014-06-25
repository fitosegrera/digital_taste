#include <SPI.h> 

const int csPin = 10;
int globalValue = 0;
int delayPot = 30;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); //We know this from the Data Sheet

  pinMode(csPin,OUTPUT);
  digitalWrite(csPin, HIGH);
}

void loop() {
  if(globalValue == 0){
    for(int i=0; i<255; i++) { 
     digitalPotWrite(0,i);
     delay(delayPot);
     globalValue = i;
     Serial.print("FIRST: ");
     Serial.println(globalValue);
   }
  }
  if(globalValue >= 254){
    Serial.println("WORKS!!!");
    for(int j=255; j>-1; j--) { 
     digitalPotWrite(0,j);
     delay(delayPot);
     globalValue = j;
     Serial.print("SECOND: ");
     Serial.println(globalValue);
    }
  }
}
void digitalPotWrite(int address, int value) {
  digitalWrite(csPin, LOW); //select slave
  byte command = 0x00; //0xB0 = 10110000 
  //command += address; 
  SPI.transfer(command); 
  byte byte1 = (value >> int(value/255));
  byte byte0 = ((value & 0x00)>>8); //0xFF = B11111111
  SPI.transfer(byte1);
  SPI.transfer(byte0);
  digitalWrite(csPin, HIGH); //de-select slave
}

