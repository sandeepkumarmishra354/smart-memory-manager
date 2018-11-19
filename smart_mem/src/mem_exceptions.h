#ifndef SMART_MEM_EXCEPTION
#define SMART_MEM_EXCEPTION
#include <iostream>
#include <string>
#include <exception>

enum class ErrorType
{
	KEY_ERROR,
	ITEM_ERROR,
	LENGTH_ERROR,
	ARRAY_INDEX_ERROR
};

class KeyError : public std::exception
{

  private:
    std::string msg = "wrong key given";

  public:
    KeyError() {}
    KeyError(std::string m) { msg = m; }
    const std::string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

class ItemError : public std::exception
{
  private:
    std::string msg = "wrong item given";

  public:
    ItemError() {}
    ItemError(std::string m) { msg = m; }
    const std::string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

class LengthError : public std::exception
{
  private:
    std::string msg = "there is no item in the container...\nto check length of the container call count()";

  public:
    LengthError() {}
    LengthError(std::string m) { msg = m; }
    const std::string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

class ArrayIndexError : public std::exception
{
  private:
    std::string msg = "Error:**Array index out of bounds**";

  public:
    ArrayIndexError() {}
    const std::string getMessage() const
    {
        return msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};

#endif
