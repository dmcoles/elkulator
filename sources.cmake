set(OBJ_SOURCE_FILES
  ${SOURCE_DIR}/1770.c
  ${SOURCE_DIR}/2xsai.c
  ${SOURCE_DIR}/2xsai.h
  ${SOURCE_DIR}/6502.c
  ${SOURCE_DIR}/adc.c
  ${SOURCE_DIR}/adf.c
  ${SOURCE_DIR}/common.h
  ${SOURCE_DIR}/config.c
  ${SOURCE_DIR}/csw.c
  ${SOURCE_DIR}/ddnoise.c
  ${SOURCE_DIR}/debugger.c
  ${SOURCE_DIR}/disc.c
  ${SOURCE_DIR}/elk.h
  ${SOURCE_DIR}/elkwin.rc
  ${SOURCE_DIR}/fdi.c
  ${SOURCE_DIR}/fdi2raw.c
  ${SOURCE_DIR}/fdi2raw.h
  ${SOURCE_DIR}/firstbyte.c
  ${SOURCE_DIR}/linux-gui.c
  ${SOURCE_DIR}/linux-keydefine.c
  ${SOURCE_DIR}/linux.c
  ${SOURCE_DIR}/main.c
  ${SOURCE_DIR}/mem.c
  ${SOURCE_DIR}/palfilt.c
  ${SOURCE_DIR}/path.c
  ${SOURCE_DIR}/path.h
  ${SOURCE_DIR}/resources.h
  ${SOURCE_DIR}/savestate.c
  ${SOURCE_DIR}/scale2x.c
  ${SOURCE_DIR}/sound.c
  ${SOURCE_DIR}/soundopenal.c
  ${SOURCE_DIR}/ssd.c
  ${SOURCE_DIR}/tapenoise.c
  ${SOURCE_DIR}/uef.c
  ${SOURCE_DIR}/ula.c
  ${SOURCE_DIR}/win-keydefine.c
  ${SOURCE_DIR}/win.c
)

if(DEFINED ELKULATOR_LINK_X11)
  set(PLATFORM_OBJ_SOURCE_FILES
    ${SOURCE_DIR}/allegro_icon.c
  )
else()
  set(PLATFORM_OBJ_SOURCE_FILES)
endif()

set(BIN_SOURCE_FILES
  ${SOURCE_DIR}/linuxmain.c
)

set(TEST_OBJ_SOURCE_FILES
  ${TEST_SOURCE_DIR}/path_test.cpp
)

set(TEST_BIN_SOURCE_FILES
  ${TEST_SOURCE_DIR}/test.cpp
)

set(PLATFORM_TEST_OBJ_SOURCE_FILES)
