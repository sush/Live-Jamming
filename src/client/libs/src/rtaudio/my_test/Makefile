PROGRAMS = audio
RM = /bin/rm
SRC_PATH = ..
INCLUDE = ..
OBJECT_PATH = Release
vpath %.o $(OBJECT_PATH)

OBJECTS	=	RtAudio.o 

CC       = g++
DEFS     =   -DHAVE_GETTIMEOFDAY -D__LINUX_ALSA__
CFLAGS   = -O2 -Wall
CFLAGS  += -I$(INCLUDE) -I../include
LIBRARY  = -lpthread -lasound 

%.o : $(SRC_PATH)/%.cpp
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $(OBJECT_PATH)/$@

%.o : ../include/%.cpp
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $(OBJECT_PATH)/$@

all : $(PROGRAMS)

audio : audio $(OBJECTS)
	$(CC) $(CFLAGS) $(DEFS) -o audio audio.cpp $(OBJECT_PATH)/*.o $(LIBRARY)

clean : 
	$(RM) -f $(OBJECT_PATH)/*.o
	$(RM) -f $(PROGRAMS)
	$(RM) -f *.raw *~ *.exe
	$(RM) -fR *.dSYM

distclean: clean
	$(RM) Makefile

strip : 
	strip $(PROGRAMS)

re : 	clean audio