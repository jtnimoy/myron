PRODUCT = mac_jni_proj
USER    = $(shell whoami)

#
# These variables are used for building separate to the source code,
# which makes building read-only examples possible
#
OBJROOT = /Builds/$(USER)/$(PRODUCT)/$(PRODUCT).obj
SYMROOT = /Builds/$(USER)/$(PRODUCT)/$(PRODUCT).sym
DSTROOT = /Builds/$(USER)/$(PRODUCT)/$(PRODUCT).dst
SRCROOT = .

#
# Set the DYLIBLOCATION variable to wherever you want the dylibs
# WARNING: dylib locations are written at build time and your program
# will not run without the dylib in the correct location
#
DYLIBLOCATION = $(SYMROOT)
JARFILE = $(SYMROOT)/mac_jni_proj.jar
JNILIB  = $(SYMROOT)/libmac_jni_proj.jnilib
DYLIB   = $(SYMROOT)/libmac_jni_proj.dylib

all: directories $(JARFILE) $(JNILIB) $(DYLIB)
	@echo Finished building.

install: $(DSTROOT) all
	mkdir -p $(DSTROOT)/Library/Java/Extensions $(DSTROOT)/$(DYLIBLOCATION)
	cp $(JARFILE) $(DSTROOT)/Library/Java/Extensions
	cp $(JNILIB) $(DSTROOT)/Library/Java/Extensions
	cp $(DYLIB) $(DSTROOT)/$(DYLIBLOCATION)

clean:
	/bin/rm -rf $(SYMROOT) $(OBJROOT)

directories: $(OBJROOT) $(SYMROOT)


C_FLAGS      = -g -I$(OBJROOT) -I/System/Library/Frameworks/JavaVM.framework/Headers
DYLIB_FLAGS  = 
BUNDLE_FLAGS = -lmac_jni_proj -L$(SYMROOT)


$(OBJROOT) $(SYMROOT) $(DSTROOT):
	mkdir -p $@

$(JARFILE): $(OBJROOT)/JNIWrapper.class
	cd $(OBJROOT); \
	echo "Main-Class: JNIWrapper" > $(OBJROOT)/manifest; \
	jar cmf $(OBJROOT)/manifest $@ *.class

$(JNILIB): $(OBJROOT)/mac_jni_projjnilib.o $(DYLIB)
	cc -bundle $(BUNDLE_FLAGS) -o $@ $<

$(OBJROOT)/mac_jni_projjnilib.o : mac_jni_projjnilib.c $(OBJROOT)/JNIWrapper.h
	cc $(C_FLAGS) -c -o $@ $<

$(OBJROOT)/JNIWrapper.h: $(OBJROOT)/JNIWrapper.class
	javah -classpath $(OBJROOT) -d $(OBJROOT) JNIWrapper

$(OBJROOT)/JNIWrapper.class: JNIWrapper.java
	javac -classpath $(OBJROOT) -d $(OBJROOT) $<

$(DYLIB): $(OBJROOT)/mac_jni_projdylib.o 
	cc -dynamiclib $(DYLIB_FLAGS) -install_name $(DYLIBLOCATION)/libmac_jni_proj.dylib -o $@ $<

$(OBJROOT)/mac_jni_projdylib.o: mac_jni_projdylib.c mac_jni_projdylib.h
	cc $(C_FLAGS) -c -o $@ $<

test: $(JARFILE)
	java -classpath $(JARFILE) -Djava.library.path=$(DYLIBLOCATION) JNIWrapper
