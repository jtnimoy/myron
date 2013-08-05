all: JMyron.jar

libJMyron.jnilib: jniwrapper.o myron.o
	g++ -bundle -o libJMyron.jnilib myron.o jniwrapper.o ../ezcam/ezcam.o  ../ezcam/macsgCamera.o \
	-framework CoreFoundation -framework ApplicationServices -framework JavaVM -framework Carbon \
	-framework Foundation  -framework Quicktime


JMyron.jar:  JMyron/JMyron.class libJMyron.jnilib
	jar cfm JMyron.jar Manifest JMyron;


JMyron/JMyron.class: JMyron.java
	mkdir JMyron; cp JMyron.java JMyron/ ; 	javac JMyron/*.java


myron.o: myron.cpp
	g++ -c myron.cpp ../ezcam/libmyron_ezcam.so -I../ezcam

JMyron_JMyron.h: JMyron/JMyron.class
	javah JMyron.JMyron

jniwrapper.o: jniwrapper.cpp JMyron_JMyron.h
	g++ -c jniwrapper.cpp -I/System/Library/Frameworks/JavaVM.framework/Headers -I/System/Library/Frameworks/ApplicationServices.framework/Headers

clean:
	rm *.o ; rm *.jnilib ; rm *.jar ; rm -r JMyron/ ; rm JMyron_JMyron.h

