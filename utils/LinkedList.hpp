/**
 * @file LinkedList.hpp
 * @author André Lucas Maegima
 * @brief Definição do template LinkedList.
 * @version 1.3
 * @date 2020-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _LINKEDLIST_HPP_
#define _LINKEDLIST_HPP_

#include <cstddef>

template <typename T>
class LinkedList{
private:
    class Node{
    public:
        T data;
        Node *next;
        Node(const T& data) : data(data) , next(nullptr) {} 
    };
    Node *_first, *_last;
    size_t _size;
public:
    /**
     * @brief Construct a new Linked List object.
     * 
     */
    LinkedList();
    /**
     * @brief Add item at the end. 
     * 
     * @param data item to add.
     */
    void push(const T& data);
    /**
     * @brief Remove item from list.
     * 
     * @param data item to remove.
     * @return true if the item was removed from list.
     * @return false if the item wasn't removed from list.
     */
    void push(const T&& data);
    /**
     * @brief Remove item at index from list.
     * 
     * @param data item to remove.
     * @return true if the item was removed from list.
     * @return false if the item wasn't removed from list.
     */
    bool remove(size_t index);
    /**
     * @brief Find item in the list.
     * 
     * @return size_t position of the item in the list or nllist if the item is not in the list.
     */
    size_t find(const T& data);
    /**
     * @brief Find item in the list.
     * 
     * @return size_t position of the item in the list or nllist if the item is not in the list.
     */
    size_t find(const T&& data);
    /**
     * @brief Return item at index.
     * 
     * @param index Item index.
     * @return T& Item.
     */
    T& operator[](size_t index);
    /**
     * @brief Return number of elements.
     * 
     * @return size_t 
     */
    size_t size() const;
    /**
     * @brief Iterator class for LinkedList.
     * 
     */
    class iterator{
    public:
        typedef T* pointer;
        typedef T& reference;
        typedef Node* iterator_pointer;
        iterator(iterator_pointer ptr) : ptr(ptr) {}
        iterator& operator++() { ptr = ptr->next; return *this; }
        iterator operator++(int) { iterator temp = *this; ptr = ptr->next; return temp; }
        reference operator*() { return ptr->data; }
        pointer operator->() { return &ptr->data; }
        bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
        bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }
    private:
        iterator_pointer ptr;
    };
    /**
     * @brief Return iterator for first item in T.
     * 
     * @return iterator
     */
    iterator begin(){
        return iterator(this->_first);
    }
    /**
     * @brief Return iterator for last item in T.
     * 
     * @return iterator 
     */
    iterator end(){
        return iterator(nullptr);
    }
};

#include "LinkedList.tpp"

#endif