//------------------------------------------------------------------------------
// Fil: CommandManager.h
// Desc: Klasser som representerar kommandon finns här och klassen CommandoManager
// som håller i en mängd Commandos för att kunna utföra undo och redo.
// Author: Hampus Davidsson
// Datum: 2016-02-14
//------------------------------------------------------------------------------
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include "Command.h"
#include <list>
#include <memory>
class HanoiEngine;
const std::string REPLAYFILENAME = "Hanoi.log";
class CommandManager {
private:
	typedef std::list<Command*> CommandList;
	CommandList iUndoList;
	CommandList iRedoList;
	int iUndoLevel;
	Command* popUndo();
	Command* popRedo();
	void clear();
	void clearCommandList(CommandList* pList);
	void addUndo(Command* pCommand);
	void addRedo(Command* pCommand);
public:
	CommandManager(int nUndoLevel = 100);
	~CommandManager();
	bool doCommand(Command* pCommand);
	bool canUndo() const;
	bool canRedo() const;
	bool undo();
	bool redo();
	void clearUndoList();
	void clearRedoList();
};
//------------------------------------------------------------------------------ 
// MoveCommand 
//------------------------------------------------------------------------------ 
// Desc: Commando Klass för att flytta i mellan torn.
//------------------------------------------------------------------------------
class MoveCommand : public Command {
private:
	HanoiEngine& m_hanoiEngine;
	int m_iFrom, m_iTo;
	void writeToFile(int p_iFrom,int p_iTo); // logga till fil
	bool m_bLogg; // skall de loggas?
public:
	MoveCommand(HanoiEngine& p_hanoiEngine, int p_iFrom=0, int p_iTo=0, bool p_bLogg = true);
	~MoveCommand();
	bool execute() override;
	bool unExecute() override;
	bool isUndoable() override;
	void readFromStream(std::ifstream& ifs) override;
};
//------------------------------------------------------------------------------ 
// ShowCommand 
//------------------------------------------------------------------------------ 
// Desc: Visa upp hanoiengine utseende
//------------------------------------------------------------------------------
class ShowCommand : public Command {
private:
	HanoiEngine& m_hanoiEngine;
public:
	ShowCommand(HanoiEngine& p_hanoiEngine);
	~ShowCommand();
	bool execute() override;
	bool unExecute() override;
	bool isUndoable() override;
	void readFromStream(std::ifstream& ifs) override;
};
//------------------------------------------------------------------------------ 
// ResetCommand 
//------------------------------------------------------------------------------ 
// Desc: Resetta hanoiengine.
//------------------------------------------------------------------------------
class ResetCommand : public Command {
private:
	HanoiEngine& m_hanoiEngine;
	CommandManager* m_commandMgr; // Måste kunna resetta cmdmanager.
	int m_iDisc;
	bool m_bLogg; // Skall de loggas?
public:
	ResetCommand(HanoiEngine& p_hanoiEngine, CommandManager* p_commandMgr,int p_iDisc=5,bool p_bLogg=true);
	~ResetCommand();
	bool execute() override;
	bool unExecute() override;
	bool isUndoable() override;
	void readFromStream(std::ifstream& ifs) override;
};
#endif

