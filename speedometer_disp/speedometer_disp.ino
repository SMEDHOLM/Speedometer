#include <EEPROM.h> //library for working with Arduino internal memory
//-----------Display----------
// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//--------Display------
unsigned long lastturn; //time storage variables
float SPEED; //speed storage variable as a decimal fraction
float DIST; //variable for storing distance as a decimal fraction
float w_length=2.050; //wheel circumference in meters
void setup() {
Serial.begin(9600); //open the port
attachInterrupt(2,sens,RISING); //connect interrupt to pin 2 when the signal rises
//Display----------
//set up the LCD's number of columns and rows:
lcd.begin(16, 2);
//--------------
DIST=(float)EEPROM.read(0)/10.0; //remember the distance traveled when the system starts (dividing by 10 is necessary to save tenths of the distance, see the entry)
}
void sens() {
if (millis()-lastturn > 80) { //protection against accidental measurements (based on the fact that the bike won't go faster than 120 km/h)
SPEED=w_length/((float)(millis()-lastturn)/1000)*3.6; //calculate speed, km/h
lastturn=millis(); //remember the time of the last rotation
DIST=DIST+w_length/1000; //add the wheel length to the distance with each rotation
}
}

void loop() {
int cel_sp=floor(SPEED);
int sot_sp=(((float)cel_sp/1000)-floor((float)cel_sp/1000))*10; 
int des_sp=(((float)cel_sp/100)-floor((float)cel_sp/100))*10; 
int ed_sp=(((float)cel_sp/10)-floor((float)cel_sp/10))*10; 
int dr_sp=(float)(SPEED-floor(SPEED))*10; 

lcd.print("SPEED: " + sot_sp + des_sp + ed_sp + dr_sp); 

int cel_di=floor(DIST); //whole 
int sot_di=(((float)cel_di/1000)-floor((float)cel_di/1000))*10; //hundreds 
int des_di=(((float)cel_di/100)-floor((float)cel_di/100))*10; //tens 
int ed_di=floor(((float)((float)cel_di/10)-floor((float)cel_di/10))*10); //units (with dot) 
int dr_di=(float)(DIST-floor(DIST))*10; //tenths 

lcd.setCursor(0, 1); 
lcd.print("DISTANCE: " + sot_di + des_di + ed_di + dr_di); 

if ((millis()-lastturn)>2000){ //if there's no signal for more than 2 seconds
SPEED=0; //assume SPEED is 0
EEPROM.write(0,(float)DIST*10.0); //write DIST to internal memory. I did it this way because internal memory doesn't like being written too often. Also, *10 to save the tenth.
}
}
