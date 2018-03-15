CXX = g++
CFLAGS = -std=c++14 -g -Wall
MongoDB_IFLAG = -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0

ui.o: ui.cpp ui.hpp
	$(CXX) -c $(CFLAGS) $< $(pkg-config --cflags --libs libmongocxx) $(MongoDB_IFLAG)

