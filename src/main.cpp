/**
 * @file main.cpp
 * @author Jugal Shah (shahjugalr@gmail.com)
 * @brief Naive Implementation of count min sketch.
 * @version 0.1
 * @date 17/04/2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.hpp"

int main(){
    
    UInt64 RBound = 9; UInt64 hashFuncCount = 2;

    Sketch s(RBound, hashFuncCount);
    
    // 21 times 0, 2, 3, all other nos 0 times.
    UInt64 arr[] = {0,0,0,2,2,2,3,3,3,0,0,0,2,2,2,3,3,3,0,0,0,2,2,2,3,3,3,0,0,0,2,2,2,3,3,3,0,0,0,2,2,2,3,3,3,0,0,0,2,2,2,3,3,3,0,0,0,2,2,2,3,3,3};

    for (auto &&i : arr)
        s.Add(i);
    
    for (UInt64 i = 0; i < RBound; i++)
    {
        std::cout << i << " occured " << s.Count(i) << " times\n"; 
    }

    // For logging Purpose only.
    //  s.Display();

    return 0;    

}
