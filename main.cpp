#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

sf::RectangleShape createRectangle(sf::Vector2f bottomLeft, sf::Vector2f bottomRight, sf::Color color)
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

int main()
{
    // Créer la fenêtre{0, 414}, {78, 429},{276, 279}, {400, 234},{730, 195}, {882, 66}
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Rectangle");

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

    // Boucle principale
    while (window.isOpen())
    {
        // Gérer les événements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Dessiner les rectangles
        window.clear();
        for (const auto& rectangle : rectangles)
        {
            window.draw(rectangle);
        }
        window.display();
    }

    return 0;
}
