# Elkulator v1.0

This is a Git fork of Tom Walker's [Elkulator](http://www.retrosoftware.co.uk/hg/elkulator).

This version has only been tested on Linux, though it should be straightforward
to fix it up so it builds on Windows under MinGW. I have introduced one or two
Linuxisms which I intend to address once I have a working Windows build
environment and sufficient motivation.

## Building and running

### Ubuntu

#### Install dependencies

```bash
$ sudo apt-get install liballegro4-dev libopenal-dev libalut-dev zlib1g-dev
```

#### Configure and build

```bash
$ autoreconf -vfi
$ ./configure
$ make
```

#### Running

```bash
$ ./elkulator &
```

# Links

* [Home page](http://elkulator.acornelectron.co.uk/)
* [Tom Walker's home page](http://www.tommowalker.co.uk/)

# Licence

GPL 2.0: see LICENSE.md for more information

