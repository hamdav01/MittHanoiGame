/*
  File:   HanoiEngine.cpp
  Topic:  Implementation of class HanoiEngine
  Date:   February 2006 / orjste
*/

#include <iostream>
#include <iomanip>
#include "HanoiEngine.h"

using std::setw;
using std::right;
using std::endl;

HanoiEngine::HanoiEngine(int aDiscs)
:iDiscs(aDiscs),iMoves(0)
{
        for(int i=iDiscs; i>0; --i)
           iTowers[0].push_front(i);
}


void HanoiEngine::show(ostream &aStrm) {
   aStrm << '\n';
   for(int row=0; row<iDiscs; ++row) {
        for(int tower=0; tower<3; ++tower) {
           if((iDiscs-row) > iTowers[tower].size())
             aStrm << '\t' << setw(2) << right << '.';
           else  {
             int index = row-iDiscs+iTowers[tower].size();
             aStrm << '\t' << setw(2) << right << iTowers[tower][index];
           }
        }
        aStrm << '\n';
   }
   aStrm << "\t==\t==\t==\n";
   aStrm << "\tT1\tT2\tT3\tmoves: " << iMoves << '\n' << endl;
   if(isDone())
     aStrm << "Congratulations - you did it!" << endl;
}

bool HanoiEngine::move(int aFrom, int aTo) {
	if (aFrom > 3 || aTo > 3) {
		return false;
	}
   // Is this move legal?
     if(iTowers[aFrom-1].size() &&
   	(!iTowers[aTo-1].size() || iTowers[aFrom-1].front() < iTowers[aTo-1].front())) {
   // Yes!
   	iTowers[aTo-1].push_front(iTowers[aFrom-1].front());
    	iTowers[aFrom-1].pop_front();
    	++iMoves;
    	return true;
   }
   // No!
   return false;
}


void HanoiEngine::reset(int aDiscs) {
    for(int i=0; i<3; ++i)
      iTowers[i].clear();

    iDiscs = aDiscs;
    iMoves=0;
    for(int i=iDiscs; i>0; --i)
      iTowers[T1].push_front(i);
}


bool HanoiEngine::isDone() {
    // All discs at the second tower?
    return iTowers[T2].size() == iDiscs;
}
