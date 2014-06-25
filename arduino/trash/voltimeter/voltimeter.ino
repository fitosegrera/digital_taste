    /*
    DC Voltmeter
    An Arduino DVM based on voltage divider concept
    T.K.Hareendran
    */
    #include <LiquidCrystal.h>
    LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
    int analogInput = 0;
    float vout = 0.0;
    float vin = 0.0;
    float R1 = 100000.0; // resistance of R1 (100K) -see text!
    float R2 = 10000.0; // resistance of R2 (10K) - see text!
    int value = 0;
    void setup(){
    pinMode(analogInput, INPUT);
    Serial.begin(115200);
    lcd.print("DC VOLTMETER");
    }
    void loop(){
    // read the value at analog input
    value = analogRead(analogInput);
    vout = (value * 5.0) / 1024.0; // see text
    vin = vout / (R2/(R1+R2));
    if (vin<0.09) {
    vin=0.0;//statement to quash undesired reading !
    }
    lcd.setCursor(0, 1);
    Serial.print("INPUT V= ");
    Serial.println(vin);
    delay(100);
    }
