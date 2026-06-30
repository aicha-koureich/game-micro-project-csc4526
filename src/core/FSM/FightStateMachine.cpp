#include "FightStateMachine.hpp"

FightStateMachine::FightStateMachine() {
  mFsm.add_transitions({
      {
          FightPhase::PLAYER_CHOICE,
          FightPhase::PRE_QTE,
          FightTrigger::CHOOSE_STRENGTH,
          nullptr,
          nullptr,

      },
      {
          FightPhase::PLAYER_CHOICE, 
          FightPhase::DEBUFF_CHOICE,
          FightTrigger::CHOOSE_ELOQUENCE, 
          nullptr, 
          nullptr,

      },
      {
          FightPhase::DEBUFF_CHOICE,
          FightPhase::PRE_QTE,
          FightTrigger::CHOOSE_DEBUFF_ATTACK,
          nullptr,
          nullptr,

      },
      {
          FightPhase::DEBUFF_CHOICE,
          FightPhase::PRE_QTE,
          FightTrigger::CHOOSE_DEBUFF_DEFENSE,
          nullptr,
          nullptr,

      },
      {
          FightPhase::PRE_QTE,
          FightPhase::PLAYER_CHOICE,
          FightTrigger::CANCEL,
          nullptr,
          nullptr,

      },
      {
          FightPhase::DEBUFF_CHOICE,
          FightPhase::PLAYER_CHOICE,
          FightTrigger::CANCEL,
          nullptr,
          nullptr,

      },
      {
          FightPhase::PRE_QTE,
          FightPhase::PLAYER_QTE,
          FightTrigger::START_QTE,
          nullptr,
          nullptr,

      },
      {
          FightPhase::PLAYER_QTE,
          FightPhase::RESOLUTION_PLAYER,
          FightTrigger::FINISH_QTE,
          nullptr,
          nullptr,

      },
      {
          FightPhase::PLAYER_QTE,
          FightPhase::RESOLUTION_PLAYER,
          FightTrigger::FINISH_TEXT_QTE,
          nullptr,
          nullptr,

      },
      {
          FightPhase::RESOLUTION_PLAYER,
          FightPhase::WAITING_AFTER_PLAYER,
          FightTrigger::START_ENEMY_TURN,
          nullptr,
          nullptr,

      },
      {
          FightPhase::WAITING_AFTER_PLAYER,
          FightPhase::PLAYER_DEFENSE_QTE,
          FightTrigger::START_DEFENSE_QTE,
          nullptr,
          nullptr,

      },
      {
          FightPhase::PLAYER_DEFENSE_QTE,
          FightPhase::RESOLUTION_ENEMY,
          FightTrigger::FINISH_DEFENSE_QTE,
          nullptr,
          nullptr,

      },
      {
          FightPhase::RESOLUTION_ENEMY,
          FightPhase::WAITING_AFTER_ENEMY,
          FightTrigger::FINISH_ENEMY_TURN,
          nullptr,
          nullptr,

      },
      {
          FightPhase::WAITING_AFTER_ENEMY,
          FightPhase::PLAYER_CHOICE,
          FightTrigger::NEXT_PLAYER_TURN,
          nullptr,
          nullptr,

      },
  });

}

FightPhase FightStateMachine::phase() const { return mFsm.state(); }

void FightStateMachine::reset() { mFsm.reset(); }

void FightStateMachine::chooseStrength() {
  mFsm.execute(FightTrigger::CHOOSE_STRENGTH);
}

void FightStateMachine::chooseEloquence() {
  mFsm.execute(FightTrigger::CHOOSE_ELOQUENCE);
}

void FightStateMachine::chooseDebuffAttack() {
  mFsm.execute(FightTrigger::CHOOSE_DEBUFF_ATTACK);
}

void FightStateMachine::chooseDebuffDefense() {
  mFsm.execute(FightTrigger::CHOOSE_DEBUFF_DEFENSE);
}

void FightStateMachine::startQte() { mFsm.execute(FightTrigger::START_QTE); }

void FightStateMachine::finishQte() { mFsm.execute(FightTrigger::FINISH_QTE);}

void FightStateMachine::finishTextQte() { mFsm.execute(FightTrigger::FINISH_TEXT_QTE); }

void FightStateMachine::startEnemyTurn() { mFsm.execute(FightTrigger::START_ENEMY_TURN); }

void FightStateMachine::startDefenseQte() {
  mFsm.execute(FightTrigger::START_DEFENSE_QTE);
}

void FightStateMachine::finishDefenseQte() { mFsm.execute(FightTrigger::FINISH_DEFENSE_QTE); }

void FightStateMachine::finishEnemyTurn() {
  mFsm.execute(FightTrigger::FINISH_ENEMY_TURN);
}

void FightStateMachine::nextPlayerTurn() {
  mFsm.execute(FightTrigger::NEXT_PLAYER_TURN);
}


void FightStateMachine::cancel() { mFsm.execute(FightTrigger::CANCEL); }
