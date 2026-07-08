import serial
import time
import subprocess

arduino_port = "/dev/ttyACM0"
print("Connected. Waiting for Arduino messages...")
baud_rate = 9600

arduino = serial.Serial(arduino_port, baud_rate)

time.sleep(2)

while True:
    message = arduino.readline()
    message = message.decode("utf-8")
    message = message.strip()

    subprocess.run([])


    if message == "PLAY_PAUSE":
        subprocess.run(["playerctl", "-p", "spotify", "play-pause"])

    if message:
        print("Received command:", message)

