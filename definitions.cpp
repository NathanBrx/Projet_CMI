#include "mainheader.hpp"
#include <iostream> 
#include <SFML/Graphics.hpp>
using namespace sf;

Perso::Perso(float x,float y,float rotation,int pvmax,int speed,int atk,Sprite persoSprite) : 
    x(x), y(y), rotation(rotation), pvmax(pvmax), speed(speed), atk(atk), persoSprite(persoSprite)
{}

void Perso::damage_taken(int atk){
    this-> pv = pv-atk;
}
void Perso::SetX(float x){
    this->x = x;
}
void Perso::SetY(float y){
    this->y = y;
}
float Perso::GetX(){
    return this->x;
}
float Perso::GetY(){
    return this->y;
}
float Perso::GetRotation(){
    return this->rotation;
}
int Perso::GetSpeed(){
    return this->speed;
}
void Perso::checkAlive(){
    if(this->pv <= 0){
        this->alive = 0;
    }
}
void Perso::speed_modif(int speed){
    this->speed = speed;
}

Projectile::Projectile(float x,float y,float direction,int vitesse,Sprite projectileSprite):
    x(x),y(y),direction(direction),vitesse(vitesse),projectileSprite(projectileSprite)
{}


Background::Background(Sprite backgroundSprite, Texture backgroundTexture,std::vector<sf::Vector2f> borduresPoints, std::vector<sf::Vector2f> portesPoints):
    backgroundSprite(backgroundSprite), backgroundTexture(backgroundTexture), borduresPoints(borduresPoints), portesPoints(portesPoints)
{}

sf::RectangleShape Background::createRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight, sf::Color color)
{
    // Calculer la longueur et l'angle du rectangle
    float length = std::sqrt(std::pow(bottomRight.x - bottomLeft.x, 2) + std::pow(bottomRight.y - bottomLeft.y, 2));
    float angle = std::atan2(bottomRight.y - bottomLeft.y, bottomRight.x - bottomLeft.x);

    // Créer le rectangle
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(length, 1.f));
    rectangle.setRotation(angle * 180.f / 3.14159f);
    rectangle.setFillColor(color);

    // Positionner le rectangle en utilisant le coin inférieur gauche
    rectangle.setPosition(bottomLeft.x, bottomLeft.y - rectangle.getSize().y);

    return rectangle;
}

void Background::setBackground(float ScaleX, float ScaleY){
    
    if (!backgroundText.loadFromFile(this->backgroundTexture)){
            cerr << "failed to load map texture" << endl;
            exit(1);
    }
    else{

        this->backgroundSprite.setTexture(backgroundText); // Set textures
        this->backgroundSprite.setScale(ScaleX, ScaleY);    // Set scales
        
    }
    backgroundText.setRepeated(false);

}


