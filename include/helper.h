//*******************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-07
// Project 5
// Sources: None
//
//*******************************************************************
#ifndef __HELPER_H__
#define __HELPER_H__

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

namespace dpost{
void print_menu();
void get_exerciseJournal_info( exerciseJournal& );
int get_positive_input( dstring const& message );
template <class T>
void get_input_and_clear( T& ); 
template <class T>
void print_width( const T&, int );

template <class T>
void print_width( const T& value, int width ){
    cout << setw(width) << value;
}

template <class T>
void get_input_and_clear( T& input ){
    cin >> input;
    if( cin.fail() ){
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        cout << "Input was invalid, please try again:" << endl;
        get_input_and_clear( input );
    }
    // Check if there is more input left in stream
    cin.unget(); // Put a char back so we can ignore without waiting for input
    cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // Clear input stream
}
}
#endif
