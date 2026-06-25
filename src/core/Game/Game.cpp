#include "Game.hpp"

#include <ranges>
#include <random>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mPlayer(100, 10, 0, 50, 5, nullptr) {
  assert(mFont.openFromFile("res/Sansation.ttf"));
  assert(mWineTexture.loadFromFile("res/vin.png"));
  assert(mLetterTexture.loadFromFile("res/lettre.png"));
  assert(mInkTexture.loadFromFile("res/ink.png"));

  mStatisticsText.setPosition({5.f, 5.f});
  mStatisticsText.setCharacterSize(10);
  loadWeaponsXML(); //ici
  loadTiradesXML();

  //Pause
  mPauseButton = std::make_unique<Button>(sf::Vector2f(615.f, 0.f), sf::Vector2f(25.f, 25.f), "| |", mFont, sf::Color{55, 55, 55, 255}, 18);
  sf::Text titlePause{mFont};
  titlePause.setString(" PAUSE ");
  titlePause.setCharacterSize(50);
  titlePause.setFillColor(sf::Color::White);
  titlePause.setPosition(sf::Vector2f(220.0f, 10.0f));
  mPauseText.push_back(titlePause);

  Button mSettingButton(sf::Vector2f(250.0f, 150.f), sf::Vector2f(120.f, 40.f), "Settings", mFont, sf::Color{55, 55, 55, 255}, 18);
  mPauseButtons.push_back(mSettingButton);
  Button mSave(sf::Vector2f(250.0f, 250.f), sf::Vector2f(120.f, 40.f), "Quit and Save", mFont, sf::Color{55, 55, 55, 255}, 18);
  mPauseButtons.push_back(mSave);
  Button mReturnMenu(sf::Vector2f(250.0f, 350.f), sf::Vector2f(120.f, 40.f), "Quit", mFont, sf::Color{55, 55, 55, 255}, 18);
  mPauseButtons.push_back(mReturnMenu);

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
  /*
  Button fightButton(sf::Vector2f(220.f, 320.f), sf::Vector2f(200.f, 50.f),
                     "FIGHT", mFont, sf::Color(80, 80, 200), 18);
  mMenuButtons.push_back(fightButton);
  */
 
  //Shop
  sf::Text titleShop{mFont};
  titleShop.setString("SHOP");
  titleShop.setCharacterSize(35);
  titleShop.setFillColor(sf::Color::White);
  titleShop.setPosition(sf::Vector2f(220.f, 10.0f));
  mShopText.push_back(titleShop);
    //items 
  std::unique_ptr<Item> vin = std::make_unique<GasconeWine>(2, 0.25f);
  std::unique_ptr<Item> lettre = std::make_unique<RoxanneLetter>(1, 0.25f);
  std::unique_ptr<Item> ink = std::make_unique<InkFlask>(1, 0.25f);

  sf::Text items{mFont};
  items.setString("ITEMS");
  items.setCharacterSize(30);
  items.setFillColor(sf::Color::Green);
  items.setPosition(sf::Vector2f(0.0f, 315.0f));
  mShopText.push_back(items);

  sf::Text item1{mFont};
  item1.setString("Gascogne Wine\n" + std::to_string(vin->getCost()) + " ecus");
  item1.setCharacterSize(12);
  item1.setFillColor(sf::Color::White);
  item1.setPosition(sf::Vector2f(50.0f, 350.0f));
  mShopText.push_back(item1);
  sf::Text item2{mFont};
  item2.setString("Roxanne Letter\n" + std::to_string(lettre->getCost()) + "ecus");
  item2.setCharacterSize(12);
  item2.setFillColor(sf::Color::White);
  item2.setPosition(sf::Vector2f(230.0f, 350.0f));
  mShopText.push_back(item2);
  sf::Text item3{mFont};
  item3.setString("Ink\n" + std::to_string(lettre->getCost()) + "ecus");
  item3.setCharacterSize(12);
  item3.setFillColor(sf::Color::White);
  item3.setPosition(sf::Vector2f(410.0f, 350.0f));
  mShopText.push_back(item3);

  mShopItem.push_back(std::move(vin));
  mShopItem.push_back(std::move(lettre));
  mShopItem.push_back(std::move(ink));
  
  float currentX = 50;
  for(int i =0; i<3; ++i){
    Button buyItem(sf::Vector2f(currentX + 20, 420.f), sf::Vector2f(60.f, 20.f),
                     "BUY", mFont, sf::Color::Red, 13);
    mShopButtons.push_back(buyItem);
    currentX+= 180.f;
  }
  mPlayerStatsText.setCharacterSize(16);
  mPlayerStatsText.setFillColor(sf::Color::White);
  mPlayerStatsText.setPosition({400.f, 350.f});

  Button goFightButton(sf::Vector2f(220.f, 445.f), sf::Vector2f(150.f, 30.f),
                       "GO FIGHT", mFont, sf::Color(80, 80, 200), 18);
  mShopButtons.push_back(goFightButton);
    //Money
  mMoneyText.setCharacterSize(18);
  mMoneyText.setFillColor(sf::Color::Yellow);
  mMoneyText.setPosition({480.f, 20.f});

    // weapon infobulle
  mTooltipBg.setFillColor(sf::Color(0, 0, 0, 220)); 
  mTooltipBg.setOutlineColor(sf::Color::White);
  mTooltipBg.setOutlineThickness(1.f);
  
  mTooltipText.setCharacterSize(14);
  mTooltipText.setFillColor(sf::Color::White);

  //Fight

  //Ennemis
  mEnemies.clear();

  // 1. Le Cosplayer Novice (Le Tuto)
  // HP: 50 | Sensibilité: 1.0f | Atk: 10 | Def: 5 | Lvl: 1
  mEnemies.push_back(Enemy{50, 1.0f, 10, 5, 1});

  // 2. Le Fan en Armure (Force le debuff de Défense)
  // HP: 70 | Sensibilité: 1.2f | Atk: 8 | Def: 20 | Lvl: 2
  mEnemies.push_back(Enemy{70, 1.2f, 8, 20, 2});

  // 3. La Brute Sanguinaire (Force le debuff d'Attaque)
  // HP: 60 | Sensibilité: 0.8f | Atk: 35 | Def: 5 | Lvl: 3
  mEnemies.push_back(Enemy{60, 0.8f, 35, 5, 3});

  // 4. Le Snob Susceptible (Sensibilité extrême à l'Éloquence)
  // HP: 90 | Sensibilité: 2.0f | Atk: 25 | Def: 25 | Lvl: 4
  mEnemies.push_back(Enemy{90, 2.0f, 25, 25, 4});

  // 5. Le Faux De Guiche (Le Boss - Endurance)
  // HP: 150 | Sensibilité: 0.5f | Atk: 25 | Def: 15 | Lvl: 5
  mEnemies.push_back(Enemy{150, 0.5f, 25, 15, 5});

  // Graphics
  //Items 
  for (int i = 0; i < 3; ++i) {
    // On donne la bonne image selon l'index (0=Vin, 1=Lettre, 2=Encre)
    if (i == 0) mItemSprites.emplace_back(mWineTexture);
    else if (i == 1) mItemSprites.emplace_back(mLetterTexture);
    else if (i == 2) mItemSprites.emplace_back(mInkTexture);

    // Le texte pour afficher la quantité 
    sf::Text qtyText{mFont};
    qtyText.setCharacterSize(14);
    qtyText.setFillColor(sf::Color::Yellow);
    mItemQtyTxt.push_back(qtyText);
}
  //Title Fight
  sf::Text titleFight{mFont};
  titleFight.setString(" FIGHT ");
  titleFight.setCharacterSize(40);
  titleFight.setFillColor(sf::Color::White);

  sf::FloatRect bounds = titleFight.getLocalBounds();
  titleFight.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

  titleFight.setPosition(sf::Vector2f(320.f, 10.f));
  mFightText.push_back(titleFight);

  // PLAYER GRAPHICS

  // Player frame
  mPlayerPortraitBg.setSize({60.f, 60.f});
  mPlayerPortraitBg.setFillColor(sf::Color(40, 40, 40));  
  mPlayerPortraitBg.setOutlineThickness(2.f);
  mPlayerPortraitBg.setOutlineColor(sf::Color(218, 165, 32));  
  mPlayerPortraitBg.setPosition({40.f, 49.f});

  //Player renderer
  
  mPlayerShape.setSize({60.f, 100.f});
  mPlayerShape.setFillColor(sf::Color::Blue);
  mPlayerShape.setPosition({130.f, 145.f});
  

  /*
  if (!mPlayerTexture.loadFromFile("res/player.png")) {
    std::cerr << "Erreur res/player.png introuvable\n";
  }
  mPlayerSprite.setTexture(mPlayerTexture, true);
  mPlayerSprite.setPosition({130.f, 145.f});
  */


  // Player Healthbar (background and fill)
  mPlayerHpBarBg.setSize({150.f, 20.f});
  mPlayerHpBarBg.setFillColor(sf::Color(60, 60, 60));
  mPlayerHpBarBg.setPosition({110.f, 65.f});
  mPlayerHpBarBg.setOutlineThickness(2.f);
  mPlayerHpBarBg.setOutlineColor(sf::Color(218, 165, 32));
  mPlayerHpBar.setSize({150.f, 20.f});
  mPlayerHpBar.setFillColor(sf::Color::Green);
  mPlayerHpBar.setPosition({110.f, 65.f});

  mPlayerHpText.setString(std::to_string(mPlayer.getHealthPoints()) + "/" +
                          std::to_string(mPlayer.getMaxHealthPoints()));
  mPlayerHpText.setCharacterSize(16);
  mPlayerHpText.setFillColor(sf::Color::White);
  mPlayerHpText.setPosition({120.f, 67.f});
  mPlayerHpText.setOutlineThickness(1.f);
  mPlayerHpText.setOutlineColor(sf::Color::Black);

  //Player Mana
  mManaBarBg.setSize({150.f, 14.f});
  mManaBarBg.setFillColor(sf::Color(60, 60, 60));
  mManaBarBg.setPosition({110.f, 95.f});
  mManaBarBg.setOutlineThickness(2.f);
  mManaBarBg.setOutlineColor(sf::Color(192, 192, 192));
  mManaBar.setSize({150.f, 14.f});
  mManaBar.setFillColor(sf::Color::Blue);
  mManaBar.setPosition({110.f, 95.f});
  mManaText.setCharacterSize(14);
  mManaText.setFillColor(sf::Color::White);
  mManaText.setPosition({120.f, 97.f});
  mManaText.setOutlineThickness(1.f);
  mManaText.setOutlineColor(sf::Color::Black);


  // ENEMY GRAPHICS
  
  //Enemy frame
  mEnemyPortraitBg.setSize({60.f, 60.f});
  mEnemyPortraitBg.setFillColor(sf::Color(40, 40, 40));
  mEnemyPortraitBg.setOutlineThickness(2.f);
  mEnemyPortraitBg.setOutlineColor(sf::Color(218, 165, 32));
  mEnemyPortraitBg.setPosition({540.f, 49.f});

  //Enemy renderer
  
  mEnemyShape.setSize({60.f, 100.f});
  mEnemyShape.setFillColor(sf::Color::Magenta);
  mEnemyShape.setPosition({450.f, 145.f});
 

  /*
  if (!mEnemyTextures[0].loadFromFile("res/enemy1.png")) {
    std::cerr << "Erreur res/enemy1.png introuvable\n";
  }

  mEnemySprite.setTexture(mEnemyTextures[0], true);
  mEnemySprite.setPosition({450.f, 145.f});
  */
  

  //Enemy HealthBar (background and fill)
  mEnemyHpBarBg.setSize({150.f, 20.f});
  mEnemyHpBarBg.setFillColor(sf::Color(60, 60, 60));
  mEnemyHpBarBg.setPosition({380.f, 65.f});
  mEnemyHpBarBg.setOutlineThickness(2.f);
  mEnemyHpBarBg.setOutlineColor(sf::Color(218, 165, 32));
  mEnemyHpBar.setSize({150.f, 20.f});
  mEnemyHpBar.setFillColor(sf::Color::Red);
  mEnemyHpBar.setPosition({380.f, 65.f});

  mEnemyHpText.setString(std::to_string(mEnemies[mCurrentEnemyIdx].getHealthPoints()) + "/" +
      std::to_string(mEnemies[mCurrentEnemyIdx].getMaxHealthPoints()));
  mEnemyHpText.setCharacterSize(16);
  mEnemyHpText.setFillColor(sf::Color::White);
  mEnemyHpText.setPosition({390.f, 67.f});
  mEnemyHpText.setOutlineThickness(1.f);
  mEnemyHpText.setOutlineColor(sf::Color::Black);

  //Enemy level
  mEnemyLevelText.setCharacterSize(14);
  mEnemyLevelText.setFillColor(sf::Color::White);
  mEnemyLevelText.setPosition({390.f, 97.f});
  mEnemyLevelText.setOutlineThickness(1.f);
  mEnemyLevelText.setOutlineColor(sf::Color(218, 165, 32));
  mEnemyLevelText.setString(
      "LEVEL : " + std::to_string(mEnemies[mCurrentEnemyIdx].getEnemyLevel()));
  

  //Weapon Text
  mWeaponNameText.setCharacterSize(18);
  mWeaponNameText.setFillColor(sf::Color::White);
  mWeaponNameText.setPosition({40.f, 320.f});

  //Hover Infos
  mHoverInfoText.setCharacterSize(14);
  mHoverInfoText.setFillColor(sf::Color(220, 220, 100));
  mHoverInfoText.setPosition(
      {48.f, 274.f});  

  mHoverInfoBg.setFillColor(
      sf::Color(20, 20, 20, 200));  
  mHoverInfoBg.setOutlineColor(sf::Color(220, 220, 100));
  mHoverInfoBg.setOutlineThickness(1.f);
  mHoverInfoBg.setPosition({40.f, 268.f});
  mHoverInfoBg.setSize({0.f, 0.f});

  //Circle QTE (strength or defense QTE)
  // 
  // Indications for the player
  mQteText.setCharacterSize(22);
  mQteText.setFillColor(sf::Color::Yellow);
  mQteText.setPosition({180.f, 300.f});
  mQteText.setString("PRESS SPACE !");

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

  //Message after player action
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
                        "ITEMS", mFont, sf::Color(0, 103, 79), 18);

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


  //WIN / DEAD
  sf::Text winTitle{mFont};
  winTitle.setString("VICTORY !!!");
  winTitle.setCharacterSize(40);
  winTitle.setFillColor(sf::Color::Green);
  winTitle.setPosition({200.f, 60.f});
  mWinText.push_back(winTitle);
  Button winToShopButton(sf::Vector2f(220.f, 330.f), sf::Vector2f(200.f, 50.f),
                         "BACK TO SHOP", mFont, sf::Color(80, 80, 200), 18);
  mWinButtons.push_back(winToShopButton);

  sf::Text deadTitle{mFont};
  deadTitle.setString("YOU LOST !");
  deadTitle.setCharacterSize(36);
  deadTitle.setFillColor(sf::Color::Red);
  deadTitle.setPosition({150.f, 150.f});
  mDeadText.push_back(deadTitle);
  Button deadRestartButton(sf::Vector2f(220.f, 300.f),
                           sf::Vector2f(200.f, 50.f), "TRY AGAIN", mFont,
                           sf::Color(150, 0, 0), 18);
  mDeadButtons.push_back(deadRestartButton);

  //Game Finished
  sf::Text finishedTitle{mFont};
  finishedTitle.setString("You beat every enemy");
  finishedTitle.setCharacterSize(36);
  finishedTitle.setFillColor(sf::Color::Yellow);
  finishedTitle.setPosition({120.f, 200.f});
  mFinishedText.push_back(finishedTitle);

  
}
void Game::loadWeaponsXML(){
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
          currentY += 110.f; 
        }  
        category = node.name();
        //titre
        sf::Text title{mFont};
        title.setString(category);
        title.setCharacterSize(30);
        title.setFillColor(sf::Color::Green);
        title.setPosition(sf::Vector2f(0.f, currentY));
        mShopText.push_back(title);
          
        currentY += 35.f; 
        currentX = 5.f;
      }
    //titre et prix des armes
    sf::Text weaponText{mFont};
    weaponText.setString(weapon->getName() + "\n" + std::to_string(weapon->getCost()) + " ecus");
    weaponText.setCharacterSize(12);
    weaponText.setFillColor(sf::Color::White);
    weaponText.setPosition(sf::Vector2f(currentX, currentY));
    mShopText.push_back(weaponText);

    // Création du carré gris (Placeholder de l'icône)
    sf::RectangleShape box(sf::Vector2f(50.f, 50.f)); 
    box.setFillColor(sf::Color(100, 100, 100)); // Gris
    box.setPosition(sf::Vector2f(currentX + 25.f, currentY + 32.f)); 
    weaponRectangles.push_back(box);

    //bouton achat
    Button buyBtn(sf::Vector2f(currentX +20.f, currentY + 85.f), sf::Vector2f(60.f, 20.f), "BUY", mFont, sf::Color::Red, 13);
    mShopButtons.push_back(buyBtn);
    currentX += 130.f; 
    
    mShopWeapon.push_back(std::move(weapon));
  } else {
    std::cerr << "Type d'arme: " << node.name() << " non reconnu par la factory\n";
  }
}

}

