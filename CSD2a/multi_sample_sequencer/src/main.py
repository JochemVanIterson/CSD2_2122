#!/usr/bin/python

import sys
import playerThread

playerInstance = playerThread.playerThread([])

def createEvent(timestamp, sound, velocity):
    """Create a new event with easier arguments

    Args:
        timestamp (integer): Timestamp on which to play the event
        sound (string): sound to be played
        velocity (integer): Velocity of the event (0 for off, non 0 for on)

    Returns:
        dict: The event
    """
    return {
        'timestamp': timestamp,
        'sound': sound,
        'velocity': velocity
    }


#### Main program
if __name__ == "__main__":
    playerInstance.start()

    # Ask user which BPM it wants, and convert into float
    bpmStr = input("\nEnter the BPM: ")
    bpm = float(bpmStr)
    timePerQuarter = 60/bpm
    timePerStep = timePerQuarter / 2

    gridLength = 8
    grid = {
        'hihat': [True,  True,  True,  True,  True,  True,  True,  True],
        'snare': [False, False, True, False,  False, False, True, False],
        'kick':  [True,  False, True, False,  True,  True,  True, False]
    }
    events = []

    for instrumentName, instrumentGrid in grid.items():
        currentTime = 0
        for value in instrumentGrid:
            # Calculate new timestamp
            nextTime = currentTime + timePerStep * 1000 * 1000 * 1000
            if value:
                events.append(createEvent(currentTime, instrumentName, 127))
                events.append(createEvent(nextTime, instrumentName, 0))
            currentTime = nextTime
    events = sorted(events, key=lambda k: k['timestamp'])

    playerInstance.replaceEvents(events)

    while True:
        command = input("> ")
        if command == 'start':
            playerInstance.setPlaybackState('start')
        elif command == 'stop':
            playerInstance.setPlaybackState('stop')
        elif command == 'pause':
            playerInstance.setPlaybackState('pause')
        elif command.startswith('loop '):
            playerInstance.setLoop(command.split()[1] == 'true')
        elif command == 'quit':
            print("DEBUG", command)
            playerInstance.killThread()
            playerInstance.join()
            sys.exit()
        else:
            print("Command not found:", command)
