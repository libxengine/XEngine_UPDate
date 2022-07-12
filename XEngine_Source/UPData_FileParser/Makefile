CC = g++ -Wall -std=c++17 -fPIC
SHAREFLAG = -shared
SHAREDLL = so
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./ -I ../XEngine_ThirdPart/jsoncpp
FILECENTOS = /etc/redhat-release
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L ../XEngine_ThirdPart/jsoncpp
LIB = -lXEngine_BaseLib -ljsoncpp
LIBEX = -ldl 
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = FileParser_Match.o FileParser_ReadVersion.o pch.o

ifeq ($(shell uname),Darwin)
	SHAREDLL = dylib
	SHAREFLAG = -dynamiclib
	LOADSO = 
else
	SHAREDLL = so
	SHAREFLAG = -shared
endif

ifeq ($(RELEASE),1)
FLAGS = -c -O2
DEBUG =
else
FLAGS = -c
DEBUG = -g
endif

ifeq ($(UNICODE),1)
UNICODE = -D _UNICODE
else
UNICODE =
endif

ifeq ($(FILECENTOS), $(wildcard $(FILECENTOS)))
	UNICODE = -D _CENTOS
else
	UNICODE = -D _UBUNTU
endif

all:$(LIBINCLUDE)
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libUPData_FileParser.$(SHAREDLL) $(SHAREFLAG) -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)


FileParser_Match.o:./FileParser_Match/FileParser_Match.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./FileParser_Match/FileParser_Match.cpp
FileParser_ReadVersion.o:./FileParser_ReadVersion/FileParser_ReadVersion.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./FileParser_ReadVersion/FileParser_ReadVersion.cpp

pch.o:pch.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) pch.cpp

InstallAll:InstallSo 
InstallSo:./libUPData_FileParser.$(SHAREDLL)
	cp ./libUPData_FileParser.$(SHAREDLL) ../../XEngine_Release/libUPData_FileParser.$(SHAREDLL)


CleanAll:CleanObj CleanMk
CleanObj:
	rm *.o                                          
CleanMk:
	rm *.$(SHAREDLL)                           
