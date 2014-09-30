BINNAME = apserver

INC_PATH  = -I.
INC_PATH += -Iinclude
INC_PATH += -I../../interface/output/bgcc/include/
INC_PATH += -I../../interface/output/acd/include
INC_PATH += -I../../interface/output/ap/include
INC_PATH += -Iinclude/apserver
INC_PATH += -Iinclude/apclient
INC_PATH += -Iinclude/core

LIB_PATH += -L../../interface/output/bgcc/lib/
LIB_PATH += -L../../interface/output/acd/lib/linux
LIB_PATH += -L../../interface/output/ap/lib/linux

VERSION=${shell echo $$SCMPF_MODULE_VERSION}

CXXFLAGS = -Wall -W -pipe -Wno-unused-parameter -Wreorder -Wwrite-strings -Wswitch -Wno-sign-compare\
		   -g -D__XDEBUG__ -D__YDEBUG__ \
		   -fPIC -finline-functions -Winline -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith \
		         -DSCMPF_MODULE_VERSION=\"$(VERSION)\"  -DPROJECT_NAME=\"$(BINNAME)\"

LDFLAGS = -lacd -lap -lpthread -lbgcc -lssl -lm -lrt

SOURCES = $(wildcard src/core/*.cpp) $(wildcard src/apserver/*.cpp) $(wildcard src/apclient/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

CXX = g++ 

OUTPUT_PATH=./output/
LOG_PATH=./log/
OUTPUT_LIBRARY_DIR = ./
LIBRARY_NAME = libapserver
STATIC_LIBRARY_NAME = $(LIBRARY_NAME).a
SO_VERSION = 1.0
#-----------------------------------------------------------------#
# make all
#-----------------------------------------------------------------#
all: outputdir 

outputdir: output
	if [ ! -d $(OUTPUT_PATH) ]; then mkdir -p $(OUTPUT_PATH); fi
	if [ ! -d $(OUTPUT_PATH)/conf ]; then mkdir -p $(OUTPUT_PATH)/conf; fi
	if [ ! -d $(OUTPUT_PATH)/include ]; then mkdir -p $(OUTPUT_PATH)/include; fi
	if [ ! -d $(OUTPUT_PATH)/log ]; then mkdir -p $(OUTPUT_PATH)/log; fi
	if [ ! -d $(OUTPUT_PATH)/lib ]; then mkdir -p $(OUTPUT_PATH)/lib; fi

	cp conf/* $(OUTPUT_PATH)/conf
	cp $(BINNAME) $(OUTPUT_PATH)/
	cp $(STATIC_LIBRARY_NAME) $(OUTPUT_PATH)/lib  
	cp $(STATIC_LIBRARY_NAME).$(SO_VERSION) $(OUTPUT_PATH)/lib  
	cp include/core/*.h $(OUTPUT_PATH)/include/
	cp include/apserver/*.h $(OUTPUT_PATH)/include/
	cp include/apclient/*.h $(OUTPUT_PATH)/include/
	

output: $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(BINNAME) $(OBJS) $(INC_PATH) $(LIB_PATH) $(LDFLAGS)
	ar cr $(OUTPUT_LIBRARY_DIR)/$(STATIC_LIBRARY_NAME).$(SO_VERSION) $^
	ln -s $(STATIC_LIBRARY_NAME).$(SO_VERSION) $(OUTPUT_LIBRARY_DIR)/$(STATIC_LIBRARY_NAME)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC_PATH) 
clean:apclean getagentclean reloadclean acdServerclean

apclean:
	rm -f $(OBJS)
	rm -f $(STATIC_LIBRARY_NAME)*
	rm -f bgcc*.log autorun.log 
	rm -fr bidl/output-cpp
	rm -f $(BINNAME)
	rm -fr $(OUTPUT_PATH)
	rm -fr $(LOG_PATH)

getagentclean:
	@$(MAKE) clean -C sample/GetAgents

reloadclean:
	@$(MAKE) clean -C sample/Reload

acdServerclean:
	@$(MAKE) clean -C sample/acdServer
