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

  // Graphics

  //Title Fight
  sf::Text titleFight{mFont};
  titleFight.setString(" FIGHT ");
  titleFight.setCharacterSize(40);
  titleFight.setFillColor(sf::Color::White);
  titleFight.setPosition(sf::Vector2f(220.f, 10.f));
  mFightText.push_back(titleFight);

  //Player renderer
  mPlayerShape.setSize({60.f, 100.f});
  mPlayerShape.setFillColor(sf::Color::Blue);
  mPlayerShape.setPosition({80.f, 120.f});

  // Player Healthbar (background and fill)
  mPlayerHpBarBg.setSize({150.f, 20.f});
  mPlayerHpBarBg.setFillColor(sf::Color(60, 60, 60));
  mPlayerHpBarBg.setPosition({40.f, 350.f});
  mPlayerHpBar.setSize({150.f, 20.f});
  mPlayerHpBar.setFillColor(sf::Color::Green);
  mPlayerHpBar.setPosition({40.f, 350.f});

  //Enemy renderer
  mEnemyShape.setSize({60.f, 100.f});
  mEnemyShape.setFillColor(sf::Color::Magenta);
  mEnemyShape.setPosition({500.f, 120.f});

  //Enemy HealthBar (background and fill)
  mEnemyHpBarBg.setSize({150.f, 20.f});
  mEnemyHpBarBg.setFillColor(sf::Color(60, 60, 60));
  mEnemyHpBarBg.setPosition({450.f, 60.f});
  mEnemyHpBar.setSize({150.f, 20.f});
  mEnemyHpBar.setFillColor(sf::Color::Red);
  mEnemyHpBar.setPosition({450.f, 60.f});

  //Weapon Text
  mWeaponNameText.setCharacterSize(18);
  mWeaponNameText.setFillColor(sf::Color::White);
  mWeaponNameText.setPosition({40.f, 320.f});

  //Circle QTE (strength or defense QTE)
  //Target Circle
  mQteTargetCircle.setRadius(40.f);
  mQteTargetCircle.setOrigin({40.f, 40.f});
  mQteTargetCircle.setPosition({320.f, 420.f});
  mQteTargetCircle.setFillColor(sf::Color::Transparent);
  mQteTargetCircle.setOutlineColor(sf::Color::White);
  mQteTargetCircle.setOutlineThickness(3.f);

  //Moving Circle
  mQteMovingCircle.setOrigin(
      {mQteMovingCircle.getRadius(), mQteMovingCircle.getRadius()});
  mQteMovingCircle.setPosition({320.f, 420.f});
  mQteMovingCircle.setFillColor(sf::Color::Transparent);
  mQteMovingCircle.setOutlineColor(sf::Color::Yellow);
  mQteMovingCircle.setOutlineThickness(2.f);

  //Sentence QTE (Eloquence Qte)
  //Sentence to Complete
  mSentenceText.setCharacterSize(18);
  mSentenceText.setFillColor(sf::Color(150, 150, 150));
  mSentenceText.setPosition({40.f, 390.f});

  //Input sentence
  mUserInputText.setCharacterSize(18);
  mUserInputText.setFillColor(sf::Color::White);
  mUserInputText.setPosition({40.f, 420.f});

  //Message afetr player action
  mPlayerTurnResMessage.setCharacterSize(22);
  mPlayerTurnResMessage.setFillColor(sf::Color::Yellow);
  mPlayerTurnResMessage.setPosition({180.f, 300.f});

  //Buttons
  Button strengthButton(sf::Vector2f(40.f, 400.f), sf::Vector2f(150.f, 50.f),
                        "STRENGTH", mFont, sf::Color(78, 0, 0), 18); 

  Button eloquenceButton(sf::Vector2f(240.f, 400.f), sf::Vector2f(150.f, 50.f),
                        "ELOQUENCE", mFont, sf::Color(75, 0, 110), 18);

  Button itemButton(sf::Vector2f(440.f, 400.f), sf::Vector2f(150.f, 50.f),
                        "ITEM", mFont, sf::Color(0, 103, 79), 18);

  mFightButtons.push_back(strengthButton);
  mFightButtons.push_back(eloquenceButton);
  mFightButtons.push_back(itemButton);



  
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
    } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (mCurrentState == GameState::FIGHT) {
        handleFightKeyPressed(keyPressed->code);
      }
    
    } else if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
      if (mCurrentState == GameState::FIGHT && mFightPhase == FightPhase::PLAYER_QTE) { 
        handleFightTextEntred(textEntered->unicode);
      }
    }
      
  }
}

