//------------------------------------------------------------------------------
// Fil: Replay.h
// Desc: Klass som representerar en replay på ett spel.
// Author: Hampus Davidsson
// Datum: 2016-02-17
//------------------------------------------------------------------------------
#ifndef REPLAY_H
#define REPLAY_H
class HanoiEngine;
#include "CommandManager.h"
#include <string>
class Replay {
public:
	Replay(HanoiEngine&);
	~Replay();
	void doReplay();
	Command* getCommand(std::string p_sCommandName);
private:
	HanoiEngine& m_hanoiEngine;
};
#endif