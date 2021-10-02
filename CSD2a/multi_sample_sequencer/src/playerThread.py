#!/usr/bin/python3

import threading
import time
import simpleaudio as sa

class playerThread (threading.Thread):
  def __init__(self, events):
    threading.Thread.__init__(self)
    self.resolution = 0.0001
    self.threadRunning = True
    self.shouldLoop = False
    self.playbackState = 'stop'
    self.elapsedTimestamp = 0

    self.sounds = {
        'kick': sa.WaveObject.from_wave_file("../../assets/kick.wav"),
        'hihat': sa.WaveObject.from_wave_file("../../assets/hihat.wav"),
        'snare': sa.WaveObject.from_wave_file("../../assets/snare.wav")
    }
    self.replaceEvents(events)

  def killThread(self):
    self.threadRunning = False

  def setPlaybackState(self, value):
    if self.playbackState == value:
      return
    if value == 'stop':
      self.elapsedTimestamp = 0
    elif value == 'start':
      if self.elapsedTimestamp == 0 or len(self.playableEvents) == 0:
        self.playableEvents = self.events.copy()
      self.startTimestamp = time.time_ns() - self.elapsedTimestamp
    self.playbackState = value
  
  def setLoop(self, value):
    self.shouldLoop = value

  def run(self):
    print("Starting player thread")

    while self.threadRunning:
      if self.playbackState == 'start':
        # Get elapsed timestamp is ms, i.e. how much time has passed since last loop
        self.elapsedTimestamp = time.time_ns() - self.startTimestamp

        # Look for events that should be played and walk through them
        nowEvents = list(filter(lambda x: (self.elapsedTimestamp > x['timestamp']), self.playableEvents))
        for event in nowEvents:
          self.execEvent(event)
          # Remove event as it has been executed
          self.playableEvents.remove(event)

        # If loop is empty, rebuild list and reset startTimestamp
        if len(self.playableEvents) == 0:
          if self.shouldLoop:
            self.startTimestamp = time.time_ns()
            self.playableEvents = self.events.copy()
          else:
            self.playbackState = 'stop'
            self.elapsedTimestamp = 0
        
      time.sleep(self.resolution)
  
  def replaceEvents(self, events):
    self.events = events
    self.playableEvents = events.copy()
    self.startTimestamp = time.time_ns()

  def execEvent(self, event):
    """Play an event

    Args:
        event (dict): Event to be played
    """
    # Check if velocity is higher than 0
    if event['velocity'] > 0:
      self.sounds.get(event['sound']).play()
    # else:
    #   print("\nKick Off", event['timestamp'])
