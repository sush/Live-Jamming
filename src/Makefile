# livejammin Makefile
#

EXEC_SERVER	=		livejammin_server
EXEC_CLIENT	=		livejammin_client
BUILD_DIR	=		build
DEBUG		=		yes
CPP		=		g++
SERVER_SRC	=		server/main.cpp\
				server/logger_modules/Syslog.cpp\
				server/Server.cpp\
				server/Packet.cpp\
				server/PacketQueue.cpp\
				server/SessionManager.cpp\
				server/Session.cpp\
				server/Config.cpp\
				server/Option.cpp\
				server/Argument.cpp

CLIENT_SRC	=		client/main_net.cpp\
				client/Client.cpp\
				client/ClientSession.cpp\
				server/Packet.cpp\
				server/PacketQueue.cpp
OBJ_SERVER	=		$(SERVER_SRC:.cpp=.o)
OBJ_CLIENT	=		$(CLIENT_SRC:.cpp=.o)
SRC		=		$(SERVER_SRC) $(CLIENT_SRC)
OBJ		=		$(SRC:.cpp=.o)
INCLUDE_DIR	=		-Iinclude -Iserver/include -Iclient/include -Iserver/logger_modules -Iserver/logger_modules/include
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
LDFLAGS		+=		$(LIB_DIR)	# must be at the end
RM		=		rm -f
STRIP		=		strip
CP		=		cp

all: server client

server: $(OBJ_SERVER)
ifneq ($(DEBUG), yes)
	 $(CPP) -o $(EXEC_SERVER) $(OBJ_SERVER) $(LDFLAGS)
	strip	$(EXEC_SERVER)
	$(CP) $(EXEC_SERVER) $(BUILD_DIR)/$(EXEC_SERVER)_release
else
	 $(CPP) -o $(EXEC_SERVER) $(OBJ_SERVER) $(LDFLAGS)
	$(CP) $(EXEC_SERVER) $(BUILD_DIR)/$(EXEC_SERVER)_debug
endif

client: $(OBJ_CLIENT)
ifneq ($(DEBUG), yes)
	 $(CPP) -o $(EXEC_CLIENT) $(OBJ_CLIENT) $(LDFLAGS)
	strip	$(EXEC_CLIENT)
	$(CP) $(EXEC_CLIENT) $(BUILD_DIR)/$(EXEC_CLIENT)_release
else
	 $(CPP) -o $(EXEC_CLIENT) $(OBJ_CLIENT) $(LDFLAGS)
	$(CP) $(EXEC_CLIENT) $(BUILD_DIR)/$(EXEC_CLIENT)_debug
endif


clean:
	@$(RM) $(OBJ)

myclean: clean
	@$(RM) *~

mrproper: clean
	@$(RM) $(EXEC)

re: clean all
