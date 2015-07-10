g++ -Wall -std=c++11 -o PointlessMake src/main.cpp src/Executable.cpp src/OutputType.cpp src/parser.cpp src/PointlessMake.cpp src/SharedObject.cpp src/StaticLibrary.cpp src/File.cpp

cp PointlessMake /usr/bin/
rm PointlessMake
