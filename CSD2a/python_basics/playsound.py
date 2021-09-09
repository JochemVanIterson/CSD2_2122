# Example from https://simpleaudio.readthedocs.io/en/latest/

# Import simpleaudio library
import simpleaudio as sa

# Load the audio from a file, and insert into 'wav_obj'

# NOTE: Can't play 32float, so had to convert original file to 44k 24bit
wave_obj = sa.WaveObject.from_wave_file("kick.wav")
# Play the audio file
play_obj = wave_obj.play()
# Wait until it's done playing
play_obj.wait_done()
