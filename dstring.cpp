//**************************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-08
// Project 5
// Reference: http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/extraction.html
//
//**************************************************************************

#include "include/dstring.h"

namespace dpost{
    /**
    * @brief Constructs an empty dstring
    *
    * Initializes a dstring to size 0 with default BUFFERSIZE and a null terminator.
    * 
    */
    dstring::dstring():
    _bufferSize( BUFFERSIZE ),
    _string( new char[_bufferSize] ),
    _size( 0 ),
    _totalSize( _bufferSize+_size )
    {
        _string[0] = '\0';

    }

    // NOT SAFE for chars without null termination
    /**
    * @brief Constructs a dstring that is initialized from a null terminated cstring
    *
    * @pre cstring must be null terminated
    * @param rhs is a const pointer to char that is assumed null terminated
    */
    dstring::dstring( char const *rhs ):
    _bufferSize( BUFFERSIZE ),
    _string( nullptr ), // point to nullptr to start with as we have something to do in the ctor
    _size( 0 ),
    _totalSize( 0 ) // Set this after calculating size
    {
        // Find the size of the char
        int count = 0;
        while( rhs[count] != '\0' ){
            count++;
        }
        _size = count;
        _totalSize = _size + _bufferSize;
        _string = new char[ _totalSize ];
        for( int i = 0; i <= count; i++ )
            _string[i] = rhs[i];
    }

    /**
    * @brief Constructs a copy of a dstring object
    *
    * During contsruction the total size is the same as the original object.  It may later be decided
    * to resize the object to be size + bufferSize as to not waste room.
    *
    * @param rhs is a reference to const that is copied
    */
    dstring::dstring( const dstring& rhs ):
    _bufferSize( BUFFERSIZE ),
    _string( new char[rhs._totalSize] ),
    _size( rhs._size ),
    _totalSize( rhs._totalSize )
    {
       for( int i=0; i <= _size; i++ ){
            _string[i] = rhs[i];
       }

    }

    /**
    * @brief Copies the rhs dstring
    *    
    * @param rhs is a reference to const dstring to be copied
    *
    * @return a reference to self
    */
    dstring& dstring::operator=( dstring const &rhs ){
        if( &rhs != this ){ // check if assigning to self
            // Check the size of the incoming object
            if( rhs._size > _totalSize ){
                resize( rhs._size + _bufferSize, false );
            }
            _size = rhs._size;
            for( int i=0; i <= _size; i++ ){
                _string[i] = rhs._string[i]; // Copy String from other string
            }
        }
        return *this;
    }

    /**
    * @brief Appends single character to string
    *
    * @param c is a single char
    *
    * @return reference to dstring
    */
    dstring& dstring::operator+=( char const c ){
        if( _size + 1 >= _totalSize ){
            resize( _totalSize + _bufferSize );
        }
        _string[_size] = c;
        _size++;
        _string[_size] = '\0';
        return *this;
    }

    /**
    * @brief Appends a dstring to current object
    *
    * @param rhs is a const reference to the dstring to be copied
    *
    * @return a reference to self
    */
    dstring& dstring::operator+=( dstring const& rhs ){
        if( _size + rhs._size >= _totalSize ){
            resize( _size + rhs._size + _bufferSize );
        }
        for( int i = 0; i <= rhs._size; i++ )
            _string[_size + i] = rhs._string[i]; // Copy String from other string
        _size += rhs._size;
        return *this;
    }

    /**
    * @brief Appends single character to string
    *
    * @param c is a single char
    *
    * @return reference to self
    */
    dstring& dstring::append( char const c ){
        return *this += c;
    }

    /**
    * @brief Appends a dstring to current object
    *
    * @param rhs is a const reference to the dstring to be copied
    *
    * @return a reference to self
    */
    dstring& dstring::append( dstring const &rhs ){
        return *this = *this + rhs;    
    }

    /**
    * @brief Streams input to be captured in the dstring
    *
    * @param lhs an istream object to read from
    * @param rhs a dstring object to write to
    *
    * @return a reference to the istream object
    */
    std::istream& operator>>( std::istream& lhs, dstring& rhs ){
        char read;
        rhs.clear(); // First reset the string
        std::istream::sentry dsentry( lhs );
        if( dsentry )
        {
            while( lhs.good() ){
                read = lhs.get();
                if( std::isspace( read, lhs.getloc() ) ){
                    break;
                }
                rhs += read;
            }
        }
        return lhs;    
    }
    
    /**
    * @brief clears the string setting the first element to the null terminator and size to 0.
    *
    * This does not change the size of already allocated space.  If shrinking is desired this
    * can be accomplished with the resize function.
    */
    void dstring::clear(){
        _string[0] = '\0';
        _size = 0;
    }

    /**
    * @brief Gets a line of input from an istream object and writes into a dstring
    *
    * Input is read until the default new line character is read, or the deliminator that was
    * passed is encountered and eats the deliminator.
    *
    * @param is is an istream object to read from
    * @param rhs is a reference to a dstring object
    * @param delim is a character to use as a deliminator to stop input.
    * @param noskipws is a boolean set to false by default and tells the sentry whether
    * or not to skip initial whitespace before input
    */
    void dgetline( std::istream& is, dstring& rhs, char delim, bool noskipws ){
        char read;
        rhs.clear(); // First reset the string
        std::istream::sentry dsentry( is, noskipws );
        if( is ){
            while( is.good() ){
                read = is.get();
                if( read == delim ){
                    break;
                }
                rhs += read;
            }
        }
    }

