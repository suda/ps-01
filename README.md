# PS-01 synthesizer

Particle Photon based chiptune synthesizer.

## Code architecture

### `/synth`

Main sound synthesis code including voices, ADSR and effects.

Proposed features of the engine are:

* six independent audio oscillators with:
	* four different waveforms per audio oscillator (sawtooth, triangle, pulse, noise)
	* variable pulse width
	* multi mode filter (low-pass, high-pass and band-pass)
	* ADSR volume controls
	* ability to specify channel (left, right or both)
* six ring modulators

This is similar to having two [SID chips](https://en.wikipedia.org/wiki/MOS_Technology_SID#Features).

### `/midi`

MIDI over USB-OTG interface.

### `/sequencer`

Code for controlling sound engine and generate actual music out of sounds. Does things like chords, arpeggio, note to frequency conversion.

### `/ui`

User interface (physical buttons, leds and screen) code.

### `/lib`

Vendored 3rd party libraries.
