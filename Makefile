SOURCES=$(HOME)/devel/sources
vpath %.cc $(SOURCES) 
vpath %.cpp $(SOURCES)
vpath %.c $(SOURCES)

CXX = g++
CXXFLAGS = -std=c++14 -I. -I $(SOURCES)/lib
LIBS = -lgsl -lgslcblas 

PROGRAM = main

OBJS = main.o spingrid.o



$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LIBS)
	
	
clean:
	rm -f $(PROGRAMS) $(OBJS)


%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< 
	
%.o: %.cc $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< 
	
%.o: %.c $(HDRS)
	gcc $(CXXFLAGS) -c $< 