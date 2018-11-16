# smart-memory-manager
An easy way to deal with c++ pointers
Now you do not have to worry about memory leakage because of pointers...
you can easily instantiate your objects with `new` keyword and asign that object with a key(key must be of std::string type) to `SmartMemoryManager` class. Now use that object and don't worry about deleting them. `SmartMemoryManager` will automatically delete the object when it goes out of scope.
