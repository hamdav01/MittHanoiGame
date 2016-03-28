//------------------------------------------------------------------------------
// Fil: Replay.cpp
// Author: Hampus Davidsson
// Datum: 2016-02-17
//------------------------------------------------------------------------------
#include "Replay.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <iostream>
#include <memory>

void delay(int n); // Delay execution n seconds
//------------------------------------------------------------------------------ 
// Konstruktor 
//------------------------------------------------------------------------------ 
Replay::Replay(HanoiEngine& p_hanoiEngine) :m_hanoiEngine(p_hanoiEngine) {}
//------------------------------------------------------------------------------ 
// Destruktor 
//------------------------------------------------------------------------------ 
Replay::~Replay() {}
//------------------------------------------------------------------------------ 
// doReplay 
//------------------------------------------------------------------------------ 
// Uppgift: Kör igång replay.
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void Replay::doReplay() {
	std::string tempString;
	std::ifstream m_dataFile;
	try {
		m_dataFile.open(REPLAYFILENAME, std::ios::in);
	}
	catch (std::ios_base::failure e) {
		throw std::runtime_error("Kan inte öppna filen " + REPLAYFILENAME + "\n" + e.what());
	}
	std::unique_ptr<Command> command;
	Command* showCmd = new ShowCommand(m_hanoiEngine);
	while (m_dataFile >> tempString) {
		system("cls");
		command.reset(getCommand(tempString));
		command->readFromStream(m_dataFile);
		command->execute();
		showCmd->execute();
		std::cout << std::endl << std::endl << " Kör ett " << tempString;
		delay(2);
	}	
	delete showCmd;
}
//------------------------------------------------------------------------------ 
// getCommand 
//------------------------------------------------------------------------------ 
// Uppgift: Retunerar rätt commando
// Indata : (string) - Namnet på commando som skall skapas
// Utdata : (Command*) - Commandot som skapats.
//------------------------------------------------------------------------------
Command* Replay::getCommand(std::string p_sCommandName) {
	if (p_sCommandName == "MoveCommand") {
		return new MoveCommand(m_hanoiEngine,0,0,false);
	}
	else if (p_sCommandName == "ResetCommand") {
		return new ResetCommand(m_hanoiEngine, nullptr,0,false);
	}
	else {
		return nullptr;
	}
}
//------------------------------------------------------------------------------ 
// delay 
//------------------------------------------------------------------------------ 
// Uppgift: Att skapa en paus i programmet
// Indata : (int) - hur många sekunder som skall väntas
// Utdata : (void)
//------------------------------------------------------------------------------
void delay(int n) {
	long t = time(NULL);
	while (time(NULL) < (t + n));
}