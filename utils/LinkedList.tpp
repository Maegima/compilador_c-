/**
 * @file LinkedList.tpp
 * @author André Lucas Maegima
 * @brief Implementação do template LinkedList.
 * @version 1.4
 * @date 2020-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _LINKEDLIST_TPP_
#define _LINKEDLIST_TPP_

static const size_t nllist = -1;

template <typename T>
LinkedList<T>::LinkedList(){
    this->_head = new Node();
    this->_last = this->_head;
    this->_find = nullptr;
    this->_find_index = nllist;
    this->_size = 0;
}

template <typename T>
void LinkedList<T>::push(const T& data){
    Node *item = new Node(data);
    _last->next = item;
    _last = item;
    _size++;
}

template <typename T>
void LinkedList<T>::push(const T&& data){
    Node *item = new Node(data);
    _last->next = item;
    _last = item;
    _size++;
}

template<typename T>
bool LinkedList<T>::remove(){
    Node *item;
    if(!_find) return false;
    item = _find->next;
    if(item == _last)
       _last = _find;
    _find->next = item->next;
    delete item;
    _find_index = nllist;
    _find = nullptr;
    _size--;
    return true;
}

template <typename T>
bool LinkedList<T>::remove(size_t index){
    Node *p = _head;
    // TODO: throw error index out of range
    if(index >= _size) return false;
    if(index == _find_index) return remove();
    while(p->next){
        if(index == 0){
            _find = p;
            return remove();
        }
        p = p->next;
        index--;
    }
    return false;
}

template <typename T>
size_t LinkedList<T>::find(const T& data){
    _find_index = 0;
    Node *p = _head;
    while(p->next){
        if(data == p->next->data){
            _find = p;
            return _find_index;
        }
        _find_index++;
        p = p->next;
    }
    _find_index = nllist;
    return _find_index;
}

template <typename T>
size_t LinkedList<T>::find(const T&& data){
    _find_index = 0;
    Node *p = _head;
    while(p->next){
        if(data == p->next->data){
            _find = p;
            return _find_index;
        }
        _find_index++;
        p = p->next;
    }
    _find_index = nllist;
    return _find_index;
}

template <typename T>
T& LinkedList<T>::operator[](size_t index){
    // TODO: throw error index out of range
    if(index >= _size) return _head->data;
    if(_find_index == index) return _find->next->data;
    for(T& p : *this){
        if(index == 0)
            return p;
        index--;
    }
    return _head->data;
}

template <typename T>
size_t LinkedList<T>::size() const {
    return _size;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& llist){
    for(T data : *this)
        this->remove(0);
    for(T data : llist)
        this->push(data);
    this->_find = llist._find;
    this->_find_index = llist._find_index;
    return *this;
}

#endif