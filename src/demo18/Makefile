ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk

BIN_DIR = ./bin
SRC_DIR = ./
SRC_FILES = ${SRC_DIR}/demo18.cc ${SRC_DIR}/texture.cc \
	${SRC_DIR}/app.cc
LIB += -lSDL2_image -lSDL2_ttf
MACRO = -DDEBUG

all: demo18

run:
	${CP} -r resources ${BIN_DIR} && cd ${BIN_DIR} && ./demo18${EXE_SUFFIX}

demo18: ${SRC_FILES}
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_FILES} ${CFLAGS} ${MACRO} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo18${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo18${EXE_SUFFIX}