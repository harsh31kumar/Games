
#include<SFML/Graphics.hpp>
#include<sstream>
#include"Bat.h"
#include"Ball.cpp"
using namespace sf;
int main()
{
	VideoMode vm(960,540);
	RenderWindow window(vm,"Pong Game");
	int score =0;
	int lives = 3;
	Bat bat(960/2,540-20);
	
	Ball ball(960/2,0);
	
	Clock clock;
	
	Text hud;
	Font font;
	font.loadFromFile("font/KOMIKAP_.ttf");
	hud.setFont(font);
	hud.setCharacterSize(30);
	hud.setFillColor(Color::White);
	hud.setPosition(20,20);
	
	
	
	while(window.isOpen()){
	Event event1;
        while (window.pollEvent(event1))
        {
            if (event1.type == event1.Closed)
            {
                window.close();
            }
            
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else
        {
        bat.stopLeft();
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }
        else
        {
        bat.stopRight();
        } 
        
        Time dt = clock.restart();
        bat.update(dt);
        
        ball.update(dt);
        
        std::stringstream ss;
        ss<<"Score "<<score<<" Lives "<<lives;
        hud.setString(ss.str());
        
        if(ball.getPosition().left<0 || ball.getPosition().left +ball.getPosition().width>window.getSize().x)
        {
        ball.reboundSides();
        }
        
        if(ball.getPosition().top<0)
        {
        ball.reboundBatOrTop();
        score++;
        }
        
        
        
        if(ball.getPosition().top>window.getSize().y)
        {
        ball.reboundBottom();
        
        lives--;
        
        if(lives<1)
        {
        ss<<"Game Over";
        hud.setString(ss.str());
        score=0;
        lives=3;
        }
        
        }
        
        
        if(ball.getPosition().intersects(bat.getPosition()))
        {
        ball.reboundBatOrTop();
        }
        
        
        
        window.clear(Color::Black);
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        
        window.display();
        }
	return 0;

}

