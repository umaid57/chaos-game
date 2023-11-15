// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;
void addpointTriangle(vector<Vector2f>& points, vector<Vector2f> vertices) {
    int randVert = rand() % 3;
    int dotX = (points[points.size() - 1].x + vertices[randVert].x) / 2;
    int dotY = (points[points.size() - 1].y + vertices[randVert].y) / 2;
    Vector2f point(dotX, dotY);

    points.push_back(point);
}
void addpointSquare(vector<Vector2f>& points, vector<Vector2f> vertices, int* prevVert) {
    int randVert = rand() % 4;
    while (randVert == *prevVert) {
        randVert = rand() % 4;
    }
    *prevVert = randVert;
    int dotX = (points[points.size() - 1].x + vertices[randVert+1].x) / 2;
    int dotY = (points[points.size() - 1].y + vertices[randVert+1].y) / 2;
    Vector2f point(dotX, dotY);

    points.push_back(point);   
}
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
    sf::Text text1;
    text.setFont(font);

    // set the character size
    text.setCharacterSize(50); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);
    
    text1 = text;
    // set the string to display
    text.setString("Click at three different points to form a triangle!");

    // set the text style
   // text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(500, 0);
    
    int* prevVert = new int;
    *prevVert = rand() % 4;

    
    bool isSquare = false;

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
                    if(event.mouseButton.x < 200 && vertices.size() == 0){
                        isSquare = true;
                        
                    }
                    if(vertices.size() < 5 && isSquare)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0 && vertices.size() >= 3)
                    {
                        
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        ///fourth click
                        ///push back to points vector
                    }
                    else {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (isSquare) {
            text.setString("Click at 4 points to form a square");

        }
        
        if ((vertices.size() == 3 && !isSquare) || (vertices.size() == 5 && isSquare)) {
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
                
        if(points.size() > 0 && points.size() < 10000)
        {
            
            if (isSquare) {
                text.setString("Square fractal!");
                addpointSquare(points, vertices, prevVert);
                addpointSquare(points, vertices, prevVert);
                addpointSquare(points, vertices, prevVert);
                addpointSquare(points, vertices, prevVert);
                addpointSquare(points, vertices, prevVert);
            }
            else {
                text.setString("The Sierpinski triangle!");
                addpointTriangle(points, vertices);
                addpointTriangle(points, vertices);
                addpointTriangle(points, vertices);
                addpointTriangle(points, vertices);
                addpointTriangle(points, vertices);
            }


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
        window.draw(text);

        text1.setString("Click the square to generate a square fractal");
        text1.setPosition(Vector2f(0, 100));
        window.draw(text1);
        
        RectangleShape rectShape(Vector2f(50, 50));
        rectShape.setPosition(Vector2f(0, 200));
        rectShape.setFillColor(Color::Magenta);
        window.draw(rectShape);

        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(5,5));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Magenta);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++) {
            CircleShape dot(2);
            dot.setPosition(Vector2f(points[i].x, points[i].y));
            dot.setFillColor(Color::Yellow);
            window.draw(dot);
        }

        window.display();
    }
    delete prevVert;
}