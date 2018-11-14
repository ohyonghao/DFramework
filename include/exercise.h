//*******************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-07
// Project 4
// Sources: None
//
//*******************************************************************

#ifndef __EXERCISE_H__
#define __EXERCISE_H__
#include "dstring.h"

namespace dpost{
    /**
    * @brief A structure containing information about exercises
    */
    class exercise{
        public:
        inline int CompareTo( const exercise& rhs, bool caseSensitive ) const{ return name.compare(rhs.name,
        caseSensitive); }
        inline int CompareTo( const exercise* rhs, bool caseSensitive ) const{ return name.compare(rhs->name, caseSensitive); }
        /**
        * @brief The name of the exercise
        */
        dstring name;
        /**
        * @brief A comment about the exercise
        */
        dstring comment;
        /**
        * @brief The date the exercise was done, currently stored as a string
        */
        dstring date; // store as string for now
        /**
        * @brief The amount of calories burned during exercise
        */
        int calories;
        /**
        * @brief The amount of time spent exercising
        */
        int time;
        /**
        * @brief The average heart rate during exercise
        */
        int hr;
        bool operator==( const exercise& rhs ) const{ return name == rhs.name 
                                                                  && comment == rhs.comment
                                                                  && date == rhs.date
                                                                  && calories == rhs.calories
                                                                  && time == rhs.time
                                                                  && hr == rhs.hr;}
    };
}
#endif
