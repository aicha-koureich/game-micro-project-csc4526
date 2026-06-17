#include "Button.hpp"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, 
               const std::string& text, const sf::Font& font, sf::Color bgColor, const int characterSize) 
    : mButtonText{font} 
{
    mButtonShape.setPosition(position);
    mButtonShape.setSize(size);
    mButtonShape.setFillColor(bgColor);
    mButtonText.setString(text);
    mButtonText.setCharacterSize(characterSize);
    mButtonText.setFillColor(sf::Color::White);
    
    //centrer le texte
    mButtonText.setPosition(sf::Vector2f(position.x + 10.f, position.y + 10.f));
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(mButtonShape);
    window.draw(mButtonText);
}

bool Button::isPressed(const sf::Vector2i& mousePosition) const {
    return mButtonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}