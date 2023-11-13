// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Fractal", Style::Default);

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.jpg");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    sf::Font font;
    font.loadFromFile("fonts/Octosquares.ttf");

    sf::Text text;
    text.setFont(font);
    // set the string to display
    text.setString("Click at three different points to form a triangle!");

    // set the character size
    text.setCharacterSize(50); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);
    


    // set the text style
   // text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(500, 0);
    


	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        ///fourth click
                        ///push back to points vector
                    }
                }
            }
        }
        
        if (vertices.size() == 3 && points.size() == 0) {
            text.setString("Click anywhere on screen to begin!");
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/
                
        if(points.size() > 0 && points.size() < 2000)
        {
            text.setString("The Sierpinski triangle!");
            int randVert = rand() % 3;
            int dotX = (points[points.size() - 1].x + vertices[randVert].x) / 2;
            int dotY = (points[points.size() - 1].y + vertices[randVert].y) / 2;
            points.push_back(Vector2f(dotX, dotY));
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
        }

        /*
		****************************************
		Draw
		****************************************
		*/
       
        window.clear();

        window.draw(spriteBackground);
        // inside the main loop, between window.clear() and window.display()
        window.draw(text);

        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Magenta);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++) {
            CircleShape dot(2.5);
            dot.setPosition(Vector2f(points[i].x, points[i].y));
            dot.setFillColor(Color::Yellow);
            window.draw(dot);
        }

        window.display();
    }
}