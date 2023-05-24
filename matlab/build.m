% copy C++ files for building
copyfile ../include/*.h include/
copyfile ../src/*.cpp src/

% build
mex -R2018a -output P2108 *.c src/*.cpp

% run validation tests
P2108Tests
