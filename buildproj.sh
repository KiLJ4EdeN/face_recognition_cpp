rm -rf build
rm -rf lib
echo "Done Cleaning."
mkdir build && cd build
cmake ..
make
echo "Finished Compliation."
