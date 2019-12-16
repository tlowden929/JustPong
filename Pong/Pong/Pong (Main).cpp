// SFML1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "bat.h"
#include "ball.h"

using namespace sf;

int main()
{
	int windowWidth = 1024;
	int windowHeight = 768;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

	int score = 0;
	int lives = 3;

	Bat bat(windowWidth / 2, windowHeight - 20);
	Ball ball(windowWidth / 2, 1);

	Text hud;
	Font font;
	font.loadFromFile("DS-DIGIT.ttf");

	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		//Player Input

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			bat.moveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			bat.moveRight();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		//Update Frame

		if (ball.getPosition().top > windowHeight) {
			ball.hitBottom();

			lives--;
			if (lives < 1) {
				score = 0;
				lives = 3;
			}
		}
		if (ball.getPosition().top < 0) {
			ball.reboundBatorTop();

			score++;
		}
		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth) {
			ball.reboundSides();
		}
		if (ball.getPosition().intersects(bat.getPosition())) {
			ball.reboundBatorTop();
		}
		ball.update();
		bat.update();
		std::stringstream ss;
		ss << "Score: " << score << "    Lives: " << lives;
		hud.setString(ss.str());

		//Draw the Frame

		window.clear(Color(26, 128, 182, 255));
		window.draw(bat.getShape());
		window.draw(ball.getShape());

		window.draw(hud);
		window.display();
	}
	
	
	return 0;  
}

