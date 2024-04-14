.PHONY: build run clean doxygen pack

build:
	mkdir -p build
	cd build && qmake ../src && make -j 10
	cp build/robots .

all: build doxygen

run: build
	./robots

clean:
	rm -rf build doc xolexa03-xsajko01.zip build-* robots

doxygen:
	doxygen Doxyfile

pack: clean
	mkdir -p doc
	zip -rX9 xolexa03-xsajko01.zip Makefile Doxyfile README.* src examples doc