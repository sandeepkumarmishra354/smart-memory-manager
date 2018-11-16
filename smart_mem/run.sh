echo "creating directory usr/include/smart_mem"
sudo mkdir /usr/include/smart_mem
echo "creating directory usr/include/smart_mem/src"
sudo mkdir /usr/include/smart_mem/src
echo "moving file 'smart_mem.h' to 'usr/include/smart_mem'"
sudo cp smart_mem.h /usr/include/smart_mem/
echo "moving file 'src/smart_mem_manager.h' to 'usr/include/smart_mem/src'"
sudo cp src/smart_mem_manager.h /usr/include/smart_mem/src/
echo "moving file 'src/smart_mem_manager.cpp' to 'usr/include/smart_mem/src'"
sudo cp src/smart_mem_manager.cpp /usr/include/smart_mem/src/
echo "moving file 'src/mem_exceptions.h' to 'usr/include/smart_mem/src'"
sudo cp src/mem_exceptions.h /usr/include/smart_mem/src/
echo "Wow !! all done..."
