#ifndef SMART_MEM_EXCEPTION
#define SMART_MEM_EXCEPTION
#include <iostream>
#include <string>
#include <exception>
using namespace std;

class KeyError : public exception
{

  private:
    string msg = "wrong key given";

  public:
    KeyError() {}
    KeyError(string m) { msg = m; }
    const string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

class ItemError : public exception
{
  private:
    string msg = "wrong item given";

  public:
    ItemError() {}
    ItemError(string m) { msg = m; }
    const string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

class LengthError : public exception
{
  private:
    string msg = "there is no item in the container...\nto check length of the container call count()";

  public:
    LengthError() {}
    LengthError(string m) { msg = m; }
    const string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

class ArrayIndexError : public exception
{
  private:
    string msg = "Error:**Array index out of bounds**";

  public:
    ArrayIndexError() {}
    const string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

#endif
