import serial
import time
import subprocess

arduino_port = "/dev/ttyACM0"
baud_rate = 9600

arduino = serial.Serial(arduino_port, baud_rate)
time.sleep(2)

print("Connected. Waiting for Arduino messages...")

last_artist = ""
last_song = ""

while True:
    # Check if Arduino sent something
    if arduino.in_waiting > 0:
        message = arduino.readline()
        message = message.decode("utf-8").strip()

        if message == "PLAY_PAUSE":
            subprocess.run(["playerctl", "-p", "spotify", "play-pause"])

        if message:
            print("Received command:", message)

    # Get current artist
    artistResult = subprocess.run(
        ["playerctl", "-p", "spotify", "metadata", "-f", "{{artist}}"],
        capture_output=True,
        text=True
    )

    # Get current song
    songResult = subprocess.run(
        ["playerctl", "-p", "spotify", "metadata", "-f", "{{title}}"],
        capture_output=True,
        text=True
    )



    artist = artistResult.stdout.strip()
    song = songResult.stdout.strip()

    # Only send artist if it changed
    if (artist and song) and (artist != last_artist or song != last_song):
        message_to_arduino = artist + "\n" + song + "\n"
        arduino.write(message_to_arduino.encode("utf-8"))

        last_artist = artist
        last_song = song

    time.sleep(0.5) 