
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

#include <GLUT/GLUT.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

using namespace std;

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

void glWindowHandler(sf::RenderWindow& window, const sf::String& windowName) {
    
    
    // run the program as long as the window is open
    if (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            
            if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
            
        }
    
        // activate the window's OpenGL context
        window.setActive(true);
        glEnable(GL_TEXTURE_2D);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // set background color to red
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

        // generate random color
        GLfloat red = ((GLfloat) rand() / (RAND_MAX));
        GLfloat green = ((GLfloat) rand() / (RAND_MAX));
        GLfloat blue = ((GLfloat) rand() / (RAND_MAX));
        
        
        // draw filled rectangle with a bit of padding (0.1 on each side)
        // NOTE: x coordinate goes from  -1 to 1 and y coordinate goes from  -1 to 1
        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
            glVertex3f(-0.9, -0.9, 0.0);
            glVertex3f(0.9, -0.9, 0.0);
            glVertex3f(0.9, 0.9, 0.0);
            glVertex3f(-0.9, 0.9, 0.0);
        glEnd();
        glFlush();
        
        window.display();
        
        // deactivate the window's OpenGL context
        window.setActive(false);
    }
    

}


void glWindow2Handler(sf::RenderWindow& window, const sf::String& windowName) {
    static int prevX, prexY = 0;
    static float rotX = 0.0;
    
    if (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
          
            if (event.type == sf::Event::MouseMoved) {
                cout << "mouse(" << event.mouseMove.x << "," << event.mouseMove.y << ")" << endl;
            }
        }
        
        window.setActive(true);
        glEnable(GL_TEXTURE_2D);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glutWireTeapot(0.5);
        
        glFlush();
        window.display();
        
        window.setActive(false);
    }
}


void window1Hanlder(sf::RenderWindow& window, const sf::String& windowName) {
    
    static sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    
    if (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                std::cout << "mouse clicked on window named " << windowName.toAnsiString() << std::endl;
            }
            

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        
        window.clear();
        
        
        sf::Text text(windowName, font, 50);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        window.display();
    }
}

void window2Hanlder(sf::RenderWindow& window, const sf::String& windowName) {
    
    static sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    
    if (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                std::cout << "mouse clicked on window named " << windowName.toAnsiString() << std::endl;
            }
            
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        
        window.clear();
        
        
        sf::Text text(windowName, font, 50);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        window.display();
    }
}


void runWithMultipleWindows() {
    // create multiple windows and manage in single thread
    //
    // On OS X, windows and events must be managed in the main thread
    // Yep, that's true. Mac OS X just won't agree if you try to create a window or handle events in a thread other than the main one.
    // src: https://www.sfml-dev.org/tutorials/2.0/window-window.php
    
    sf::RenderWindow win1(sf::VideoMode(800, 600), "window 1");
    sf::RenderWindow win2(sf::VideoMode(800, 600), "window 2");
    sf::RenderWindow glWin1(sf::VideoMode(800, 600), "OpenGL Window #1");
    sf::RenderWindow glWin2(sf::VideoMode(800, 600), "OpenGL Window #2");
    
    sf::Vector2i firstWindowPosition = {200,200};
    sf::Vector2i windowXandYPositionOffset = {100,100};
    
    win1.setPosition(firstWindowPosition);
    win2.setPosition(win1.getPosition() + windowXandYPositionOffset);
    glWin1.setPosition(win2.getPosition() + windowXandYPositionOffset);
    glWin2.setPosition(glWin1.getPosition() + windowXandYPositionOffset);
    
    while (true) {
        window1Hanlder(win1, "Window #1");
        window2Hanlder(win2, "Window #2");
        glWindowHandler(glWin1, "OpenGL Window #1");
        glWindow2Handler(glWin2, "OpenGL Window #2");
        sf::sleep(sf::milliseconds(200));
    }
    
}


int main(int, char const**)
{
    runWithMultipleWindows();
    
    return 0;
    
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
        //drawRandomColorRectangleWithOpenGL();
        
        
        // set background color to red
//        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
