#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // prefix input with 'a' to make it 36 characters long
        std::string paddedString = k;
        while(paddedString.size() < 36)
        {
            paddedString = "a" + paddedString;
        }
        // do in groups of 6
        // Add your code here
        HASH_INDEX_T hashValue[6];
        // do in groups of 6

        for(int i=0; i < 5; ++i)
        {
            hashValue[i] = 0;
            // for each character in the string, convert to base 36
            for(int j=0; j < 6; ++j)
            {
                hashValue[i] += letterDigitToNumber(paddedString[6+i * 6 + j]);
                hashValue[i] *= 36;
            }
            hashValue[i] /= 36;
        }
        // multiply with rvalues
        HASH_INDEX_T result = 0;
        for(int i=0; i < 5; ++i)
        {
            result += hashValue[i] * rValues[i];
        }
        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else if(letter >= 'A' && letter <= 'Z')
        {
            return letter - 'A';
        }
        else if(letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
        }
        else
        {
            return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
