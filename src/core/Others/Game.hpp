#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

enum class GameState{MAIN_MENU, SHOP, FIGHT, WIN, DEAD};
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
 
};

#endif  // BOOK_GAME_HPP
