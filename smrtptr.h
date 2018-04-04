//
//  smrtptr.h
//
//  An implementation of a very basic smart pointer in C++ using reference counting. Things to consider: thread safety?
//
//  Created by Damjan Markovic on 2018-03-25.
//  Copyright © 2018 GWBRecords©™®. All rights reserved.
//

#ifndef smrtptr_h
#define smrtptr_h

template <class T>
class SmrtPtr {

public:
    
    //default constructor
    SmrtPtr() : data(0), references(0) {}
    
    //wrapper constructor
    SmrtPtr(T * d) : data(d)
    {
        *references = 1;
    }
    
    //copy constructor
    SmrtPtr(const SmrtPtr& sp) : data(sp.data), references(sp.references)
    {
        *references++;
    }
    
    //destructor
    ~SmrtPtr()
    {
        release();
    }
    
    //copy assignment
    SmrtPtr& operator= (const SmrtPtr& sp)
    {
        if(this != sp)
        {
            release();
            data = sp.data;
            references = sp.references;
            *references++;
        }
        
        return *this;
    }
    
    T& operator* () const { return *data; } //derefence operator
    T* operator-> () const { return data; } //reference operator
    
    
private:
    T * data; //the data pointed to
    int * references; //number of pointers currently pointing to this data
    
    void release() 
    {
        if (--*references == 0)
        {
            delete data;
            delete references;
        }
    }

};

#endif /* smrtptr_h */
