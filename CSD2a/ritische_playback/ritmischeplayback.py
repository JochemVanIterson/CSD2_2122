#!/usr/bin/python
# Sources:
# https://simpleaudio.readthedocs.io/en/latest/

# Import the simpleaudio library
import simpleaudio as sa
import time

# Load the audio from a file, and insert into 'wav_obj'
# NOTE: Can't play 32float, so had to convert original file to 44k 24bit
wave_obj = sa.WaveObject.from_wave_file("kick.wav")

#### Functions

def playEvent(duration):
    # Play the audio file
    play_obj = wave_obj.play()
    print("\nPlayed event")
    # Wait for <duration> seconds
    time.sleep(duration)

#### Main program

# Ask the user how many times the file should be played. Convert var to integer.
numPlaybackTimesStr = input("\nHow many times should the audio file be played: ")
numPlaybackTimes = int(numPlaybackTimesStr)

# Create an empty list of size 'numPlaybackTimes'
events = [None] * numPlaybackTimes

# Provide user with expected syntax. Ask duration for every event and insert into an array
print("\nEnter the duration of your notes with 1 as a quarter note, 0.5 as an 8e note, and so on.")
for i in range(numPlaybackTimes):
    inputStr = input("\nEnter duration for event nr "+str(i+1)+": ")
    inputVal = float(inputStr)
    events[i] = inputVal

# Ask user which BPM it wants, and convert into float
bpmStr = input("\nEnter the BPM: ")
bpm = float(bpmStr)
timePerQuarter = 60/bpm

# for every event in list events execute function playEvent
for event in events:
    duration = event * timePerQuarter
    playEvent(duration)

