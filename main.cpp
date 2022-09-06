//This is not a big project so all the OPP stuff is unnecessary
//EDIT (2nd day into the project): it is necessary and i am not as smart as i thaught :(

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collider.hpp"

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
    Collider *cols[5];
    float posX = 0, posY = 0;
    for(int i = 0; i < 5; i++)
    {    
        cols[i] = new Collider(sf::Vector2f(posX, posY));
        std::cout << "Collider created with coordinates: " << posX << " " << posY << "\n";
        posX += 256.0f;
        posY += 144.0f;
    }
    


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
                

                /*
                //Test for texture change (Press Tab)
                if(evnt.key.code == sf::Keyboard::Tab)
                {
                    good = !good;
                    switch(good)
                    {
                        case true: player.setTexture(&playerTextureGood); click.play(); break;
                        case false: player.setTexture(&playerTextureBad); click.play(); break;     
                    }
                }*/

        }

        //Collision detection

        /*

        Final decision is that while player object intersects with any of collison objects
        variable numberOfCols gets an id of that col. object, and if that number is
        different than 0, it must mean that collision is happening.

        If i try to do it in a for loop, one object would trigger as positive while all
        others would trigger as negative and that will make the whole process loop
        as it gets both positive signal from colliding object and negative signals from
        all the other non-colliding objects.

        I feel like a genius for now :)
        
        */
        int numberOfCols = 0;
        for (size_t i = 0; i < 5; i++)
                {
                    if(cols[i]->getColliderBody().getGlobalBounds().intersects(player.getGlobalBounds()))
                    {
                        numberOfCols = i+1; // Must be +1 because if it collides with cols[0], it won't react
                    }             
                }

                if(numberOfCols != 0)
                {
                    if(good == true){
                            good = false;
                            click.play();
                       }
                }
                else
                {
                if(good == false)
                {
                    good = true;

                }
                }
                switch(good)
                        {
                        case true: player.setTexture(&playerTextureGood); break;
                        case false: player.setTexture(&playerTextureBad); break;     
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
        for (size_t i = 0; i < 5; i++)
        {
            cols[i]->drawCollider(&window);
        }
        
        window.draw(player);
        window.display();
    }

    return 0;
}

//Implementations
