/**
 * @file Sketch.hpp
 * @author Jugal Shah (shahjugalr@gmail.com)
 * @brief Contains implementation of Data Structure for count min sketch.
 * @version 0.1
 * @date 17/04/2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/***
 * 
 * So Basically idea is two make two matrices.
 * 
 * First matrix is definition matrix which will hold hash value for each input.
 * Rows = no of hash functions we use.
 * Columns = no of inputs.
 * 
 * RowthCoulmn will have hash value output. for given input and hash function.
 * 
 * Second matrix is recording matrix which will keep track of all hash outputs occurences.
 * i.e.
 * 
 * Rows = no of hash functionss.
 * colums = no of outputs possible from hash functions.
 * 
 * RowthCoulmn will have no of times the output hash values occured 
 * for given hash function and hash values.
 * 
 * At last when we will need to get the no of occurences of particular input we will
 * pass into hash function we will get its hash output.
 * 
 * Then we will take that hash output and get occurences from second table ie record table.
 * 
 * So now why more than one hash functions are we using.
 * 
 * well we take min of all.
 * 
 * We are using more hash functions so that we can actually distinguish between different inputs.
 * because there's always a chance that one hash function can return a value which it returns for other input as well.
 * 
 * 
 * NOTE: The more the hash functions the more will be accuracy.
 ***/


#include "helper.hpp"
#include <bits/stdc++.h>

class Sketch
{
private:
    UInt64 defMat_x, defMat_y;     // X: no of distinct inputs from 0 to X. Y: no of hash functions.
    UInt64 recMat_x, recMat_y;     // X: no of distinct outputs from hash funcs. Y: no of hash functions.

    UInt64 **definitionMatrix = nullptr;        UInt64 **recordMatrix = nullptr;

public:
    // More no of hash function more accuracy, more no of output range more accuracy.
    Sketch(UInt64 inputRange, UInt64 noOfhashFunc);
    ~Sketch();
    void Display();
    void Init();
    void Add(UInt64& value);
    UInt64 Count(UInt64& value);
};

Sketch::Sketch(UInt64 inputRange, UInt64 noOfhashFunc){

    //  Allocated memory dynamically. 

    defMat_x = inputRange;  defMat_y = recMat_y = noOfhashFunc; recMat_x = 20;

    definitionMatrix = new UInt64* [defMat_y];

    for (UInt64 i = 0; i < defMat_y; i++)
    {   
        //  Allocate a new array of size column count for each row.
        definitionMatrix[i] = new UInt64 [defMat_x];
    }

    recordMatrix = new UInt64* [recMat_y];

    for (UInt64 i = 0; i < recMat_y; i++)
    {   
        //  Allocate a new array of size column count for each row.
        recordMatrix[i] = new UInt64 [recMat_x];
    }

    Init();
}

void Sketch::Init(){

    // Initialize the definittion matrice.
    for (UInt64 i = 0; i < defMat_y; i++)
    {
        for (UInt64 j = 0; j < defMat_x; j++)
        {
            definitionMatrix[i][j] = int(float(rand())*float(LONG_PRIME)/float(RAND_MAX) + 1) % 20;
        }
        
    }

    // Initialize the record matrice.
    for (UInt64 i = 0; i < recMat_y; i++)
    {
        for (UInt64 j = 0; j < recMat_x; j++)
        {
            recordMatrix[i][j] = 0;
        }
        
    }
}

Sketch::~Sketch(){

    for (UInt64 i = 0; i < defMat_y; i++)
    {   
        //  de-Allocate an allocated array of size column count for each row.
        delete [] definitionMatrix[i];
    }

    // de-Allocates array containing pointers to those arrays which we de-allocated proviously.
    delete [] definitionMatrix;

    for (UInt64 i = 0; i < recMat_y; i++)
    {   
        //  de-Allocate an allocated array of size column count for each row.
        delete [] recordMatrix[i];
    }

    // de-Allocates array containing pointers to those arrays which we de-allocated proviously.
    delete [] recordMatrix;

}

// Just for loggin puporse.
void Sketch::Display(){
    for (UInt64 i = 0; i < defMat_y; i++){
        for (UInt64 j = 0; j < defMat_x; j++)
            std::cout << definitionMatrix[i][j] << " ";
        std::cout << std::endl;
    }
    for (UInt64 i = 0; i < recMat_y; i++){
        for (UInt64 j = 0; j < recMat_x; j++)
            std::cout << recordMatrix[i][j] << " ";
        std::cout << std::endl;
    }
}

// Track new value.
void Sketch::Add(UInt64& value){

    // So we will first get the hash values from each of the hash functions by using definiton matrice.
    // After that we will inc the cell Rowth hash func and hash output from prev step.

    for (UInt64 i = 0; i < defMat_y; i++){
        UInt64 hashOutput = definitionMatrix[i][value];
        recordMatrix[i][hashOutput]++;
    }
    
}

// Find count of provided variable.
UInt64 Sketch::Count(UInt64& value){

    // So we will now do this that first we know that what is the hash output for this value for
    // each hash function and then we will get count of that once we do that we will now take
    // min from all hash trackings.

    UInt64 occurences = UINT64_MAX;

    for (UInt64 i = 0; i < defMat_y; i++)
    {
        UInt64 hashOutput = definitionMatrix[i][value];
        occurences = std::min(recordMatrix[i][hashOutput], occurences);
    }
    
    return occurences;

}
