#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
// g++ -std=c++11 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
// g++ -std=c++11 wtf.cpp -o wtf -lsfml-graphics -lsfml-window -lsfml-system 

//If cube touches the paddles  it bounces off in the opposite direction while the angle of reflection depends on where on the paddle the ball hits and how fast the paddle is moving
//AI maybe
//Optional stuff: screen menu, game ending after 10 points saying who won. Replay button and back to menu button

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");

    sf::Font font;
    if (!font.loadFromFile("/Users/will/Random_codes/C++_stuff/Pong_game/Poppins/Poppins-Bold.ttf")){
        std::cout << "Couldn't load font" << std::endl;
        return 0;
    }

    class ScoreCounter {
        public:
        int score;
        ScoreCounter() : score(0){}

        void incrementScore(){
            score++;
        }

        int getScore() const{
            return score;
        }

        void draw(sf::RenderWindow& window){
            sf::Font font;
            font.loadFromFile("/Users/will/Random_codes/C++_stuff/Pong_game/Poppins/Poppins-Bold.ttf");

            sf::Text text;
            text.setFillColor(sf::Color::White);
            text.setCharacterSize(90);
            text.setPosition(300, 20);
            text.setFont(font);
            text.setString(std::to_string(getScore()));
            window.draw(text);
        }
    };

    class ScoreCounterPlayer2 : public ScoreCounter{
        public:

        void incrementScore(){
            ScoreCounter::incrementScore();
        }
        
        void draw(sf::RenderWindow& window){
            sf::Font font;
            font.loadFromFile("/Users/will/Random_codes/C++_stuff/Pong_game/Poppins/Poppins-Bold.ttf");
            sf::Text text;
            text.setFillColor(sf::Color::White);
            text.setCharacterSize(90);
            text.setFont(font);
            text.setString(std::to_string(getScore()));
            text.setPosition(435, 20);
            window.draw(text);
        }
    };

    ScoreCounter scoreCounter;
    ScoreCounterPlayer2 scoreCounter2;

    sf::SoundBuffer buffer1, buffer2, buffer3;
    if (!buffer1.loadFromFile("/Users/will/Random_codes/C++_stuff/Pong_game/4390__noisecollector__pongblipf4.wav") || !buffer2.loadFromFile("/Users/will/Random_codes/C++_stuff/Pong_game/4391__noisecollector__pongblipf5.wav")
    || !buffer3.loadFromFile("/Users/will/Random_codes/C++_stuff/Pong_game/score_sound.wav")){
        return 1;
    }

    sf::Sound sound1, sound2, sound3;

    sound1.setBuffer(buffer1);
    sound2.setBuffer(buffer2);
    sound3.setBuffer(buffer3);

    sf::RectangleShape dashedLine(sf::Vector2f(15.f, 15.f));
    dashedLine.setFillColor(sf::Color::White);
    dashedLine.setPosition(800 / 2 - 10.f, 0.f); // Set the position of the dashed line to the center of the window


    sf::RectangleShape cube(sf::Vector2f(15, 15));
    cube.setPosition(400, 15);
    cube.setFillColor(sf::Color::White);

    sf::RectangleShape player1(sf::Vector2f(15, 100));
    player1.setFillColor(sf::Color::White);
    player1.setPosition(40, 300);


    sf::RectangleShape player2(sf::Vector2f(15,100));
    player2.setFillColor(sf::Color::White);
    player2.setPosition(740, 300);

    sf::RectangleShape borderTop(sf::Vector2f(800, 15));
    borderTop.setFillColor(sf::Color::White);
    borderTop.setPosition(0, 0);

    sf::RectangleShape borderBottom(sf::Vector2f(800, 15));
    borderBottom.setFillColor(sf::Color::White);
    borderBottom.setPosition(0, window.getSize().y - borderBottom.getSize().y);

    float ball_speed = 0.5f;
    float ball_velocity_x = ball_speed;
    float ball_velocity_y = -ball_speed;


    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
    window.clear();
    for (int i = 0; i < 600 / 15; i += 2) {
    dashedLine.setPosition(800 / 2 - 10.f, i * 15.f);
    window.draw(dashedLine);
}

    //KEYBOARD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        player2.move(0, -2);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        player2.move(0, 2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        player1.move(0, -2);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        player1.move(0,2);
    }
    //PLAYER 2
    if (player2.getGlobalBounds().intersects(borderTop.getGlobalBounds())){
        sf::Vector2f playerPos = player2.getPosition();
        playerPos.y = borderTop.getGlobalBounds().height;
        player2.setPosition(playerPos);
    }
    if (player2.getGlobalBounds().intersects(borderBottom.getGlobalBounds())){
        sf::Vector2f playerPos = player2.getPosition();
        playerPos.y = borderBottom.getGlobalBounds().top - player2.getGlobalBounds().height;
        player2.setPosition(playerPos);
    }

    //CUBE
    window.draw(cube);
    cube.move(ball_velocity_x, ball_velocity_y);
    if (cube.getPosition().y < 15) {
        ball_velocity_y = ball_speed;
        sound1.play();
    }
    if (cube.getPosition().y > 590 - cube.getSize().y) {
        ball_velocity_y = -ball_speed;
        sound1.play();
    }

    if (cube.getGlobalBounds().intersects(player1.getGlobalBounds())){
        ball_speed = 1.5f;
        ball_velocity_x = ball_speed;
        sound2.play();
    }
    if (cube.getGlobalBounds().intersects(player2.getGlobalBounds())){
        ball_speed = 1.5f;
        ball_velocity_x = -ball_speed;
        sound2.play();
    }
    //FOR THE X AXIS IN CASE IT'S NEEDED
    if (cube.getPosition().x < 0) {
        ball_velocity_y = 0.5f;
        ball_velocity_x = -0.5f;
        cube.setPosition(400, 15);
        sound3.play();
        scoreCounter2.incrementScore();
        if (scoreCounter2.score == 10){
            std::cout << "Player 2 wins" <<std::endl;
            window.close();
        }
    }
    if (cube.getPosition().x > 800) {
        ball_velocity_y = 0.5f;
        ball_velocity_x = 0.5f;
        cube.setPosition(400, 15);
        sound3.play();
        scoreCounter.incrementScore();
        if (scoreCounter.score == 10){
            std::cout << "Player 1 wins" <<std::endl; //Change it to menu screen or something
            window.close();
        }
    }
    
    //PLAYER 1
    if (player1.getGlobalBounds().intersects(borderTop.getGlobalBounds())){
        sf::Vector2f playerPos = player1.getPosition();
        playerPos.y = borderTop.getGlobalBounds().height;
        player1.setPosition(playerPos);
    }
    if (player1.getGlobalBounds().intersects(borderBottom.getGlobalBounds())){
        sf::Vector2f playerPos = player1.getPosition();
        playerPos.y = borderBottom.getGlobalBounds().top - player1.getGlobalBounds().height;
        player1.setPosition(playerPos);
    }
    

    // ScoreCounter scoreCounter;
    // scoreCounter.draw(window);
    // ScoreCounterPlayer2 scoreCounter2;
    scoreCounter2.draw(window);
    window.draw(player1);
    window.draw(player2);
    window.draw(borderTop);
    window.draw(borderBottom);
    scoreCounter.draw(window);
    window.display(); 
    }

    return 0;
}
//g++ -std=c++11 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio