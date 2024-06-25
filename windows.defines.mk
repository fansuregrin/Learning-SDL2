CXX = g++
CFLAGS = -g -fdiagnostics-color=always --std=c++14 -Wall
MSYS_ROOT = C:\\msys64
MKDIR = ${MSYS_ROOT}\\usr\\bin\\mkdir -p
RM = ${MSYS_ROOT}\\usr\\bin\\rm
CP = ${MSYS_ROOT}\\usr\\bin\\cp
INCLUDE_PATH = -I${MSYS_ROOT}\\mingw64\\include
LIB_PATH = -L${MSYS_ROOT}\\mingw64\\lib
LIB = -lmingw32 -lSDL2main -lSDL2
EXE_SUFFIX = .exe