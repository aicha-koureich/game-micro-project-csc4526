#include "Button.hpp"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
               const std::string& text, const sf::Font& font, sf::Color bgColor,
               const int characterSize)
    : mButtonText{font} {
  mButtonShape.setPosition(position);
  mButtonShape.setSize(size);
  mButtonShape.setFillColor(bgColor);
  mButtonText.setString(text);
  mButtonText.setCharacterSize(characterSize);
  mButtonText.setFillColor(sf::Color::White);

  // centrer le texte
  float rectCenterX = position.x + (size.x / 2.0f);
  float rectCenterY = position.y + (size.y / 2.0f);

  sf::FloatRect textBounds = mButtonText.getLocalBounds();
  mButtonText.setOrigin(sf::Vector2f(textBounds.position.x + (textBounds.size.x / 2.0f),
                  textBounds.position.y + (textBounds.size.y / 2.0f)));

  mButtonText.setPosition(sf::Vector2f(rectCenterX, rectCenterY));
}

void Button::draw(sf::RenderWindow& window) const {
  window.draw(mButtonShape);
  window.draw(mButtonText);
}

bool Button::isHovered(sf::Vector2i& mousePosition) const {
  return mButtonShape.getGlobalBounds().contains(
      static_cast<sf::Vector2f>(mousePosition));
}

bool Button::isPressed(const sf::Vector2i& mousePosition) const {
  return mButtonShape.getGlobalBounds().contains(
      static_cast<sf::Vector2f>(mousePosition));
}