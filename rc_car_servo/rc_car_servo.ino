#include <Servo.h>

Servo ser;          // Servo instance.
String serialInput; // String to store serial input.

//************************************
// Runs before loop() starts.
//************************************
void setup() {

  // Start Serial at baud rate 9600.
  Serial.begin(9600);
  Serial.setTimeout(10);
  
  // Attach Servo to pin 10;
  ser.attach(10);

  // Set the servo to center.
  ser.write(0);
  
} // end setup.

void loop() { /* Not used in this program. */ }

//************************************
// Triggered when there is a serial 
// event at the end of loop().
//************************************
void serialEvent() {
  serialInput = Serial.readString();

  // Set the servo to position specified
  // by Serial input.
  ser.write(parseInput(serialInput));
  
} // end serialEvent.

//************************************
// Returns int value of String.
//************************************
int parseInput(String in) {
  in.remove(serialInput.indexOf('\n'));
  
  return in.toInt();
  
} // end parseInput.
