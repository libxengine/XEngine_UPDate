CC = g++ -Wall -std=c++17 -fPIC
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./
FILECENTOS = /etc/redhat-release
LOADBIN = -L ../../XEngine_Lib/XEngine_BaseLib -L ../../XEngine_SystemSdk/XEngine_SystemApi -L ../UPData_FileParser
LIB = -lXEngine_BaseLib -lXEngine_SystemApi -lUPData_FileParser
LIBEX = -static-libgcc -lrt -ldl
LOADSO = -Wl,-rpath=./:../XEngine_BaseLib:../XEngine_SystemSdk,--disable-new-dtags
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
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) pch.cpp


InstallAll:InstallSo InstallHeader
InstallSo:./libUPData_HelpModule.so
ifeq ($(FILECENTOS), $(wildcard $(FILECENTOS)))
	cp ./libUPData_HelpModule.so ../../../XEngine_Release/XEngine_Linux/Centos/XEngine_UPData/libUPData_HelpModule.so
else
	cp ./libUPData_HelpModule.so ../../../XEngine_Release/XEngine_Linux/Ubuntu/XEngine_UPData/libUPData_HelpModule.so
endif
InstallHeader:./HelpModule_Define.h ./HelpModule_Error.h
	cp ./HelpModule_Define.h ../../../XEngine_Release/XEngine_Include/XEngine_UPData/HelpModule_Define.h
	cp ./HelpModule_Error.h ../../../XEngine_Release/XEngine_Include/XEngine_UPData/HelpModule_Error.h


CleanAll:CleanObj CleanMk
CleanObj:
	rm *.o                                            
CleanMk:
	rm *.so                                           
