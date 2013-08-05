PORTVIDEO = ./extern/PortVideoSDL-0.3

GCCFLAGS = -g0 -O3  -I$(PORTVIDEO)/common  -I$(PORTVIDEO)/macosx -arch i386 -arch ppc

all: extern/PortVideoSDL-0.3/win32/sdl.dll
	make `uname` 

extern:
	mkdir extern

extern/PortVideoSDL-0.3.src.zip: extern
	cd extern;wget -nc http://prdownloads.sourceforge.net/portvideo/PortVideoSDL-0.3.src.zip

extern/PortVideoSDL-0.3/win32/sdl.dll : extern/PortVideoSDL-0.3.src.zip
	cd extern ; unzip -n PortVideoSDL-0.3.src.zip

CYGWIN_NT-5.1: test.o myron_ezcam.dll DSVL.dll myronlite.dll
	g++ $(GCCFLAGS)  -o test -D__CYGWIN__\
	test.o myron_ezcam.dll ; \

Linux: dc1394Camera.o ezcam.o test.o  
	g++ $(GCCFLAGS)  -o test test.o ezcam.o dc1394Camera.o -ldc1394


Darwin: test.o libmyron_ezcam.so
	g++ $(GCCFLAGS)  -o test test.o libmyron_ezcam.so


libmyron_ezcam.so: vdigGrab.o macsgCamera.o ezcam.o
	g++ $(GCCFLAGS) -dynamiclib -o libmyron_ezcam.so \
		vdigGrab.o \
		macsgCamera.o \
		ezcam.o \
		-framework Foundation \
		-framework Carbon \
		-framework ApplicationServices \
		-framework Quicktime \
		-framework Cocoa \
		-framework GLUT	


myron_ezcam.dll:
	cd winwrap; make

test.o: test.cpp
	g++ $(GCCFLAGS) -c test.cpp

myronlite.o: myronlite.cpp
	g++ $(GCCFLAGS) -c myronlite.cpp


ezcam.o: ezcam.cpp
	g++ $(GCCFLAGS) -c ezcam.cpp

vdigGrab.o:
	gcc $(GCCFLAGS) -c $(PORTVIDEO)/macosx/vdigGrab.c


macsgCamera.o: macsgCamera.cpp macsgCamera.h
	g++ $(GCCFLAGS) -c macsgCamera.cpp


macsgCamera.cpp:
	patch $(PORTVIDEO)/macosx/macsgCamera.cpp macsgCamera.cpp.patch -o macsgCamera.cpp

macsgCamera.h: vdigGrab.h
	patch $(PORTVIDEO)/macosx/macsgCamera.h macsgCamera.h.patch -o macsgCamera.h


vdigGrab.h:
	patch $(PORTVIDEO)/macosx/vdigGrab.h vdigGrab.h.patch -o vdigGrab.h

dc1394Camera.o: dc1394Camera.h dc1394Camera.cpp
	g++ $(GCCFLAGS) -c dc1394Camera.cpp

DSVL.dll:
	cp $(PORTVIDEO)/win32/DSVL.dll .


myronlite.dll: myronlite.o
	g++ $(GCCFLAGS) -shared -o myronlite.dll myronlite.o myron_ezcam.dll ; \



run:
	./test

clean:
	rm test  2> /dev/null; \
	rm test.exe  2> /dev/null; \
	rm *.o  2> /dev/null; \
	rm *.so  2> /dev/null; \
	rm *~  2> /dev/null; \
	rm vdigGrab.h  2> /dev/null; \
	rm macsgCamera.cpp  2> /dev/null; \
	rm macsgCamera.h  2> /dev/null; \
	rm v4linuxCamera.cpp  2> /dev/null; \
	rm v4linuxCamera.h  2> /dev/null; \
	rm linuxfwCamera.cpp  2> /dev/null; \
	rm linuxfwCamera.h  2> /dev/null; \
	rm ccvt.h  2> /dev/null; \
	rm -r extern ;\
	cd winwrap ; \
	make clean ; \
	cd .. ;

