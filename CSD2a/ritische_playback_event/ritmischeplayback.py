#!/usr/bin/python

# Import the simpleaudio library
import simpleaudio as sa
import time

# Load the audio from a file, and insert into 'soundKick'
# NOTE: Can't play 32float, so had to convert original file to 44k 24bit
soundKick = sa.WaveObject.from_wave_file("../assets/kick.wav")

#### Functions

def createEvent(timestamp, instrument, velocity):
    """Create a new event with easier arguments

    Args:
        timestamp (integer): Timestamp on which to play the event
        instrument (string): Instrument to be played
        velocity (integer): Velocity of the event (0 for off, non 0 for on)

    Returns:
        dict: The event
    """
    return {
        'timestamp': timestamp,
        'instrument': instrument,
        'velocity': velocity
    }

def execEvent(event):
    """Play an event

    Args:
        event (dict): Event to be played
    """
    
    # Check if instrument is 'kick'
    if event['instrument'] == 'kick':
        # Check if velocity is higher than 0
        if event['velocity'] > 0:
            print("\nKick On", event['timestamp'])
            soundKick.play()
        else:
            print("\nKick Off", event['timestamp'])
    

#### Main program

# Ask user which BPM it wants, and convert into float
bpmStr = input("\nEnter the BPM: ")
bpm = float(bpmStr)
timePerQuarter = 60/bpm

# Ask the user how many times the file should be played. Convert var to integer.
numPlaybackTimesStr = input("\nHow many times should the audio file be played: ")
numPlaybackTimes = int(numPlaybackTimesStr)

# Create an empty list of size 'numPlaybackTimes'
events = []

# Provide user with expected syntax. Ask duration for every event and insert into an array
print("\nEnter the duration of your notes with 1 as a quarter note, 0.5 as an 8e note, and so on.")
currentTime = 0
for i in range(numPlaybackTimes):
    inputStr = input("\nEnter duration for event nr "+str(i+1)+": ")
    inputVal = float(inputStr)
    # Add note On event to eventList
    events.append(createEvent(currentTime, 'kick', 127))
    # Calculate new timestamp
    currentTime += inputVal * timePerQuarter * 1000
    # Add note Off event to eventList
    events.append(createEvent(currentTime, 'kick', 0))

playableEvents = events.copy()
startTimestamp = time.time_ns() # Work with ms
while len(playableEvents) > 0:
    # Get elapsed timestamp is ms, i.e. how much time has passed since last loop
    elapsedTimestamp = (time.time_ns() - startTimestamp) / 1000000.

    # Look for events that should be played and walk through them
    nowEvents = list(filter(lambda x: (elapsedTimestamp > x['timestamp']), playableEvents))
    for event in nowEvents:
        execEvent(event)
        # Remove event as it has been executed
        playableEvents.remove(event)

    # If loop is empty, rebuild list and reset startTimestamp
    if len(playableEvents) == 0:
        startTimestamp = time.time_ns()
        playableEvents = events.copy()

    time.sleep(0.01)  # Time resolution is 1ms
