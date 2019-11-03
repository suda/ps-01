# PS-01 synthesizer

[![Build Status](https://travis-ci.org/suda/ps-01.svg?branch=master)](https://travis-ci.org/suda/ps-01)

Software synthesizer that can be run on Particle 3rd gen devices (Argon, Boron or Xenon) as well as desktop. Inspired by MOS6581 and the Pocket Operator series.

## Abstract

**This is a work in progress.** You can follow the updates on:
* [Hackaday](https://hackaday.io/project/167405-ps-01)
* [Instagram stories](https://www.instagram.com/stories/highlights/18089019253003770/)
* [YouTube playlist](https://www.youtube.com/playlist?list=PLW9dSXWX1cLJcqKuNrfPg6BXtz2fbAJwX)

[See planned milestones and features](docs/ps-01.pdf).


## Running

This synth is designed to run both on embedded device but also to be compiled on a desktop (helps with debugging).

### Desktop (macOS/Linux/Windows)

```
$ cmake .
$ make
$ ./build/ps_01
```

### Particle

1. Assemble the [hardware](docs/hardware.md).
2. Open this repo in [Particle Workbench](https://www.particle.io/workbench)
3. Set `deviceOS@1.4.2` and the correct device you're using (`xenon`, `argon` or `boron`)
4. Flash the project to the device

## UI

![](docs/ui/color_v1@2x.png)
[UI documentation and guidelines](docs/ui.md)

## Code structure

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
* [SID chip datasheet](http://www.waitingforfriday.com/index.php/Commodore_SID_6581_Datasheet)