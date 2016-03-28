//------------------------------------------------------------------------------
// Fil: CommandManager.cpp
// Author: Hampus Davidsson
// Datum: 2016-02-14
//------------------------------------------------------------------------------
#include "CommandManager.h"
#include "HanoiEngine.h"
#include <fstream>
#include <sstream>
#include <iostream>

using std::cerr;
using std::endl;
//------------------------------------------------------------------------------ 
// Konstruktor 
//------------------------------------------------------------------------------ 
CommandManager::CommandManager(int nUndoLevel) :iUndoLevel(nUndoLevel) {}
//------------------------------------------------------------------------------ 
// Destruktor 
//------------------------------------------------------------------------------ 
CommandManager::~CommandManager() {
	clear();
}
//------------------------------------------------------------------------------ 
// canUndo 
//------------------------------------------------------------------------------ 
// Uppgift: Testar ifall man kan undo.
// Indata : (void)
// Utdata : (bool) - true ifall man kan undo
//------------------------------------------------------------------------------
bool CommandManager::canUndo() const {
	return (iUndoList.size() > 0);
}
//------------------------------------------------------------------------------ 
// canRedo 
//------------------------------------------------------------------------------ 
// Uppgift: Testar ifall man kan redo.
// Indata : (void)
// Utdata : (bool) - true ifall man kan redo
//------------------------------------------------------------------------------
bool CommandManager::canRedo() const {
	return (iRedoList.size() > 0);
}
//------------------------------------------------------------------------------ 
// popUndo 
//------------------------------------------------------------------------------ 
// Uppgift: Retunerar ett Command* objekt ifr�n undo listan.
// Indata : (void)
// Utdata : (Command*) - Command objektet som retuneras
//------------------------------------------------------------------------------
Command* CommandManager::popUndo() {
	Command* pCommand = iUndoList.back();
	iUndoList.pop_back();
	return pCommand;
}
//------------------------------------------------------------------------------ 
// popRedo 
//------------------------------------------------------------------------------ 
// Uppgift: Retunerar ett Command* objekt ifr�n redo listan.
// Indata : (void)
// Utdata : (Command*) - Command objektet som retuneras
//------------------------------------------------------------------------------
Command* CommandManager::popRedo() {
	Command* pCommand = iRedoList.back();
	iRedoList.pop_back();
	return pCommand;
}
//------------------------------------------------------------------------------ 
// doCommand 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r ett kommando och placerar detta sen i undo ifall kommandot
// kan utf�ra undo.
// Indata : (Command*) - Kommandot som skall utf�ras
// Utdata : (bool) - Retunerar true ifall kommandot placerades i undo listan.
//------------------------------------------------------------------------------
bool CommandManager::doCommand(Command *pCommand) {
	if (pCommand->execute() && pCommand->isUndoable()) {
		addUndo(pCommand);
		clearRedoList();
		return true;
	}
	else {
		delete pCommand;
		return false;
	}	
}
//------------------------------------------------------------------------------ 
// undo 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r undo
// Indata : (void)
// Utdata : (bool) - True ifall undo lyckades annars false.
//------------------------------------------------------------------------------
bool CommandManager::undo() {
	if (canUndo()) {
		Command* pCommand = popUndo();
		if (pCommand->unExecute()) {
			addRedo(pCommand);
		}
		else {
			delete pCommand;
		}
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------ 
// redo 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r redo
// Indata : (void)
// Utdata : (bool) - True ifall redo lyckades annars false.
//------------------------------------------------------------------------------
bool CommandManager::redo() {
	if (canRedo()) {
		Command* pCommand = popRedo();
		if (pCommand->execute()) {
			addUndo(pCommand);
		}
		else {
			delete pCommand;
		}
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------ 
// clear 
//------------------------------------------------------------------------------ 
// Uppgift: Deletar b�de undo och redo listan
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void CommandManager::clear() {
	clearUndoList();
	clearRedoList();
}
//------------------------------------------------------------------------------ 
// addUndo 
//------------------------------------------------------------------------------ 
// Uppgift: L�gger till kommando i undo listan
// Indata : (Command*) - Kommando soms kall l�ggas till
// Utdata : (void)
//------------------------------------------------------------------------------
void CommandManager::addUndo(Command* pCommand) {
	if (iUndoList.size() >= iUndoLevel) {
		delete iUndoList.front();
		iUndoList.pop_front();
	}
	iUndoList.push_back(pCommand);
}
//------------------------------------------------------------------------------ 
// addRedo 
//------------------------------------------------------------------------------ 
// Uppgift: L�gger till kommando i redo listan
// Indata : (Command*) - Kommando soms kall l�ggas till
// Utdata : (void)
//------------------------------------------------------------------------------
void CommandManager::addRedo(Command* pCommand) {
	iRedoList.push_back(pCommand);
}
//------------------------------------------------------------------------------ 
// clearUndoList 
//------------------------------------------------------------------------------ 
// Uppgift: Raderar element i undo listan
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void CommandManager::clearUndoList() {
	clearCommandList(&iUndoList);
}
//------------------------------------------------------------------------------ 
// clearRedoList 
//------------------------------------------------------------------------------ 
// Uppgift: Raderar element i redo listan
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void CommandManager::clearRedoList() {
	clearCommandList(&iRedoList);
}
//------------------------------------------------------------------------------ 
// clearCommandList 
//------------------------------------------------------------------------------ 
// Uppgift: Raderar element i en listan
// Indata : (CommandList*) - Listan vars element som skall raderas
// Utdata : (void)
//------------------------------------------------------------------------------
void CommandManager::clearCommandList(CommandList* pList) {
	CommandList::iterator it;
	for (it = pList->begin(); it != pList->end(); it++) {
		delete *it;
	}
	pList->erase(pList->begin(), pList->end());
}
//------------------------------------------------------------------------------ 
// MoveCommand 
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
// Konstruktor 
//------------------------------------------------------------------------------ 
MoveCommand::MoveCommand(HanoiEngine & p_hanoiEngine, int p_iFrom, int p_iTo,bool p_bLogg)
	: m_hanoiEngine(p_hanoiEngine), m_iFrom(p_iFrom),m_iTo(p_iTo), m_bLogg(p_bLogg){}
//------------------------------------------------------------------------------ 
// Destruktor 
//------------------------------------------------------------------------------ 
MoveCommand::~MoveCommand() {}
//------------------------------------------------------------------------------ 
// execute 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r uppdraget kommandot har.
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool MoveCommand::execute() {
	if (m_hanoiEngine.move(m_iFrom, m_iTo)) { 
		writeToFile(m_iFrom, m_iTo);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------ 
// writeToFile 
//------------------------------------------------------------------------------ 
// Uppgift: Loggar info till fil om MoveCommand
// Indata : (int p_iFrom) - Fr�n vart man flyttar
//			(int p_iTo) - Vart man flyttar.
// Utdata : (void)
//------------------------------------------------------------------------------
void MoveCommand::writeToFile(int p_iFrom, int p_iTo) {
	if (m_bLogg) { // Skall vi logga  detta ?
		std::fstream datafile;
		datafile.open(REPLAYFILENAME, std::ios::out | std::fstream::app);
		datafile << "MoveCommand " << p_iFrom << " " << p_iTo << "\n";;
		datafile.close();
	}
}
//------------------------------------------------------------------------------ 
// unExecute 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r en undo.
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool MoveCommand::unExecute() {
	writeToFile(m_iTo, m_iFrom);
	return m_hanoiEngine.move(m_iTo, m_iFrom);
}
//------------------------------------------------------------------------------ 
// isUndoable 
//------------------------------------------------------------------------------ 
// Uppgift: Retunerar ifall man kan utf�ra undo
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool MoveCommand::isUndoable() {
	return true;
}
//------------------------------------------------------------------------------ 
// readFromStream 
//------------------------------------------------------------------------------ 
// Uppgift: L�ser in information ifr�n str�mmen
// Indata : (ifstream&) - Str�mmen som h�ller i informationen
// Utdata : (void)
//------------------------------------------------------------------------------
void MoveCommand::readFromStream(std::ifstream &ifs) {
	ifs >> m_iFrom >> m_iTo;
}
//------------------------------------------------------------------------------ 
// ShowCommand 
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
// Konstruktor 
//------------------------------------------------------------------------------
ShowCommand::ShowCommand(HanoiEngine & p_hanoiEngine) : m_hanoiEngine(p_hanoiEngine) {
}
//------------------------------------------------------------------------------ 
// Destruktor 
//------------------------------------------------------------------------------
ShowCommand::~ShowCommand(){
}
//------------------------------------------------------------------------------ 
// execute 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r uppdraget kommandot har.
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool ShowCommand::execute() {
	m_hanoiEngine.show();
	return true;
}
//------------------------------------------------------------------------------ 
// unExecute 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r undo
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool ShowCommand::unExecute() {
	return true;
}
//------------------------------------------------------------------------------ 
// isUndoable 
//------------------------------------------------------------------------------ 
// Uppgift: Retunerar ifall man kan utf�ra undo
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool ShowCommand::isUndoable() {
	return false;
}
//------------------------------------------------------------------------------ 
// readFromStream
//------------------------------------------------------------------------------ 
// Uppgift: L�ser ifr�n str�mmen
// Indata : (ifstream &) - str�mmen som har informationen
// Utdata : (void)
//------------------------------------------------------------------------------
void ShowCommand::readFromStream(std::ifstream &ifs) {
}
//------------------------------------------------------------------------------ 
// ResetCommand 
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
// Konstruktor 
//------------------------------------------------------------------------------
ResetCommand::ResetCommand(HanoiEngine& p_hanoiEngine,CommandManager* p_commandMgr, int p_iDisc, bool p_bLogg) 
	: m_hanoiEngine(p_hanoiEngine),m_commandMgr(p_commandMgr), m_iDisc(p_iDisc),m_bLogg(p_bLogg) {}
//------------------------------------------------------------------------------ 
// Destruktor 
//------------------------------------------------------------------------------
ResetCommand::~ResetCommand(){}
//------------------------------------------------------------------------------ 
// execute 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r uppdraget kommandot har.
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool ResetCommand::execute() {
	m_hanoiEngine.reset(m_iDisc); // resetta hanoi.
	if (m_commandMgr != nullptr) { // Ifall m_commandMgr har v�rde delete redo och undo
		m_commandMgr->clearRedoList();
		m_commandMgr->clearUndoList();
	}
	if (m_bLogg) { // Logga inforamtion.
		std::fstream datafile;
		datafile.open(REPLAYFILENAME, std::ios::out | std::fstream::app);
		datafile << "ResetCommand " << m_iDisc << "\n";
		datafile.close();
	}
	return true;
}
//------------------------------------------------------------------------------ 
// unExecute 
//------------------------------------------------------------------------------ 
// Uppgift: Utf�r undo
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool ResetCommand::unExecute() {
	return true;
}
//------------------------------------------------------------------------------ 
// isUndoable 
//------------------------------------------------------------------------------ 
// Uppgift: Retunerar ifall man kan utf�ra undo
// Indata : (void)
// Utdata : (bool) - retunerar true ifall de gick annars false.
//------------------------------------------------------------------------------
bool ResetCommand::isUndoable() {
	return false;
}
//------------------------------------------------------------------------------ 
// readFromStream 
//------------------------------------------------------------------------------ 
// Uppgift: L�ser in information ifr�n str�mmen
// Indata : (ifstream&) - Str�mmen som h�ller i informationen
// Utdata : (void)
//------------------------------------------------------------------------------
void ResetCommand::readFromStream(std::ifstream &ifs) {
	ifs >> m_iDisc;
}
