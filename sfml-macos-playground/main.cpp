
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

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

void scratch() {
    std::ifstream fin;
    fin.open(resourcePath() + "readme.txt");
    std::string line;
    std::getline(fin, line);
    std::cout << line << std::endl;
    fin.close();
}

sf::Texture randomTexture() {
    sf::Texture texture;
    auto width = 200;
    auto height = 200;
    texture.create(width, height);
    
    auto pixelUint8Count = width * height * 4;
    
    std::vector<sf::Uint8> pixels(width * height * 4);

    for (int i = 0; i < (pixelUint8Count); i+=4) {
        pixels[i] = (rand() % 256); // red
        pixels[i+1] = (rand() % 256); // green
        pixels[i+2] = (rand() % 256); // blue
        pixels[i+3] = (255); // alpha
    }
    texture.update(&pixels[0]);
    return texture;
}

void drawRandomColorRectangleWithOpenGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // generate random color
    GLfloat red = ((GLfloat) rand() / (RAND_MAX));
    GLfloat green = ((GLfloat) rand() / (RAND_MAX));
    GLfloat blue = ((GLfloat) rand() / (RAND_MAX));
    
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();

}
int main(int, char const**)
{
    scratch();
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    
    
    sf::View view = window.getDefaultView();
    view.zoom(2.0f);
    window.setView(view);
    
    //sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    //window.setVerticalSyncEnabled(true);
    
    // activate the window
    //window.setActive(true);
    
    //glEnable(GL_TEXTURE_2D);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    
    
    
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    //music.play();
    
    sf::Texture rndTxt = randomTexture();
    sf::Sprite randomSprite(rndTxt);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            std::cout << "mouse (x,y): (" << localPosition.x << ", " << localPosition.y << ")" << std::endl;
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                rndTxt = randomTexture();
                randomSprite = sf::Sprite(rndTxt);
                randomSprite.setPosition(localPosition.x, localPosition.y);
            
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // Clear screen
        //window.clear();

        // Draw the sprite
        //window.draw(sprite);

        // Draw the string
        //window.draw(text);
        
        
        //window.draw(randomSprite);
        drawRandomColorRectangleWithOpenGL();
        
        
        // set background color to red
//        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
