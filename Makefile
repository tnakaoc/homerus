all:
	make sv
	make prinfo
sv: src/simple_view.cpp
	g++ -std=c++11 -Iinclude src/simple_view.cpp -O2 -Wall -W -o bin/sv
prinfo: src/prinfo.cpp
	g++ -std=c++11 src/prinfo.cpp -Wall -O2 -W -o bin/prinfo
