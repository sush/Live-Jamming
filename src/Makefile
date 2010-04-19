# livejammin Makefile
#

EXEC		=		livejammin_server
BUILD_DIR	=		build
DEBUG		=		no
CPP		=		g++
SRC		=		server/main.cpp\
				server/Server.cpp\
				server/Packet.cpp\
				server/PacketQueue.cpp\
				server/SessionManager.cpp\
				server/Session.cpp\
				server/Config.cpp\
				server/Option.cpp\
				server/Argument.cpp
OBJ		=		$(SRC:.cpp=.o)
INCLUDE_DIR	=		-Iinclude -Iserver/include -Iclient/include
LIB_DIR		=		-Llibs
CXXFLAGS	=		-W -Wall -ansi $(INCLUDE_DIR)
LDFLAGS		=		-lboost_system -lboost_thread -lboost_program_options -lyaml-cpp
ifeq ($(DEBUG), yes)
	CXXFLAGS	+=		-g3 -pg -D_DEBUG
	LDFLAGS		+=		-pg
else
	CXXFLAGS	+=		-DNDEBUG
	LDFLAGS		+=		
endif
LDFLAGS		+=	$(LIB_DIR)	# must be at the end
RM		=		rm -f
STRIP		=		strip
CP		=		cp

all: 	$(EXEC)

$(EXEC): $(OBJ)
ifneq ($(DEBUG), yes)
	 $(CPP) -o $(EXEC) $(OBJ) $(LDFLAGS)
	strip	$(EXEC)
	$(CP) $(EXEC) $(BUILD_DIR)/$(EXEC)_release
else
	 $(CPP) -o $(EXEC) $(OBJ) $(LDFLAGS)
	$(CP) $(EXEC) $(BUILD_DIR)/$(EXEC)_debug
endif

clean:
	@$(RM) $(OBJ)

myclean: clean
	@$(RM) *~

mrproper: clean
	@$(RM) $(EXEC)

re: clean all
