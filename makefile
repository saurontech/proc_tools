HDR = $(shell find ./ -name '*.h' -print)
SRC = $(shell find ./ -name '*.c' -print)

INCDIR = $(shell find ./ -type d -printf ' -I ./%P ')

all: sw_wdt

sw_wdt: ${HDR} ${SRC}
	gcc -o $@ ${SRC} ${INCDIR}

clean:
	rm -f ./sw_wdt
