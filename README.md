# Elkulator v1.0

This is a Git fork of Tom Walker's [Elkulator](http://www.retrosoftware.co.uk/hg/elkulator).

Check out the `linux` branch for the Linux version and `windows` for the
Windows version. This arrangement of sources is temporary until I figure out a
better configuration for merging changes between the different versions.

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

