#pragma once
#include "GameState.h"
#include <stack>

using namespace std;

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	// use for one-way only state changes (ex. main menu to main state)
	void setState(const string &s);
	map <string, GameState*> STATES_;

	string get_CurrentStateName() const;
	GameState* get_CurrentState();
	void initStates();

	void fromMainStateToGasMainMenu ();

	void fromGasMainMenuToMainState ();
	void fromGasMainMenuToFillMenu ();
	void fromGasMainMenuToShopMenu();
	void fromFillMenuToGasMainMenu ();

protected:
	string currentState_;

private:
	bool gasMainMenuStartedOnce_ = false;
	bool gasFillMenuStartedOnce_ = false;
	bool ShopMenuStartedOnce_ = false;

};

