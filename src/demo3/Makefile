ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk

BIN_DIR = ./bin
SRC_DIR = ./

all: demo3

demo3: ${SRC_DIR}/demo3.cc
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_DIR}/demo3.cc ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo3${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo2${EXE_SUFFIX}