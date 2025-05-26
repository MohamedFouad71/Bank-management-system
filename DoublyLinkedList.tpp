#pragma once
#include <iostream>
#include "account.hpp"
#include "DoublyLinkedList.hpp"

// Make Sure To check all the variable for each edited node
// first, last , previous , next , value , length [## 6 vars]

template<typename t>
DoublyLinkedList<t>::DoublyLinkedList() {
        first = last = nullptr;
        length =0;
}

template<typename t>
DoublyLinkedList<t>::~DoublyLinkedList(){
        node *current = first;
        while (current != nullptr){
                node *next = current->next;
                delete current;
                current = next;
        }
}

template<class t>
bool DoublyLinkedList<t>::isEmpty() const {return length == 0;}

template<class t>
int DoublyLinkedList<t>::getLength() const {return length;}


template<typename t>
void DoublyLinkedList<t>::display() const{

        std::cout << "[ ";

        node *temp = first;
        while (temp != nullptr) {
                std::cout << temp->value;
                if (temp->next != nullptr) {
                        std::cout << " , ";
                }
                temp = temp->next;
        }

        std::cout << " ]\n";
}

template <typename t>
void DoublyLinkedList<t>::insertFirst(t val) {

        node *newNode = new node;
        newNode->value = val;
        newNode->next = first;
        newNode->previous = nullptr;

        if (isEmpty()) {
                first = last = newNode;
        }
        else {
                first->previous = newNode;
                first = newNode;
        }

        length++;
}

template<class t>
void DoublyLinkedList<t>::insertLast(t val) {

        node *newNode = new node;
        newNode->value = val;
        newNode->next = nullptr;
        newNode->previous = last;

        if (isEmpty()) {
                last = first = newNode;
        }
        else {
                last->next = newNode;
                last = newNode;
        }

        length++;
}

template<class t>
void DoublyLinkedList<t>::insertAt(int index, t val) {

        if (index < 0 || index >= length) {
                std::cerr << "Error: index out of bounds\n";
                return;
        }

        if (index == 0) {
                insertFirst(val);
                return;
        } else if (index == length) {
                insertLast(val);
                return;
        }

        node* newNode = new node;
        newNode->value = val;

        bool reversedInsert = (length - index) < index;

        if (reversedInsert) {
                node* nodeAfterIndex = last;
                for (int i = 0; i < length - index - 1; i++) {
                        nodeAfterIndex = nodeAfterIndex->previous;
                }

                newNode->next = nodeAfterIndex;
                newNode->previous = nodeAfterIndex->previous;

                nodeAfterIndex->previous->next = newNode;
                nodeAfterIndex->previous = newNode;
        } else {
                node* prev = first;
                for (int i = 0; i < index - 1; i++) {
                        prev = prev->next;
                }

                newNode->next = prev->next;
                newNode->previous = prev;

                prev->next->previous = newNode;
                prev->next = newNode;
        }

        length++;
}

template <typename t>
void DoublyLinkedList<t>::removefirst(){

    if (isEmpty()){
    std::cerr<<"List is Empty!!\n";
    return;
    }
    else if (length == 1){
        delete first;
        first = last = nullptr;
    }
    else {
        node *temp = first;
        first = first->next;
        first->previous = nullptr;
        delete temp;
    }

    --length;
}

template <typename t>
void DoublyLinkedList<t>::removeLast(){
    
    if (isEmpty()){
        std::cerr<<"List is Empty!!\n";
        return;
    }
    else if (length == 1){
        delete first;
        first = last = nullptr;
        return;
    }
    else {
        node *temp = last;
        last = last->previous;
        last->next = nullptr;
        delete temp;
    }
    --length;
}

template <typename t>
void DoublyLinkedList<t>::removeAt(int index){

        if (isEmpty()){
            std::cerr<<"List is Empty!!\n";
            return;
        }
        else if (index < 0 || index >= length ) {
            std::cerr << "Error: index out of bounds\n";
            return;
        }
        
        if (index == 0) {
            removefirst();
            return;
        }
        else if (index == length - 1) {
            removeLast();
            return;
        }

        bool reversedRemove = (length - index) < index;
        node *current;

        if (reversedRemove){
            
            current = last;
            for (size_t i = 0 ; i < length - index - 1; i++){
                current = current -> previous;
            }

        }
        else {

            current = first;
            for (size_t i = 0; i <index ; i++){
                current = current->next; // untill it reaches index
            }

        }

        node *afterIndex = current->next;
        node *beforeIndex = current->previous;
        beforeIndex -> next = afterIndex;
        afterIndex->previous = beforeIndex;
        delete current;
        --length;
}

template <typename t>
t DoublyLinkedList<t>::twoPointerSearch(t item){
        
        node *forwardSearcher = first , *backwardSearcher = last;
        unsigned int counter = 0;
        if(isEmpty()){
                throw std::runtime_error("Cannot search an empty list");
                return;
        }

        while( counter != length/2 + 1) {
                
                if (item == forwardSearcher-> value){
                        return forwardSearcher->value;
                }
                else if (item == backwardSearcher -> value){
                        return backwardSearcher -> value;
                }
                forwardSearcher = forwardSearcher->next;
                backwardSearcher = backwardSearcher->previous;
                
                ++counter;
        }

        throw std::runtime_error("Item not found");
}

template <class t>
user* DoublyLinkedList<t>::searchAccount(const std::string& username) {

    if (isEmpty()) {
        throw std::runtime_error("Cannot search an empty list");
    }

    // Search from both ends simultaneously
    node* front = first;
    node* back = last;
    short int counter = 0 ;
    while (counter != length/2 + 1) {
        // Check front pointer
        if ((front->value).getUserName() == username) {   
                
            user* returned = &(front->value);    
            return returned;
        }
        
        // Check back pointer
        if ((back->value).getUserName() == username) {

            user *returned = &(back->value);    
            return returned;
        }        
        
        // Move pointers toward center
        front = front->next;
        back = back->previous;
    }
    
    throw std::runtime_error("Not Found");
  // Not found
}