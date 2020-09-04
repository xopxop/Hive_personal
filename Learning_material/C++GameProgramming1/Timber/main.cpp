/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 10:34:40 by dthan             #+#    #+#             */
/*   Updated: 2020/09/04 05:53:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

//Function decleration
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];
//Where is the player/branch?
//Left or RIGHT
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main() {
	//Create a video mode object
	sf::VideoMode vm(1920, 1080);

	//Create and open a window for the game
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	sf::Texture textureBrackground;
	// Load a graphic into the texture
	textureBrackground.loadFromFile("graphics/background.png");

	// Create a sprite
	sf::Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBrackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);
	
	//Make a tree sprite
	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	//Prepare the bee
	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	//Is the bee currently moving?
	bool beeActive = false;
	//How fast can the bee fly
	float beeSpeed = 0.0f;

	//Make 3 cloud sprites from 1 texture
	sf::Texture textureCloud;
	//Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");
	//3 New sprites with the same texture
	sf::Sprite spriteCloud1;
	sf::Sprite spriteCloud2;
	sf::Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	//Position the coulds off screen
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);
	//Is the bee currently moving?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	//How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Variables to control time itself
	sf::Clock clock;

	//Time bar
	sf::RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	sf::Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Track whether the game is running
	bool paused = true;

	//Draw some text
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	//We need to choose a font
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	//Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	//Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//Choose a color
	messageText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	//Position the text
	sf::FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	//Prepare 6 branches
	sf::Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	//Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		//Set the sprite origin to dead center
		//We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	//Prepare the player
	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	sf::Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	//The player start on the left
	side playerSide = side::LEFT;

	//Prepare the gravestone
	sf::Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	sf::Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	//Prepare the axe
	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//Prepare the flying log
	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	sf::Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	//Some useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	//Controll the player input
	bool acceptInput = false;

	//Prepare the sound
	sf::SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	sf::Sound chop;
	chop.setBuffer(chopBuffer);

	sf::SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	sf::Sound death;
	death.setBuffer(deathBuffer);
	
	//Out of time
	sf::SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	sf::Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	while(window.isOpen()) {
		/*
		***************************
		Handle the player input
		***************************
		*/

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && !paused) {
				//Listen for key presses again
				acceptInput = true;

				//hide the axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}

		// Start the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			paused = false;

			//Reset the time and the score
			score = 0;
			timeRemaining = 5;

			//Make all the branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}

			//Make sure the gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			//move the player into position
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}

		//Wrap the player controls to
		//Make sure we are accepting input
		if (acceptInput) {
			//More code here next...
			//First handle pressing the right cursor key
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				//Make sure the player is on the right
				playerSide = side::RIGHT;
				score++;

				//Add the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);

				//update the branches
				updateBranches(score);

				//Set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}
			
			//Handle the left cursor key
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				//Make sure the player is on the left
				playerSide = side::LEFT;
				score++;

				//Add the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);

				//update the branches
				updateBranches(score);

				//Set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				//Play the chop sound
				chop.play();
			}
		}

		/*
		***************************
		Update the scence
		***************************
		*/
		if (!paused) {

			//Measure time
			sf::Time dt = clock.restart();

			//Substract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			//size up the time bar
			timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				//pause the game
				paused =  true;

				//Change the message shown to the player
				messageText.setString("Out of time!!");

				//Reposition the text based on its new size
				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				//Play the out of time sound
				outOfTime.play();
			}

			//Setup the bee
			if (!beeActive) {
				//How fast is the bee
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;
			
				//How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			} else {
				//Move the bee

				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

				//Has the bee reached the right hand edge of the screen?
				if (spriteBee.getPosition().x < -100) {
					//Set it up ready to be a whole new bee next frame
					beeActive = false;
				}
			}

			//Manage the clouds
			//Cloud 1
			if (!cloud1Active) {
				//How fast is the cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);
			
				//How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			} else {
				//Move the cloud
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);

				//Has the cloud reached the right hand edge of the screen?
				if (spriteCloud1.getPosition().x > 1920) {
					//Set it up ready to be a whole new bee next frame
					cloud1Active = false;
				}
			}
		
			//Cloud 2
			if (!cloud2Active) {
				//How fast is the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);
			
				//How high is the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			} else {
				//Move the cloud
				spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);

				//Has the cloud reached the right hand edge of the screen?
				if (spriteCloud2.getPosition().x > 1920) {
					//Set it up ready to be a whole new bee next frame
					cloud2Active = false;
				}
			}

			//Cloud 3
			if (!cloud3Active) {
				//How fast is the cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);
			
				//How high is the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			} else {
				//Move the cloud
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);

				//Has the cloud reached the right hand edge of the screen?
				if (spriteCloud3.getPosition().x > 1920) {
					//Set it up ready to be a whole new bee next frame
					cloud3Active = false;
				}
			}

			//Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
			
			//Update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT) {
					//Move the sprite to the left side
					branches[i].setPosition(610, height);
					//Flip the sprite round the other way
					branches[i].setRotation(180);
				} else if (branchPositions[i] == side::RIGHT) {
					//Move the sprite to the right side
					branches[i].setPosition(1330, height);
					//Set the sprite rotation to normal
					branches[i].setRotation(0);
				} else {
					//Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

			//Handle a flying log
			if(logActive) {
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				//Has the log reached the left/right hand edge
				if (spriteLog.getPosition().x < - 100 || spriteLog.getPosition().y > 2000) {
					//Set it up ready to be a while new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			//Has the player been squished by a branch?
			if (branchPositions[5] == playerSide) {
				//death
				paused = true;
				acceptInput = false;

				//Draw the gravestone
				spriteRIP.setPosition(525, 760);

				//hide the player
				spritePlayer.setPosition(2000, 660);

				//Change the text of the message
				messageText.setString("SQUISHED!");

				//Center it on the screen
				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				death.play();
			}

		} //End if (!pause)
		/*
		***************************
		Draw the scence
		***************************
		*/
		//Clear everything from the last frame
		window.clear();
		
		// Draw our game scene here
		window.draw(spriteBackground);

		//Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		//Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}

		//Draw the Tree
		window.draw(spriteTree);

		//Draw the player
		window.draw(spritePlayer);

		//Draw the axe
		window.draw(spriteAxe);

		//Draw the flying log
		window.draw(spriteLog);

		//Draw the gravestone
		window.draw(spriteRIP);
		
		//Draw the insect
		window.draw(spriteBee);

		//Draw the score
		window.draw(scoreText);

		//Draw the time bar
		window.draw(timeBar);

		if (paused) {
			//Draw our message
			window.draw(messageText);
		}
		// Show everything we just drew
		window.display();
	}
	return 0;
}

//Function definition
void updateBranches(int seed) {
	//Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}
	//Spawn a new branch at position 0
	//LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
		case 0:
			branchPositions[0] = side::LEFT;
			break;
		case 1:
			branchPositions[0] = side::RIGHT;
			break;
		default:
			branchPositions[0] = side::NONE;
			break;
	}
}
