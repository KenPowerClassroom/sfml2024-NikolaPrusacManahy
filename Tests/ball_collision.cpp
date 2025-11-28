#include "pch.h"
#include "../16_SFML_Games/ball_collision.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void cheackBallCollision(float& ballPosX, float& ballPosY,
    float& ballVelocityX, float& ballVelocityY,
    Sprite* blocks, int& blockCount)
{
    ballPosX += ballVelocityX;
    for (int i = 0; i < blockCount; i++)
        if (FloatRect(ballPosX + 3, ballPosY + 3, 6, 6).intersects(blocks[i].getGlobalBounds()))
        {
            blocks[i].setPosition(-100, 0);
            ballVelocityX = -ballVelocityX;
        }

    ballPosY += ballVelocityY;
    for (int i = 0; i < blockCount; i++)
        if (FloatRect(ballPosX + 3, ballPosY + 3, 6, 6).intersects(blocks[i].getGlobalBounds()))
        {
            blocks[i].setPosition(-100, 0);
            ballVelocityY = -ballVelocityY;
        }

    if (ballPosX < 0 || ballPosX > 520)  ballVelocityX = -ballVelocityX;
    if (ballPosY < 0 || ballPosY > 450)  ballVelocityY = -ballVelocityY;
}