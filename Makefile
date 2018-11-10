#This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c or .cc file.
#
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.c is the name of the file you wish to compile 
#       
# A binary named xxxx will be produced
# Eduardo Rubio 

COMP = g++
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include
LDLIBS =  -lglut -lGL -lGLU -lX11 -lm

UNAME_S := $(shell uname -s)
ifeq ( $(UNAME_S), Linux)
	CCFLAG += -D LINUX 
endif 

ifeq ( $(UNAME_S), Darwin)
	CCFLAG += -D OSX 
endif

.cpp:
	$(COMP) $(CCFLAG) -O $@.cpp -g $(INCDIRS) $(LIBDIRS) $(LDLIBS) -o $@
                                                                                                                                                                                                             
                                                                                                                                                                                                    
