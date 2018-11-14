//*******************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-07
// Project 5
// Sources: None
//
//*******************************************************************

#include "include/dstring.h"
#include "include/exerciseJournal.h"
#include "include/dnode.h"
#include "include/helper.h"
#include <fstream>
#include <cstdlib>

using namespace std;

namespace dpost{
    /**
    * @brief Construct an empty exerciseJournal object
    */
    exerciseJournal::exerciseJournal():
    _name(),
    _exercise(),
    _filename()
    {

    }

    /**
    * @brief Destroys an exerciseJournal object
    */
    exerciseJournal::~exerciseJournal(){
    }

    /**
    * @brief The athletes name
    */
    const dstring& exerciseJournal::name() const{
        return _name;
    }

    /**
    * @brief Total calories burned
    */
    int exerciseJournal::totalCalories() const{
        return _totalCalories;
    }

    /**
    * @brief Total time spent exercising
    */
    int exerciseJournal::totalTime() const{
        return _totalTime;
    }

    /**
    * @brief Sets the athletes name
    */
    void exerciseJournal::setName( const dstring& rhs ){
        _name = rhs;
    }

    /**
    * @brief Goes through a user prompt to add a new exercise to the journal
    *
    * @post the exerciseJournal will have one more exercise if the user chooses to save their input
    */
    void exerciseJournal::add( ){
        dstring input;
        int time_cal;
        bool verified = false; // var used when verifying input

        exercise * e = new exercise;

        // Name of exercise
        cout << "Please enter the name of your exercise: " << endl;
        dgetline( cin, e->name );

        // Time spent on exercise
        cout << "Please enter the time spent exercising: " << endl;
        time_cal = get_positive_input( dstring("Time can only be entered as a positive value.  Please try again.") );
        e->time = time_cal;

        // Calories burned
        cout << "Please enter the calories you burned: " << endl;
        time_cal = get_positive_input( dstring("Calories can only be entered as a positive value.  Please try again.") );
        e->calories = time_cal;

        // Heart Rate
        cout << "Please enter your max heart rate during exercise: " << endl;
        time_cal = get_positive_input( dstring("Heart Rate can only be entered as a positive value.  Please try again.") );
        e->hr = time_cal;

        // Date
        cout << "Please enter the date for this exercise: " << endl;
        dgetline( cin, e->date );

        // Notes
        cout << "Please enter any notes for this exercise: " << endl;
        dgetline( cin, e->comment, '\n', true ); // include white spaces for blank logs

        cout << "You entered the following: " << endl;
        printExercise( e );

        do{
            cout << "Is this correct? [y/n]: ";
            input.clear(); // clear input string
            get_input_and_clear( input );

            if( input.compare( 'y' ) == 0 ){
                addExercise( e );
                cout << "Exercise has been recorded." << endl;
                verified = true;
            }else if( input.compare( 'n' ) == 0 ){
                cout << "Exercise has NOT been recorded." << endl;
                verified = true;
                delete e;
            }
        }while( !verified );
    }

    bool exerciseJournal::remove(){
        // Remove script
        // List everything, but we need to append a number
		dstring input;
        int num = -1;
        bool verified = false;

        // First, get the search term
		listAll( true );
        cout << "Enter the exercise you wish to delete for: ";
        dgetline( cin, input );
        num = atoi(input) - 1; // We print the numbers starting from 1

        if( num > _exercise.size() ){
            cout << "Exercise does not exist, please try again" << endl;
        }
        // Confirm deletion
        printExercise(&_exercise[num]);
        do{
            cout << "Are you sure you want to delete this exercise? [y/n]: ";
            input.clear(); // clear input string
            get_input_and_clear( input );

            if( input.compare( 'y' ) == 0 ){
                _exercise.remove(num);
                cout << "Exercise has been removed." << endl;
                verified = true;
            }else if( input.compare( 'n' ) == 0 ){
                cout << "Exercise has NOT been removed." << endl;
                verified = true;
            }
        }while( !verified );
        return verified;
    }

    /**
    * @brief Adds an exercise to the exerciseJournals log
    *
    * @post The exercise passed to exerciseJournal will be managed by its internal list and destroyed
    * when exerciseJournal goes out of scope.
    * Totals for Calories and Time are updated with the information from exercise.  If exercise
    * is changed there is no way for exerciseJournal to know that the totals are now inaccurate.
    *
    * @param rhs is a pointer to the exercise
    */
    void exerciseJournal::addExercise( exercise *rhs ){
        _totalCalories += rhs->calories;
        _totalTime += rhs->time;
        _exercise.insert( rhs );
    }

    /**
    * @brief Adds an exercise to the exerciseJournals log
    *
    * @post The exercise passed to exerciseJournal will be copied to its internal list
    * Totals for Calories and Time are updated with the information from exercise. 
    *
    * @param rhs is a reference to an exercise
    */
    void exerciseJournal::addExercise( exercise& rhs ){
        addExercise( &rhs );
    }

    /**
    * @brief Prompts user for file to load data from
    *
    * @post sets an internal filename to save to as default
    *
    * @return the number of items loaded
    */
    int exerciseJournal::loadData( ){
        // Load exercises from file
        dstring input;
        ifstream file;
        int index = 0;
        
        do{
            cout << "Enter the name of the file you want to load: ";
            get_input_and_clear( _filename );
            file.open( _filename );
            if( !file.is_open( ) ){
                cout << "File does not exist, please try again. " << endl;
            }
        }while( !file.is_open() );


        while( !file.eof() ){
            exercise *e = new exercise;
            dgetline( file, e->name, ',' );
            dgetline( file, e->date, ',' );
            dgetline( file, e->comment, ',' );
            dgetline( file, input, ',' );
            e->time = atoi( input );
            dgetline( file, input, ',' );
            e->calories = atoi( input );
            dgetline( file, input, '\n' );
            e->hr = atoi( input );
            if( file.fail() ){
                delete e;
            } else {
                addExercise( e );
                index++;
            }
        }
        file.close();
        return index;
    }

