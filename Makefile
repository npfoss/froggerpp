default: frogger.cpp
	g++ -framework GLUT -framework OpenGL -framework Cocoa frogger.cpp
	./a.out
