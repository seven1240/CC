BINNAME = acd_server

DEP_ROOT = ../../dep/

INC_PATH  = -Iinclude/
INC_PATH += -I../../interface/output/bgcc/include/
INC_PATH += -I../../interface/output/bgcc/include/libs/
INC_PATH += -I../../interface/output/acd/include/
INC_PATH += -I../../interface/output/ims/include/
INC_PATH += -I$(DEP_ROOT)/mysql/output/include/

LIB_PATH  = -L../../interface/output/bgcc/lib/
LIB_PATH += -L../../interface/output/acd/lib/linux/
LIB_PATH += -L../../interface/output/ims/lib/linux/
LIB_PATH += -L$(DEP_ROOT)/mysql/output/lib/

VERSION = ${shell echo $$SCMPF_MODULE_VERSION}
TAG = ${shell echo $$SCMPF_MODULE_TAG}
CXXFLAGS = -Wall -W -pipe -Wno-unused-parameter -Wreorder -Wwrite-strings -Wswitch -Wno-sign-compare\
		   -g -D__XDEBUG__ -D__YDEBUG__ \
		   -fPIC -finline-functions -Winline -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Werror \
		         -DACD_VERSION=\"$(VERSION)\" -DCVSTAG=\"$(TAG)\" -DPROJECT_NAME=\"$(BINNAME)\"\
#				 -Dprotected=public -Dprivate=public

LDFLAGS =  -lacd -lims -lbgcc -lmysqlclient_r -luuid -lpthread -lxml2 -lssl -lm -lrt 

SOURCES = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

CXX = g++ 

OUTPUT_PATH=./output/

#-----------------------------------------------------------------#
# make all
#-----------------------------------------------------------------#
all: clean outputdir

outputdir: output
	if [ ! -d $(OUTPUT_PATH) ]; then mkdir -p $(OUTPUT_PATH); fi
	if [ ! -d $(OUTPUT_PATH)/conf ]; then mkdir -p $(OUTPUT_PATH)/conf; fi
	
	cp $(BINNAME) $(OUTPUT_PATH)/	
	cp conf/* $(OUTPUT_PATH)/conf
#	cp test.cov $(OUTPUT_PATH)/test.cov

output: $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(BINNAME) $(OBJS) $(INC_PATH) $(LIB_PATH) $(LDFLAGS)
	ar -r lib$(BINNAME).a $(OBJS)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC_PATH) 
    
clean:
	rm -f $(OBJS)
	rm -f *.a
	rm -f $(BINNAME)
	rm -fr $(OUTPUT_PATH)
