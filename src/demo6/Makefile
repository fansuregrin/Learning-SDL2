ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk

LIB += -lSDL2_image
BIN_DIR = ./bin
SRC_DIR = ./

all: demo6

demo6: ${SRC_DIR}/demo6.cc
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_DIR}/demo6.cc ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo6${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo6${EXE_SUFFIX}