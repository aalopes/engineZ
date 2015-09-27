AC_INIT([EngineZ], [0.0.1], [alexmiguelaraujolopes@gmail.com])
AM_INIT_AUTOMAKE([-Wall])
AC_PROG_CXX
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 data/Makefile
])

AC_CONFIG_MACRO_DIRS([m4])

dnl Check for SDL
SDL_VERSION=2.0.0
AM_PATH_SDL2($SDL_VERSION,
          :,
          AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CPPFLAGS="$CFLAGS $SDL_CFLAGS"
CPPFLAGS+=-std=c++11
LIBS="$LIBS $SDL_LIBS"
LIBS="$LIBS -lSDL2_image -lSDL2_ttf -lSDL2_mixer"

AC_OUTPUT
