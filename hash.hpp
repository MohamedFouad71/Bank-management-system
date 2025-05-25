#pragma once
#include <string>
#include "DoublyLinkedList.hpp"
#include "account.hpp"
    
extern DoublyLinkedList<account> hashTable[52][52];










//##############################################################################################
//                                      String Hashing
//##############################################################################################


/* 
    #################### first character hashing by me #######################

    this hash function takes a string and return an index depending on 
    the first character, where it is sorted from A to Z for uppercase letters, 
    and for lowercase letters it continues from index 26 to reduce conflicts providing 
    better searching effitioncy

    ### Advantages : the table will be sorted by default , KISS applied.
    ### Disadvantages : Not optimum for applications where some 'first characters' are used
        more than the others like people names. hash table size should be 52
        and of course this is not optimum for large databases.
*/ 

int firstCharacterHashing(std::string &name){

    const char firstCharacter = name.at(0);
    if (firstCharacter >= 'A' && firstCharacter <= 'Z') // checking if first character is uppercase
    {
        return int(firstCharacter) - 65 ;
    }
    else {
        return int(firstCharacter) - 71 ; // Start from index 26 for more searching effectioncy
    }
}

/*  another better hash function, good for storing names, but not optimum for all strings
    because it ignors the position of the string, for example ali == lia
*/
int sumHashing(std::string &key , int tableSize){

    int sum = 0;
    for (size_t i = 0; i < key.length(); i++){
        sum += int(key.at(i));
    }

    return sum % tableSize;
}


// character position matters, avoids overflow by making i%5
int weigtedSumHashing(std::string &key , int tableSize){

    unsigned int sum = 0;
    for (size_t i = 0; i < key.length(); i++){
        sum += int(key.at(i)) * (i%5 + 1) ;
    }

    return sum % tableSize;
}

/*  
    - exchanges time and memory, hash table will have 52^m objects, where m is the number of characters taken
    its like sorting the table by the first character, each string will have a hash table sorting the second letter,
    and so on, you could make it o(1) but this will require a huge ammount of memory, maybe in a search engine.
    you could also make the memory usage 26^m if you implemented a function to decapitalize your string.

    - keep in mind that you should ignore non alphabitic characters, or the memory usage will be larger.

    - in small projects, you could take 2 or 3 characters.
*/
int mazeHashing(std::string &name , int characterPosition){

    const char character = name.at(characterPosition);
    if (character >= 'A' && character <= 'Z') // checking if the character is uppercase
    {
        return int(character) - 65 ;
    }
    else {
        return int(character) - 71 ; // Start from index 26 for more searching effectioncy
    }
}