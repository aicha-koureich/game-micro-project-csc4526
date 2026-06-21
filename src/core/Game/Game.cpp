#include "Game.hpp"

#include <ranges>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mPlayer(100, 10, 0, 5, nullptr) {
  assert(mFont.openFromFile("res/Sansation.ttf"));
  mStatisticsText.setPosition({5.f, 5.f});
  mStatisticsText.setCharacterSize(10);
  loadXML(); //ici

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
  Button fightButton(sf::Vector2f(220.f, 320.f), sf::Vector2f(200.f, 50.f),
                     "FIGHT", mFont, sf::Color(80, 80, 200), 18);
  mMenuButtons.push_back(fightButton);
 
  //Shop
  sf::Text titleShop{mFont};
  titleShop.setString(" SHOP");
  titleShop.setCharacterSize(35);
  titleShop.setFillColor(sf::Color::White);
  titleShop.setPosition(sf::Vector2f(220.f, 10.0f));
  mShopText.push_back(titleShop);
    //items 
  sf::Text items{mFont};
  items.setString("Items");
  items.setCharacterSize(30);
  items.setFillColor(sf::Color::Green);
  items.setPosition(sf::Vector2f(0.0f, 315.0f));
  mShopText.push_back(items);

  sf::Text item1{mFont};
  item1.setString("Vin de Gascogne");
  item1.setCharacterSize(12);
  item1.setFillColor(sf::Color::White);
  item1.setPosition(sf::Vector2f(50.0f, 350.0f));
  mShopText.push_back(item1);
  sf::Text item2{mFont};
  item2.setString("Lettre de Roxanne");
  item2.setCharacterSize(12);
  item2.setFillColor(sf::Color::White);
  item2.setPosition(sf::Vector2f(230.0f, 350.0f));
  mShopText.push_back(item2);
  sf::Text item3{mFont};
  item3.setString("Encre");
  item3.setCharacterSize(12);
  item3.setFillColor(sf::Color::White);
  item3.setPosition(sf::Vector2f(410.0f, 350.0f));
  mShopText.push_back(item3);
  
  float currentX = 50;
  for(int i =0; i<3; ++i){
    Button buyItem(sf::Vector2f(currentX, 380.f), sf::Vector2f(80.f, 30.f),
                     "ACHETER", mFont, sf::Color::Red, 15);
    mShopButtons.push_back(buyItem);
    currentX+= 180.f;
  }

  Button goFightButton(sf::Vector2f(220.f, 420.f), sf::Vector2f(200.f, 50.f),
                       "GO FIGHT", mFont, sf::Color(80, 80, 200), 18);
  mShopButtons.push_back(goFightButton);
  mMoneyText.setCharacterSize(18);
  mMoneyText.setFillColor(sf::Color::Yellow);
  mMoneyText.setPosition({480.f, 20.f});



  //Fight

  //Armes de bases d�j� �quip�es pour le joueurs

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
  // Fight Buttons
  Button strengthButton(sf::Vector2f(40.f, 400.f), sf::Vector2f(150.f, 50.f),
                        "STRENGTH", mFont, sf::Color(78, 0, 0), 18); 

  Button eloquenceButton(sf::Vector2f(240.f, 400.f), sf::Vector2f(150.f, 50.f),
                        "ELOQUENCE", mFont, sf::Color(75, 0, 110), 18);

  Button itemButton(sf::Vector2f(440.f, 400.f), sf::Vector2f(150.f, 50.f),
                        "ITEM", mFont, sf::Color(0, 103, 79), 18);

  mFightButtons.push_back(strengthButton);
  mFightButtons.push_back(eloquenceButton);
  mFightButtons.push_back(itemButton);

  //Debuff Buttons
  Button attackDebuffButton(sf::Vector2f(40.f, 400.f),
                            sf::Vector2f(150.f, 50.f), "DEBUFF ATTACK", mFont,
                            sf::Color(120, 0, 0), 16);

  Button defenseDebuffButton(sf::Vector2f(240.f, 400.f),
                            sf::Vector2f(150.f, 50.f), "DEBUFF DEFENSE", mFont,
                            sf::Color(0, 0, 120), 16);

  mDebuffButtons.push_back(attackDebuffButton);
  mDebuffButtons.push_back(defenseDebuffButton);

  
}
void Game::loadXML(){
  pugi::xml_document doc;
  pugi::xml_parse_result res = doc.load_file("res/Weapons.xml");
  if(!res){
    std::cerr<<"Erreur chargement xml\n";
    return;
  }
  pugi::xml_node weaponsNode = doc.child("Weapons");
  float currentY = 30.f; 
  float currentX = 0.f; 
  std::string category = ""; // Pour le changement de catégorie
  for (pugi::xml_node node = weaponsNode.first_child(); node; node = node.next_sibling()) {
   std::unique_ptr<Weapon> weapon = Factory::create(node);
    if (weapon != nullptr) {
      if (category != node.name()) {
        if (!category.empty()) { 
          currentY += 100.f; 
        }  
        category = node.name();
        //titre
        sf::Text title{mFont};
        title.setString(category);
        title.setCharacterSize(30);
        title.setFillColor(sf::Color::Green);
        title.setPosition(sf::Vector2f(0.f, currentY));
        mShopText.push_back(title);
        
        currentY += 50.f; 
        currentX = 5.f;
      }
    //titre et prix des armes
    sf::Text weaponText{mFont};
    weaponText.setString(weapon->getName() + "\n" + std::to_string(weapon->getCost()) + " ecus");
    weaponText.setCharacterSize(12);
    weaponText.setFillColor(sf::Color::White);
    weaponText.setPosition(sf::Vector2f(currentX, currentY));
    mShopText.push_back(weaponText);
    //bouton achat
    Button buyBtn(sf::Vector2f(currentX, currentY + 50.f), sf::Vector2f(80.f, 30.f), "ACHETER", mFont, sf::Color::Red, 15);
    mShopButtons.push_back(buyBtn);
    currentX += 130.f; 
    
    mShopWeapon.push_back(std::move(weapon));
  } else {
    std::cerr << "Type d'arme: " << node.name() << " non reconnu par la factory\n";
  }
}

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
  mMoneyText.setString("Solde : " + std::to_string(mPlayer.getTotalMoney()) + " ecus"); //update le solde
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

      if (enemy.getHealthPoints() <= 0) {
        int moneyGained = static_cast<int>(mPlayer.getHealthPoints() * 0.1f) *
                          enemy.getEnemyLevel();
        mPlayer.addMoney(moneyGained);
        mPlayer.increaseNoseSize(enemy.getEnemyLevel());
        mPlayer.restoreHealth();
        
        mPlayerTurnResMessage.setString("Enemy is dead !");
        mCurrentState = GameState::WIN;
        return;
      }

      if (mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
        enemy.resetDefenseDebuff();
        mPlayerTurnResMessage.setString("Sword strike !");
      } else {
        mPlayerTurnResMessage.setString("Debuff applied !");
      }

      mResolutionTimer = 1.5f;
      mFightPhase = FightPhase::WAITING_AFTER_PLAYER;
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

      if (mPlayer.getHealthPoints() <= 0) {
        mPlayerTurnResMessage.setString("You lost !");
        mCurrentState = GameState::DEAD;
        return;
      }

      enemy.resetAttackDebuff();
      mPlayerTurnResMessage.setString("Enemy attacks !");

      mResolutionTimer = 1.5f;
      mFightPhase = FightPhase::WAITING_AFTER_ENEMY;
      break;

    case FightPhase::WAITING_AFTER_PLAYER:
      mResolutionTimer -= dt;
      if (mResolutionTimer <= 0.f) {
        mCircleQte = {150.f, 80.f, 40.f, 0.f};
        mFightPhase = FightPhase::PLAYER_DEFENSE_QTE;
      }
      break;
       
    case FightPhase::WAITING_AFTER_ENEMY:
      mResolutionTimer -= dt;
      if (mResolutionTimer <= 0.f) {
        mPlayerTurnResMessage.setString("");
        mFightPhase = FightPhase::PLAYER_CHOICE;
      }
      break;
  }


  //Barres de vie mises � jour
  mPlayerHpBar.setSize(
      {120.f * mPlayer.getHealthPoints() / mPlayer.getMaxHealthPoints(),
       16.f}); 
  mEnemyHpBar.setSize(
      {120.f * enemy.getHealthPoints() / enemy.getMaxHealthPoints(),
       16.f}); 

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
    mWindow.draw(mMoneyText);
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
        } else if (mFightPhase == FightPhase::DEBUFF_CHOICE) {
          for (const auto& button : mDebuffButtons) button.draw(mWindow);
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
    
  } else if (mMenuButtons.size() > 1 &&
             mMenuButtons[1].isPressed(mousePosition)) {
    mCurrentState = GameState::FIGHT;
  
  } else if (mCurrentState == GameState::SHOP) {
    if (!mShopButtons.empty() && mShopButtons.back().isPressed(mousePosition)) {
        //Le dernier bouton est le bouton fight car loadXML est appelé avant 
      mCurrentState = GameState::FIGHT;
    } else {
        for (size_t i = 0; i < mShopWeapon.size(); ++i) {
            if (mShopButtons[i].isPressed(mousePosition)) {
            if (mShopWeapon[i] == nullptr) {
                std::cout << "Deja vendu !\n";
                continue; 
            }
            bool success = mPlayer.purchaseWeapon(mShopWeapon[i]);
            if (success) {
            std::cout << "Achat reussi !\n";
            mShopButtons[i].setText("VENDU");
            mShopButtons[i].setBackColor(sf::Color{55, 55, 55, 255});
            } else {
            std::cout << "Fonds insuffisants !\n";

            }
        }
    
        }
    }
  } else if (mCurrentState == GameState::FIGHT &&
             mFightPhase == FightPhase::PLAYER_CHOICE) {
    // Strength attack
    if (mFightButtons[0].isPressed(mousePosition)) {
      mPlayer.pickWeapon(mSwordIdx);
      mCircleQte = {150.f, 80.f, 40.f, 0.f};
      mFightPhase = FightPhase::PLAYER_QTE;
    } else if (mFightButtons[1].isPressed(mousePosition)) {
      mPlayer.pickWeapon(mFeatherIdx);
      mFightPhase = FightPhase::DEBUFF_CHOICE;
    }
  } else if (mCurrentState == GameState::FIGHT && mFightPhase == FightPhase::DEBUFF_CHOICE) {
    if (mDebuffButtons[0].isPressed(mousePosition)) {
        mPendingDebuffChoice = DebuffType::STRENGTH;
    } else if (mDebuffButtons[1].isPressed(mousePosition)) {
      mPendingDebuffChoice = DebuffType::DEFENSE;
    } else {
      mMouseLeftButtonReleased = false;
      return;
    }
    
    if (auto* feather = dynamic_cast<Feather*>(mPlayer.getCurrentWeapon())) {
        feather->setDebuffChoice(DebuffType::DEFENSE);
    }

    mSentenceQte = {"Je suis Cyrano de Bergerac", "", 8.f, 0.f};
    mSentenceText.setString(mSentenceQte.sentence);
    mUserInputText.setString("");
    mFightPhase = FightPhase::PLAYER_QTE;
  }
      
    

  //A ajouter : ITEM
  
  mMouseLeftButtonReleased = false;

}


// Cette m�thode est appel� lorsque le joueur va devoir executer une QTE avec un cercle: cela peut �tre pour son tour lors d'une attaque � l'�p�e ou lorsqu'il doit d�fendre pendant le tour de l'ennemi
void Game::handleFightKeyPressed(sf::Keyboard::Key key) {
  if (key != sf::Keyboard::Key::Space) return;
  if (mFightPhase == FightPhase::PLAYER_QTE && mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
    
    // On calcule la distance entre le rayon du cercle qui r�tr�cit et le rayon du cercle vis�, plus cette distance est petite, plus la performance est proche de 1 donc les d�gats sont �lev�s
    float diff = std::abs(mCircleQte.currentRadius - mCircleQte.targetRadius);
    mCircleQte.circlePerf = std::max(0.f, 1.f - diff / mCircleQte.targetRadius);
    mFightPhase = FightPhase::RESOLUTION_PLAYER; //Le tour du joueur se termine apr�s la QTE d'attaque

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
