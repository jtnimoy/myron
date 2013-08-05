all:
	make all_`uname`

all_CYGWIN_NT-5.1:
	cd ezcam;make;cd ..;\
	g++ -c  -D_WINDOWS -D__CYGWIN__ source/myron.cpp -Iezcam;\
	mkdir lib;cd lib;\
	cp ../myron.o .;cp ../ezcam/ezcam.o .;cp ../ezcam/macsgCamera.o .;\
	ar rc libmyron.a *.o;


all_Darwin:
	cd ezcam;make;cd ..;\
	g++ -c source/myron.cpp -Iezcam;\
	mkdir lib;cd lib;\
	cp ../myron.o .;cp ../ezcam/ezcam.o .;cp ../ezcam/macsgCamera.o .;\
	ar rc libmyron.a *.o;

clean:
	cd ezcam;make clean;cd ..;\
	rm myron.o;\rm -r lib

install:
	mkdir /usr/local ; \
	mkdir /usr/local/include ; \
	mkdir /usr/local/lib ; \
	cp source/myron.h /usr/local/include/;\
	cp lib/libmyron.a /usr/local/lib/ ; cd /usr/local/lib ; ranlib libmyron.a ;
	cp ezcam/myron_ezcam.dll /usr/local/lib/myron_ezcam.dll