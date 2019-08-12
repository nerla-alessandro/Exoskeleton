
#include <HX711.h>


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 5;

#include <FastX9CXXX.h>

#define X9_CS_PIN 10
#define X9_UD_PIN 8
#define X9_INC_PIN 9

int forceReading = 0;
int tmpPulse = 1500;


#define upTreshold 4
#define downTreshold -4
#define maxTreshold 30
#define minTreshold -20


HX711 scale;
FastX9CXXX potentiometer;

void setup() {
  Serial.begin(9600);
  potentiometer.Setup(X9_CS_PIN, X9_UD_PIN, X9_INC_PIN);
  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0


}

void loop() {
  readForce();
  tmpPulse = constrain(tmpPulse, 1, 100);
  potentiometer.JumpToStep(tmpPulse);
  Serial.println(tmpPulse);
}

int readForce(){
  forceReading = scale.get_units();
  forceReading = constrain(forceReading, minTreshold, maxTreshold);
  if(forceReading > upTreshold){
    Serial.print("Up - ");
    tmpPulse = map(forceReading, upTreshold, maxTreshold, 60, 100);
    //Serial.println(tmpPulse);
  }
  else if(forceReading < downTreshold){
    Serial.print("Down - ");
    tmpPulse = map(forceReading, downTreshold, minTreshold, 35, 0);
    //Serial.println(tmpPulse);
  } 
  else{
    Serial.print("Neutral -");
    tmpPulse = 50;
    //Serial.println(tmpPulse);
  }
}
