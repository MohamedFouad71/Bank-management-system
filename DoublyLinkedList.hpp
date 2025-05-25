//
// Created by DELL on 11/05/2025.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H



template <class t>
class DoublyLinkedList {
private:

    struct node {
        t value;
        node *next, *previous;
    };
    int length;
    node *first , *last;

public:
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

};




#include "DoublyLinkedList.tpp"
#endif //DOUBLYLINKEDLIST_H