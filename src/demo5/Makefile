ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk

BIN_DIR = ./bin
SRC_DIR = ./

all: demo5

demo5: ${SRC_DIR}/demo5.cc
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_DIR}/demo5.cc ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo5${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo4${EXE_SUFFIX}