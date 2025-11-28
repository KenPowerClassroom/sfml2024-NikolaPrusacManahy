#include "pch.h"            
#include "gtest/gtest.h"
#include "../16_SFML_Games/ball_collision.h""
#include <SFML/Graphics.hpp>


using namespace sf;

// Helper to create a block sprite with a valid size
Sprite makeBlock(float x, float y)
{
    static Texture dummyTex;
    static bool created = false;

    if (!created)
    {
        // 32x16 empty texture; enough for getGlobalBounds() to work
        dummyTex.create(32, 16);
        created = true;
    }

    Sprite block(dummyTex);
    block.setPosition(x, y);
    return block;
}

// 1) Hitting a block horizontally reverses X and removes the block
TEST(BallCollisionTest, HorizontalBlockCollisionReversesXAndRemovesBlock)
{
    float x = 50.f;
    float y = 50.f;
    float vx = 5.f;
    float vy = 0.f;

    Sprite blocks[1];
    // After cheackBallCollision: x becomes 55, y stays 50
    // Collision rect: (x+3, y+3, 6, 6) -> (58, 53)
    blocks[0] = makeBlock(58.f, 53.f);
    int blockCount = 1;

    cheackBallCollision(x, y, vx, vy, blocks, blockCount);

    EXPECT_FLOAT_EQ(x, 55.f);   // moved by vx
    EXPECT_FLOAT_EQ(y, 50.f);
    EXPECT_FLOAT_EQ(vx, -5.f);  // X reversed
    EXPECT_FLOAT_EQ(vy, 0.f);   // Y unchanged
    EXPECT_LT(blocks[0].getPosition().x, 0.f); // block moved off-screen (-100,0)
}

// 2) Hitting a block vertically reverses Y and removes the block
TEST(BallCollisionTest, VerticalBlockCollisionReversesYAndRemovesBlock)
{
    float x = 100.f;
    float y = 100.f;
    float vx = 0.f;
    float vy = 5.f;

    Sprite blocks[1];
    // First, x += vx (still 100), no block there.
    // Then y += vy -> 105; collision rect is (x+3, y+3) -> (103, 108)
    // We want NO hit before moving, and a hit after moving:
    blocks[0] = makeBlock(103.f, 110.f);   // <-- changed from 108 to 110
    int blockCount = 1;

    cheackBallCollision(x, y, vx, vy, blocks, blockCount);

    EXPECT_FLOAT_EQ(x, 100.f);
    EXPECT_FLOAT_EQ(y, 105.f);
    EXPECT_FLOAT_EQ(vx, 0.f);
    EXPECT_FLOAT_EQ(vy, -5.f);             // Y reversed
    EXPECT_LT(blocks[0].getPosition().x, 0.f); // removed
}

// 3) Ball crossing the right border bounces on X
TEST(BallCollisionTest, BallBouncesOffRightWall)
{
    float x = 519.f;   // close to 520
    float y = 200.f;
    float vx = 5.f;    // moving right
    float vy = 0.f;

    Sprite blocks[1];
    int blockCount = 0; // no blocks

    cheackBallCollision(x, y, vx, vy, blocks, blockCount);

    // x becomes 524, then condition (x > 520) flips vx
    EXPECT_FLOAT_EQ(vx, -5.f);
    EXPECT_FLOAT_EQ(vy, 0.f);
}

// 4) Ball crossing the bottom border bounces on Y
TEST(BallCollisionTest, BallBouncesOffBottomWall)
{
    float x = 200.f;
    float y = 449.f;   // close to 450
    float vx = 0.f;
    float vy = 5.f;    // moving down

    Sprite blocks[1];
    int blockCount = 0; // no blocks

    cheackBallCollision(x, y, vx, vy, blocks, blockCount);

    // y becomes 454, then condition (y > 450) flips vy
    EXPECT_FLOAT_EQ(vx, 0.f);
    EXPECT_FLOAT_EQ(vy, -5.f);
}