    /**
    * @brief Prompts for search term
    *
    * Search is case sensitive.  Prints the results before returning the count.
    *
    * @return number of results
    */
    int exerciseJournal::search( ) const{
        // do a sequential search through the list and return
        // the number of objects found.
        dstring dsearch;
        int count = 0; // number to store for how many objects are found
        dlist<exercise> matches;

        // First, get the search term
        cout << "Enter the exercise you wish to search for: ";
        dgetline( cin, dsearch );
        // search the loop adding matches to the matches node
        int size = _exercise.size();
        for( int i = 0; i < size; i++ ){
            if( _exercise[i].name == dsearch ){
                matches.insert(_exercise[i]);
                count++;
            }
        }

        // print the matches
        list( matches );
        return count;
    }

    /**
    * @brief Lists all exercises in the journal
    */
    void exerciseJournal::listAll( bool numbers ) const{
        list(_exercise, numbers);
    }
    void exerciseJournal::list( const dlist<exercise> & _list, bool numbers ) const{
        int numbers_column = 5;
        int name_column = 15;
        int time_column = 6;
        int calorie_column = 10;
        int HR_column = 8;
        int date_column = 12;
        int notes_column = 6;

        // Go through exercise list first to check if any columns
        int size = _list.size();
        for( int i = 0; i < size; i++ ){
            _list[i].name.size();
            if( _list[i].name.size() + 2 > name_column ){ // +2 so we have some buffer
                name_column = _list[i].name.size() + 2;
            }
            if( _list[i].comment.size() + 2 > notes_column ){
                notes_column = _list[i].comment.size() + 2;
            }
            if( _list[i].date.size() + 2 > date_column ){
                date_column = _list[i].date.size() + 2;
            }
        }

        // Print header
        cout << left;
        if(numbers)
            print_width("#", numbers_column);
        print_width("Date", date_column); 
        print_width("Exercise Name ", name_column); 
        print_width("Time", time_column) ;
        print_width("Calories", calorie_column) ;
        print_width("Max HR", HR_column); 
        print_width("Comments", notes_column); 
        cout << endl;

     
        // Print list of exercises
        for( int i = 0; i < size; i++ ){
            if(numbers)
                print_width( i + 1, numbers_column ); // only programmers start from 0
            print_width( _list[i].date, date_column );
            print_width( _list[i].name, name_column );
            print_width( _list[i].time, time_column );
            print_width( _list[i].calories, calorie_column );
            print_width( _list[i].hr, HR_column );
            print_width( _list[i].comment, notes_column );
            cout << endl;
        }
    }

    /**
    * @brief Writes the current exercise list to file
    *
    * @post the internal filename will be saved to the filename entered.
    *
    * Uses a prompt to ask user which file to write to, by default if a file was loaded
    * it will ask if you would like to save to this file, or enter a new one.
    */
    void exerciseJournal::writeData(){
        // Open the file for writing
        ofstream file;
        bool getNewName = false;

        if( !_filename.empty() ){
            dstring input;
            bool verified = false;
            cout << "Do you want to save to " << _filename << "? Your data will be overwritten. [y/n] ";

            do{
                input.clear();
                get_input_and_clear( input );

                if( input.compare( 'y' ) == 0 ){
                    verified = true;
                    getNewName = false;
                }else if( input.compare( 'n' ) == 0 ){
                    verified = true;
                    getNewName = true;
                }else{
                    cout << endl << "Input invalid, please try again. [y/n] ";
                }
            }while( !verified );
                    
        }
       
        do{
            if( getNewName ){
                cout << "Enter the name of the file you want to write to: ";
                get_input_and_clear( _filename );
            }
            file.open( _filename );
            if( !file.is_open( ) ){
                cout << "File does not exist, please try again. " << endl;
                getNewName = true;
            }
        }while( !file.is_open() );
        // print in file format
        int size = _exercise.size();
        for( int i = 0; i < size ; i++ ){
            file << _exercise[i].name << ','
                 << _exercise[i].date << ','
                 << _exercise[i].comment << ','
                 << _exercise[i].time << ','
                 << _exercise[i].calories << ','
                 << _exercise[i].hr << '\n';
        }
        file.close();
        cout << "Exercise information written to " << _filename << endl;
    }

    /**
    * @brief Prints the total time and calories burned
    */
    void exerciseJournal::printSummary( ){
        cout << _name
             << " Exercised for " 
             << _totalTime
             << " minutes and burned " 
             << _totalCalories << '!' << endl;

    }
    void exerciseJournal::printExercise( exercise *e ){
        cout
             << "Exercise Name: " << e->name << endl
             << "Exercise Time: " << e->time << endl
             << "Exercise Calories: " << e->calories << endl
             << "Exercise HR: " << e->hr << endl
             << "Exercise Date: " << e->date << endl
             << "Exercise Comment: " << e->comment << endl
             << endl;
    }

    /**
    * @brief Prompts for the first and last name for the journal
    */
    void exerciseJournal::promptAthleteName( ){
        dstring firstName;
        dstring lastName;
        // First get the journals name
        cout << "Please enter your first name" << endl;
        get_input_and_clear( firstName );
        cout << "Please enter your last name" << endl;
        get_input_and_clear( lastName );
        setName( firstName + ' ' + lastName );
        cout << "Thanks, " << name() << ".  Nice to meet you." << endl;
    }

}
