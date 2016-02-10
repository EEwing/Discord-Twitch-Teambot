LIBS=-lcurl -ltidy -ltinyxml2 -lpthread -L ../
INCLUDE=-I../tinyxml2 -L../libtidy/
SOURCES=main.cxx DiscordClient.cxx Message.cxx User.cxx Team.cxx CURLutils.cxx TwitchEndpoints.cxx
FLAGS=-std=c++11 -g

all:
	g++ ${FLAGS} ${INCLUDE} ${SOURCES} -o tacbot ${LIBS}
