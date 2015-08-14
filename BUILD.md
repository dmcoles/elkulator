# Building and running

Elkulator requires the following libraries:

* Allegro 4.x
* OpenAL
* ALut
* Zlib
* CppUnit

Elkulator uses a CMake-based build system, so this is also a prerequisite. The
following build instructions will detail how to install these dependencies, if
required, and build Elkulator on Linux and Windows.

Elkulator has been tested on x86-32 and x86-64 machines. No other architectures
are guaranteed to work and big-endian machines (eg PowerPC) almost certainly
won't work.

## <a name="linux"></a>Linux prerequisites

These steps have been tested on Ubuntu 12.04 x64.

### Install dependencies

```bash
$ sudo apt-get install \
  liballegro4-dev \
  libopenal-dev \
  libalut-dev \
  zlib1g-dev \
  libcppunit-dev
```

[Continue to _Build with CMake_](#build)

## <a name="windows"></a>Windows prerequisites

These steps have been tested on Windows 7, Windows 8.1 and Windows 10 x64.

### Install dependencies

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
1. Open the MSYS terminal by double-clicking the "msys" shortcut
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

#### CppUnit

[Background information](http://www.freedesktop.org/wiki/Software/cppunit/) and
[here](http://people.freedesktop.org/~mmohrhard/cppunit/index.html)

Run following commands:

```bash
$ git clone git://anongit.freedesktop.org/git/libreoffice/cppunit/
$ cd cppunit/
$ ./autogen.sh
$ ./configure
$ make
$ make check
$ make install
```

Note that you may need to patch the following files so that the `NOMINMAX`
macro is not multiply defined and to avoid warnings such as "ISO C++ forbids
casting between pointer-to-function and pointer-to-object" etc.

* `cppunit/include/cppunit/plugin/DynamicLibraryManager.h`
* `cppunit/include/cppunit/plugin/TestPlugIn.h`
* `cppunit/src/cppunit/Win32DynamicLibraryManager.cpp`

### Runtime dependencies

Elkulator requires following binaries to be available on the system path:

* `OpenAL32.dll`
* `alleg44.dll`
* `libalut.dll`
* `libgcc_s_dw2-1.dll`
* `zlib1.dll`

If you have built and installed the packages as described here, then these
should already be available without any extra steps.

[Continue to _Build with CMake_](#build)

## <a name="build"></a>Build with CMake

1. Open terminal (Linux) or start MSYS environment by double-clicking "msys"
shortcut (Windows)
1. Run following commands:

```bash
$ cd elkulator/
$ script/cmake --build-type debug
$ cd build/debug/
$ make
$ make test # Optional: run unit tests
$ make install # Optional: install binaries
```

The `script/cmake` wrapper script will create build systems from the CMake build
description under the `build` directory. On Windows, this will generate MSYS
Makefiles while under Linux it will generate GNU Makefiles.

Options currently supported by `script/cmake` are:

* `--build-type` (required): build type (`debug` or `release`)
* `--install-prefix` (optional): install location

## <a name="test"></a>Run unit tests

Tests can be run using `make test` or by running the unit test executable
`elkulator-test` (Linux) or `elkulator-test.exe` (Windows) directly.

## <a name="run"></a>Run Elkulator

Running Elkulator requires a valid `elk.cfg` configuration file and ROM images
etc. in the locations referenced in `elk.cfg`. The install prefix can be set
using the `--install-prefix` option to `script/cmake`. It is convenient to point
at a directory containing a `bin` directory that is prepopulated with an
`elk.cfg` configuration file and all required ROM images in a `roms`
subdirectory.
