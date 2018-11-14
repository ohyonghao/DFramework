//*****************************************************************
//
// Author: David Post
// Class: CS162
// Date: 2017-08-08
// Project 5
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
#include "helper.h"

using namespace std;

namespace dpost{
/**
* @brief Prints the main menu
*/
void print_menu(){
    cout << endl;
    cout << "Please make a selection:" << endl;
    cout << "[A]dd Exercise" << endl;
    cout << "[R]emove Exercise" << endl;
    cout << "L[i]st Exercises" << endl;
    cout << "[L]oad Exercises From File" << endl;
    cout << "[W]rite Exercises To File" << endl;
    cout << "[S]earch Exercise List By Name" << endl;
    cout << "[C]hange Athlete Information" << endl;
    cout << "[P]rint Athlete Information" << endl;
    cout << "[Q]uit" << endl;
    cout << "Selection[a/r/i/l/w/s/c/p/q]: ";
}

int get_positive_input( dstring const& message ){
    int positive;
    bool verified = false;

    do{
        get_input_and_clear( positive );

        if( positive > 0 ){
            verified = true;
        }else{
            cout << message << endl;
        }
    }while( !verified );
    
    return positive;
}


}
