OUT_NAME = project
OUT_DIR = build
CC = gcc
main = main.c
src_deps = buffer_struct/buffer_circular.c printer/printer.c
libs = -lpthread

MKDIR_P = mkdir -p

build/project:
	${MKDIR_P} ${OUT_DIR}
	${CC} ${main} ${src_deps} $(libs) -o ${OUT_DIR}/${OUT_NAME}
