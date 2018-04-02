//
//  dynarray.hpp
//
//  Created by Bingo Star on 2018-03-24.
//  Copyright © 2018 GWBRecords©™®. All rights reserved.
//

#ifndef dynarray_hpp
#define dynarray_hpp

#include <stdio.h>
#include <stdexcept>

template <class T>
class DynArray {
    
public:
    
    //default constructor
    DynArray() : t_size(0), memsize(2), array(new T[memsize]) {}
    
    //size specified constructor
    DynArray(int size) : t_size(size), memsize(size << 1), array(new T[memsize]) {}
    
    //copy constructor (deep copy)
    DynArray(const DynArray& d) : t_size(d.get_size()), memsize(d.get_size() << 1), array(new T[memsize])
    {
        for (int i = 0; i < t_size; i++)
        {
            array[i] = d[i];
        }
    }
    
    //destructor
    ~DynArray()
    {
        delete[] array;
    }
    
    //copy assignment
    DynArray& operator= (const DynArray& d)
    {
        delete array;
        t_size = d.get_size();
        memsize = t_size << 1;
        
        for (int i = 0; i < t_size; i++)
        {
            array[i] = d[i];
        }
    }
    
    //returns the value at index
    T const& operator [] (unsigned int index) const
    {
        return array[index];
    }
    
    //returns the reference at index
    T& operator [] (unsigned int index)
    {
        return array[index];
    }
    
    //shift all elements from index to end by one to the right, then set the value at index to element
    void squeeze_in (T element, unsigned int index)
    {
        if(index < t_size)
        {
            t_size += 1;
            
            resize();
            
            for (int i = t_size-1; i > index; i--)
            {
                array[i] = array[i-1];
            }
            
            array[index] = element;
        }
    }
    
    //remove element at index
    void remove (unsigned int index)
    {
        if(index < t_size)
        {
            
            for(int i = index; i < t_size; i++)
            {
                array[i] = array[i+1];
            }
            
            t_size -= 1;
            resize();
        }
    }
    
    //add to end of array
    void push (T element)
    {
        t_size += 1;
        
        resize();
        
        array[t_size-1] = element;
    }
    
    //remove and return last element of array
    T pop()
    {
        if (isEmpty())
        {
            throw std::logic_error("Cannot remove an element from an empty list.");
        }
        
        T temp = array[t_size-1];
        remove(t_size-1);
        return temp;
    }
    
    //add to front of array
    void but(T element)
    {
        squeeze_in(element, 0);
    }
    
    //remove and return the element at the front of array
    T flick()
    {
        if (isEmpty())
        {
            throw std::logic_error("Cannot remove an element from an empty list.");
        }
        
        T temp = array[0];
        remove(0);
        return temp;
        
    }
    
    //get number of elements currently stored
    int get_size() const
    {
        return t_size;
    }
    
    //return true if no elements are currently stored
    bool isEmpty () const
    {
        return t_size == 0;
    }
    

private:
    
    int t_size; //number of occupied memory slots
    int memsize; //number of allocated memory slots
    T * array; //internal array
    
    //if the allocated memory is more than twice the occupied memory, halve the allocated memory 
    //if the allocated and occupied memory are equal, double the allocated memory
    void resize ()
    {
        if (t_size < (memsize >> 1))
        {
            memsize = (memsize >> 1);
            T * new_array = new T[memsize];
            
            for (int i = 0; i < memsize; i++)
            {
                new_array[i] = array[i];
            }
            
            delete[] array;
            array = new_array;
        }
        
        if (t_size == memsize)
        {
            memsize = (memsize << 1);
            T * new_array = new T[memsize];
            
            for (int i = 0; i < memsize; i++)
            {
                new_array[i] = array[i];
            }
            
            delete[] array;
            array = new_array;
        }
    }
    
};

#endif /* dynarray_hpp */
