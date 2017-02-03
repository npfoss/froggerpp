default: frogger.cpp
	g++ -std=c++11 -framework GLUT -framework OpenGL -framework Cocoa frogger.cpp
	./a.out
	rm a.out