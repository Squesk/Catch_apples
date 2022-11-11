#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <vector>

bool end = false;
int points = 0;

float GetRandomNumber(std::mt19937& random_generator, float from, float to) {
    std::uniform_real_distribution<float> dis(from, to);
    return dis(random_generator);
}
std::mt19937 random_generator(1337);


class Tray
{
public:
    sf::RectangleShape sprite;
    Tray(int pos_x, int pos_y)
    {
        sprite = sf::RectangleShape(sf::Vector2f(100, 10));
        sprite.setFillColor(sf::Color(180,200,180));
        sprite.setPosition(pos_x,pos_y);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }


    float tray_speed = 0.2;



    void movement_and_collision(sf::RenderWindow &window)
    {
        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if(mouse_position.x <= 500 && mouse_position.x >= 0)
        {
            sprite.setPosition(mouse_position.x,650);
        }

    }

    float pos_x()
    {
        return sprite.getPosition().x;
    }

    float pos_y()
    {
        return sprite.getPosition().y;
    }
};

class Apple
{
public:
    sf::Sprite sprite;

    Apple(std::string file_name,int pos_x, int pos_y)
    {
        sf::Texture *texture;
        texture = new sf::Texture;
        if(!texture->loadFromFile(file_name))
        {
            std::cout << "Nie mozna otworzyc pliku";
        }

        sprite.setTexture(*texture);
        sprite.setScale(0.09765625,0.09765625);
        sprite.setPosition(pos_x,pos_y);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

    float y_speed = 0.2;

    void movement()
    {
        sprite.move(0,y_speed);
    }



    void out_of_map()
    {
        if(sprite.getPosition().y >= 700)
        {
            end = true;

        }
    }



    void collision_with_tray(Tray& tray)
    {

        if(sprite.getPosition().y >= 600 && sprite.getPosition().x >= (tray.pos_x()-50) && (sprite.getPosition().x) <= (tray.pos_x()+100))
        {
            points++;
            sprite.setPosition(GetRandomNumber(random_generator,0,550),GetRandomNumber(random_generator,-3000,-50));
            std::cout << "points: " << points << std::endl;
        }

    }

};


class Background
{
public:

    sf::Sprite sprite;

    Background(std::string file_name,int pos_x, int pos_y)
    {
        sf::Texture *texture;
        texture = new sf::Texture;
        if(!texture->loadFromFile(file_name))
        {
            std::cout << "Nie mozna otworzyc pliku";
        }

        sprite.setTexture(*texture);
        sprite.setScale(2.15,2.15);
        sprite.setPosition(pos_x,pos_y);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }
};

int main() {

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(600, 700), "Catch Apples");

    Tray tray(250,650);

    window.setMouseCursorVisible(false);


    Background background("C:/Users/filof/OneDrive/Pulpit/Qt/Project1/catch_apples/bg.jpg",0,0);


    std::vector<Apple> apples;

    for(auto i=0; i<10; i++)
    {


        Apple apple("C:/Users/filof/OneDrive/Pulpit/Qt/Project1/catch_apples/apple.png",GetRandomNumber(random_generator,0,550),GetRandomNumber(random_generator,-3000,-50));
        apples.emplace_back(apple);

    }


    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();


        }



        window.clear(sf::Color::Black);

        background.draw(window);

        if(end == false)
        {
            tray.draw(window);
            tray.movement_and_collision(window);




            for(auto &i:apples)
            {
                i.draw(window);
                i.movement();
                i.out_of_map();
                i.collision_with_tray(tray);
            }

        }


        window.display();


    }

    return 0;
}
