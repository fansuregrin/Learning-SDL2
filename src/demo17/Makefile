ROOT = ../..
PLATFORM = $(shell ${ROOT}/systype.sh)
include ${ROOT}/${PLATFORM}.defines.mk
LIB += -lSDL2_image -lSDL2_ttf
MACRO = -DDEBUG

BIN_DIR = ./bin
SRC_DIR = .
SRC_FILES = ${SRC_DIR}/demo17.cc ${SRC_DIR}/texture.cc \
	${SRC_DIR}/button.cc ${SRC_DIR}/app.cc

all: demo17

run:
	${CP} -r resources ${BIN_DIR} && ${BIN_DIR}/demo17${EXE_SUFFIX}

demo17: ${SRC_FILES}
	${MKDIR} ${BIN_DIR}
	${CXX} ${SRC_FILES} ${CFLAGS} ${MACRO} ${INCLUDE_PATH} ${LIB_PATH} ${LIB} \
		-o ${BIN_DIR}/demo17${EXE_SUFFIX}

clean:
	${RM} -f ${BIN_DIR}/demo17${EXE_SUFFIX}