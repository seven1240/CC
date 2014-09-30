BINNAME = ims_server

WORKROOT=../../

THIRD_PATH=$(WORKROOT)/dep/

INC_PATH  = -I.
INC_PATH += -I$(WORKROOT)/interface/output/bgcc/include/
INC_PATH += -Iinc/fs
INC_PATH += -Iinc/core
INC_PATH += -Iinc/utl
INC_PATH += -Iinc/api
INC_PATH += -I$(WORKROOT)/interface/output/ims/include/
INC_PATH += -I$(THIRD_PATH)/boost/output/include
INC_PATH += -I$(THIRD_PATH)/libxml2/output/include
INC_PATH += -I$(THIRD_PATH)/pcre/output/include
INC_PATH += -I$(THIRD_PATH)/freeswitch/output/libs/esl/include

LIB_PATH += -L$(THIRD_PATH)/boost/output/lib
LIB_PATH += -L$(THIRD_PATH)/pcre/output/lib
LIB_PATH += -L$(THIRD_PATH)/libxml2/output/lib
LIB_PATH += -L$(THIRD_PATH)/freeswitch/output/libs/esl/
LIB_PATH += -L$(WORKROOT)/interface/output/ims/lib/linux/
LIB_PATH += -L$(WORKROOT)/interface/output/bgcc/lib/

VERSION="1.2.0.4"

CXXFLAGS = -Wall -W -pipe -Wno-unused-parameter -Wreorder -Wwrite-strings -Wswitch -Wno-sign-compare\
		   -g -D__XDEBUG__ -D__YDEBUG__ \
		   -fPIC -finline-functions -Winline -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Werror \
		   -DVERSION=\"$(VERSION)\"  -DCVSTAG=\"$(VERSION)\" -DPROJECT_NAME=\"$(BINNAME)\"

LDFLAGS = -lboost_system -lboost_filesystem -lims -lbgcc -lssl -lesl -lxml2 -lpcre -lpthread  -lrt -lm -lz -ldl -luuid

SOURCES = $(wildcard *.cpp) $(wildcard src/fs/*.cpp) $(wildcard src/utl/*.cpp) $(wildcard src/core/*.cpp) $(wildcard src/api/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

CXX = g++ 

OUTPUT_PATH=./output/

#-----------------------------------------------------------------#
# make all
#-----------------------------------------------------------------#
all: outputdir

outputdir: output
	if [ ! -d $(OUTPUT_PATH) ]; then mkdir -p $(OUTPUT_PATH); fi
	if [ ! -d $(OUTPUT_PATH)/conf ]; then mkdir -p $(OUTPUT_PATH)/conf; fi
	if [ ! -d $(OUTPUT_PATH)/dtmf ]; then mkdir -p $(OUTPUT_PATH)/dtmf; fi
	if [ ! -d $(OUTPUT_PATH)/imsclient ]; then mkdir -p $(OUTPUT_PATH)/imsclient; fi
	
	cp conf/* $(OUTPUT_PATH)/conf
	cp bgcc.cfg $(OUTPUT_PATH)/
	cp dtmf/8k-alaw/* $(OUTPUT_PATH)/dtmf
	cp $(BINNAME) $(OUTPUT_PATH)/

test: output
	ar -r libims_server.a $(OBJS)

output: $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(BINNAME) $(OBJS) $(INC_PATH) $(LIB_PATH) $(LDFLAGS)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(INC_PATH) -c $<
    
clean:
	rm -f $(OBJS)
	rm -f *.a
	rm -f $(BINNAME)
	rm -fr $(OUTPUT_PATH)
