#include <SFML\Graphics.hpp>

#pragma once

class Collider{
    private:
        sf::RectangleShape *colliderBody;
        sf::Texture colliderTexture;
    public:
        Collider(sf::Vector2f coordinates);
        void drawCollider(sf::RenderWindow* wnd);   
        sf::RectangleShape getColliderBody();     
};