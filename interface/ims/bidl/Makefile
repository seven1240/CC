ROOT_DIR=../../

include $(ROOT_DIR)/Makefile.rule
NAME=libims.a
VERSION=1.0.0
BIN=$(NAME).$(VERSION)

BIDL2SL   := $(ROOT_DIR)$(BIDL2SL)
INC_PATH  := $(ROOT_DIR)$(INC_PATH)

INC_PARAM  = -I.
INC_PARAM += -I$(INC_PATH)

BIDL_FILES = $(notdir $(wildcard *.bidl))
SOURCES    = $(patsubst %.bidl,%.cpp,$(BIDL_FILES) )
OBJS       = $(patsubst %.cpp,%.o,$(SOURCES) )


CXXFLAGS = -Wall -W -pipe -Wno-unused-parameter -Wreorder -Wwrite-strings -Wswitch -Wno-sign-compare\
		   -g -D__XDEBUG__ -D__YDEBUG__ \
		   -fPIC -finline-functions -Winline -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Werror

$(BIN): $(SOURCES) $(OBJS)
	$(AR) $(BIN) $(OBJS)
	@cp $(BIN) $(NAME)

$(SOURCES) : %.cpp:%.bidl
	$(BIDL2SL) -g cpp  $<
	mv output-cpp/* ./

$(OBJS) : %.o:%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(INC_PARAM) -c $<

clean:
	rm -fr *.h *.cpp *.o *.a* output-cpp
