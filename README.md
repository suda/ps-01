# PS-01 synthesizer

[![Build Status](https://travis-ci.org/suda/ps-01.svg?branch=master)](https://travis-ci.org/suda/ps-01)

Particle Photon based chiptune synthesizer.

## Code architecture

### `/src/synth`

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

### `/src/midi`

MIDI abstraction including:
* MIDI over USB-OTG interface
* MIDI over DIN5 connector
* QWERTY keyboard support

### `/src/sequencer`

Code for controlling sound engine and generate actual music out of sounds. Does things like chords, arpeggio, note to frequency conversion.

### `/src/ui`

User interface (physical buttons, leds and screen) code.

### `/lib`

Vendored 3rd party libraries.

## References

* https://ccrma.stanford.edu/software/stk/
* [VICE - C64 emulator with multiple SID implementations (reSID, FastSID)](http://vice-emu.sourceforge.net/index.html#download)
* [NES Audio - series of videos explaining some chiptune effects](https://www.youtube.com/playlist?list=PLW9dSXWX1cLKxzAsxP4dfWyhK3B1bAzJg)
* [wavepot - tool for live sound synthesis](http://wavepot.com/)
