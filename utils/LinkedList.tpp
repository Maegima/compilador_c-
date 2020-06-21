/**
 * @file LinkedList.tpp
 * @author André Lucas Maegima
 * @brief Implementação do template LinkedList.
 * @version 1.3
 * @date 2020-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _LINKEDLIST_TPP_
#define _LINKEDLIST_TPP_

#include <iostream>

using namespace std;

static const size_t nllist = -1;

template <typename T>
LinkedList<T>::LinkedList(){
    this->_first = nullptr;
    this->_last = nullptr;
    this->_size = 0;
}

template <typename T>
void LinkedList<T>::push(const T& data){
    Node *item = new Node(data);
    if(!_first)
        _first = item;
    else
        _last->next = item;
    _last = item;
    _size++;
}

template <typename T>
void LinkedList<T>::push(const T&& data){
    Node *item = new Node(data);
    if(!_first)
        _first = item;
    else
        _last->next = item;
    _last = item;
    _size++;
}

template <typename T>
bool LinkedList<T>::remove(size_t index){
    Node *p0 = nullptr;
    Node *p1 = _first;
    // TODO: throw error index out of range
    if(index >= _size) return false;
    while(p1){
        if(index == 0){
            if(p0)
                p0->next = p1->next;
            else
                _first = p1->next;
            if(p1 == _last)
                _last = p0;
            delete p1;
            _size--;
            return true;
        }
        p0 = p1;
        p1 = p1->next;
        index--;
    }
    return false;
}

template <typename T>
size_t LinkedList<T>::find(const T& data){
    size_t count = 0;
    for(T p : *this){
        if(data == p)
            return count;
        count++;
    }
    return nllist;
}

template <typename T>
size_t LinkedList<T>::find(const T&& data){
    size_t count = 0;
    for(T p : *this){
        if(data == p)
            return count;
        count++;
    }
    return nllist;
}

template <typename T>
T& LinkedList<T>::operator[](size_t index){
    // TODO: throw error index out of range
    if(index >= _size) return _last->data;
    for(T& p : *this){
        if(index == 0)
            return p;
        index--;
    }
    return _last->data;
}

template <typename T>
size_t LinkedList<T>::size() const {
    return _size;
}

#endif