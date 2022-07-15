CC = g++ -std=c++17 -Wall
RELEASE = 0
UNICODE = 0  
FILECENTOS = /etc/redhat-release
LOADBIN = 0
LIB = -lXEngine_BaseLib -lHelpComponents_XLog -lNetHelp_APIHelp -lXEngine_SystemApi \
      -lUPData_FileParser -lUPData_Downloads -lUPData_HelpModule -lUPData_Configure \
	  -ljsoncpp
LIBEX = -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = UPDater_Net.o UPDater_Config.o XEngine_UPDater.o

ifeq ($(shell uname),Darwin)
	LOADBIN = -L ../UPData_Downloads -L ../UPData_FileParser -L ../UPData_HelpModule -L ../UPData_Configure \
			  -L ../XEngine_ThirdPart/jsoncpp
	LOADSO = 
else
	LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -L /usr/local/lib/XEngine_Release/XEngine_SystemSdk \
	          -L ../UPData_Downloads -L ../UPData_FileParser -L ../UPData_HelpModule -L ../UPData_Configure \
			  -L ../XEngine_ThirdPart/jsoncpp
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
	$(CC) $(DEBUG) $(LIBINCLUDE) -o XEngine_UPDateApp.exe $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)
  
UPDater_Net.o:./UPDater_Net.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./UPDater_Net.cpp
UPDater_Config.o:./UPDater_Config.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./UPDater_Config.cpp
XEngine_UPDater.o:./XEngine_UPDater.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_UPDater.cpp   

InstallAll:InstallApp
InstallApp:./XEngine_UPDateApp.exe
	cp ./XEngine_UPDateApp.exe ../../XEngine_Release/XEngine_UPDateApp.exe
	
CleanAll:CleanObj CleanMk
CleanObj:                                              
	rm *.o
CleanMk:                                  
	rm XEngine_UPDateApp.exe     
	       
