#Get current unix timestamp
timestamp=$(date +%s)
rm -r build
mkdir build
cd build
cmake ..
cd kernel
make -j8
cp ./kernel.uf2 ../../
cd ../.. 
new_timestamp=$(date +%s)
diff=$(($new_timestamp-$timestamp))
echo "Build time: $diff seconds"