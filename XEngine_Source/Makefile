RELEASE = 0
UNICODE = 0

FLAGS = RELEASE=$(RELEASE)

MODULE_FILEPARSE_PATH = ./UPData_FileParser
MODULE_DOWNLOAD_PATH = ./UPData_Downloads
MODULE_HELP_PATH = ./UPData_HelpModule
MODULE_CONFIGURE_PATH = ./UPData_Configure

UPDATE_APP_PATH = ./XEngine_UPDater

XENGINE = libUPData_FileParser.so libUPData_Downloads.so libUPData_HelpModule.so libUPData_Configure.so        \
	   XEngine_UPDater.exe 

.PHONY:MakeAll 
MakeAll:$(XENGINE)

libUPData_Downloads.so:
	make -C $(MODULE_DOWNLOAD_PATH) $(FLAGS)
libUPData_FileParser.so:
	make -C $(MODULE_FILEPARSE_PATH) $(FLAGS)
libUPData_HelpModule.so:
	make -C $(MODULE_HELP_PATH) $(FLAGS)
libUPData_Configure.so:
	make -C $(MODULE_CONFIGURE_PATH) $(FLAGS)
		
XEngine_UPDater.exe:
	make -C $(UPDATE_APP_PATH) $(FLAGS)


SetFlags_Install:
	export FLAGS=InstallAll
InstallAll:SetFlags_Install $(NETENGINE_LIB) 
 
SetFlags_Clean:
	export FLAGS=CleanAll
CleanAll:SetFlags_Clean $(NETENGINE_LIB) 
	
	
	
