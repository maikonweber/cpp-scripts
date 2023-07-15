#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong Game");

    const int paddleWidth = 15;
    const int paddleHeight = 100;
    sf::RectangleShape playerPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    playerPaddle.setPosition(30, windowHeight / 2 - paddleHeight / 2);
    playerPaddle.setFillColor(sf::Color::White);

    sf::RectangleShape computerPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    computerPaddle.setPosition(windowWidth - 30 - paddleWidth, windowHeight / 2 - paddleHeight / 2);
    computerPaddle.setFillColor(sf::Color::White);

    const int ballRadius = 10;
    sf::CircleShape ball(ballRadius);
    ball.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);
    ball.setFillColor(sf::Color::White);

    float ballSpeedX = 4.0f;
    float ballSpeedY = 4.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerPaddle.getPosition().y > 0) {
            playerPaddle.move(0, -5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerPaddle.getPosition().y + paddleHeight < windowHeight) {
            playerPaddle.move(0, 5);
        }

        ball.move(ballSpeedX, ballSpeedY);

        if (ball.getPosition().y <= 0 || ball.getPosition().y >= windowHeight - ballRadius * 2) {
            ballSpeedY = -ballSpeedY;
        }

        if (ball.getGlobalBounds().intersects(playerPaddle.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(computerPaddle.getGlobalBounds())) {
            ballSpeedX = -ballSpeedX;
        }

        if (ball.getPosition().x <= 0 || ball.getPosition().x >= windowWidth - ballRadius * 2) {
            ball.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);
            ballSpeedX = -ballSpeedX;
        }

        float computerPaddleY = ball.getPosition().y + ballRadius - paddleHeight / 2;
        if (computerPaddleY < 0) computerPaddleY = 0;
        if (computerPaddleY + paddleHeight > windowHeight) computerPaddleY = windowHeight - paddleHeight;
        computerPaddle.setPosition(windowWidth - 30 - paddleWidth, computerPaddleY);

        window.clear();
        window.draw(playerPaddle);
        window.draw(computerPaddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}