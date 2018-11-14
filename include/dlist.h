//*******************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-08
// Project 5
// Sources: None
//
//*******************************************************************

#ifndef __DLIST_H__
#define __DLIST_H__

#include "dnode.h"
#include <stdexcept>

namespace dpost{
    /**
    * @brief A template container class that has a linked list.
    *
    * @tparam T
    */
    template <class T>
    class dlist{
        public:
            ~dlist();

            void insert(T* rhs);
            void insert(const T& rhs);
            void remove(int index) throw(std::out_of_range);

            /**
            * @brief the size of the list
            *
            */
            inline int size() const{ return _size; }
            /**
            * @brief the length of the list, same as size()
            *
            */
            inline int length() const{ return _size; }
            /**
            * @brief Returns if the list is empty
            *
            */
            inline bool isEmpty() const{ return !_size; }

            void clear(); // Empty the list

            /**
            * @brief Accesses the pos element in the list
            *
            * @param pos is the position of the element
            *
            * @return a reference to the element at position pos
            */
            T& operator[]( int pos )throw(std::out_of_range);
            const T& operator[]( int pos ) const throw(std::out_of_range);
        private:
            dnode<T*>* _head{nullptr};
            dnode<T*>* _tail{nullptr};
            int _size{0};
    };


    /**
    * @brief Destroys a list
    *
    * @post Destroys the nodes and the data that the nodes point to.
    *
    * @tparam T
    */
    template <class T>
    dlist<T>::~dlist(){
        dnode<T*>* temp = _head;
        while( _head != nullptr ){
            _head = temp->next();
            delete temp->data;
            delete temp;
            temp = _head;
        }
    }

    /**
    * @brief Inserts an item to the list
    *
    * @post the pointed to item will be managed by the list.  At destruction of the list the
    * data associated with the item will also be destroyed.  The item will be inserted in
    * alphabetical order according to a given field.
    *
    * @tparam T
    * @param rhs is the item to insert
    */
    template <class T>
    void dlist<T>::insert(T* rhs){
        if( !_size ){ // no elements first time adding
            _head = new dnode<T*>;
            _tail = _head;
            _head->data = rhs;
            _size++;
            return;
        }

        // find the place to insert first
        dnode<T*>* cur = _head;
        dnode<T*>* match = cur;
        while( cur ){
            int compare = cur->data->CompareTo( rhs, false );
            if( compare < 0 ){
                match = cur;
                cur = cur->next();
            }else if( compare == 0 ){ // have a match
                // No instruction on how to handle this, we will append to end
                match = cur;
                cur = cur->next();
            }else{
                match = cur->previous(); // cur is too far, in first iter match is too far
                cur = nullptr; // set to nullptr to exit the loop as we have passed the location we want
            }
        }

        // Begin insertion
        if( match == nullptr ){
            _head->insertFirst(rhs);
            _head = _head->previous();
        }else if( match == _tail ){
             _tail = _tail->append(rhs);
        }else{
            match->insert( rhs );
        }
        _size++;
    }

    /**
    * @brief Inserts an item to the list by first making a copy.
    *
    * @tparam T
    * @param rhs a reference to an item to be copied and inserted.
    */
    template <class T>
    void dlist<T>::insert(const T& rhs){
        insert( new T(rhs) );
    }

    /**
    * @brief Clears all items on the list
    *
    * @post All current items will be destroyed, including the data that the nodes point to.
    *
    * @tparam T
    */
    template <class T>
    void dlist<T>::clear(){
        while( _head != nullptr ){
            dnode<T*>* _next = _head->next();
            delete _head->data;
            delete _head;
            _head = _next;
        }
        _size = 0;
    }

    template <class T>
    T& dlist<T>::operator[]( int pos )throw(std::out_of_range){
        try{ // froward throw from const function
            return const_cast<T&>( static_cast< const dlist<T>& >(*this)[pos] );
        }catch(...){
            throw;
        }
    }
    /**
    * @brief Accesses the item at the position pos which is passed to it as a reference
    *
    * @throw std::out_of_range
    *
    * @tparam T
    * @param pos
    *
    * @return a reference to the data item which can be modified
    */
    template <class T>
    const T& dlist<T>::operator[]( int pos ) const throw(std::out_of_range){
        if( pos > _size || pos < 0 ){
            throw std::out_of_range("Trying to access element out of range");
        }
        dnode<T*>* _current = _head;
        for( int i=0; i < pos; i++ ){
            _current = _current->next();
        }
        return *_current->data;
    }

    /**
    * @brief Removes item at position from list
    *
    * @throw std::out_of_range
    *
    * @tparam T
    * @param pos position of item
    *
    * @throw std::out_of_range
    */
    template <class T>
    void dlist<T>::remove( int pos ) throw(std::out_of_range){
        if( pos > _size || pos < 0) {
            throw std::out_of_range("Trying to remove element out of range");
        }
        dnode<T*>* _current = _head;
        for( int i=0; i < pos; ++i ){
            _current = _current->next();
        }
        if( _current == _head ){
            _head = _current->next();
        }else if( _current == _tail ){
            _tail = _current->previous();
        }
        delete _current->data;
        _current->remove();
        --_size;
    }
}

#endif
