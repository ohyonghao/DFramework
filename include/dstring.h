//*******************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-08
// Project 5
// Sources: None
//
//*******************************************************************

#ifndef __DSTRING_H__
#define __DSTRING_H__

#include <iostream>

namespace dpost{
    /**
    * @brief An implementation of a string class
    *
    * This class uses the same public interface as the std::string class, but is my own implementation.
    * The class works by allocating a buffered area defined as the const BUFFERSIZE.  Characters can be
    * added to the string without reallocating space until it reaches the buffer size.  Once the buffer
    * is used up a new char string is allocated with the current string size plus the buffer size, and
    * the old string is copied over.
    *
    * The class maintains a null termination of the string, but does not include the null terminator
    * as part of the size.
    *
    * In the case of anticipating a lot of room being needed one can request to allocate enough size to
    * start with as to avoid copying the string many times.
    *
    * In future renditions the class may allow for changing the size of the default buffer.
    */
    class dstring{
        public:
            dstring();
            dstring( char const *c );
            dstring( const dstring& rhs );
            ~dstring();

            dstring& operator=( dstring const& rhs );
            /**
            * @brief Not Implemented
            *
            * @param rhs
            *
            * @return 
            */
            dstring& operator=( char const* rhs );
            dstring& operator+=( char const rhs );
            dstring& operator+=( dstring const& rhs );
            dstring& append( char const rhs );
            dstring& append( dstring const& rhs );

            /**
            * @brief convert dstring to cstring
            *
            * @return a constant pointer to a const cstring
            */
            inline operator const char * const() const{ return _string; }

            friend std::istream& operator>>( std::istream& lhs, dstring& rhs );

            /**
            * @brief The size of the string
            *
            */
            inline int size() const{ return _size; }
            /**
            * @brief The length of the string, same as size()
            *
            */
            inline int length() const{ return _size; }
            /**
            * @brief The capacity of the string, including unused allocated space.
            *
            */
            inline int capacity() const{ return _totalSize; }
            void reserve( int size );
            void clear(); // deletes string
            /**
            * @brief Tells if the string is empty
            */
            inline bool empty() const{ return _size == 0; }
            /**
            * @brief Not Implemented
            */
            inline void shrink_to_fit(){}

            /**
            * @brief Index accessor
            *
            * @pre pos is within bounds of string
            * @param pos is the position to return
            *
            * @return reference to char at position pos
            */
            inline char& operator[]( int pos ){ return _string[pos]; }
            /**
            * @brief Index accessor for const
            *
            * @pre pos is within bounds of string
            * @param pos is the position to return
            *
            * @return reference to const char at position pos
            */
            inline const char& operator[]( int pos ) const{ return _string[pos]; }
            /**
            * @brief Index accessor for
            *
            * @pre pos is within bounds of string
            * @param pos is the position to return
            *
            * @return reference to char at position pos
            */
            inline char& at( int pos ){ return _string[pos]; }
            /**
            * @brief Index accessor for const
            *
            * @pre pos is within bounds of string
            * @param pos is the position to return
            *
            * @return reference to const char at position pos
            */
            inline const char& at( int pos ) const{ return *this[pos]; }
            /**
            * @brief Returns a reference to the last character in the string
            */
            inline char& back(){ return _string[_size]; }
            /**
            * @brief Returns a reference to const to the last character in the string
            */
            inline const char& back() const{ return _string[_size]; }
            /**
            * @brief Returns a reference to the first character in the string
            */
            inline char& front(){ return _string[0]; }
            /**
            * @brief Returns a reference to const to the first character in the string
            */
            inline const char& front() const{ return _string[0]; }

            int compare( const dstring& rhs ) const;
            int compare( const dstring& rhs, bool caseSensitive ) const;
            int compare( const char* rhs ) const;
            int compare( const char rhs ) const;
            bool operator==( const dstring& rhs ) const;

            dstring tolower() const;

        private:
            /**
            * @brief default amount of buffer to allocate
            */
            static const int BUFFERSIZE = 15;
            /**
            * @brief Contains the amount of extra space that will be set aside
            * in the array for expansion whenever the array is resized
            */
            int _bufferSize;
            /**
            * @brief A pointer to the actual string array
            */
            char* _string;
            /**
            * @brief The current used size of the string excluding the null
            * terminator
            */
            int _size;
            /**
            * @brief The total size of the string array including any unused
            * buffer
            */
            int _totalSize;
            
            void resize( int newsize, bool copy = true );
    };
    dstring operator+( dstring const& lhs, char const rhs );
    dstring operator+( dstring const& lhs, dstring const& rhs );
    void dgetline( std::istream& is, dstring& rhs, char delim = '\n', bool noskipws = false );
}
#endif
