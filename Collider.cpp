#include "Collider.hpp"

Collider::Collider(sf::Vector2f coordinates)
{
    colliderTexture.loadFromFile("assets/coll32.png");
    this->colliderBody = new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f));
    this->colliderBody->setTexture(&colliderTexture);
    this->colliderBody->setPosition(coordinates);
}

void Collider::drawCollider(sf::RenderWindow* wnd)
{
    wnd->draw(*colliderBody);
}

sf::RectangleShape Collider::getColliderBody()
{
    return *colliderBody;
}