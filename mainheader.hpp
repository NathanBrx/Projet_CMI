#include <SFML/Graphics.hpp>
using namespace sf;

class Perso : public Sprite {
    public :

        Perso(float x,float y,float rotation,int pvmax,int speed,int atk,Sprite persoSprite);

        void damage_taken(int atk); //méthode pour réduire les pv du personnage 
        void speed_modif(int speed);// modifier la vitesse du personnage 
        void SetX(float x);
        void SetY(float y);
        float GetRotation();
        float GetX();
        float GetY();
        int GetSpeed();
        void checkAlive();
        Sprite persoSprite ; //attribut sprite du personnage

    private :

        float  x,y ; // position de l'entité
        float rotation;
        int pvmax; // pv max du perso 
        int pv = pvmax ; // pv de l'entité
        int speed ; // vitesse de l'entité 
        int atk ;
        int alive = 1; // booléen qui indique si le perso est mort ou vivant (1=vivant, 0=mort )
};

class Projectile : public Sprite {
    
    public:

        Projectile(float x,float y,float direction,int vitesse,Sprite projectileSprite);
        Sprite projectileSprite; // sprite

    private:

        float x,y;
        float direction;
        int vitesse; //déplacement pixel par seconde
//        FloatRect hitbox;
        int Xlimite;
        int Ylimite;
};

class Background {
    public :

        Background(Sprite backgroundSprite);

        sf::RectangleShape Background::createRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight, sf::Color color);
        void Background::setBackground(float ScaleX, float ScaleY);
        Sprite backgroundSprite ; //attribut sprite du background
        Texture backgroundTexture; //attribut texture du background

        // Créer des points pour définir les rectangles
        std::vector<sf::Vector2f> borduresPoints;
        std::vector<sf::Vector2f> portesPoints;
        
};