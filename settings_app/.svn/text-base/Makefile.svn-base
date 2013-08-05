all: settings_app.o myron.o ../ezcam/ezcam.o ../ezcam/macsgCamera.o
	g++ settings_app.o myron.o -o settings_app -framework GLUT -framework Foundation -framework ApplicationServices -framework Carbon -framework CoreServices -framework Quicktime  ../ezcam/ezcam.o ../ezcam/macsgCamera.o


settings_app.o: settings_app.cpp
	g++ -c settings_app.cpp


myron.o: ../source/myron.cpp
	g++ -c ../source/myron.cpp  -I../ezcam

clean:
	rm settings_app ; rm *.o

