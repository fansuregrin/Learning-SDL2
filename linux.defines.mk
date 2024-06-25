CXX = g++
CFLAGS = -g -fdiagnostics-color=always --std=c++14 -Wall
MKDIR = mkdir -p
RM = rm
CP = cp
INCLUDE_PATH = -I/usr/include
LIB_PATH = -L/usr/lib/x86_64-linux-gnu
LIB = -lSDL2main -lSDL2
EXE_SUFFIX =