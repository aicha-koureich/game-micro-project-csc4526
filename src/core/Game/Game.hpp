#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

#include "Weapons/Sword.h"
#include "Weapons/Feather.h"
#include "Item/Item.hpp"
#include "Item/GasconeWine.hpp"
#include "Item/InkFlask.hpp"
#include "Item/RoxanneLetter.hpp"

enum class GameState {
  MAIN_MENU,
  SHOP,
  FIGHT,
  WIN,
  DEAD,
  GAME_FINISHED, 
  SETTING,
  PAUSE
};

//FIGHT PHASE
enum class FightPhase { 
	PLAYER_CHOICE, 
	DEBUFF_CHOICE,
	PRE_QTE,
	PLAYER_QTE, 
	RESOLUTION_PLAYER,
	WAITING_AFTER_PLAYER,
	PLAYER_DEFENSE_QTE,
	RESOLUTION_ENEMY,
	WAITING_AFTER_ENEMY
	
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
  void loadWeaponsXML();
  void loadTiradesXML();

 private:
  void handleHover();
  void handleMouseLeftButtonPressed();
  void handleCancelAction();

  void processEvents();
  void update(sf::Time elapsedTime);
  void render();

  void updateStatistics(sf::Time elapsedTime);

  void handleFightKeyPressed(sf::Keyboard::Key key);
  void handleFightTextEntred(std::uint32_t unicode);

  bool equipBestWeapon(AttackType type);
  void restartCombat();

  int getBestWeaponEffect(AttackType type) const;


  static const sf::Time TimePerFrame;

  GameState mPreviousState;

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
  std::vector<Button> mDebuffButtons;
  std::vector<Button> mWinButtons;
  std::vector<Button> mDeadButtons;
  std::vector<Button> mPauseButtons;
  std::vector<sf::Text> mMenuText;
  std::vector<sf::Text> mShopText;
  std::vector<sf::Text> mFightText;
  std::vector<sf::Text> mWinText;
  std::vector<sf::Text> mDeadText;
  std::vector<sf::Text> mFinishedText;
  std::vector<sf::Text> mPauseText;

  std::vector<unique_ptr<Weapon>> mShopWeapon;
  std::vector<unique_ptr<Item>> mShopItem;
  sf::Text mMoneyText{mFont};

  std::vector<std::string> mTirades;

  sf::RectangleShape mHoverInfoBg;
  sf::Text mHoverInfoText{mFont};

  std::unique_ptr<Button> mPauseButton;
  //Fight Phase
 
  Player mPlayer;
  std::vector<Enemy> mEnemies;
  std::size_t mCurrentEnemyIdx{0};

  sf::RectangleShape mPlayerShape;
  sf::RectangleShape mEnemyShape;

  //Sprites
  /*
  sf::Texture mPlayerTexture;
  std::vector<sf::Texture> mEnemyTextures;
  sf::Sprite mPlayerSprite{mPlayerTexture};
  sf::Sprite mEnemySprite;
  */
 

  // UI Portraits
  sf::RectangleShape mPlayerPortraitBg;
  sf::RectangleShape mEnemyPortraitBg;

  FightPhase mFightPhase{FightPhase::PLAYER_CHOICE};
  DebuffType mPendingDebuffChoice{DebuffType::DEFENSE};
  CircleQTE mCircleQte{};
  SentenceQTE mSentenceQte{};

  //Healthbars
  sf::RectangleShape mPlayerHpBarBg, mPlayerHpBar;
  sf::RectangleShape mEnemyHpBarBg, mEnemyHpBar;
  sf::Text mPlayerHpText{mFont};
  sf::Text mEnemyHpText{mFont};
  sf::Text mEnemyLevelText{mFont};

  //Mana
  const int eloquenceCost = 25;
  sf::RectangleShape mManaBarBg, mManaBar;
  sf::Text mManaText{mFont};



  sf::Text mWeaponNameText{mFont};
  sf::Text mPlayerStatsText{mFont};

  sf::Text mQteText{mFont};
  sf::CircleShape mQteTargetCircle;
  sf::CircleShape mQteMovingCircle;
  sf::Text mSentenceText{mFont};
  sf::Text mUserInputText{mFont};
  sf::Text mPlayerTurnResMessage{mFont};

  sf::Texture mWineTexture;
  sf::Texture mLetterTexture;
  sf::Texture mInkTexture;
  std::vector<sf::Sprite> mItemSprites;
  std::vector<sf::Text> mItemQtyTxt;
  float mResolutionTimer{0.f};

  //Pre fight stats
  int mPrevMoney{0};
  float mPrevNoseSize{0.f};
  int mPrevMaxHp{0};
  int mPrevBaseDefense{0};

  //weapons placeholder
  std::vector<sf::RectangleShape> weaponRectangles;
  //weapon tooltips
  sf::RectangleShape mTooltipBg;
  sf::Text mTooltipText{mFont};
  bool mShowTooltip = false;
};

#endif  // BOOK_GAME_HPP
