//
// Created by DELL on 11/05/2025.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <string>
#include "account.hpp"

template <class t>
class DoublyLinkedList {

    struct node {
    t value;
    node *next, *previous;
};

public:
    int length;
    node *first , *last;

    DoublyLinkedList();
    ~DoublyLinkedList();
    bool isEmpty() const;
    int getLength() const;
    void display() const;
    void insertFirst(t value);
    void insertLast(t value);
    void insertAt(int index , t value);
    void removefirst();
    void removeLast();
    void removeAt(int index);
    t twoPointerSearch(t item);
    user* searchAccount(const std::string& username);
};



#include "DoublyLinkedList.tpp"
#endif //DOUBLYLINKEDLIST_H