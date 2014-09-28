ROOT_DIR=../../

include $(ROOT_DIR)/Makefile.rule
NAME=libjson-cpp.a
VERSION=0.5.0
BIN=$(NAME).$(VERSION)

INC_PARAM := -I./include

SOURCES    = $(wildcard *.cpp)
OBJS       = $(patsubst %.cpp,%.o,$(SOURCES) )


CXXFLAGS = -Wall -W -pipe -Wno-unused-parameter -Wreorder -Wwrite-strings -Wswitch -Wno-sign-compare\
		   -g -D__XDEBUG__ -D__YDEBUG__ \
		   -fPIC -finline-functions -Winline -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Werror

$(BIN): $(OBJS)
	@echo $(OBJS)
	$(AR) $(BIN) $(OBJS)
	@cp $(BIN) $(NAME)

$(OBJS) : %.o:%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(INC_PARAM) -c $<

clean:
	rm -fr *.o *.a* 
