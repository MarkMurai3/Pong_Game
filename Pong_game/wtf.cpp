#include <SFML/Graphics.hpp>

int main()
{
    // Create the game window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    // Create the paddles and ball
    sf::RectangleShape paddle1(sf::Vector2f(20, 100));
    paddle1.setPosition(50, 250);

    sf::RectangleShape paddle2(sf::Vector2f(20, 100));
    paddle2.setPosition(730, 250);

    sf::CircleShape ball(10);
    ball.setPosition(395, 295);

    // Set the ball's initial velocity
    float ball_speed = 0.2f;
    float ball_velocity_x = -ball_speed;
    float ball_velocity_y = ball_speed;

    // Game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the ball
        ball.move(ball_velocity_x, ball_velocity_y);

        // Check for collisions with walls
        if (ball.getPosition().y < 0 || ball.getPosition().y > 590)
            ball_velocity_y = -ball_velocity_y;

        // Check for collisions with paddles
        if (ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()))
            ball_velocity_x = -ball_velocity_x;

        // Move the paddles with the keyboard
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            paddle1.move(0, -0.3f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            paddle1.move(0, 0.3f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            paddle2.move(0, -0.3f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            paddle2.move(0, 0.3f);

        // Clear the screen
        window.clear(sf::Color::Black);

        // Draw the paddles and ball
        window.draw(paddle1);
        window.draw(paddle2);
        window.draw(ball);

        // Display the frame
        window.display();
    }

    return 0;
}
