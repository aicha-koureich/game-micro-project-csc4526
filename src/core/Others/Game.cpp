#include "Game.hpp"

#include <random>
#include <ranges>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() {
  assert(mFont.openFromFile("res/Sansation.ttf"));
  // We do not need to do mStatisticsText.setFont(mFont); as mStatisticsText is
  // initialized with a reference to mFont
  mStatisticsText.setPosition({5.f, 5.f});
  mStatisticsText.setCharacterSize(10);
  // Fill mTargets
  constexpr auto nbTargets = 100;
  constexpr auto minRadius = 10.f;
  constexpr auto maxRadius = 50.f;
  constexpr auto maxSpeed = 100.f;
  const std::vector<sf::Color> colors{sf::Color::Green, sf::Color::Blue,
                                      sf::Color::Yellow, sf::Color::Magenta};
  static std::random_device rd;
  static std::default_random_engine gen(rd());
  std::uniform_real_distribution<> distrib_radius(minRadius, maxRadius);
  std::uniform_int_distribution distrib_colors(
      0, static_cast<int>(colors.size()) - 1);
  std::uniform_real_distribution<> distrib_posX(
      0, static_cast<float>(mWindow.getSize().x) - 2 * maxRadius);
  std::uniform_real_distribution<> distrib_posY(
      0, static_cast<float>(mWindow.getSize().y) - 2 * maxRadius);
  std::uniform_real_distribution<> distrib_speedX(-maxSpeed, maxSpeed);
  std::uniform_int_distribution distrib_sign_speedY(0, 1);
  for (auto i = 0; i < nbTargets; ++i) {
    auto speedX = distrib_speedX(gen);
    mTargets.emplace_back(
        static_cast<float>(distrib_radius(gen)), colors[distrib_colors(gen)],
        static_cast<float>(distrib_posX(gen)),
        static_cast<float>(distrib_posY(gen)), static_cast<float>(speedX),
        static_cast<float>((distrib_sign_speedY(gen) ? -1 : 1) *
                           sqrt(maxSpeed * maxSpeed - speedX * speedX)));
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
    }
  }
}

void Game::update(sf::Time elapsedTime) {
  for (auto &target : mTargets) {
    target.update(elapsedTime, mWindow.getSize());
  }
  std::erase_if(mTargets, [](const RoundTarget &r) { return r.isDead(); });
  if (mTargets.empty()) {
    exit(EXIT_SUCCESS);
  }
}

void Game::render() {
  mWindow.clear();
  for (const auto &target : mTargets) {
    target.drawCurrent(mWindow);
  }
  mWindow.draw(mStatisticsText);
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
  mMouseLeftButtonReleased = false;
  // Search for a target hit by the mouse (we search in reverse order as top
  // targets are displayed last)
  for (auto &mTarget : std::ranges::reverse_view(mTargets)) {
    if (mTarget.isHitByMouse(sf::Mouse::getPosition(mWindow))) {
      mTarget.die();
      break;
    }
  }
}
