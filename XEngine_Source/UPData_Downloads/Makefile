CC = g++ -Wall -std=c++17 -fPIC
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./
FILECENTOS = /etc/redhat-release
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_DownLoad -L ../UPData_FileParser
LIB = -lXEngine_BaseLib -lXEngine_Download -lUPData_FileParser
LIBEX = -static-libgcc -lrt -ldl -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = UPData_DlParser.o pch.o

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

all:$(LIBINCLUDE)
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libUPData_Downloads.so -shared -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)


UPData_DlParser.o:./UPData_DlParser/UPData_DlParser.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./UPData_DlParser/UPData_DlParser.cpp
pch.o:pch.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) pch.cpp


InstallAll:InstallSo 
InstallSo:./libUPData_Downloads.so
	cp ./libUPData_Downloads.so ../../XEngine_Release/libUPData_Downloads.so


CleanAll:CleanObj CleanMk
CleanObj:
	rm *.o                                            
CleanMk:
	rm *.so
