BINNAME = ivrserver 

DEP_ROOT = ../../dep/

INC_PATH  = -Iinclude/
INC_PATH += -Iinclude/fs
INC_PATH += -Iinclude/cppconn
INC_PATH += -Iinclude/cppconn/nativeapi
INC_PATH += -I../../interface/output/bgcc/include/
INC_PATH += -I../../interface/output/bgcc/include/libs/
INC_PATH += -I../../interface/output/ims/include/
INC_PATH += -I../../interface/output/ivr/include
INC_PATH += -I$(DEP_ROOT)/mysql/output/include
INC_PATH += -I$(DEP_ROOT)/libcurl/output/include
INC_PATH += -I$(DEP_ROOT)/freeswitch/output/libs/esl/include
INC_PATH += -I$(DEP_ROOT)/json-c/output/include
INC_PATH += -I$(DEP_ROOT)/boost/output/include

LIB_PATH = -Llib
LIB_PATH += -L../../interface/output/ims/lib/linux/
LIB_PATH += -L../../interface/output/ivr/lib/linux/
LIB_PATH += -L../../interface/output/bgcc/lib/
LIB_PATH += -L$(DEP_ROOT)/mysql/output/lib
LIB_PATH += -L$(DEP_ROOT)/boost/output/lib
LIB_PATH += -L$(DEP_ROOT)/libcurl/output/lib
LIB_PATH += -L$(DEP_ROOT)/freeswitch/output/libs/esl/
LIB_PATH += -L$(DEP_ROOT)/json-c/output/lib

CXX = g++
OUTPUT_PATH = ./output

VERSION=${shell echo $$SCMPF_MODULE_VERSION}

LDFLAGS = -lesl -lpthread -luuid  -lmysqlclient -lmysqlclient_r -lmystrings -lmysys -lcrypto -lidn -lssl -lldap -lcurl -lrt -lz -ljson -lims -livr -lbgcc  -lboost_system 
CXX_FLAGS = -DSCMPF_MODULE_VERSION=\"$(VERSION)\" -Wall -pipe -Wno-unused-parameter -Wno-reorder -Wwrite-strings -Wswitch -Wconversion -g \
                   -fPIC -Winline -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith \
				   -fthreadsafe-statics \
				   -Werror

OBJ_DIR = ./obj
SRC_DIR = ./src

SOURCES  = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard src/fs/*.cpp) 
SOURCES += $(wildcard src/cppconn/*.cpp) 
SOURCES += $(wildcard src/ims/*.cpp)
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: objdir outputdir

objdir:
	if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	if [ ! -d $(OBJ_DIR)/src ]; then mkdir -p $(OBJ_DIR)/src; fi
	if [ ! -d $(OBJ_DIR)/src/ims ]; then mkdir -p $(OBJ_DIR)/src/ims; fi
	if [ ! -d $(OBJ_DIR)/src/fs ]; then mkdir -p $(OBJ_DIR)/src/fs; fi
	if [ ! -d $(OBJ_DIR)/src/cppconn ]; then mkdir -p $(OBJ_DIR)/src/cppconn; fi

outputdir:  output
	
	if [ ! -d $(OUTPUT_PATH) ]; then mkdir -p $(OUTPUT_PATH); fi
	if [ ! -d $(OUTPUT_PATH)/conf ]; then mkdir -p $(OUTPUT_PATH)/conf; fi
	if [ ! -d $(OUTPUT_PATH)/flow ]; then mkdir -p $(OUTPUT_PATH)/flow; fi
		
	cp conf/bgcc.cfg $(OUTPUT_PATH)/conf
	cp conf/*.conf $(OUTPUT_PATH)/conf
	cp flow/*.flow $(OUTPUT_PATH)/flow
	cp $(BINNAME) $(OUTPUT_PATH)/

output: $(OBJS)
	ar -r libivrserver.a $(OBJS) 
	$(CXX) $(CXX_FLAGS) -o $(BINNAME) $(OBJS_BIDL) $(OBJS) $(INC_PATH) $(LIB_PATH) $(LDFLAGS)
 
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(INC_PATH) 

clean:
	rm -rf output obj  
	rm -f libivrserver.a ivrserver
