
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>



using namespace sf;

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int i,j;

int main(int, char const**)
{
    
//--------------------- Set up -----------------------------------
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 700), "ECE3220 Final Project");
/*
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

 

 
    
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Boss Camera", font, 50);
    text.setFillColor(sf::Color::Black);

    // Load a music to play
*    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
*/

    // Load sprites to display
    sf::Texture texture;
    if (!texture.loadFromFile("settings.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Sprite sprite( texture );
        
    int gridx, gridy;
    RectangleShape grid[8][8];
    
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j<8 ; j++ ){
            gridx = (25+i*51);
            gridy = (25+j*51);
            RectangleShape newPix(sf::Vector2f(50, 50));
            newPix.setPosition( gridx, gridy );
            newPix.setFillColor(sf::Color::White);
            grid[i][j] = newPix;
        }
    }
    
    sf::RectangleShape rectangle(sf::Vector2f( 700, 700 ));
    rectangle.setFillColor(sf::Color(72, 80, 94));
    rectangle.setPosition(0, 0);

//---------------------- Draw -------------------------
    // Play the music
//    music.play();

    
    // Start the game loop
    while (window.isOpen())
    {
        
        window.draw(rectangle);
        
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();
        // Draw Rectangle First
        window.draw(rectangle);
        
        
        // Draw the sprite
        window.draw(sprite);
        
        for( i=0 ; i < 8 ; i++ ){
            for( j=0 ; j<8 ; j++ ){
                window.draw( grid[i][j] );
            }
        }
        
        // Draw the string
    //    window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
