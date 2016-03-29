/*
  File:   HanoiEngine.h
  Topic:  Class HanoiEngine manages and displays moves of
          'Towers of Hanoi'. The towers are numbered from 1 to 3,
          left to right.
  Last change:   Mars 2016 / Hampus
*/

#ifndef HanoiEngine_H
#define HanoiEngine_H

#include <iostream>
#include <deque>

using std::cout;
using std::ostream;
using std::deque;

class HanoiEngine {

public:
       HanoiEngine(int aDiscs=5); // aDiscs is the nr of discs
       ~HanoiEngine() { }

       // Display the towers with the discs
       void show(ostream &aStrm=cout);

       // Move a disc from tower aFrom to tower aTo.
       // A successful move returns true
       bool move(int aFrom, int aTo);

       // Reset the game, start with aDiscs discs
       void reset(int aDiscs);

       // Is the game successfully finished?
       bool isDone();

private:
        enum {T1,T2,T3};  // Index in iTowers
        int iDiscs;
        int iMoves;
        deque<int> iTowers[3];
};

#endif
