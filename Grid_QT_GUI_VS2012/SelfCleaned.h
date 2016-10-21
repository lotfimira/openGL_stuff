#pragma once

#include <memory>

/*

HOW TO USE SelfCleaned

1- Make your class derrive publicly from SelfCleaned

2- define the void clean() method in your derived class

3- call autoClean() in the destructor of the derived class

class Derived : public SelfCleaned
{
protected:
    void clean()
    {
        // implement the cleanup of your resources here
    }

public:
    ~Derived()
    {
        // checks reference counter, if last then call clean()
        autoClean();
    }
};

*/

//-----------------------------------------------------------------------------
class DummyPlug
{
public:
    DummyPlug(){}
    ~DummyPlug(){}
};

//-----------------------------------------------------------------------------
class SelfCleaned
{
private:
    // reference counter
    std::shared_ptr<DummyPlug> _auto_clean;

protected:
    virtual void clean() = 0;
    void autoClean()
    {
        // destructor of last object triggers the clean() method
        if(_auto_clean.use_count() == 1)
        {
            clean();
        }
    }

public:
    SelfCleaned() 
    {
        // create a shared ptr to keep a reference count
        // copy constructor will increment reference count
        _auto_clean = std::make_shared<DummyPlug>();
    }

    virtual ~SelfCleaned() {}
};