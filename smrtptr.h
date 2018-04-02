//
//  smrtptr.h
//
//  Created by Damjan Markovic on 2018-03-25.
//  Copyright © 2018 GWBRecords©™®. All rights reserved.
//

#ifndef smrtptr_h
#define smrtptr_h

template <class T>
class SmrtPtr {

public:
    SmrtPtr(T * d) : data(d) {}
    ~SmrtPtr() { delete data; }
    
    T& operator* () const { return *data; }
    T* operator-> () const { return data; }
    
private:
    T * data;

};


#endif /* smrtptr_h */
