//
//  main.cpp
//  Sorting
//
//  Created by Damjan Markovic on 2018-03-05.
//  Copyright © 2018 GWBRecords©™®. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "heap.h"
#include "dynarray.h"
#include "smrtptr.h"

using namespace std;

//swap value of a at index b with value of a at index c
void swap(int *a, int b, int c)
{
    int temp = a[b];
    a[b] = a[c];
    a[c] = temp;
}


int quickindex(int *nums, int leftIndex, int rightIndex)
{
    //select right-most index in [leftIndex, rightIndex] as pivot
    int pivot = rightIndex;
    
    //boolean to determine whether or not leftIndex is moving upwards or rightIndex downwards
    bool left = true;
    
    //while leftIndex isn't passed rightIndex
    while (leftIndex-1 < rightIndex)
    {
        if (left)
        {
            //if leftIndex is at the pivot signal to begin moving rightIndex to the left
            if(leftIndex == pivot)
            {
                left = false;
            }
            else
            {
                //swap values at leftIndex and pivot if the latter is greater than the former
                if(nums[leftIndex] > nums[pivot])
                {
                    swap(nums, leftIndex, pivot);
                    pivot = leftIndex;
                    left = false;
                }
            }
            //move leftIndex by 1 to the left
            leftIndex++;
        }
        else
        {
            //if rightIndex is at the pivot signal to move leftIndex to the right
            if(rightIndex == pivot)
            {
                left = true;
            }
            else
            {
                //swap values at rightIndex and pivot if the latter is less than the former
                if(nums[rightIndex] < nums[pivot])
                {
                    swap(nums, rightIndex, pivot);
                    pivot = rightIndex;
                    left = true;
                }
            }
            //move rightIndex by 1 to the right
            rightIndex--;
        }
    }
    
    //now that the list on the interval [leftIndex, rightIndex] has been properly arranged return pivot
    return pivot;
}

/*
    
    input: pointer to an array of numbers and 2 index values defining an interval on this array
 
    assumptions:
        1) leftIndex < rightIndex
        2) nums is a valid list of numbers such that leftIndex is atleast the lowest possible index and
           rightIndex is at most the highest possible index
    
    output: a call to function quickindex after the values at rightIndex and a random index in [leftIndex,
            rightIndex] of nums have been swapped.
 
 */
int quickindex_rand(int *nums, int leftIndex, int rightIndex)
{
    srand ((unsigned int)(time(NULL))); //seed random number
    int r = leftIndex + rand() % (rightIndex - leftIndex); //select rand r between leftIndex and rightIndex
    swap(nums, r, leftIndex); //swap nums[r] and nums[leftIndex]
    return quickindex(nums, leftIndex, rightIndex);
}

void quicksort(int* nums, int leftIndex, int rightIndex)
{
    if (leftIndex < rightIndex) //if the interval is of valid length, ie of size greater than 0
    {
        int pivot = quickindex_rand(nums, leftIndex, rightIndex);
        quicksort(nums, leftIndex, pivot-1);
        quicksort(nums, pivot+1, rightIndex);
    }
}

/*
 
 input: a pointer to an array of numbers as well as the left index, center, and right index of the array
 
 assumptions: 
    1) li < ci < ri, 
    2) the sub-arrays defined by the intervals [li,ci] and [ci+1,ri] on the array
       nums are assumed to be sorted in increasing order respectively
    3) nums is a valid list of numbers such that li is atleast the lowest possible index and ri is at most
       the highest possible index
 
 result: nums such that on the interval [li,ri] nums is sorted in increasing order
 
*/
void merge(int* nums, int li, int ci, int ri)
{
    
    int leftSize = ci-li + 1; //size of the left interval
    int rightSize = ri-(ci+1) + 1; //size of the right interval
    
    int leftIndex = li; //beginning index of the left interval in nums
    int rightIndex = ci+1; //beginning index of the right interval in nums
    
    int result[leftSize+rightSize]; //the resulting sorted array of both intervals
    int resultIndex = 0; //beginning index for this resulting array
    
    //loop until one of the intervals has been traversed
    while(leftIndex < li+leftSize && rightIndex < (ci+1)+rightSize)
    {
        //current element in left interval less than one in right
        if(nums[leftIndex] < nums[rightIndex])
        {
            result[resultIndex++] = nums[leftIndex++];
        }
        //current element in right interval less than one in left
        else if(nums[leftIndex] > nums[rightIndex])
        {
            result[resultIndex++] = nums[rightIndex++];
        }
        //elements are equal
        else
        {
            result[resultIndex++] = nums[leftIndex++];
            result[resultIndex++] = nums[rightIndex++];
        }
    }
    
    //add the remaining elements in the left interval to the result array
    if (leftIndex < li+leftSize)
    {
        while(resultIndex < leftSize+rightSize)
        {
            result[resultIndex++] = nums[leftIndex++];
        }
    }
    
    //add the remaining elements in the right interval to the result array
    if (rightIndex < (ci+1)+rightSize)
    {
        while(resultIndex < leftSize+rightSize)
        {
            result[resultIndex++] = nums[rightIndex++];
        }
    }
    
    //overwrite the interval [li, ri] in nums with the result array
    for(int i = 0; i < leftSize+rightSize; i++)
    {
        nums[li+i] = result[i];
    }
    
}

//sort in increasing order a list of numbers in the interval [leftIndex,rightIndex]
void mergesort(int* nums, int leftIndex, int rightIndex)
{
    if (leftIndex < rightIndex) //if the interval is of valid length, ie of size greater than 0
    {
        int halfway = (int)floor((leftIndex+rightIndex)/2); //midpoint of the interval
        mergesort(nums,leftIndex,halfway); //
        mergesort(nums,halfway+1,rightIndex);
        merge(nums,leftIndex,halfway,rightIndex);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int test[44] = {10, 3, 33, 2, 32, 41, 1, 6, 5, 23, 25, 39, 4, 37, 43, 36, 14, 12, 11, 13, 18, 15, 20, 38, 16, 42, 28, 8, 9, 35, 24, 22, 30, 31, 27, 40, 21, 26, 34, 19, 17, 20, 7, 29};
    
    //int test2[5] = {4,2,12,88,0};
    /*cout << quickindex(test, 0, 43) << "\n\n";
    cout << "indexed = { ";
    for(int j = 0; j < 44; j++) {
        string s = (j == 43) ? " " : ", ";
        cout << test[j] << s;
    }
    cout << "}\n\n";
    quicksort(test, 0, 43);
    cout << "sorted = { ";
    for(int i = 0; i < 44; i++) {
        string s = (i == 43) ? " " : ", ";
        cout << test[i] << s;
    }
    cout << "}\n";*/
    
    DynArray<int> d;
    
    for(int i = 0; i < 44; i++)
    {
        d.push(test[i]);
    }
    
    d.squeeze_in(9999, 12);
    
    d.but(8888);
    
    SmrtPtr<DynArray<int>> dynPtr (new DynArray<int>(d));
    
    dynPtr->but(4000000);
    
    cout << "DynArray = { ";
    while(!d.isEmpty())
    {
        string s = (d.get_size() == 1) ? " " : ", ";
        cout << d[0] << s;
        d.flick();
    }
    cout << "}\n";
    
    //d.flick();
    
    
    
    return 0;
}
