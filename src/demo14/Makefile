ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk
LIB += -lSDL2_image

BIN_DIR = ./bin
SRC_DIR = ./
SRC_FILES = ${SRC_DIR}/demo14.cc ${SRC_DIR}/texture.cc

all: demo14

demo14: ${SRC_FILES}
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_FILES} ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo14${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo14${EXE_SUFFIX}