libs = -lpthread

all: build/project

build/project: 
	gcc main.c buffer_struct/buffer_circular.c printer/printer.c $(libs) -o build/project

.PHONY: clean
clean:
	@rm -f ./build/project