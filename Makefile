EXE = pa2

OBJS_EXE = HSLAPixel.o lodepng.o PNG.o stack.o convexhull.o convexintersection.o main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm 
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all : pa2

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

#object files
HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

stack.o : point.h stack.h stack.cpp
	$(CXX) $(CXXFLAGS) stack.cpp -o $@

convexhull.o : point.h convexhull.h stack.h convexhull.cpp
	$(CXX) $(CXXFLAGS) convexhull.cpp -o $@

convexintersection.o : point.h convexintersection.h convexintersection.cpp
	$(CXX) $(CXXFLAGS) convexintersection.cpp -o $@

main.o : main.cpp cs221util/PNG.h cs221util/HSLAPixel.h convexhull.h convexintersection.h point.h drawingio.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

clean :
	-rm -f *.o $(EXE)
