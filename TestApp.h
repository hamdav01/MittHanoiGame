//------------------------------------------------------------------------------
// Fil: TestApp.h
// Desc: En klass som representerar är en meny som agerar utefter
// användarens val.
// Author: Hampus Davidsson
// Datum: 2016-02-17
//------------------------------------------------------------------------------
#ifndef TESTAPP_H
#define TESTAPP_H
#include "CommandManager.h"
#include "HanoiEngine.h"
using std::cin;
using std::cout;
using std::endl;
class TestApp {
private:
	enum class menu {
		NEWGAME, REPLAY, REDO, UNDO, MOVE, RESET, EXIT
	};
	void startMenu();
	void gamePlayMenu();
	void startMove();
	void doMenuChoice(const menu& p_menuChoice);
	void createNewGame();
	int getMenuOption(int p_iMin, int p_iMax);
	void startReplay();
public:
	TestApp();
	~TestApp();
	void run();
private:
	CommandManager* m_commandMgr;
	HanoiEngine m_hannoiEngine;
	menu startMenuitems[3] = { menu::EXIT,menu::NEWGAME,menu::REPLAY };
	menu gamePlayMenuItems[5] = { menu::EXIT,menu::MOVE,menu::UNDO,menu::REDO,menu::RESET };
};

#endif
