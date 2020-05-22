output: main.o jsoncpp.o
	g++ main.o jsoncpp.o -o output
main.o: main.cpp
	g++ -c main.cpp
jsoncpp.o: Json/jsoncpp-master/dist/jsoncpp.cpp
	g++ -c Json/jsoncpp-master/dist/jsoncpp.cpp
clean:
	rm *.o output