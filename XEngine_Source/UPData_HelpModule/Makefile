CC = g++ -Wall -std=c++17 -fPIC
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./ -I ../XEngine_ThirdPart/jsoncpp
FILECENTOS = /etc/redhat-release
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_SystemSdk -L ../XEngine_ThirdPart/jsoncpp -L ../UPData_FileParser
LIB = -lXEngine_BaseLib -lXEngine_SystemApi -ljsoncpp -lUPData_FileParser
LIBEX = -static-libgcc -lrt -ldl
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = HelpModule_Api.o pch.o

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
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libUPData_HelpModule.so -shared -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)


HelpModule_Api.o:./HelpModule_Api/HelpModule_Api.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./HelpModule_Api/HelpModule_Api.cpp
pch.o:pch.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) pch.cpp


InstallAll:InstallSo 
InstallSo:./libUPData_HelpModule.so
	cp ./libUPData_HelpModule.so ../../XEngine_Release/libUPData_HelpModule.so


CleanAll:CleanObj CleanMk
CleanObj:
	rm *.o                                            
CleanMk:
	rm *.so                                           
