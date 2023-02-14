#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;
using namespace sf;

#define SPRITE_SPEED 5

int main()
{
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Body Guard",Style::Fullscreen);
    
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);

    

    // rectangle
    Rect r1(0, 0, 300, 300);

    // background texture
    Vector2u TextureSize;
    Vector2u WindowSize;
    Sprite background;
    Texture backgroundTexture;
    float ScaleX;
    float ScaleY;
        if (!backgroundTexture.loadFromFile("Map1.jpg")){
                cerr << "failed to load image" << endl;
                exit(1);
        }
        else{
            TextureSize = backgroundTexture.getSize(); //Get size of texture.
            WindowSize = window.getSize();             //Get size of window.

            ScaleX = (float) WindowSize.x / TextureSize.x;
            ScaleY = (float) WindowSize.y / TextureSize.y;    // Calculate scale

            background.setTexture(backgroundTexture);
            background.setScale(ScaleX, ScaleY);    // Set scale
        }
    backgroundTexture.setRepeated(false);
    background.setTexture(backgroundTexture);

    // Create sprite1 and apply texture1
    Texture texture1;
        if (!texture1.loadFromFile("Spritev1.png")){
            cerr << "failed to load image" << endl;
            exit(1);
        }
    texture1.setRepeated(false);
    texture1.setSmooth(true);
    Sprite sprite1;
    sprite1.setTexture(texture1);
    sprite1.setOrigin(50.f,50.f);
    
    // Sprite coordinates
    int x=window.getSize().x/2.;
    int y=window.getSize().y/2.;

    // Flags for key pressed
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;
    float sprite1Rotation=0.f;

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
        if (leftFlag) x-=SPRITE_SPEED;
        if (rightFlag) x+=SPRITE_SPEED;
        if (upFlag) y-=SPRITE_SPEED;
        if (downFlag) y+=SPRITE_SPEED;

        // Check screen boundaries
        if (x<0) x=0;
        if (r1.left+r1.width >= x && r1.top+r1.height >= y){
            leftFlag = false;
            upFlag = false;
        }
        if (x>(int)window.getSize().x) x=window.getSize().x;
        if (y<0) y=0;
        if (y>(int)window.getSize().y) y=window.getSize().y;

        // Clear the window and apply background
        window.clear(Color::White);

        window.draw(background);

        //////////////////////////////////////////////////////

        Sprite HG_1;
        Texture HG_1_Texture;
        HG_1_Texture.loadFromFile("map/gauche_haut_1.png");

        HG_1.setTexture(HG_1_Texture);
        HG_1.setScale(ScaleX*1.76, ScaleY*1.76);

        Sprite HG_2;
        Texture HG_2_Texture;
        HG_2_Texture.loadFromFile("map/gauche_haut_2.png");

        HG_2.setTexture(HG_2_Texture);
        HG_2.setScale(ScaleX*1.76, ScaleY*1.76);
        
        HG_2.setPosition(HG_1_Texture.getSize().x*HG_1.getScale().x,0);

        Sprite HG_3;
        Texture HG_3_Texture;
        HG_3_Texture.loadFromFile("map/gauche_haut_3.png");

        HG_3.setTexture(HG_3_Texture);
        HG_3.setScale(ScaleX*1.76, ScaleY*1.76);

        HG_3.setPosition((HG_1_Texture.getSize().x*HG_1.getScale().x)+(HG_2_Texture.getSize().x*HG_2.getScale().x),0);



        // récupération de la boîte englobante de l'entité
        sf::FloatRect boundingBox = sprite1.getGlobalBounds();


        // test de collision avec un autre rectangle (comme par exemple la boîte englobante d'une autre entité)
        sf::FloatRect otherBox = HG_1.getGlobalBounds();
        if (boundingBox.intersects(otherBox))
        {
            cout << "Collision" << endl;
        }
        
        //////////////////////////////////////////////////////

        // Rotate and draw the sprite1

        
        sprite1.setPosition(x,y);
        sprite1.setRotation(sprite1Rotation);
        window.draw(sprite1);
        window.display();
    }
    return 0;
}