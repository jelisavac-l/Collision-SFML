//This is not a big project so all the OPP stuff is unnecessary

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Function definitions

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Collision detection test");

	//DEFINITIONS

    bool good = true;
    

	//Player shape
	sf::RectangleShape player(sf::Vector2f(64.0f, 64.0f));
    player.setOrigin(sf::Vector2f(32.0f, 32.0f));
    player.setPosition(sf::Vector2f(640.0f, 360.0f));

    //Player texture
    sf::Texture playerTextureGood;
    sf::Texture playerTextureBad;
    playerTextureGood.loadFromFile("assets/PTGood.png");
    playerTextureBad.loadFromFile("assets/PTBad.png");
    player.setTexture(&playerTextureGood);

    //Background
    sf::RectangleShape background(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/bp.png");
    background.setTexture(&backgroundTexture);

    //Collision objects array
    sf::RectangleShape object1(sf::Vector2f(25.0f, 25.0f));
    sf::RectangleShape object2(sf::Vector2f(25.0f, 25.0f));
    sf::RectangleShape object3(sf::Vector2f(25.0f, 25.0f));

    object1.setPosition(sf::Vector2f(0.0f, 0.0f));
    object2.setPosition(sf::Vector2f(640.0f, 142.0f));
    object3.setPosition(sf::Vector2f(1200.0f, 256.0f));
    


    //Deltatime
    float deltaTime = 0.0f;
    sf::Clock clock;

    //Click sound
    sf::SoundBuffer clickBuffer;
    if(!clickBuffer.loadFromFile("audio/Click.ogg"))
    {
        std::cerr << "Failed to load click sound!\n";
    }

    sf::Sound click;
    click.setBuffer(clickBuffer);
    //click.setVolume(20.0f);
	
	//Game loop
    while (window.isOpen())
    {
        //dTime
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window.close();
            
            if(evnt.type == sf::Event::KeyPressed)
            {
                if(evnt.key.code == sf::Keyboard::Tab)
                {
                    good = !good;
                    switch(good)
                    {
                        case true: player.setTexture(&playerTextureGood); click.play(); break;
                        case false: player.setTexture(&playerTextureBad); click.play(); break;     
                    }
                }
            }

        }

        //Movement
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.move(sf::Vector2f(-300.0f * deltaTime, 0.0f));
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.move(sf::Vector2f(300.0f * deltaTime, 0.0f));
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player.move(sf::Vector2f(0.0f, -300.0f * deltaTime));
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player.move(sf::Vector2f(0.0f, 300.0f * deltaTime));
            }

		//Drawing & displaying DON'T FORGET TO PUT EVERY ELEMENT HERE!
		
        window.clear();
        window.draw(background);
        
        //It looks like I can't pass an array as an argument to draw();
       window.draw(object1);
       window.draw(object2);
       window.draw(object3);

        window.draw(player);
        window.display();
    }

    return 0;
}

//Implementations
