#include <bits/stdc++.h>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
using namespace sf;
using namespace std;
int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(640, 480), "Test Shooting Game");
    window.setFramerateLimit(60);
	//Make bullets
	CircleShape bullet;
	bullet.setFillColor(Color::Red);
	bullet.setRadius(5.f);
    vector<CircleShape> bullets;
	bullets.push_back(CircleShape(bullet));
	//Make targets
	RectangleShape target;
	target.setFillColor(Color::Blue);
	target.setSize(Vector2f(50.f, 50.f));
    vector<RectangleShape> targets;
	targets.push_back(RectangleShape(target));
	//Make a shooter
	CircleShape shooter;
	shooter.setFillColor(Color::White);
	shooter.setRadius(50.f);
	shooter.setPosition(window.getSize().x/2-shooter.getRadius(), window.getSize().y-shooter.getRadius()*2-10.f);
	//Make others tools
	Vector2f shooterCenter;
	int shootTime=0;
	int targetSpawnTime=0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type==Event::Closed) window.close();
		}
		//Update shooter position
		shooterCenter=Vector2f(shooter.getPosition().x+shooter.getRadius(), shooter.getPosition().y+shooter.getRadius());
		shooter.setPosition(Mouse::getPosition(window).x, shooter.getPosition().y);
		//Update bullets position
		if (shootTime<5) shootTime++;
		if (Mouse::isButtonPressed(Mouse::Left) && shootTime>=5)
		{
			bullet.setPosition(shooterCenter);
			bullets.push_back(CircleShape(bullet));
			shootTime=0;
		}
		for (size_t i=0; i<bullets.size(); i++)
		{
            bullets[i].move(0.f, -10.f);
			if (bullets[i].getPosition().y<=0) bullets.erase(bullets.begin()+i);
		}
		//Update targets position
		if (targetSpawnTime<20) targetSpawnTime++;
		if (targetSpawnTime>=20)
		{
			target.setPosition((rand()%int(window.getSize().x-target.getSize().x)), 0.f);
			targets.push_back(RectangleShape(target));
			targetSpawnTime=0;
		}
		for (size_t i=0; i<targets.size(); i++)
		{
			targets[i].move(0.f, 5.f);
			if (targets[i].getPosition().y>window.getSize().y) targets.erase(targets.begin()+i);
		}
		//Targets and bullets collision
		if (!targets.empty() && !bullets.empty())
		{
			for (size_t i=0; i<bullets.size(); i++)
			{
				for (size_t k=0; k<targets.size(); k++)
				{
					if (bullets[i].getGlobalBounds().intersects(targets[k].getGlobalBounds()))
					{
						bullets.erase(bullets.begin()+i);
						targets.erase(targets.begin()+k);
						break;
					}
				}
			}
		}
		//Draw
		window.clear();
		window.draw(shooter);
		for (size_t i=0; i <targets.size(); i++)
		{
			window.draw(targets[i]);
		}
		for (size_t i=0; i<bullets.size(); i++)
		{
			window.draw(bullets[i]);
		}
		window.display();
	}
	return 0;
}
