
const int ENABLE_PIN = 5;

const int DIR_ONE_PIN = 3;
const int DIR_TWO_PIN = 4;

String serialInput;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(DIR_ONE_PIN, OUTPUT);
  pinMode(DIR_TWO_PIN, OUTPUT);
}

void loop() {}

void serialEvent() {
  serialInput = Serial.readString();

  delay(2000);
  
  // Turn the motor on to a speed from serial input.
  analogWrite(ENABLE_PIN, parseInput(serialInput));
  
  // Set the direction of the motor.
  digitalWrite(DIR_ONE_PIN, HIGH);
  digitalWrite(DIR_TWO_PIN, LOW);

  // Let motor run for 2 seconds.
  delay(5000);

  // Turn the motor off.
  analogWrite(ENABLE_PIN, 0);
  
}// end serialEvent.

//************************************
// Returns int value of String.
//************************************
int parseInput(String in) {
  in.remove(serialInput.indexOf('\n'));
  
  return in.toInt();
  
} // end parseInput.
