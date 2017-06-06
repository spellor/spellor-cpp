# make build folder and cd to it
mkdir build
cd build

# clean
rm -r *

# cmake and make
cmake ..
make

# run the tests
./unit_tests
