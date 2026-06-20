#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

#include "Weapons/Sword.h"
#include "Weapons/Feather.h"


enum class GameState{MAIN_MENU, SHOP, FIGHT, WIN, DEAD, SETTING};

//FIGHT PHASE
enum class FightPhase { 
	PLAYER_CHOICE, 
	PLAYER_QTE, 
	RESOLUTION_PLAYER,
	PLAYER_DEFENSE_QTE,
	RESOLUTION_ENEMY
};

struct CircleQTE {
  float currentRadius;
  float closeSpeed;
  float targetRadius;
  float circlePerf;

};

struct SentenceQTE {
  std::string sentence;
  std::string userInput;
  float remainingTime;
  float sentencePerf;
};

class Game {
 public:
  Game();
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  void run();

 private:
  void handleMouseLeftButtonPressed();
  void processEvents();
  void update(sf::Time elapsedTime);
  void render();

  void updateStatistics(sf::Time elapsedTime);

  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow{sf::VideoMode({640, 480}), "Jeu Cyrano AA"};
  sf::Texture mTexture;
  sf::Font mFont;
  sf::Text mStatisticsText{mFont};
  sf::Time mStatisticsUpdateTime;
  std::size_t mStatisticsNumFrames{0};
  bool mMouseLeftButtonReleased{true};
  GameState mCurrentState;
  std::vector<Button> mMenuButtons;
  std::vector<Button> mShopButtons;
  std::vector<Button> mFightButtons;
  std::vector<Button> mWinButtons;
  std::vector<Button> mDeadButtons;
  std::vector<sf::Text> mMenuText;
  std::vector<sf::Text> mShopText;
  std::vector<sf::Text> mFightText;
  std::vector<sf::Text> mWinText;
  std::vector<sf::Text> mDeadText;
 
  Player mPlayer;
  std::vector<Enemy> mEnemies;
  std::size_t mCurrentEnemyIdx{0};

  FightPhase mFightPhase{FightPhase::PLAYER_CHOICE};
  CircleQTE mCircleQte{};
  SentenceQTE mSentenceQte{};

};

#endif  // BOOK_GAME_HPP
