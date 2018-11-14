//*******************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-07
// Project 5
// Sources: None
//
//*******************************************************************

#ifndef __DNODE_H__
#define __DNODE_H__

namespace dpost{
    /**
    * @brief A template class implementing the linked list algorithm
    *
    * @tparam T
    */
    template <class T>
    class dnode{
        public:
            dnode<T>* append(T& rhs);
            dnode<T>* insertFirst(T& rhs);
            dnode<T>* insert(T& rhs);
            void remove();
            dnode<T>* next() const;
            dnode<T>* previous() const;
            /**
            * @brief The data stored in the node
            */
            T data;
        private:
            dnode<T>* _previous{nullptr};
            dnode<T>* _next{nullptr};
    };


    /**
    * @brief Appends the rhs reference to the item as the next data of the next node
    *
    * @pre This is the last node in the list.  This is not checked for, but assumed.
    * @post The next pointer is set to the newly created node.  The next node is assigned the
    * rhs item passed to it.
    *
    * @tparam T
    * @param rhs is a reference to the item to be appended
    *
    * @return the appended node.
    */
    template <class T>
    dnode<T>* dnode<T>::append(T& rhs){
        _next = new dnode<T>;
        _next->data = rhs;
        _next->_previous = this;
        return _next;
    }

    template <class T>
    dnode<T>* dnode<T>::insertFirst(T& rhs){
        dnode<T>* tmp = new dnode<T>;
        tmp->data = rhs;
        tmp->_next = this;
        this->_previous = tmp;
        return tmp;
    }

    template <class T>
    dnode<T>* dnode<T>::insert(T& rhs){
        // Insert into the list
        dnode<T>* tmp = _next;
        tmp->_previous = append(rhs);
        _next->_next = tmp;
        return _next;
    }

    template <class T>
    void dnode<T>::remove(){
        // Remove itself from the list
        // If it is head
        if( _previous == nullptr ){
            if( _next != nullptr ){
                _next->_previous = nullptr;
            }
        }else {
            dnode<T>* next = _next;
            if( _next != nullptr )
                _next->_previous = _previous;
            _previous->_next = next;
        }
        delete this;
    }

    /**
    * @brief Accesses the previous node
    *
    * @tparam T
    *
    * @return a pointer to the previous node
    */
    template <class T>
    dnode<T>* dnode<T>::previous() const{
        return _previous;
    }

    /**
    * @brief Accesses the next node
    *
    * @tparam T
    *
    * @return a pointer to the next node
    */
    template <class T>
    dnode<T>* dnode<T>::next() const{
        return _next;
    }
}

#endif