void Game::update(sf::Time elapsedTime) {
  if (mCurrentState != GameState::FIGHT) return;
  float dt = elapsedTime.asSeconds();
  Enemy& enemy = mEnemies[mCurrentEnemyIdx];

  switch (mFightPhase) { 
    case FightPhase::PLAYER_CHOICE:
      break;

    case FightPhase::PLAYER_QTE:
      if (mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
        mQteMovingCircle.setRadius(mCircleQte.currentRadius);
        mQteMovingCircle.setOrigin(
            {mCircleQte.currentRadius, mCircleQte.currentRadius});
        mCircleQte.currentRadius -= mCircleQte.closeSpeed * dt;
        if (mCircleQte.currentRadius <= 0.f) {
          mCircleQte.circlePerf = 0.f;
          mFightPhase = FightPhase::RESOLUTION_PLAYER;
        }
      } else {
        mSentenceQte.remainingTime -= dt;
        if (mSentenceQte.remainingTime <= 0.f) {
          mFightPhase = FightPhase::RESOLUTION_PLAYER;
        }
      }
      break;

    case FightPhase::RESOLUTION_PLAYER: {
      float perf =
          (mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH)
               ? mCircleQte.circlePerf
               : mSentenceQte.sentencePerf;
      mPlayer.playerAttack(enemy, perf);

      if (mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
        enemy.resetDefenseDebuff();
        mPlayerTurnResMessage.setString("Sword strike !");
      } else {
        mPlayerTurnResMessage.setString("Debuff applied !");
      }

      mResolutionTimer = 1.5f;
      break;
    }
    
    case FightPhase::PLAYER_DEFENSE_QTE:
      mQteMovingCircle.setRadius(mCircleQte.currentRadius);
      mQteMovingCircle.setOrigin(
          {mCircleQte.currentRadius, mCircleQte.currentRadius});

      mCircleQte.currentRadius -= mCircleQte.closeSpeed * dt;
      if (mCircleQte.currentRadius <= 0.f) {
        mCircleQte.circlePerf = 0.f;
        mFightPhase = FightPhase::RESOLUTION_ENEMY;
      }

      break;

    case FightPhase::RESOLUTION_ENEMY:
      enemy.enemyAttack(mPlayer, mCircleQte.circlePerf);
      enemy.resetAttackDebuff();
      mPlayerTurnResMessage.setString("Enemy attacks !");
      mResolutionTimer = 1.5f;
      break;

  }

  //Pause d'affichage après le tour d'une entité
  if (mResolutionTimer > 0.f) {
    mResolutionTimer -= dt;
    if (mResolutionTimer <= 0.f) {
      if (mFightPhase == FightPhase::RESOLUTION_PLAYER) {
        //Qte défense 
        mCircleQte = {150.f, 80.f, 40.f, 0.f};
        mFightPhase = FightPhase::PLAYER_DEFENSE_QTE;
      } else if (mFightPhase == FightPhase::RESOLUTION_ENEMY) {
        //Tour suivant
        mPlayerTurnResMessage.setString("");
        mFightPhase = FightPhase::PLAYER_CHOICE;
      }
    }
  }

  //Barres de vie mises à jour
  mPlayerHpBar.setSize(
      {120.f * mPlayer.getHealthPoints() / mPlayer.getMaxHealthPoints(),
       16.f});  // remplacer 100 par maxHealthPoints
  mEnemyHpBar.setSize(
      {120.f * enemy.getHealthPoints() / enemy.getMaxHealthPoints(),
       16.f});  // idem

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

      case GameState::FIGHT:
        for (const auto& text : mFightText) mWindow.draw(text);

        mWindow.draw(mPlayerShape);
        mWindow.draw(mPlayerHpBarBg);
        mWindow.draw(mPlayerHpBar);

        mWindow.draw(mEnemyShape);
        mWindow.draw(mEnemyHpBarBg);
        mWindow.draw(mEnemyHpBar);

        mWindow.draw(mWeaponNameText);
        mWindow.draw(mPlayerTurnResMessage);

        if (mFightPhase == FightPhase::PLAYER_CHOICE) {
          for (const auto& button : mFightButtons) button.draw(mWindow);
        } else if (mFightPhase == FightPhase::PLAYER_QTE &&
                   mPlayer.getCurrentWeapon()->getType() ==
                       AttackType::STRENGTH) {
          mWindow.draw(mQteTargetCircle);
          mWindow.draw(mQteMovingCircle);
        } else if (mFightPhase == FightPhase::PLAYER_QTE) {
          mWindow.draw(mSentenceText);
          mWindow.draw(mUserInputText);
        } else if (mFightPhase == FightPhase::PLAYER_DEFENSE_QTE) {
          mWindow.draw(mQteTargetCircle);
          mWindow.draw(mQteMovingCircle);
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


// Cette méthode est appelé lorsque le joueur va devoir executer une QTE avec un cercle: cela peut être pour son tour lors d'une attaque à l'épée ou lorsqu'il doit défendre pendant le tour de l'ennemi
void Game::handleFightKeyPressed(sf::Keyboard::Key key) {
  if (key != sf::Keyboard::Key::Space) return;
  if (mFightPhase == FightPhase::PLAYER_QTE && mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
    
    // On calcule la distance entre le rayon du cercle qui rétrécit et le rayon du cercle visé, plus cette distance est petite, plus la performance est proche de 1 donc les dégats sont élevés
    float diff = std::abs(mCircleQte.currentRadius - mCircleQte.targetRadius);
    mCircleQte.circlePerf = std::max(0.f, 1.f - diff / mCircleQte.targetRadius);
    mFightPhase = FightPhase::RESOLUTION_PLAYER; //Le tour du joueur se termine après la QTE d'attaque

  } else if (mFightPhase == FightPhase::PLAYER_DEFENSE_QTE) {
    float diff = std::abs(mCircleQte.currentRadius - mCircleQte.targetRadius);
    mCircleQte.circlePerf = std::max(0.f, 1.f - diff / mCircleQte.targetRadius);
    mFightPhase = FightPhase::RESOLUTION_ENEMY;

  }
}

void Game::handleFightTextEntred(std::uint32_t unicode) { 
    if (unicode == 8) { //backspace
        if (!mSentenceQte.userInput.empty()) mSentenceQte.userInput.pop_back();
        return;
    }
    if (unicode < 128) {
      mSentenceQte.userInput += static_cast<char>(unicode);
      mUserInputText.setString(mSentenceQte.userInput);
      if (mSentenceQte.userInput.size() >= mSentenceQte.sentence.size()) {
        int correct = 0;
        for (std::size_t i = 0; i < mSentenceQte.sentence.size(); ++i) {
          if (i < mSentenceQte.userInput.size() && mSentenceQte.userInput[i] == mSentenceQte.sentence[i]) correct++;
        }

        mSentenceQte.sentencePerf =
            static_cast<float>(correct) / mSentenceQte.sentence.size();
        mFightPhase = FightPhase::RESOLUTION_PLAYER;
      }
    }
}
