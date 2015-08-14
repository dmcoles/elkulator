# Elkulator v1.1

[![Build status](https://travis-ci.org/rcook/elkulator.svg)](https://travis-ci.org/rcook/elkulator)

This is a Git fork of Tom Walker's [Elkulator](http://www.retrosoftware.co.uk/hg/elkulator)
[Acorn Electron](http://en.wikipedia.org/wiki/Acorn_Electron) emulator for
Windows and Linux.

Check out the [wiki](https://github.com/rcook/elkulator/wiki) where I have
documented a few issues I have run into here and there.

## Changes since last major version

* Improved stability
* CSS Sound Expansion emulation
* Plus 1 and First Byte joystick emulation
* Sound pitch fixed
* FDI disc support
* Save states added
* Debugger added
* Redefinable keyboard
* Bug fix to Master RAM Board emulation
* Few other fixes
* Linux port

## Features

* Emulates basic 32k Electron
* Emulation of all modes including line-by-line effects
* Turbo board and Master RAM Board emulation
* Tape emulation
* Plus 3 emulation
* ROM cartridges
* Emulates sound including sample playback
* CSS Sound Expansion emulation
* Super 2xSaI, SuperEagle, Scale2X and PAL filters

## Status

* 6502: Enough to run all games AFAIK; cycle-accurate
* ULA: Cycle-accurate graphics emulation
* Sound: Plays back samples correctly
* Tape: Works with UEF, HQ-UEF and CSW files; loading is (optionally)
accelerated; read-only
* Plus 1: ADC only (joysticks)
* Plus 3: Two drives, ADFS plus DFS, read/write; FDI support (though no images
exist yet)
* CSS: Using SN emulator from B-em

## Menu

The menu options are:

* _File_
  * _Reset_: hard-resets the Electron
  * _Load state_: loads machine state
  * _Save state_: saves machine state
  * _Exit_: exits to operating system
* _Tape_
  * _Load tape..._: loads a new UEF tape image file
  * _Rewind tape_: rewinds tape to beginning
  * _Speed_: select tape speed from _Normal_, _Fast_ and _Really Fast_ (_Really
Fast_ can break compatibility)
* _Disc_
  * _Load disc :0/2..._: loads a disc image into drives 0 and 2
  * _Load disc :1/3..._: loads a disc image into drives 1 and 3
  * _Eject drive :0/2_: removes disc image from drives 0 and 2
  * _Eject drive :1/3_: removes disc image from drives 1 and 3
  * _New disc :0/2_: creates a new DFS/ADFS disc and loads it into drives 0 and
2
  * _New disc :1/3_: creates a new DFS/ADFS disc and loads it into drives 1 and
3
  * _Write protect disc :0/2_: toggles write protection on drives 0 and 2
  * _Write protect disc :1/3_: toggles write protection on drives 1 and 3
  * _Default write protect_: determines whether loaded discs are write-protected
by default
* _ROM_
  * _Load ROM Cartridge 1..._: loads the first ROM cartridge
  * _Load ROM cartridge 2..._: loads the second ROM cartridge (some stuff (e.g.
Starship Command) comes on two ROMs and both must be loaded in order to work
(these would both be in the same cartridge but have been imaged separately))
  * _Unload ROM Cartridges..._: unloads both ROM cartridges
* _Hardware_
  * _Video_
    * _Display type_: selects display output mode from _Scanlines_,
_Line doubling_, _2xSaI_, _Scale2X_, _SuperEagle_ and _PAL filter_
    * _Fullscreen_: enables full-screen mode; press Alt+Enter to leave
    * _Resizeable window_: lets you resize the window at will; forces line
doubling
  * _Disc_
    * _Plus 3 enable_: toggles Plus 3 emulation
    * _ADFS enable_: toggles the presence of the ADFS ROM
    * _DFS enable_: toggles the presence of the DFS ROM
  * _Memory_
    * _Elektuur/Slogger turbo board_: emulates a turbo board (see below)
    * _Slogger/Jafa Master RAM board_: emulates a master RAM board (see below)
    * _Master RAM board mode_: selects the mode of operation for the master RAM
board (see below) from _Off_, _Turbo_ and _Shadow_
  * _Sound_
    * _Internal sound output_: enables output of the internal Electron speaker
    * _CSS Sound Expansion_: emulates a CSS Sound Expansion cartridge
    * _Disc drive noise_: enables authentic disc drive sounds
    * _Tape noise_: enables less authentic tape sounds
    * _Disc drive type_: selects from _5.25_ and _3.5_ to emulate 5.25&Prime;
and 3.5&Prime; disc drive sounds respectively
    * _Disc drive volume_: selects volume of disc drive sounds from _33%_, _66%_
and _100%_
  * _Joystick_
    * _Plus 1 interface_: enables Plus 1 emulation; disables First Byte
    * _First Byte interface_: enables First Byte emulation; disables Plus 1 and
Plus 3 (due to conflicts)
  * _Keyboard_
    * _Redefine keyboard_: lets you redefine the keyboard
    * _Restore default layout_: restores default keyboard layout
* _Misc_
  * _Save screenshot_: saves a screenshot in .BMP format
  * _Debugger_: enters the debugger
  * _Break_: breaks into debugger (when debugger enabled)

## Turbo boards

Elkulator can emulate an Elektuur/Slogger turbo board. This board replaces the
lower 8k of RAM in the system with the faster RAM on the board. This has the
effect of speeding up most of the system, as most OS workspace is in this lower
8k, along with the stack. However, it can have some slight compatibility
problems---the Electron ULA can't display anything from this area, and some
timing sensitive games (e.g. Firetrack) will mess up.

Elkulator can also emulate a Slogger/Jafa Master RAM board. This is a far more
ambitious affair, attempting to replace all the Electron memory. It has three
modes:

* _Off_: disabled; same as a normal Electron
* _Turbo_: same as the above Turbo board---only replaces 8k
* _Shadow_: as above, but also shadows the screen memory: the screen is left in
normal memory, and BASIC works with the "shadow memory" on the board; the
computer boasts this as "64k mode"; you can use up to 28k in BASIC in all modes,
and it runs noticeably faster as well; mode is incompatible with almost all
games, though

## Linux-specific information

* The menu is not available all the time: press F11 to open it and F11 to close
it again
* The debugger is only available via the command line
* Hardware line doubling mode is not available on Linux
* Full-screen mode doesn't appear to work correctly, at least on my machine:
Elkulator takes over the screen, but the resolution never changes
* Video performance is noticeably slower than on Windows: this is largely due
to the lack of hardware acceleration support in Elkulator

## FAQ

Q: How do I run a game?

A: Load the UEF file through the tape menu. Then, at the `>` prompt, type
`CHAIN""` (for most games; a few will need `*RUN`).

Q: Why is the 2xSaI filter so slow?

A: The code itself isn't terribly fast to start with, but due to my laziness,
the screen rendering code is still in 8-bit, so Elkulator has to perform an
8-bit to 16-bit conversion every frame.

Q: Why is the PAL filter even slower?
A: The PAL filter is actually doing a lot of work---processing three 16MHz data
streams. It's made worse by my inability to optimise it properly.

## Thanks

Dave Moore for the web site and for testing

Peter Edwards for testing and for feature suggestions

Gary Forrest for hosting

Bob Austin, Astec, Harry Barman, Paul Bond, Allen Boothroyd, Ben Bridgewater,
Cambridge, John Cox, Chris Curry, 6502 designers, Jeremy Dion, Tim Dobson, Joe
Dunn, Ferranti, Steve Furber, David Gale, Andrew Gordon, Martyn Gilbert,
Lawrence Hardwick, Hermann Hauser, John Herbert, Hitachi, Andy Hopper, Paul
Jephcot, Brian Jones, Chris Jordan, Computer Laboratory, Tony Mann, Peter
Miller, Trevor Morris, Steve Parsons, Robin Pain, Glyn Phillips, Brian
Robertson, Peter Robinson, David Seal, Kim Spence-Jones, Graham Tebby, Jon
Thackray, Topexpress, Chris Turner, Hugo Tyson, John Umney, Alex van Someren,
Geoff Vincent, Adrian Warner, Robin Williamson and Sophie Wilson for
contributing to the  development of the Acorn Electron (among others too
numerous to mention)

## Other stuff

Also check out Tom's other emulators:

* [B-em](http://b-em.bbcmicro.com/): BBC/Master emulator
* [Arculator](http://b-em.bbcmicro.com/arculator/): Archimedes emulator
* [RPCemu](http://www.riscos.info/RPCEmu): RiscPC/A7000 emulator

## Building

* See build instructions for [Linux](BUILD.md#linux) and [Windows](BUILD.md#windows)

## Links

* [Home page](http://elkulator.acornelectron.co.uk/)
* [Tom Walker's home page](http://www.tommowalker.co.uk/) and [e-mail](mailto:b-em@bbcmicro.com)

## Licence

Elkulator is licensed under GPL 2.0, see [LICENSE.md](LICENSE.md) for more
details
