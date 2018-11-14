//*****************************************************************
//
// Author: David Post
// Class: CS162
// Project 5
// Date: 2017-08-07
// Sources: None
//
//*****************************************************************
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

#include "include/dstring.h"
#include "include/exercise.h"
#include "include/exerciseJournal.h"
#include "include/dlist.h"
#include "include/helper.h"

using namespace std;
using namespace dpost;

enum programstate{
    ADD_EXERCISE = 'a',
    REMOVE_EXERCISE = 'r',
    LIST_EXERCISES = 'i',
    LOAD_EXERCISES = 'l',
    WRITE_EXERCISES = 'w',
    SEARCH_EXERCISES = 's',
    CHANGE_ATHLETE_INFO = 'c',
    PRINT_ATHLETE_INFO = 'p',
    QUIT = 'q'
};


int main( int /*argc*/, char ** /*argv*/ ){
    exerciseJournal journal{};

    cout << "Welcome to our Exercise tracking program!" << endl;
    cout << "To start, we will create an athletic profile for you!" << endl;
    cout << "Do not enter any spaces as anything after the space will be discarded." << endl << endl;

    journal.promptAthleteName();

    // Start main loop execution
    while( true ){
        char command = 0;
        int count = 0;
        print_menu();

        get_input_and_clear( command );
        cout << endl; // give some space after the menu

        if( command >= 'A' && command <= 'Z' ){
            command += 32; // to lower
        }

        switch( command ){
            case ADD_EXERCISE:
                journal.add( );
                break;
            case REMOVE_EXERCISE:
                journal.remove( );
                break;
            case LIST_EXERCISES:
                journal.listAll( );
                break;
            case LOAD_EXERCISES:
                count = journal.loadData( );
                cout << "File loaded. " << count << " exercises added to list. " << endl << endl;
                break;
            case WRITE_EXERCISES:
                journal.writeData();
                break;
            case SEARCH_EXERCISES:
                count = journal.search( );
                cout << "Total matching exercises found: " << count << endl;
                break;
            case CHANGE_ATHLETE_INFO:
                journal.promptAthleteName( );
                break;
            case PRINT_ATHLETE_INFO:
                journal.printSummary( );
                break;
            case QUIT:
                journal.writeData( );
                journal.listAll( );
                journal.printSummary( );
                return 0;
            default:
                cout << "Invalid input, please try again" << endl;
                break;
        }

    }
    return 0;
}

