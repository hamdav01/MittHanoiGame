//------------------------------------------------------------------------------
// Fil: TestApp.cpp
// Author: Hampus Davidsson
// Datum: 2016-02-17
//------------------------------------------------------------------------------
#include "TestApp.h"
#include <iostream>
#include <string>
#include "Replay.h"
//------------------------------------------------------------------------------ 
// Konstruktor 
//------------------------------------------------------------------------------ 
TestApp::TestApp(){
	m_commandMgr = new CommandManager();
}
//------------------------------------------------------------------------------ 
// Destruktor 
//------------------------------------------------------------------------------ 
TestApp::~TestApp() {
	delete m_commandMgr;
}
//------------------------------------------------------------------------------ 
// startMenu 
//------------------------------------------------------------------------------ 
// Uppgift: Visar upp startmenyn.
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void TestApp::startMenu() {
	int choice = 0;
	int maxSize = sizeof(startMenuitems) / sizeof(startMenuitems[0]);
	do {
		system("cls");
		cout << " \n /**** HANOI GAME ****/\n\n 1. Start newgame\n 2. Replay\n 0. Exit " << endl;
		choice = getMenuOption(0, maxSize-1);
		doMenuChoice(startMenuitems[choice]);
	} while (startMenuitems[choice] != menu::EXIT);
}
//------------------------------------------------------------------------------ 
// createNewGame 
//------------------------------------------------------------------------------ 
// Uppgift: Startar upp ett nytt spel.
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void TestApp::createNewGame() {
	system("cls");
	cout << endl << " Hur många discs vill du ha? ";
	int input = 0;
	cin >> input;
	cin.get();
	m_commandMgr->doCommand(new ResetCommand(m_hannoiEngine,m_commandMgr,input));
	system("cls");
}
//------------------------------------------------------------------------------ 
// gamePlayMenu 
//------------------------------------------------------------------------------ 
// Uppgift: Visar upp gameplay menyn.
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void TestApp::gamePlayMenu() {
	int choice = 0;
	int maxSize = sizeof(gamePlayMenuItems) / sizeof(gamePlayMenuItems[0]);
	do {
		system("cls");
		m_commandMgr->doCommand(new ShowCommand(m_hannoiEngine));
		cout << endl << endl << " 1. Move\n 2. Undo\n 3. Redo\n 4. Reset\n 0. Exit " << endl;
		choice = getMenuOption(0, maxSize - 1);
		doMenuChoice(gamePlayMenuItems[choice]);
	} while (gamePlayMenuItems[choice] != menu::EXIT);
}

//------------------------------------------------------------------------------ 
// getMenuOption 
//------------------------------------------------------------------------------ 
// Uppgift: Tar emot användarens input om val.
// Indata : (int p_iMin) - Minimum int man kan välja
//			(int p_iMax) - Max int man kan välja
// Utdata : (int) - Valet man gjort
//------------------------------------------------------------------------------
int TestApp::getMenuOption(int p_iMin, int p_iMax) {
	int input = 0;
	while (!(cin >> input) || input <p_iMin || input >p_iMax) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}
	cin.get();
	return input;
}
//------------------------------------------------------------------------------ 
// startMove 
//------------------------------------------------------------------------------ 
// Uppgift: Funktion som hanterar hur man flyttar i mellan två torn i hanoi.
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void TestApp::startMove() {
	int move1 = 0;
	int move2 = 0;
	do {
		system("cls");
		m_commandMgr->doCommand(new ShowCommand(m_hannoiEngine));
		if (move1 != 0) { cout << endl << endl << " Du kan inte flytta i mellan dessa torn " << endl << endl; }
		move1;
		cout << endl << "Från vilket torn vill du flytta?(1-3 är de torn som existerar)" << endl;
		while (!(cin >> move1) || move1 < 1 || move1 >3) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
		move2;
		cout << "Till vilket torn vill du flytta?(1-3 är de torn som existerar)" << endl;
		while (!(cin >> move2) || move2 < 1 || move2 > 3) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
	} while (!m_commandMgr->doCommand(new MoveCommand(m_hannoiEngine, move1, move2)));
}
//------------------------------------------------------------------------------ 
// doMenuChoice 
//------------------------------------------------------------------------------ 
// Uppgift: Meny som agerar på användarens val.
// Indata : (const menu&) - en referens till menu objekt som håller i vilket
// val användern gjort.
// Utdata : (void)
//------------------------------------------------------------------------------
void TestApp::doMenuChoice(const menu& p_menuChoice) {
	switch (p_menuChoice) {
	case menu::EXIT:  // EXIT
		break;
	case menu::NEWGAME:
		std::remove(REPLAYFILENAME.c_str()); // remove log file
		createNewGame();
		gamePlayMenu();
		break;
	case menu::REPLAY:
		startReplay();
		break;
	case menu::REDO:
		if (m_commandMgr->canRedo()) { m_commandMgr->redo(); }
		break;
	case menu::MOVE:
		startMove();
		break;
	case menu::RESET:
		createNewGame();
		break;
	case menu::UNDO:
		if (m_commandMgr->canUndo()) { m_commandMgr->undo(); }
		break;
	}
}
//------------------------------------------------------------------------------ 
// startReplay 
//------------------------------------------------------------------------------ 
// Uppgift: Startar upp replay för hanoispelet
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void TestApp::startReplay() {
	Replay replay{m_hannoiEngine};
	replay.doReplay();
	cout << endl << endl << " Replay är avslutad tryck på enter för att återgå till menyn!" << endl;
	cin.get();
}
//------------------------------------------------------------------------------ 
// run 
//------------------------------------------------------------------------------ 
// Uppgift: Funktion som startar igång programmet genom att visa upp menyn.
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
void TestApp::run() {
	startMenu();
}
//------------------------------------------------------------------------------ 
// main 
//------------------------------------------------------------------------------ 
// Uppgift: Main start för programmet.
// Indata : (void)
// Utdata : (void)
//------------------------------------------------------------------------------
int main() {
	TestApp testApp;
	testApp.run();
	system("pause");
}

