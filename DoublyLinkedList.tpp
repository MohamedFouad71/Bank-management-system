#pragma once
#include <iostream>

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
        } else if (index == length - 1) {
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
    std::cerr<<"List is Empty!!";
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
        std::cerr<<"List is Empty!!";
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
            std::cerr<<"List is Empty!!";
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
            for (size_t i = 0; i <index; i++){
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