#pragma once

#include <SFML/Graphics.hpp>

void cheackBallCollision(float& ballPosX, float& ballPosY,
    float& ballVelocityX, float& ballVelocityY,
    sf::Sprite* blocks, int& blockCount);