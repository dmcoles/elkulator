# Building and running

## <a name="ubuntu"></a>Ubuntu

### Install dependencies

```bash
$ sudo apt-get install liballegro4-dev libopenal-dev libalut-dev zlib1g-dev
```

### Configure and build Elkulator

```bash
$ autoreconf -vfi
$ ./configure
$ make
```

To build with tracing enabled and F1 "quick quit" behaviour, run
`./configure --enable-debug`.

### Run unit tests

```bash
$ ./elkulator-test
```

There are currently only a handful of tests.

### Run Elkulator

```bash
$ ./elkulator &
```

Running Elkulator requires a valid `elk.cfg` configuration file and ROMs etc.

## <a name="windows"></a>Windows

Tested on Windows 7 Professional

### Install prerequisites

The following assumes that your default Windows hard drive is `C:`. If this is
not the case, adjust the instructions accordingly.

#### MinGW

1. [Download](http://downloads.sourceforge.net/project/mingw/Installer/mingw-get-setup.exe)
and [install](http://www.mingw.org/wiki/Getting_Started) MinGW---these
instructions were developed with version 0.6.2-beta-20131004-1
1. Use default options
1. Right-click and select "Mark for Installation" on following packages:
  * `mingw-developer-toolkit`
  * `mingw32-base`
  * `mingw32-gcc-g++`
  * `msys-base`
1. Go to "Installation" and click "Apply Changes".
1. Click "Apply" to proceed.
1. Follow instructions at "After Installing You Should...":
  1. Create `C:\MinGW\msys\1.0\etc\fstab` with single line `C:\MinGW /mingw`
  1. Edit `C:\MinGW\msys\1.0\etc\profile` and add line `export MINGDIR=/mingw`
  1. Create an "msys" shortcut pointing to `C:\MinGW\msys\1.0\msys.bat`
1. Open the "msys" terminal by double-clicking the "msys" shortcut
1. Install wget: `mingw-get.exe install msys-wget`
1. Install unzip: `mingw-get.exe install msys-unzip`

#### CMake

1. [Download](http://www.cmake.org/files/v3.2/cmake-3.2.2-win32-x86.zip) the
latest CMake distribution
1. Unzip the archive to `C:\cmake`
1. Edit `C:\MinGW\msys\1.0\etc\profile` and add `C:\cmake\bin` to path using
`export PATH=/c/cmake/bin:$PATH`

#### Allegro

[Background information](http://alleg.sourceforge.net/stabledocs/en/build/mingw32.html)

1. [Download](http://alleg.sourceforge.net/files/dx70_mgw.zip) minimal DirectX 7
SDK for MinGW
1. Extract contents of `include` and `lib` directories from `dx70_mgw.zip` into
`C:\MinGW\include` and `C:\MinGW\lib` directories respectively, choosing to
overwrite any existing files
1. [Download](http://sourceforge.net/projects/alleg/files/allegro/4.4.1.1/allegro-4.4.1.1.zip)
the latest recent 4._x_ source archive of Allegro for MinGW
1. Unzip contents into `allegro` directory alongside `elkulator` source
directory
1. Run following commands:
```bash
$ cd allegro/
$ mkdir build
$ cd build/
$ cmake .. -G "MSYS Makefiles"
$ make
$ make install
$ ln /mingw/lib/liballeg44.dll.a  /mingw/lib/liballeg.dll.a
```

#### zlib

[Background information](https://wiki.openttd.org/Compiling_on_Windows_using_MinGW#Compiling_zlib)

Run following commands to build zlib and install it into the system default location:

```bash
$ wget http://zlib.net/zlib-1.2.8.tar.gz
$ tar xvfz zlib-1.2.8.tar.gz
$ cd zlib-1.2.8/
$ make -f win32/Makefile.gcc BINARY_PATH=$MINGDIR/bin INCLUDE_PATH=$MINGDIR/include LIBRARY_PATH=$MINGDIR/lib install
```

#### OpenAL

[Background information](http://kcat.strangesoft.net/openal.html#download) and
[here](http://ingar.satgnu.net/devenv/mingw32/local.html#openalsoft)

Run following commands:

```bash
$ wget http://kcat.strangesoft.net/openal-releases/openal-soft-1.16.0.tar.bz2
$ tar xjf openal-soft-1.16.0.tar.bz2
$ cd openal-soft-1.16.0/
$ cd build/
$ cmake .. -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=$MINGDIR
$ make
$ make install
$ ln /mingw/lib/libOpenAL32.dll.a  /mingw/lib/libopenal.dll.a
```

#### freealut

Run following commands:

```bash
$ git clone https://github.com/vancegroup/freealut
$ cd freealut/
$ mkdir build
$ cd build/
$ cmake .. -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=$MINGDIR -DOPENAL_INCLUDE_DIR=$MINGDIR/include/ -DOPENAL_LIBRARY=$MINGDIR/lib/libOpenAL32.dll.a
$ make
$ make install
```

### Build Elkulator

1. Start "msys" environment by double-clicking shortcut
1. Run following commands:

```bash
$ cd elkulator/src/
$ make -f Makefile.mingw
```

### Run unit tests

```bash
$ cd test/
$ make -f Makefile.mingw
$ ElkulatorTest.exe
```

There are currently only a handful of tests.

### Run Elkulator

Elkulator requires following binaries to be available on the system path:

* `OpenAL32.dll`
* `alleg44.dll`
* `libalut.dll`
* `libgcc_s_dw2-1.dll`
* `zlib1.dll`

If you have built and installed the packages as described here, then these
should already be available without any extra steps.

Running Elkulator requires a valid `elk.cfg` configuration file and ROMs etc.
