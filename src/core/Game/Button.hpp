#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>

class Button {
 private:
  sf::RectangleShape mButtonShape;
  sf::Text mButtonText;
 public:
 Button(const sf::Vector2f& position, const sf::Vector2f& size, 
           const std::string& text, const sf::Font& font, sf::Color color, const int characterSize);
 ~Button() = default;
 void draw(sf::RenderWindow& window) const;
 bool isPressed(const sf::Vector2i& mousePosition) const;
 void setText(const std::string& newText) {mButtonText.setString(newText);}
 void setBackColor(const sf::Color& color) {mButtonShape.setFillColor(color);}
};

#endif