    /**
    * @brief Compares a null terminated cstring to the current string
    *
    * @pre the cstring must be null terminated
    *
    * @param rhs is a null terminated cstring
    *
    * @return true or false if the string is exactly the same.
    */
    /*int dstring::compare( const char* rhs ) const{

        bool result = true;
        for( int i = 0; i < _size && result; ++i ){
            // Check if current character is equal
            if( _string[i] != rhs[i] ){
                result = false;
            }
            // Check if rhs hits end of string before this
            if( rhs[i] == '\0' && _string[i] != '\0' ){
                result = false;
            }
        }
        // everything checks out, our strings match
        return result;
    }*/

    /**
    * @brief Compares if a single character matches the dstring
    *
    * @param rhs is a single character to compare
    *
    * @return true if the character matches the dstring, false if it does not, or if the dstring
    * size is greater than 1.
    */
    int dstring::compare( const char rhs ) const{
        int result = 0;
        if( _size != 1 ){
            result = ( _size == 0 ) ? -1 : 1;
        }else if( _string[0] != rhs ){
            result = _string[0] < rhs ? -1 : 1;
        }
        return result;
    }

    int dstring::compare( const dstring& rhs, bool caseSensitive ) const{
        if( !caseSensitive ){
        // tolower the strings
        dstring lower(this->tolower());
        dstring lower2(rhs.tolower());
        // call compare
        return lower.compare(lower2);
        }else{
            return compare( rhs );
        }

    }
    dstring dstring::tolower() const{
        dstring result(*this);
        for( int i = 0; i < _size; ++i ){
            if( _string[i] > 64 && _string[i] < 91 ){
                result._string[i] = _string[i] + 32;
            }else{
                result._string[i] = _string[i];
            }
        }
        return result;
    }

    /**
    * @brief Compares a dstring with another dstring for a char by char match of equality
    *
    * @param rhs is a dstring to compare
    *
    * @return true if the strings match, not including extra allocated space.  False if the
    * strings do not match.
    */
    int dstring::compare( const dstring& rhs) const{
        int result = 0;
        for( int i = 0; i < _size && i < rhs._size && !result; ++i ){
            // Check if current character is equal
            if( _string[i] != rhs._string[i] ){
                result = ( _string[i] < rhs._string[i] ) ? -1 : 1;
            }
        }

        // If everything is equal up to this point, check if the other string is longer
        if( !result )
            result = ( _size < rhs._size ) ? -1 : 1;
        // everything checks out, our strings match
        return result;
    }

    /**
    * @brief Checks for equality of the string
    *
    * This is limited to only the characters of the string itself and does not include other
    * elements such as the buffersize or the unused allocated space.
    *
    * @param rhs is the string to be compared to
    *
    * @return true if the strings are the same, including length, or false if they differ.
    */
    bool dstring::operator==( dstring const& rhs ) const{
        int result = true;
        if( _size != rhs._size ){
            result = false;
        }
        for( int i = 0; i < _size && result ; i++ ){
            if( _string[i] != rhs._string[i] )
                result = false;
        }
        // Everything checks out
        return result;
    }

    /**
    * @brief Destroys the dstring and unallocates the array.
    */
    dstring::~dstring(){
        delete [] _string;
    }

    /**
    * @brief Requests to expand the extra allocated space to newBuffer
    *
    * If the requested size is less than the current extra allocated space then nothing is done.
    *
    * @param newBuffer is the new size beyond the current size of the string to be allocated.
    */
    void dstring::reserve( int newBuffer ){
        // Change size of buffer
        _bufferSize = newBuffer;
        if( _size + _bufferSize > _totalSize ){
            resize( _size + _bufferSize );
        }
    }

    /**
    * @brief Resizes the dstring to the newsize with an option to copy
    *
    * @post the string will be null terminated.  If the new size is less than the current
    * string then the string will be truncated to the size requested.
    *
    * @param newsize is the new size that is being requested
    * @param copy is a flag to copy the old string.  If set to false then size is set to 0
    * and the first element is set to the null terminator.
    */
    void dstring::resize( int newsize, bool copy ){
        _totalSize = newsize;
        // Perform a copy on write maneuver
        char *temp = new char[_totalSize];
        if( copy ){
            for( int i = 0; i < _size; i++ ){ // skipping '\0'
                temp[i] = _string[i];
            } 
            temp[_size] = '\0'; // make sure that string is null terminated
        }else{
            temp[0] = '\0'; // no copy done, make sure first char is null
        }
        delete [] _string;
        _string = temp;
    }

    /**
    * @brief Concatenates a string and a single char
    *
    * @param lhs is a dstring to be appended to
    * @param rhs is a single char to append to the dstring
    *
    * @return a dstring with the char concatenated to the dstring
    */
    dstring operator+( dstring const& lhs, char const rhs ){
        dstring result(lhs);

        result += rhs;
        return result;
    }

    /**
    * @brief Concatenates two strings
    *
    * @param lhs is the dstring to be appended to
    * @param rhs is the dstring to append
    *
    * @return a dstring with both strings concatenated together
    */
    dstring operator+( dstring const& lhs, dstring const& rhs ){
        dstring result(lhs);

        result += rhs;
        return result;
    }
}

