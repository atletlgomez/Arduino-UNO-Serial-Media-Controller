import serial
import subprocess
import time

ARDUINO_PORT = "/dev/ttyACM0"
BAUD_RATE = 9600
PLAYER = "spotify"


def run_playerctl(*args):
    subprocess.run(["playerctl", "-p", PLAYER, *args], check=False)


arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE)
time.sleep(2)

print("Connected. Waiting for Arduino messages...")

last_artist = ""
last_song = ""

while True:
    if arduino.in_waiting > 0:
        message = arduino.readline().decode("utf-8").strip()

        if message:
            print("Received command:", message)

            if message == "PLAY_PAUSE":
                run_playerctl("play-pause")
            elif message == "NEXT":
                run_playerctl("next")
            elif message == "PREV":
                run_playerctl("previous")
            elif message == "VOL+":
                run_playerctl("volume", "0.1+")
            elif message == "VOL-":
                run_playerctl("volume", "0.1-")

    artist = subprocess.run(
        ["playerctl", "-p", PLAYER, "metadata", "-f", "{{artist}}"],
        capture_output=True,
        text=True,
        check=False,
    ).stdout.strip()

    song = subprocess.run(
        ["playerctl", "-p", PLAYER, "metadata", "-f", "{{title}}"],
        capture_output=True,
        text=True,
        check=False,
    ).stdout.strip()

    # Only send updates when the metadata changes.
    if artist and song and (artist != last_artist or song != last_song):
        arduino.write(f"{artist}\n{song}\n".encode("utf-8"))
        last_artist, last_song = artist, song

    time.sleep(0.5) 