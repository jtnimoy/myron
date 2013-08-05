MSVS_WIN32=C:\Program Files/Microsoft Visual Studio 8
MSVS_CYGWIN=/cygdrive/c/Program\ Files/Microsoft\ Visual\ Studio\ 8

PORTVIDEO_WIN32=..\extern\PortVideoSDL-0.3\win32
PORTVIDEO_CYGWIN=../extern/PortVideoSDL-0.3/win32

WIN32_SDK_WIN32=C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2

EZCAM_INCLUDES=   /I . \
		  /I "$(PORTVIDEO_WIN32)/dslib" \
		  /I "$(PORTVIDEO_WIN32)" \
		  /I "$(WIN32_SDK_WIN32)/Include" \
		  /I "$(MSVS_WIN32)/VC/Include"



PREPENV=PATH=$PATH:$(MSVS_CYGWIN)/Common7/IDE

CL=$(PREPENV) ; $(MSVS_CYGWIN)/VC/bin/cl /nologo  $(EZCAM_INCLUDES) /D "NDEBUG" /D "_WINDLL" /FD  /EHsc /MT /c /TP 


all: ../myron_ezcam.dll


../myron_ezcam.dll : dslibCamera.obj ezcam.obj
	$(PREPENV) ; $(MSVS_CYGWIN)/VC/bin/link /NOLOGO /DLL /LIBPATH:"$(MSVS_WIN32)/VC/Lib" /LIBPATH:"$(WIN32_SDK_WIN32)/Lib" /LIBPATH:"$(PORTVIDEO_WIN32)/dslib"  /SUBSYSTEM:WINDOWS /MACHINE:X86 Uuid.lib Ole32.lib dsvl.lib dslibCamera.obj ezcam.obj /OUT:../myron_ezcam.dll /IMPLIB:myron_ezcam.lib

ezcam.obj: ../ezcam.cpp
	$(CL)  ../ezcam.cpp


dslibCamera.obj: dslibCamera.h dslibCamera.cpp
	$(CL)  dslibCamera.cpp


dslibCamera.h:
	patch $(PORTVIDEO_CYGWIN)/dslibCamera.h dslibCamera.h.patch -o dslibCamera.h


dslibCamera.cpp:
	patch $(PORTVIDEO_CYGWIN)/dslibCamera.cpp dslibCamera.cpp.patch -o dslibCamera.cpp

clean:
	rm dslibCamera.h 2> /dev/null ; \
	rm dslibCamera.cpp  2> /dev/null; \
	rm *.obj  2> /dev/null; \
	rm ../myron_ezcam.dll  2> /dev/null; \
	rm *.pdb  2> /dev/null; \
	rm *.manifest   2> /dev/null; \
	rm *.lib  2> /dev/null; \
	rm *.exp 2> /dev/null; \
	rm *.idb 2> /dev/null

