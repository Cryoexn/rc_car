import serial;
import codecs;
import time;

# Open serial communications with arduino.
arduino_serial = serial.Serial(port='COM3', baudrate=9600, timeout=10)

time.sleep(2.5)

def send_to_serial(msg):
	print("Sending...")
	arduino_serial.write(bytes(msg+"\n", 'utf-8'))


def get_input():
	userIn = input("Enter Angle (0-180): ")
	while userIn != "q":
		if int(userIn) < 180 and int(userIn) >= 0:
			send_to_serial(userIn)
		else:
			print("Not valid.")

		userIn = input("Enter Angle (0-180): ")


get_input()


