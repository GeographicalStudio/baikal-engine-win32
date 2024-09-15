SRC=src/
INC=include/
build:
	x86_64-w64-mingw32-g++ -o baikal-window $(SRC)main.cpp $(SRC)window.cpp -mwindows -I $(INC) -lstdc++ -lwinmm
clean:
	rm -rf baikal-window.exe