//------------------------------------------------------------------------------
// Fil: Command.h
// Desc: Abstrakt klass som representerar ett interface för ett kommando.
// Author: Hampus Davidsson
// Datum: 2016-02-13
//------------------------------------------------------------------------------
#ifndef COMMAND_H
#define COMMAND_H
#include <fstream>
class Command {
public:
	virtual ~Command() = default;
	virtual bool execute() = 0;
	virtual bool unExecute() = 0; // undo
	virtual bool isUndoable() = 0;
	virtual void readFromStream(std::ifstream& ifs) = 0;
};
#endif