void Game::loadTiradesXML() {
  pugi::xml_document doc;
  pugi::xml_parse_result res = doc.load_file("res/Tirades.xml");

  if (!res) {
    std::cerr << "Erreur chargement xml\n";
    return;
  }

  pugi::xml_node tiradesNode = doc.child("Tirades");

  for (pugi::xml_node node = tiradesNode.first_child(); node;
       node = node.next_sibling()) {
    std::string tirade = node.child_value();
    mTirades.push_back(tirade);
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
  mMoneyText.setString("WALLET : " + std::to_string(mPlayer.getTotalMoney()) + " ecus"); //update le solde
  if (mCurrentState == GameState::SHOP) {
    //SPRITES ITEM
    for (int i = 0; i < 3; ++i) {
          sf::Vector2u texSize = mItemSprites[i].getTexture().getSize();
          mItemSprites[i].setScale({50.f / texSize.x, 50.f / texSize.y});
          mItemSprites[i].setPosition({70.f + (i * 180.f), 370.f});
          mItemSprites[i].setColor(sf::Color::White);
      }

    //INFO-BULLES
    mShowTooltip = false;  //  cache l'infobulle (default)

    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                           static_cast<float>(mousePos.y));

    std::string specs = ""; //memoire pour le txt de l'infobulle
      //INFOBULLES ARMES
    for (size_t i = 0; i < mShopWeapon.size(); ++i) {
      if (mShopWeapon[i] != nullptr && weaponRectangles[i].getGlobalBounds().contains(mousePosF)) {
        specs = mShopWeapon[i]->getName() + "\nEffect : " + std::to_string(mShopWeapon[i]->getEffect());
        break;
      }
    }
    if (specs == ""){
      for(size_t i = 0; i< mItemSprites.size(); ++i){
        if(mItemSprites[i].getGlobalBounds().contains(mousePosF)){
          switch (i)
          {
          case 0:
            specs = "A fine Gascogne Wine\nthat restores health\n+25% Player HP";
            break;
          
          case 1:
            specs = "Roxanne's words boost\n your fencing skills\n +25% Strength";
            break;
          case 2:
            specs = "The finest China ink\nfor the best tirades\n+25% Eloquence applied to Feather";
            break;
          }
        }
      }
    }
    if(specs != ""){
      mShowTooltip =  true;
      mTooltipText.setString(specs);
      // On positionne le texte juste à côté de la souris 
      mTooltipText.setPosition({mousePosF.x + 20.f, mousePosF.y +5.f});
      //ajuste le rectangle de fond selon la taille du texte
      sf::FloatRect bounds = mTooltipText.getGlobalBounds();
      mTooltipBg.setSize({bounds.size.x + 10.f, bounds.size.y + 10.f});
      mTooltipBg.setPosition(
          {bounds.position.x - 5.f, bounds.position.y - 5.f});
    }
  }
  if (mCurrentState != GameState::FIGHT) return;
  float dt = elapsedTime.asSeconds();
  Enemy& enemy = mEnemies[mCurrentEnemyIdx];
  handleHover();

  //REPOSITION DES SPRITES ITEMS POUR COMBAT & QUANTITES

  float X = 420.f;
  float Y = 320.f;
  float spacing = 60.f;
  //potions'quantities
  int wineQty = 0, letterQty = 0, inkQty = 0;
  
  // On compte les objets présents dans l'inventaire
  for (const auto& item : mPlayer.getItemInventory()) {
      if (dynamic_cast<GasconeWine*>(item.get())) wineQty++;
      else if (dynamic_cast<RoxanneLetter*>(item.get())) letterQty++;
      else if (dynamic_cast<InkFlask*>(item.get())) inkQty++;
  }

  // On met les résultats dans un tableau pour correspondre à nos 3 icônes
  int quantities[3] = {wineQty, letterQty, inkQty};

  // On met à jour l'affichage des sprites et les qtés
  for (int i = 0; i < 3; ++i) {
    sf::Vector2u texSize = mItemSprites[i].getTexture().getSize();
    mItemSprites[i].setScale({75.f / texSize.x, 75.f / texSize.y});
    mItemSprites[i].setPosition(sf::Vector2f(X + (i * spacing), Y));

    mItemQtyTxt[i].setString("x" + std::to_string(quantities[i]));
    mItemQtyTxt[i].setPosition({X + (i * spacing) + 30.f, Y + 30.f});

    if (quantities[i] <= 0) {
      // noir si qté nulle
        mItemSprites[i].setColor(sf::Color(100, 100, 100, 150)); 
    } else {
        mItemSprites[i].setColor(sf::Color::White); 
    }
  }
  switch (mFightPhase) { 
    case FightPhase::PLAYER_CHOICE: {
      
      if (mPlayer.getMana() < eloquenceCost) {
        mFightButtons[1].setBackColor(sf::Color(65, 65, 65));
      } else {
        mFightButtons[1].setBackColor(sf::Color(75, 0, 110));
      }
      break;
    }
      

    case FightPhase::PLAYER_QTE:
      if (mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
        mQteMovingCircle.setRadius(mCircleQte.currentRadius);
        mQteMovingCircle.setOrigin(
            {mCircleQte.currentRadius, mCircleQte.currentRadius});
        mCircleQte.currentRadius -= mCircleQte.closeSpeed * dt;
        if (mCircleQte.currentRadius <= 0.f) {
          mCircleQte.circlePerf = 0.5f;
          mFightPhase = FightPhase::RESOLUTION_PLAYER;
        }
      } else {
        mSentenceQte.remainingTime -= dt;
        if (mSentenceQte.remainingTime <= 0.f) {
          mSentenceQte.sentencePerf = 0.5f;
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
        mPrevMoney = mPlayer.getTotalMoney();
        mPrevNoseSize = mPlayer.getNoseSize();
        mPrevMaxHp = mPlayer.getMaxHealthPoints();
        mPrevBaseDefense = mPlayer.getBaseDefense();

        int moneyGained = static_cast<int>(mPlayer.getHealthPoints() * 0.3f) *
                          enemy.getEnemyLevel();
        mPlayer.addMoney(moneyGained);
        mPlayer.increaseNoseSize(enemy.getEnemyLevel());
        mPlayer.restoreHealth();

        mCurrentEnemyIdx++;
        if (mCurrentEnemyIdx >= mEnemies.size()) {
          mCurrentState = GameState::GAME_FINISHED;
        } else {
          /*
          * if (!mEnemyTextures[mCurrentEnemyIdx].loadFromFile(
                  "res/enemy" + std::to_string(mCurrentEnemyIdx + 1) +
                  ".png")) {
            std::cerr << "Erreur chargement sprite ennemi " << mCurrentEnemyIdx
                      << "\n";
          }
          mEnemySprite.setTexture(mEnemyTextures[mCurrentEnemyIdx], true);
          */ 
          mPlayerTurnResMessage.setString("ENEMY IS DEAD !");
          mCurrentState = GameState::WIN;
        }
        return;
      }

      if (mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
        enemy.resetDefenseDebuff();
        mPlayerTurnResMessage.setString("SWORD STRIKE !");
      } else {
        mPlayerTurnResMessage.setString("ENEMY AFFECTED BY YOUR ELOQUENCE !");
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
        mCircleQte.circlePerf = 0.5f;
        mFightPhase = FightPhase::RESOLUTION_ENEMY;
      }

      break;

    case FightPhase::RESOLUTION_ENEMY:
      enemy.enemyAttack(mPlayer, mCircleQte.circlePerf);

      if (mPlayer.getHealthPoints() <= 0) {
        mPlayerTurnResMessage.setString("YOU LOST !");
        mCurrentState = GameState::DEAD;
        return;
      }

      enemy.resetAttackDebuff();
      mPlayerTurnResMessage.setString("ATTACK RECEIVED !");

      mResolutionTimer = 1.5f;
      mFightPhase = FightPhase::WAITING_AFTER_ENEMY;
      break;

    case FightPhase::WAITING_AFTER_PLAYER:
      mResolutionTimer -= dt;
      if (mResolutionTimer <= 0.f) {
        mCircleQte = {150.f, 80.f, 40.f, 0.f};
        mPlayerTurnResMessage.setString("");
        mFightPhase = FightPhase::PLAYER_DEFENSE_QTE;
      }
      break;
       
    case FightPhase::WAITING_AFTER_ENEMY:
      mResolutionTimer -= dt;
      if (mResolutionTimer <= 0.f) {
        mPlayer.regenMana(10);
        mPlayerTurnResMessage.setString("");
        mFightPhase = FightPhase::PLAYER_CHOICE;
      }
      break;
  }


  //Barres de vie mises � jour
  mPlayerHpBar.setSize(
      {120.f * mPlayer.getHealthPoints() / mPlayer.getMaxHealthPoints(),
       16.f}); 
  mPlayerHpText.setString(std::to_string(mPlayer.getHealthPoints()) + "/" +
                          std::to_string(mPlayer.getMaxHealthPoints()));
  mEnemyHpBar.setSize(
      {120.f * enemy.getHealthPoints() / enemy.getMaxHealthPoints(),
       16.f});
  mEnemyHpText.setString(std::to_string(enemy.getHealthPoints()) + "/" +
                          std::to_string(enemy.getMaxHealthPoints()));

  // Barres de mana mises � jour
  mManaBar.setSize({150.f * mPlayer.getMana() / mPlayer.getMaxMana(), 14.f});
  mManaText.setString(std::to_string(mPlayer.getMana()) + "/" +
                      std::to_string(mPlayer.getMaxMana()));

}

void Game::render() {
  mWindow.clear();
  mWindow.draw(mStatisticsText);
  if(mPauseButton != nullptr) mPauseButton->draw(mWindow);
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
    for(const auto& shape : weaponRectangles){
      mWindow.draw(shape);
    }
    for(const auto& text : mShopText){
      mWindow.draw(text);
    }
    for(const auto& button : mShopButtons){
       button.draw(mWindow);
    }
    for(const auto& sprite: mItemSprites){
      mWindow.draw(sprite);
    }
    mWindow.draw(mMoneyText);
    mWindow.draw(mPlayerTurnResMessage);

    if (mShowTooltip) {
        mWindow.draw(mTooltipBg);
        mWindow.draw(mTooltipText);
    }
      break;

      case GameState::FIGHT:
        for (const auto& text : mFightText) mWindow.draw(text);

        mWindow.draw(mPlayerPortraitBg);
        mWindow.draw(mPlayerShape);
        //mWindow.draw(mPlayerSprite);
        mWindow.draw(mPlayerHpBarBg);
        mWindow.draw(mPlayerHpBar);
        mWindow.draw(mPlayerHpText);

        mWindow.draw(mEnemyPortraitBg);
        mWindow.draw(mEnemyShape);
        //mWindow.draw(mEnemySprite);
        mWindow.draw(mEnemyHpBarBg);
        mWindow.draw(mEnemyHpBar);
        mWindow.draw(mEnemyHpText);
        mWindow.draw(mEnemyLevelText);

        mWindow.draw(mManaBarBg);
        mWindow.draw(mManaBar);
        mWindow.draw(mManaText);

        if (!mHoverInfoText.getString().isEmpty()) {
          mWindow.draw(mHoverInfoBg);
          mWindow.draw(mHoverInfoText);
        }


        mWindow.draw(mWeaponNameText);
        mWindow.draw(mPlayerTurnResMessage);

        for (const auto& sprite : mItemSprites) mWindow.draw(sprite);
        for (const auto& text : mItemQtyTxt) mWindow.draw(text);
        
        if (mFightPhase == FightPhase::PLAYER_CHOICE) {
          for (const auto& button : mFightButtons) button.draw(mWindow);
        } else if (mFightPhase == FightPhase::DEBUFF_CHOICE) {
          for (const auto& button : mDebuffButtons) button.draw(mWindow);
        } else if (mFightPhase == FightPhase::PLAYER_QTE &&
                   mPlayer.getCurrentWeapon()->getType() ==
                       AttackType::STRENGTH) {
          mWindow.draw(mQteText);
          mWindow.draw(mQteTargetCircle);
          mWindow.draw(mQteMovingCircle);
        } else if (mFightPhase == FightPhase::PLAYER_QTE) {
          mWindow.draw(mSentenceText);
          mWindow.draw(mUserInputText);
        } else if (mFightPhase == FightPhase::PLAYER_DEFENSE_QTE) {
          mWindow.draw(mQteText);
          mWindow.draw(mQteTargetCircle);
          mWindow.draw(mQteMovingCircle);
        }

        break;

      case GameState::WIN: {
        int moneyGain = mPlayer.getTotalMoney() - mPrevMoney;
        float noseGain = mPlayer.getNoseSize() - mPrevNoseSize;
        int hpGain = mPlayer.getMaxHealthPoints() - mPrevMaxHp;
        int defGain = mPlayer.getBaseDefense() - mPrevBaseDefense;

        mPlayerStatsText.setString(
            "WALLET : " + std::to_string(mPlayer.getTotalMoney()) + " ecus (+" +
            std::to_string(moneyGain) + ")\n" +
            "NOSE SIZE : " + std::to_string(mPlayer.getNoseSize()) + " (+" +
            std::to_string(noseGain) + ")\n" +
            "MAX HP : " + std::to_string(mPlayer.getMaxHealthPoints()) + " (+" +
            std::to_string(hpGain) + ")\n" +
            "DEFENSE : " + std::to_string(mPlayer.getBaseDefense()) + " (+" +
            std::to_string(defGain) + ")");

        mPlayerStatsText.setCharacterSize(20);
        mPlayerStatsText.setFillColor(sf::Color(120, 255, 120));

        sf::FloatRect bounds = mPlayerStatsText.getLocalBounds();
        mPlayerStatsText.setOrigin(
            {bounds.position.x + bounds.size.x / 2.f, bounds.position.y});
        mPlayerStatsText.setPosition({320.f, 220.f});

        mWindow.draw(mPlayerStatsText);

        for (const auto& text : mWinText) mWindow.draw(text);
        for (const auto& button : mWinButtons) button.draw(mWindow);
        break;
      }
        

      case GameState::DEAD:
        for (const auto& text : mDeadText) mWindow.draw(text);
        for (const auto& button : mDeadButtons) button.draw(mWindow);
        break;

      case GameState::GAME_FINISHED:
        mPlayerStatsText.setString(
            "WALLET : " + std::to_string(mPlayer.getTotalMoney()) + " ecus\n" +
            "NOSE SIZE : " + std::to_string(mPlayer.getNoseSize()) + "\n" +
            "HEALTH POINTS : " + std::to_string(mPlayer.getMaxHealthPoints()) +
            "HP\n" + "DEFENSE : " + std::to_string(mPlayer.getBaseDefense()));
        mWindow.draw(mPlayerStatsText);

        for (const auto& text : mFinishedText) mWindow.draw(text);
        break;

      case GameState::PAUSE:
      for(const auto& text : mPauseText) mWindow.draw(text);
      for(const auto& button : mPauseButtons) button.draw(mWindow);
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


void Game::handleHover() {
  sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);

  if (mFightPhase == FightPhase::PLAYER_CHOICE) {
    if (mFightButtons[0].isHovered(mousePosition)) {
      int effect = getBestWeaponEffect(AttackType::STRENGTH);
      mHoverInfoText.setString(effect >= 0
                                   ? "Raw damage : " + std::to_string(effect)
                                   : "No sword equipped");
    } else if (mFightButtons[1].isHovered(mousePosition)) {
      int effect = getBestWeaponEffect(AttackType::ELOQUENCE);
      mHoverInfoText.setString(
          effect >= 0 ? "Cost : " +
                            std::to_string(eloquenceCost) + " mana"
                      : "No quill equipped");
    } else {
      mHoverInfoText.setString("");
    }   
  } else if (mFightPhase == FightPhase::DEBUFF_CHOICE) {
    if (mDebuffButtons[0].isHovered(mousePosition)) {
      int playerRawDebuff =
          getBestWeaponEffect(AttackType::ELOQUENCE) *
          2.f;    // On montre le debuff max que l'on peut appliqué à l'ennemi
        int reduction =  (playerRawDebuff * mEnemies[mCurrentEnemyIdx].getSensitivityToEloq()) /
              mEnemies[mCurrentEnemyIdx].getEnemyLevel();
      int reelDebuff = std::max(
          1, mEnemies[mCurrentEnemyIdx].getCurrentDamage() - reduction);
      mHoverInfoText.setString(
          "Reduce enemy attack\n Max debuff : " +
                               std::to_string(reelDebuff) + " attack points"
             );
    } else if (mDebuffButtons[1].isHovered(mousePosition)) {
      int playerRawDebuff =
          getBestWeaponEffect(AttackType::ELOQUENCE) *
          2.f;  // On montre le debuff max que l'on peut appliqué à l'ennemi
      int reduction = (playerRawDebuff *
                       mEnemies[mCurrentEnemyIdx].getSensitivityToEloq()) /
                      mEnemies[mCurrentEnemyIdx].getEnemyLevel();
      int reelDebuff = std::max(
          1, mEnemies[mCurrentEnemyIdx].getCurrentDefense() - reduction);
      mHoverInfoText.setString(
          "Reduce enemy defense\n Max debuff : " +
                               std::to_string(reelDebuff) + " defense points");
    } else {
      mHoverInfoText.setString("");
    }
  } else {
    mHoverInfoText.setString("");
    mHoverInfoBg.setSize(sf::Vector2f(0, 0));
  }

  sf::FloatRect bounds = mHoverInfoText.getLocalBounds();
  if (!mHoverInfoText.getString().isEmpty()) {
    float padding = 8.f;
    mHoverInfoBg.setPosition({mHoverInfoText.getPosition().x - padding,
                              mHoverInfoText.getPosition().y - padding});
    mHoverInfoBg.setSize(
        {bounds.size.x + padding * 2.f, bounds.size.y + padding * 2.f});
  }
  
}

void Game::handleMouseLeftButtonPressed() {
  if (!mMouseLeftButtonReleased) {
    return;
  }
  sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
 if (mPauseButton != nullptr && mPauseButton->isPressed(mousePosition)) {
      if (mCurrentState == GameState::PAUSE) {
          mCurrentState = mPreviousState; 
      } else {
          mPreviousState = mCurrentState; //on save pour y retourner
          mCurrentState = GameState::PAUSE;
      }
      mMouseLeftButtonReleased = false;
      return; 
  }

  // Dans Pause
  if (mCurrentState == GameState::PAUSE) {
      if (mPauseButtons[0].isPressed(mousePosition)) {
          mCurrentState = GameState::SETTING;
      } 
      else if (mPauseButtons[1].isPressed(mousePosition)) {
          mCurrentState = GameState::MAIN_MENU; // Save
      } 
      else if (mPauseButtons[2].isPressed(mousePosition)) {
          restartCombat();
          mCurrentState = GameState::MAIN_MENU;
      }
      mMouseLeftButtonReleased = false;
      return; 
  }

  //SHOP
  if(mCurrentState == GameState::MAIN_MENU && mMenuButtons[0].isPressed(mousePosition)){
    mCurrentState = GameState::SHOP;
    
  } else if (mCurrentState == GameState::SHOP) {
    if (!mShopButtons.empty() && mShopButtons.back().isPressed(mousePosition)) {
        //Le dernier bouton est le bouton fight car loadXML est appelé avant 
      mCurrentState = GameState::FIGHT;
      mFightPhase = FightPhase::PLAYER_CHOICE;  
      mPlayerTurnResMessage.setString("");
    } else {
        for (size_t i = 0; i < mShopWeapon.size(); ++i) {
            if (mShopButtons[i].isPressed(mousePosition)) {
            if (mShopWeapon[i] == nullptr) {
              mPlayerTurnResMessage.setString("Already sold !");
                continue; 
            }
            bool success = mPlayer.purchaseWeapon(mShopWeapon[i]);
            if (success) {
            mPlayerTurnResMessage.setString("Purchase successful!");
            mShopButtons[i].setText("SOLD");
            mShopButtons[i].setBackColor(sf::Color{55, 55, 55, 255});
            } else {
            mPlayerTurnResMessage.setString("Not enough money !");

           }
           mMouseLeftButtonReleased = false;
              return;
          }
        }
        //ACHAT ITEMS
        for (size_t j = 0; j < mShopItem.size(); ++j) {
            // Le bouton correspondant à l'item est décalé par le nombre d'armes 
            size_t buttonIndex = mShopWeapon.size() + j; 

            if (mShopButtons[buttonIndex].isPressed(mousePosition)) {
              if (mShopItem[j] == nullptr) {
                    std::cerr << "ERROR : mShopItem[" << j << "] is null !" << std::endl;
                    return; 
                }
              //on les crée à la volée et on clone l'item dans le catalogue
              std::unique_ptr<Item> newItem = mShopItem[j]->clone();
              //achat
              bool success = mPlayer.purchaseItem(newItem); 
              
              if (success) {
                  mPlayerTurnResMessage.setString("Item purchased successfully !\n");
              } else {
                  mPlayerTurnResMessage.setString("Not enough money !");
              } 
              mMouseLeftButtonReleased = false;
              return;
            }
        }
    }
  } else if (mCurrentState == GameState::FIGHT &&
             mFightPhase == FightPhase::PLAYER_CHOICE) {
    //UTILISER ITEMS
    sf::Vector2f mousePosFloat(mousePosition.x, mousePosition.y);
    for (int i = 0; i < 3; ++i) {
        if (mItemSprites[i].getGlobalBounds().contains(mousePosFloat)) {
            
            int indexToUse = -1; // L'index exact de l'objet dans le Player
            const auto& inv = mPlayer.getItemInventory();
            std::string itemMessage = "";
            // On cherche le premier objet du bon type dans l'inventaire
            for (size_t k = 0; k < inv.size(); ++k) {
                if (i == 0 && dynamic_cast<GasconeWine*>(inv[k].get())) { indexToUse = k; itemMessage = "+25% Hp!"; break; }
                if (i == 1 && dynamic_cast<RoxanneLetter*>(inv[k].get())) { indexToUse = k; itemMessage = "+25% Strength!"; break; }
                if (i == 2 && dynamic_cast<InkFlask*>(inv[k].get())) { indexToUse = k; itemMessage = "+25% Eloquence!"; break; }
            }

            // Si on a trouvé l'objet, on l'utilise
            if (indexToUse != -1) {
                if(mPlayer.useItem(indexToUse)) 
                  mPlayerTurnResMessage.setString(itemMessage);
                else{
                  mPlayerTurnResMessage.setString("Non usable Item !");
                }
            } else {
                mPlayerTurnResMessage.setString("Out of stock !");
            }
            
            mMouseLeftButtonReleased = false;
            return; 
        }
    }
    // Strength attack
      //Fix bug crash si pas l'arme adaptée
    if (mFightButtons[0].isPressed(mousePosition)) {
      if (equipBestWeapon(AttackType::STRENGTH)) {
        mPlayerTurnResMessage.setString("SPACE : ATTACK   ESC : CANCEL");
        mFightPhase = FightPhase::PRE_QTE;
      }

    } else if (mFightButtons[1].isPressed(mousePosition)) {
      if (mPlayer.getMana() < eloquenceCost) {
        mPlayerTurnResMessage.setString("NOT ENOUGH MANA !");
        mMouseLeftButtonReleased = false;
        return;
      }
      if (equipBestWeapon(AttackType::ELOQUENCE)) {
        mFightPhase = FightPhase::DEBUFF_CHOICE;
      }

    }
  } else if (mCurrentState == GameState::FIGHT && mFightPhase == FightPhase::DEBUFF_CHOICE) {
    //if (mPlayer.getMana() >= eloquenceCost) {
    if (mDebuffButtons[0].isPressed(mousePosition)) {
      mPendingDebuffChoice = DebuffType::STRENGTH;

    } else if (mDebuffButtons[1].isPressed(mousePosition)) {
      mPendingDebuffChoice = DebuffType::DEFENSE;
    } else {
      mMouseLeftButtonReleased = false;
      return;
    }
    /*
    * else {
      mMouseLeftButtonReleased = false;
      return;
    }
    */ 
    
    
    
    
    if (auto* feather = dynamic_cast<Feather*>(mPlayer.getCurrentWeapon())) {
        feather->setDebuffChoice(mPendingDebuffChoice);
    }

    if (!mTirades.empty()) {
      static std::mt19937 gen(std::random_device{}());
      std::uniform_int_distribution<std::size_t> dist(0, mTirades.size() - 1);
      int randomIdx = dist(gen);
      mSentenceQte = {mTirades[randomIdx], "", 8.f, 0.f};
    } else {
      mSentenceQte = {"I'm Cyrano de Bergerac", "", 8.f, 0.f};
    }

    mSentenceText.setString(mSentenceQte.sentence);
    mUserInputText.setString("");
    mPlayerTurnResMessage.setString("SPACE : WRITE   ESC : CANCEL");
    mFightPhase = FightPhase::PRE_QTE;

  } else if (mCurrentState == GameState::WIN) {
    if (!mWinButtons.empty() && mWinButtons[0].isPressed(mousePosition)) {
      mCurrentState = GameState::SHOP;
    }
  } else if (mCurrentState == GameState::DEAD) {
    if (!mDeadButtons.empty() && mDeadButtons[0].isPressed(mousePosition)) {
      restartCombat();
      mCurrentState = GameState::SHOP;
    }
  }  
  mMouseLeftButtonReleased = false;

}


// Cette m�thode est appel� lorsque le joueur va devoir executer une QTE avec un cercle: cela peut �tre pour son tour lors d'une attaque � l'�p�e ou lorsqu'il doit d�fendre pendant le tour de l'ennemi
void Game::handleFightKeyPressed(sf::Keyboard::Key key) {
  if (key == sf::Keyboard::Key::Escape) {
    handleCancelAction();
    return;
  }

  if (key != sf::Keyboard::Key::Space) return;

  if (mFightPhase == FightPhase::PRE_QTE) {
    mPlayerTurnResMessage.setString("");
    if (mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
      mCircleQte = {150.f, 80.f, 40.f, 0.f};
    } else {
      mPlayer.reduceMana(eloquenceCost);
    }
    mFightPhase = FightPhase::PLAYER_QTE;
    return;
  }

  if (mFightPhase == FightPhase::PLAYER_QTE && mPlayer.getCurrentWeapon()->getType() == AttackType::STRENGTH) {
    
    // On calcule la distance entre le rayon du cercle qui r�tr�cit et le rayon du cercle vis�, plus cette distance est petite, plus la performance est proche de 1 donc les d�gats sont �lev�s
    float diff = std::abs(mCircleQte.currentRadius - mCircleQte.targetRadius);
    float rawPerf = std::max(0.f, 1.f - diff / mCircleQte.targetRadius);
    mCircleQte.circlePerf = 0.5f + rawPerf * 1.5f;  //QTE manquée -> moitié des dégats infligés, QTE parfaitement réussie -> double des dégats 
    mFightPhase = FightPhase::RESOLUTION_PLAYER; //Le tour du joueur se termine apr�s la QTE d'attaque

  } else if (mFightPhase == FightPhase::PLAYER_DEFENSE_QTE) {
    float diff = std::abs(mCircleQte.currentRadius - mCircleQte.targetRadius);
    float rawPerf = std::max(0.f, 1.f - diff / mCircleQte.targetRadius);
    mCircleQte.circlePerf = 0.5 + rawPerf * 1.5f;
    mFightPhase = FightPhase::RESOLUTION_ENEMY;

  }
}

void Game::handleFightTextEntred(std::uint32_t unicode) {
  if (mPlayer.getCurrentWeapon()->getType() != AttackType::STRENGTH) {
    if (unicode == 8) {  // backspace
      if (!mSentenceQte.userInput.empty()) mSentenceQte.userInput.pop_back();
      return;
    }
    if (unicode < 128) {
      mSentenceQte.userInput += static_cast<char>(unicode);
      mUserInputText.setString(mSentenceQte.userInput);
      if (mSentenceQte.userInput.size() >= mSentenceQte.sentence.size()) {
        int correct = 0;
        for (std::size_t i = 0; i < mSentenceQte.sentence.size(); ++i) {
          if (i < mSentenceQte.userInput.size() &&
              mSentenceQte.userInput[i] == mSentenceQte.sentence[i])
            correct++;
        }

        mSentenceQte.sentencePerf =
            static_cast<float>(correct) / mSentenceQte.sentence.size();
        mFightPhase = FightPhase::RESOLUTION_PLAYER;
      }
    }
  }
    
}

void Game::handleCancelAction() {
    switch (mFightPhase) { 
      case FightPhase::DEBUFF_CHOICE:
      case FightPhase::PRE_QTE:
        mPlayerTurnResMessage.setString("");
        if (mPlayer.getCurrentWeapon()->getType() == AttackType::ELOQUENCE) {
          mPlayer.regenMana(eloquenceCost);
        }
        mFightPhase = FightPhase::PLAYER_CHOICE;
        break;

      default:
        break;
    }

}

/* MOdifs: devenu un bool pour fixer le bug : si t'as pas l'arme correspondant a l'attaque ca crash*/
bool Game::equipBestWeapon(AttackType type) {
  const auto& inventory = mPlayer.getWeaponInventory();
  int bestEffect = -1;
  size_t bestIdx = 0;
  bool found = false;

  for (size_t i = 0; i < inventory.size(); ++i) {
    if (inventory[i]->getType() == type && inventory[i]->getEffect() > bestEffect) {
      bestEffect = inventory[i]->getEffect();
      bestIdx = i;
      found = true;
      
    }
  }

  if (found) {
    mPlayer.pickWeapon(bestIdx);
    mPlayerTurnResMessage.setString("");
    return true;
  } else{
    mPlayerTurnResMessage.setString("Buy the correct weapon to attack");
    return false;
  }
}
void Game::restartCombat(){
  // restart hp player & ennemie qui vient de nous battre
  mEnemies[mCurrentEnemyIdx].setHealthPoints(mEnemies[mCurrentEnemyIdx].getMaxHealthPoints());
  mPlayer.setHealthPoints(mPlayer.getMaxHealthPoints());
  
  mPlayerTurnResMessage.setString("");
  mSentenceQte.userInput = "";
  mUserInputText.setString("");
}
 



int Game::getBestWeaponEffect(AttackType type) const {
  const auto& inventory = mPlayer.getWeaponInventory();
  int bestEffect = -1;
  for (const auto& weapon : inventory) {
    if (weapon->getType() == type && weapon->getEffect() > bestEffect) {
      bestEffect = weapon->getEffect();
    }
  }
  return bestEffect;
}
