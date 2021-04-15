//****************************************************************
// Project : IRC_Car
// Author  : David Pitoniak
// Date    : 04/15/2021
// Description: 
//  Infared Remote Conrolled Car, Using the materials 
//  from the Arduino Starter Kit attempt to create 
//  a basic remote controlled car.
//****************************************************************

#include <Servo.h>
#include <IRremote.h>

// Constants.
const int MOTOR_ENABLE_PIN  = 5;  // Pin to enable motor.
const int MOTOR_DIR_ONE_PIN = 3;  // Pin for motor direction.
const int MOTOR_DIR_TWO_PIN = 4;  // Pin for motor direction.

const int SERVO_PIN           = 10; // Pin for servo output.
const int SERVO_INITIAL_ANGLE = 90; // Servo intial angle.

const int IR_RECEIVER_PIN = 2; // Pin for IR Sensor.

// Variables.
Servo steeringServo; // Servo variable for steering.
String serialInput;  // Container for serial messages.
IRrecv receiver(IR_RECEIVER_PIN); // IR Receiver.
decode_results results;  // decoded IR data.
unsigned long key_value;  // Key value for decoded data.

int motor_speed;
String motor_dir;
bool motor_stopped;
int servo_angle;


//****************************************************************
// Runs before loop() starts. Initialize all starting values and
// pin modes.
//****************************************************************
void setup() {
  
  // Setup Motor.
  pinMode(MOTOR_ENABLE_PIN,  OUTPUT);
  pinMode(MOTOR_DIR_ONE_PIN, OUTPUT);
  pinMode(MOTOR_DIR_TWO_PIN, OUTPUT);
  motor_speed = 0;
  motor_dir = "F";
  motor_stopped = false;

  // Setup Servo.
  steeringServo.attach(SERVO_PIN);         // Attach servo to correct pin.
  steeringServo.write(SERVO_INITIAL_ANGLE); // Set initial angle.
  servo_angle = steeringServo.read();

  // Setup IRreceiver.
  receiver.enableIRIn();

  // Setup Serial.
  Serial.begin(9600);    // Set baud rate to 9600.
  Serial.setTimeout(10); // Set timeout to 10ms.
  
} // end setup.

void loop() { 
  if (receiver.decode()) { // decode the received signal and store it in results
    
    results.value = receiver.decodedIRData.decodedRawData;
    
    if (results.value == 0xFFFFFFFF) {
      results.value = key_value;
    }
    
    switch (results.value) {
      case 0xBA45FF00:
        Serial.println("POWER");
        break;
      case 0xB946FF00:
        Serial.println("Forward ->>");
        // Change motor direction to forward.
        motor_speed += 30;
        analogWrite(MOTOR_ENABLE_PIN, motor_speed);
        break;
      case 0xBB44FF00:
        Serial.println("Left <-");
        // Change servo angle.
        servo_angle -= 20;
        
        if(servo_angle >= 0) {
          
        } else {
          servo_angle = 0;
        }
        
        steeringServo.write(servo_angle);
        
        break;
      case 0xBF40FF00:
        Serial.println("Stop");
        // Start/Stop Motor.
        if(!motor_stopped) {
          analogWrite(MOTOR_ENABLE_PIN, 0);
          digitalWrite(MOTOR_DIR_ONE_PIN, LOW);
          digitalWrite(MOTOR_DIR_TWO_PIN, LOW);
          motor_stopped = true;
        } else {
          analogWrite(MOTOR_ENABLE_PIN, motor_speed);
          setMotorDirection("F");
          motor_stopped = false;
        }
        break;
      case 0xBC43FF00:
        Serial.println("Right ->");
        // Change servo angle.
        servo_angle += 20;
        
        if(servo_angle <= 180) {
          
        } else {
          servo_angle = 180;
        }
        
        steeringServo.write(servo_angle);
        
        break;
      case 0xEA15FF00:
        Serial.println("Reverse <<-");
        // Change motor direction to reverse.
        
        break;
    }
    key_value = results.value; // store the value as key_value
    receiver.resume(); // reset the receiver for the next code
  } }

//****************************************************************
// Triggered at the end of loop() if there is a serialEvent.
// input should be in form:
//  "M{0-255}?{F|R}:S{0-180}"
//    M = Motor, 0-255 = Speed, F|R = Forward or Reverse.
//    S = Servo, 0-180 = Angle.
//****************************************************************
void serialEvent() {

  // Read command from serial.
  serialInput = Serial.readString();

  // Update Motor state based on command.
  analogWrite(MOTOR_ENABLE_PIN, parseMotorSpeed(serialInput));
  setMotorDirection(parseMotorDirection(serialInput));

  // Update Servo state based on command.
  steeringServo.write(parseServoAngle(serialInput));
  
} // end serialEvent.

//****************************************************************
// Returns int value of parsed input for motor speed.
//****************************************************************
int parseMotorSpeed(String in) {

  // Remove non motor speed characters.
  in.remove(0, 1);
  in.remove(in.indexOf('?'));
  
  return in.toInt();
  
} // end parseInput.

//****************************************************************
// Returns int value of parsed input for motor direction.
//****************************************************************
String parseMotorDirection(String in) {

  // Remove all non motor direction characters.
  in.remove(0, in.indexOf('?') + 1);
  in.remove(in.indexOf(':'));
  
  return in;
  
} // end parseInput.

//****************************************************************
// Returns int value of parsed input for servo angle.
//****************************************************************
int parseServoAngle(String in) {

  //Remove all non Servo angle characters.
  in.remove(0, in.indexOf('S') + 1);
  
  return in.toInt();
  
} // end parseInput.

//****************************************************************
// Changes the direction of the motor based on the dir String.
//****************************************************************
void setMotorDirection(String dir) {
  
  if(dir == "F") {
    digitalWrite(MOTOR_DIR_ONE_PIN, HIGH);
    digitalWrite(MOTOR_DIR_TWO_PIN, LOW);
  } else {
    digitalWrite(MOTOR_DIR_ONE_PIN, HIGH);
    digitalWrite(MOTOR_DIR_TWO_PIN, LOW);
  }
  
} // end parseInput.
