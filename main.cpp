#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;
using namespace sf;
#include <vector>
#include <cmath>
#include "mainheader.hpp"

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard");
    
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);

    // background texture
    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite background, spriteMain, projectile1;
    Texture backgroundTexture, textureMain, textureProjectile;
        if (!backgroundTexture.loadFromFile("Map1.jpg")){
                cerr << "failed to load map texture" << endl;
                exit(1);
        }
        if (!textureMain.loadFromFile("Spritev1.png")){
            cerr << "failed to load spriteMain texture" << endl;
            exit(1);
        }
        if (!textureProjectile.loadFromFile("projectilev1.png")){
            cerr << "failed to load projectile texture" << endl;
            exit(1);
        }
        else{
            TextureSize = backgroundTexture.getSize(); //Get size of texture.
            WindowSize = window.getSize();             //Get size of window.

            float ScaleX = (float) WindowSize.x / TextureSize.x;
            float ScaleY = (float) WindowSize.y / TextureSize.y;    // Calculate scale

            background.setTexture(backgroundTexture); // Set textures
            background.setScale(ScaleX, ScaleY);    // Set scales
            
            spriteMain.setTexture(textureMain);
            spriteMain.setScale(ScaleX,ScaleY);

            projectile1.setTexture(textureProjectile);
            projectile1.setScale(ScaleX,ScaleY);
        }
    backgroundTexture.setRepeated(false);

    textureMain.setRepeated(false);
    textureMain.setSmooth(true);
    
    textureProjectile.setRepeated(false);
    textureProjectile.setSmooth(true);

    Perso A(window.getSize().x/2.,window.getSize().x/2.,0.,100,5,10,spriteMain);
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;
    float x = A.GetX(),y = A.GetY();
    float sprite1Rotation = A.GetRotation();
    Projectile p1(x,y,sprite1Rotation,A.GetSpeed(),projectile1);

    while (window.isOpen())
    {  
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();

            // If a key is pressed
            if (event.type == Event::KeyPressed){
                switch (event.key.code){
                // If escape is pressed, close the application
                case  Keyboard::Escape : window.close(); break;

                // up, down, left and right keys
                
                case Keyboard::Up : upFlag=true; sprite1Rotation=270.f; break;
                case Keyboard::Down : downFlag=true; sprite1Rotation=90.f; break;
                case Keyboard::Left : leftFlag=true; sprite1Rotation=180.f; break;
                case Keyboard::Right : rightFlag=true; sprite1Rotation=0.f; break;
                default : break;
                }
            }

            // If a key is released
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                // up, down, left and right keys
                case Keyboard::Up : upFlag=false; break;
                case Keyboard::Down : downFlag=false; break;
                case Keyboard::Left : leftFlag=false; break;
                case Keyboard::Right : rightFlag=false; break;
                default : break;
                }
            }
        }

        // Update coordinates
        if (leftFlag) x-=A.GetSpeed();
        if (rightFlag) x+=A.GetSpeed();
        if (upFlag) y-=A.GetSpeed();
        if (downFlag) y+=A.GetSpeed();

        // Check screen boundaries

        if (x<0) x=0;
        if (x>(int)window.getSize().x) x=window.getSize().x;
        if (y<0) y=0;
        if (y>(int)window.getSize().y) y=window.getSize().y;

        // Clear the window and apply background
        window.clear(Color::White);

        window.draw(background);

        // Créer des points pour définir les rectangles
        std::vector<sf::Vector2f> points = {
            {0, 414}, {78, 429},{276, 279}, {400, 234},{730, 195}, {882, 66}
        };

        // Créer un tableau de rectangles
        std::vector<sf::RectangleShape> rectangles;

        // Itérer sur les points deux par deux et créer un rectangle à chaque itération
        for (std::size_t i = 0; i < points.size() - 1; i += 1)
        {
            sf::Vector2f bottomLeft = points[i];
            sf::Vector2f bottomRight = points[i + 1];
            sf::RectangleShape rectangle = createRectangle(bottomLeft, bottomRight, sf::Color::Red);
            rectangles.push_back(rectangle);
        }

        // Rotate and draw the sprite1
        A.persoSprite.setOrigin(50.,50.);
        A.persoSprite.setPosition(x,y);
        A.persoSprite.setRotation(sprite1Rotation);

        p1.projectileSprite.setOrigin(15.,15.);
        p1.projectileSprite.setPosition(x+200,y+200);
        p1.projectileSprite.setRotation(sprite1Rotation);

        window.draw(p1.projectileSprite);
        window.draw(A.persoSprite);

        // Dessiner les rectangles
        for (const auto& rectangle : rectangles)
        {
            window.draw(rectangle);
        }

        window.display();
    }
}