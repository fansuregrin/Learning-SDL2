ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk
LIB += -lSDL2_image -lSDL2_ttf

BIN_DIR = ./bin
SRC_DIR = ./
SRC_FILES = ${SRC_DIR}/demo16.cc ${SRC_DIR}/texture.cc

all: demo16

demo16: ${SRC_FILES}
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_FILES} ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo16${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo16${EXE_SUFFIX}