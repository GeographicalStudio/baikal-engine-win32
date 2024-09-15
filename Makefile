SRC = src/
INC = include/
build:
	x86_64-w64-mingw32-g++ -o baikal-window $(SRC)main.cpp $(SRC)window.cpp $(SRC)graphics.cpp -mwindows -I$(INC) -lwinmm -static
clean:
	rm -f baikal-window.exe