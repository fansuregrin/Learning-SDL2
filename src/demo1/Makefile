ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk

BIN_DIR = ./bin
SRC_DIR = ./

all: demo1

demo1: ${SRC_DIR}/demo1.cc
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_DIR}/demo1.cc ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo1${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo1${EXE_SUFFIX}