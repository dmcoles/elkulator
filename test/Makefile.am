# Makefile.am for Elkulator tests

AM_CPPFLAGS = -I../src

bin_PROGRAMS = elkulator-test
noinst_SCRIPTS = ../elkulator-test
CLEANFILES = $(noinst_SCRIPTS)

../elkulator-test: elkulator-test
	cp elkulator-test ..

amrefresh:

elkulator_test_CFLAGS = $(allegro_CFLAGS)

# workaround for Win32 Allegro, which has `allegro-config' missing
if OS_WIN
elkulator_test_LDADD = -lalleg -lz -lopenal -lalut
else
elkulator_test_LDADD = $(allegro_LIBS) -lz -lopenal -lalut
endif

elkulator_test_SOURCES = \
  ../src/path.c \
  path_test.c \
  test.c

