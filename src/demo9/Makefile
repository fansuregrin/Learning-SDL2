ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk

LIB += -lSDL2_image
BIN_DIR = ./bin
SRC_DIR = ./

all: demo9

demo9: ${SRC_DIR}/demo9.cc
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_DIR}/demo9.cc ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo9${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo9${EXE_SUFFIX}