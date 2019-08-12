#include <Servo.h>
#include <ESC.h>

#define INPUT_PIN A0

int val;

ESC myESC (4, 800, 2200, 550);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");
  delay(2500);
  /*
  Serial.println("Calibrating");
  myESC.calib();                  // Calibration of the Max and Min value the ESC is expecting
  Serial.println("Stopping");
  myESC.stop();  
  Serial.println("ARMED");
  */
  myESC.arm();  
  Serial.println("Controls passed to user");
  Serial.println("\n");
}

void loop() {
  val = analogRead(INPUT_PIN);            // reads the value of the potentiometer (value between 0 and 1023)
  //Serial.println(val);
  val = map(val, 0, 1023, 2200, 800);  // scale it to use it with the ESC (value between 1000 and 2000)
  myESC.speed(val);                     // sets the ESC speed according to the scaled value
  Serial.println(val);
  delay(5);  
}
