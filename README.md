# smart-memory-manager
An easy way to deal with c++ pointers
Now you do not have to worry about memory leakage because of pointers...
you can easily instantiate your objects with `new` keyword and asign that object with a key(key must be of std::string type) to `SmartMemoryManager` class. Now use that object and don't worry about deleting them. `SmartMemoryManager` will automatically delete the object for you when it goes out of scope.
# Example
```
#include <smart_mem/smart_mem.h>
#include <iostream>
#include <string>
using namespace std;

class Demo {
  string name = "default";
  public:
    Demo() { cout<<"constructor\n"; }
    ~Demo() { cout<<"destructor\n"; }
    Demo(string n) {name = n;}
    string get() { return name; }
    void set(string n) { name = n; }
};

int main() {
  SmartMemoryManager<Demo*> sm;
  Demo *d1 = new Demo("demo name 1");
  Demo *d2 = new Demo("demo name 2");
  sm.append("demo1",d1);
  sm.append("demo2",d2);
  sm.append("demo3",new Demo());
  cout<<"----\n";
  return 0;
}
```
# Output
```
constructor
----
destructor
destructor
destructor
```
in output you can see that `Demo` class destructor gets automatically called when `sm` object goes out of scope.

# More
you can use your objects created with `new` like this--
```
sm["demo1"]->get(); // return string "demo name 1"
sm["demo3"]->get(); // return string "default"
Demo *tmp = sm["demo3"];
tmp->set("new demo name");
tmp->get(); `or` sm["demo3"]->get(); // return "new demo name"
```
you can also access items like an array,(Array starts with 0)
```
for(int i=0; i<sm.count(); i++) {
  sm[i]->call_method();
}

OR BEST WAY IS-->

sm.for_each( [](Demo *td) { td->get(); } ); // passing a lambda function
--------------------------------------------
void foo(Demo *td) {
  td->get();
  td->set("hello world");
}

sm.for_each(foo);// passing a function as argument make sure that function must accept an argument of type `classType *`
```
### Note
if a wrong key given then an exception `KeyError` thrown
# All available methods
```
append(string key, classType *obj);//this method used for adding new items in the list
clear();//clears the list and also deletes all the items
count(); returns the nubmber of items
at_beginning(string key, classType *obj);//adds an item at the beginning of the list
first_value();//returns the first item in list
last_value();//returns the last item in list
first_key();//returns the key of first item
last_key();//returns the key of last item
get_item(string key);//returns the item associated with this key
get_key(classType *obj);//returns the key associated with this *obj
remove(string key);//removes the item associated with this key also deletes that object
remove(classType *obj);//removes the item if item is in list also deletes that object
swap_item(string key1, string key2);//swap items not the keys
swap_item(classType *obj1, classType *obj2);//swap items not the keys
swap_key(string key1, string key2);//swap keys not the items
swap_key(classType *obj1, classType *obj2);//swap keys not the items
```
# Exceptions
`KeyError` this exception occurs when an incorrect key is given
`ItemError` this exception occurs when an incorrect item (classType *obj) is given
`LengthError` this exception occurs when there is no items in the list
`ArrayIndexError` this exception occurs when arrayIndex > numberOfItems

# Attention !!!
Here is use `classType` as general term...
`classType` can be any valid data type like- `int`,`float`,`string`, or `user defined data types` etc...

in the above example `classTypes` is a user defined data type `Demo`
