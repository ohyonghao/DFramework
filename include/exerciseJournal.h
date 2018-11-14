//*******************************************************************
//
// Author: David Post
// Class: CS 162
// Date: 2017-08-07
// Project 5
// Source: Effective C++ by Scott Meyer, Item 3, pg 37
//
//*******************************************************************

#ifndef __EXERCISE_JOURNAL_H__
#define __EXERCISE_JOURNAL_H__
#include "dstring.h"
#include "dlist.h"
#include "exercise.h"

namespace dpost{
    /**
    * @brief Contains information about an exerciseJournals exercises with running totals of 
    * time spent and calories burned.
    */
    class exerciseJournal{
        public:
            exerciseJournal();
            ~exerciseJournal();

            const dstring& name() const;
            int totalCalories() const;
            int totalTime() const;
            int search() const;
            void listAll(bool numbers = false) const;
            void setName( const dstring& rhs );
            int loadData();
            void add();
            bool remove();
            void writeData();
            void printSummary();
            void printExercise( exercise* );
            void promptAthleteName();
            /**
            * @brief The list of exercises the exerciseJournal has done
            *
            * @return a reference to const of the list of exercises
            */
            inline const dlist<exercise>& exerciseList() const{ return _exercise; }
        private:
            dstring _name;
            int _totalCalories{0};
            int _totalTime{0};
            dlist<exercise> _exercise;
            /**
            * @brief only used internally
            */
            dstring _filename;
            void addExercise( exercise *rhs );
            void addExercise( exercise &rhs );
            void list( const dlist<exercise>& list, bool numbers = true ) const;
    };
}
#endif
