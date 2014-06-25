#include <math.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
int pot = 0;
int potHeat = 0;
int heatPin = 10;
int elecPin = 11;

float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!
int value = 0;

double Thermister(int RawADC) {
  double Temp;
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //uTemp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
}

void setup() {
  Serial.begin(9600);
  display.begin();
  pinMode(heatPin, OUTPUT);
  pinMode(elecPin, OUTPUT);
  display.setContrast(50);
}

void loop() { 
  // read the value at analog input
  value = analogRead(A0);
  vout = (value * 5.0) / 1024.0; // see text
  vin = vout / (R2/(R1+R2));
  if (vin<0.09) {
    vin=0.0;//statement to quash undesired reading !
  }

  int temperature = (int(Thermister(analogRead(A2))));  
  //pot = analogRead(A0);
  potHeat = analogRead(A1);
  //int potMap = int(map(pot, 100, 0, 0, 5));
  int potHeatMap = int(map(potHeat, 0, 1023, 0, 255));
  float potMap = float(map(vin, 4.46, 0, 0, 4.46));
  analogWrite(heatPin, potHeatMap);
  //analogWrite(elecPin, potElecMap);
  delay(100);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  display.println("Digital Taste");
  display.println("");
  display.setTextColor(BLACK);
  display.print("Volt: ");
  display.print(potMap);
  display.println(" v");
  //display.println("");
  display.print("Temp_LVL: ");
  display.println(potHeatMap);
  //display.println(" v");
  display.print("Temp: ");
  display.print(temperature);
  display.print(" c");
  display.display();
  //Serial.println(potMap);
  delay(10);

}



