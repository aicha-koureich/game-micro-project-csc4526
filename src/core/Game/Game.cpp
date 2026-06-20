#include "Game.hpp"

#include <ranges>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mPlayer(100, 50, 0, 5, nullptr) {
  assert(mFont.openFromFile("res/Sansation.ttf"));
  mStatisticsText.setPosition({5.f, 5.f});
  mStatisticsText.setCharacterSize(10);

  //Start Menu
  mCurrentState = GameState::MAIN_MENU;
  sf::Text titleMenu{mFont};
  titleMenu.setString(" Cyrano de A&A ");
  titleMenu.setCharacterSize(50);
  titleMenu.setFillColor(sf::Color::White);
  titleMenu.setPosition(sf::Vector2f(130.0f, 100.0f));
  mMenuText.push_back(titleMenu);
  Button startButton(sf::Vector2f(220.f,240.f ), sf::Vector2f(200.f, 60.f), "START", mFont, sf::Color::Red, 30);
  mMenuButtons.push_back(startButton);
 
  //Shop
  sf::Text titleShop{mFont};
  titleShop.setString(" SHOP");
  titleShop.setCharacterSize(50);
  titleShop.setFillColor(sf::Color::White);
  titleShop.setPosition(sf::Vector2f(220.f, 10.0f));
  mShopText.push_back(titleShop);
  sf::Text swords{mFont};
  swords.setString(" CYRANO-SWORDS");
  swords.setCharacterSize(30);
  swords.setFillColor(sf::Color::White);
  swords.setPosition(sf::Vector2f(0.f, 100.0f));
  mShopText.push_back(swords);
  sf::Text feathers{mFont};
  feathers.setString(" CYRANO-FEATHER");
  feathers.setCharacterSize(30);
  feathers.setFillColor(sf::Color::White);
  feathers.setPosition(sf::Vector2f(0.f, 225.f));
  mShopText.push_back(feathers);
  sf::Text items{mFont};
  items.setString("ITEMS");
  items.setCharacterSize(30);
  items.setFillColor(sf::Color::White);
  items.setPosition(sf::Vector2f(0.0f, 350.0f));
  mShopText.push_back(items);

  //Fight

  //Armes de bases déjà équipées pour le joueur
  std::unique_ptr<Weapon> baseSword =
      std::make_unique<Sword>(10, "Wooden stick", 0);
  std::unique_ptr<Weapon> baseFeather =
      std::make_unique<Feather>(5, "Pigeon feather", 0);

  mPlayer.purchaseWeapon(std::move(baseSword));
  mPlayer.purchaseWeapon(std::move(baseFeather));
  
  mPlayer.pickWeapon(0);

  Enemy firstEnemy{50, 0.5f, 15, 10, 1};
  mEnemies.push_back(firstEnemy);







  
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  mWindow.setFramerateLimit(60);
  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      processEvents();
      update(TimePerFrame);
    }

    updateStatistics(elapsedTime);
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    } else if (event->is<sf::Event::MouseButtonPressed>() &&
               sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      handleMouseLeftButtonPressed();
    } else if (event->is<sf::Event::MouseButtonReleased>() &&
               !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      mMouseLeftButtonReleased = true;
    }
  }
}

void Game::update(sf::Time elapsedTime) {

}

void Game::render() {
  mWindow.clear();
  mWindow.draw(mStatisticsText);
  switch(mCurrentState){
    case GameState::MAIN_MENU:
    for(const auto& text : mMenuText){
      mWindow.draw(text);
    }
    for(const auto& button : mMenuButtons){
       button.draw(mWindow);
    }
      break;
    case GameState::SHOP:
    for(const auto& text : mShopText){
      mWindow.draw(text);
    }
    for(const auto& button : mShopButtons){
       button.draw(mWindow);
    }
      break;
  }

  mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime) {
  mStatisticsUpdateTime += elapsedTime;
  mStatisticsNumFrames += 1;

  if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
    mStatisticsText.setString(std::format(
        "Frames / Second = {}\nTime / Update = {} us", mStatisticsNumFrames,
        mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames));
    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
}

void Game::handleMouseLeftButtonPressed() {
  if (!mMouseLeftButtonReleased) {
    return;
  }
  sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);

  if(mMenuButtons[0].isPressed(mousePosition)){
    mCurrentState = GameState::SHOP;
  
  

  }
  mMouseLeftButtonReleased = false;

}
