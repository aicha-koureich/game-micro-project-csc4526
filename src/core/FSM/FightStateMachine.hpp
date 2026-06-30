#pragma once

#include "fsm.h"
#include "FightState.hpp"

class FightStateMachine {
	public:
		FightStateMachine();

		FightPhase phase() const;
        void reset();

		void chooseStrength();
        void chooseEloquence();
        void chooseDebuffAttack();
        void chooseDebuffDefense();
        void startQte();
        void finishQte();
        void finishTextQte();
        void startEnemyTurn();
        void startDefenseQte();
        void finishDefenseQte();
        void finishEnemyTurn();
        void nextPlayerTurn();
        void cancel();

    private:
        FSM::Fsm<FightPhase, FightPhase::PLAYER_CHOICE, FightTrigger> mFsm;

};