import serial;
import codec;


def get_input():
		userIn = input("Enter Angle (0-180): ")
		while userIn != "q":
				userIn = input("Enter Angle (0-180): ")
				send_cmd(userIn)


