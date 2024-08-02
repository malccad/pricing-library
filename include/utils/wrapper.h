#ifndef WRAPPER_H
#define WRAPPER_H

template< class T>
class Wrapper
{
public:
    Wrapper()
    {
        DataPtr=0;
    }

    Wrapper(const T& inner)
    {
        DataPtr = inner.clone();
    }

    ~Wrapper()
    {
        if (DataPtr!=0)
        {
            delete DataPtr;
        }
    }

    Wrapper(const Wrapper& original)
    {   
        DataPtr = original.DataPtr -> clone();
    }

    Wrapper& operator=(const Wrapper& original)
    {
        if (this!=&original)
        {
            if (DataPtr!=0)
            {
                delete DataPtr;
            }
            DataPtr = (original.DataPtr!= 0)?
                original.DataPtr->clone(): 0;            
        }
        return *this;
    }

    T& operator*()
    {
        return *DataPtr;
    }

    const T& operator*() const
    {
        return *DataPtr;
    }

    const T* operator->()const
    {
        return DataPtr;
    }

    T* operator->()
    {
        return DataPtr;
    }
private:
    T* DataPtr;
};
#endif