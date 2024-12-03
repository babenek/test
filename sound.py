from pyo import Server, Sine, SuperSaw, Pattern


def main():
    with open(__file__) as f :
        lines = f.readlines()

    
    current_index = 0
    sound1 = Sine(freq=440, mul=0.3)
    sound2 = Sine(freq=660, mul=0.3)
    sound3 = Sine(freq=880, mul=0.3)

    # Create a list of sounds to loop through
    sounds = [sound1, sound2, sound3]
    # Define a function to play the current sound and advance to the next one
    def play_next_sound():
        global current_index
        # Stop the previous sound
        for sound in sounds:
            sound.stop()

        # Play the current sound
        sounds[current_index].out()

        # Move to the next sound
        current_index = (current_index + 1) % len(sounds)  # Loop back to the start

    #
    # # Create multiple sine waves at different frequencies
    # sine1 = Sine(freq=440, mul=0.2).out()
    # sine2 = Sine(freq=660, mul=0.2).out()
    # sine3 = Sine(freq=880, mul=0.2).out()
    #
    # # Create a sawtooth wave and combine it with the sine waves
    # saw = SuperSaw(freq=550, mul=0.3).out()

    loop_pattern = Pattern(play_next_sound, time=2)
    loop_pattern.play()


if __name__ == """__main__""":
    s = Server().boot()
    s.start()
    main()
