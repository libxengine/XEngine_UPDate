CC = g++ -Wall -std=c++17 -fPIC
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./
FILECENTOS = /etc/redhat-release
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib
LIB = -lXEngine_BaseLib -ljsoncpp
LIBEX = -static-libgcc -lrt -ldl 
LOADSO = -Wl,-rpath=
LIBINCLUDE = FileParser_Match.o FileParser_ReadVersion.o pch.o

ifeq ($(RELEASE),1)
FLAGS = -c -O2
DEBUG =
else
FLAGS = -c -lc_p
DEBUG = -g -pg
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
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libUPData_FileParser.so -shared -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)


FileParser_Match.o:./FileParser_Match/FileParser_Match.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./FileParser_Match/FileParser_Match.cpp
FileParser_ReadVersion.o:./FileParser_ReadVersion/FileParser_ReadVersion.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./FileParser_ReadVersion/FileParser_ReadVersion.cpp

pch.o:pch.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) pch.cpp

InstallAll:InstallSo InstallHeader
InstallSo:./libUPData_FileParser.so
ifeq ($(FILECENTOS), $(wildcard $(FILECENTOS)))
	cp ./libUPData_FileParser.so ../../../XEngine_Release/XEngine_Linux/Centos/XEngine_UPData/libUPData_FileParser.so
else
	cp ./libUPData_FileParser.so ../../../XEngine_Release/XEngine_Linux/Ubuntu/XEngine_UPData/libUPData_FileParser.so
endif
InstallHeader:./FileParser_Define.h ./FileParser_Error.h
	cp ./FileParser_Define.h ../../../XEngine_Release/XEngine_Include/XEngine_UPData/FileParser_Define.h
	cp ./FileParser_Error.h ../../../XEngine_Release/XEngine_Include/XEngine_UPData/FileParser_Error.h


CleanAll:CleanObj CleanMk
CleanObj:
	rm *.o                                          
CleanMk:
	rm *.so                           
