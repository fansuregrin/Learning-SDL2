SRC_ROOT = src
SUB_DIRS = demo1 demo2 demo3 demo4 demo5 demo6 demo7 demo8 demo9 demo10

all:
	for i in ${SUB_DIRS}; do \
		(cd ${SRC_ROOT}/$$i && echo "making $$i" && ${MAKE} ) || exit 1; \
	done

clean:
	for i in ${SUB_DIRS}; do \
		(cd ${SRC_ROOT}/$$i && echo "cleaning $$i" && ${MAKE} clean) || exit 1; \
	done