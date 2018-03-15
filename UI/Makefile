CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o: %.cpp %.hpp
	$(CXX) -c $(CFLAGS) $<

test-build: ui.o ui-demo.o
	$(CXX) -lncurses -o test-ui.out $^
