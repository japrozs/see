CXX ?= gcc
PKGCONFIG = $(shell which pkg-config)
CXXFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -Wall -g -I include
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC = src/simulator.cpp src/location.cpp  src/mobility_model.cpp  src/person.cpp  src/ppmodel.cpp  src/ui.cpp

OBJS = simulator.o location.o  mobility_model.o  person.o  ppmodel.o  ui.o

all: simulator

%.o: %.cpp
	$(CXX) -c -o $(@F) $(CXXFLAGS) $<

simulator: $(OBJS)
	$(CXX) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f simulator