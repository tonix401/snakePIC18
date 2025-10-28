#include "Definitions.h"
#include "globals.h"
#include <pic18f47k42.h>
#include <builtins.h>

int direction = 0x01; //0x01: left, 0x10: down, -0x01: right, -0x10: up
unsigned int score = 2;
unsigned int snake_body[64] = {0x01, 0x00};
unsigned int apple_position = 0x55;
unsigned long apple_seed = 42069;

// Using a simple pseudo-random-number generator to get a new position for the apple 
unsigned int getRandom8x8Position() {
    apple_seed = (1664525 * apple_seed + 1013904223) % 64;
    return apple_seed;
}

void moveApple() {
    unsigned int apple_position_allowed = 0;

    while(!apple_position_allowed) {
        apple_position = getRandom8x8Position();
        
        for(unsigned int i = 0; i <= score; i++) {
            apple_position_allowed = !(snake_body[i] == apple_position);
        }
    }
}

void pushAppleInSnakeBody() {
    for(unsigned int i = score; i > 0; i--) {
        snake_body[i] = snake_body[i-1];
    }
    snake_body[0] = apple_position;
}

void resetGame() {
    score = 2;
    snake_body[0] = 0x10;
    snake_body[1] = 0x00;

    for(unsigned int i = 2; i < 64; i++) {
        snake_body[i] = 0x0;
    }

    moveApple();
}

void updateBodyMovement() {
    int newHead = ((int)snake_body[0] + direction) % 0xFF;
    for(int i = 64; i > 0; i--) {
        snake_body[i] = snake_body[i - 1];
    }
    snake_body[0] = newHead;
}

unsigned char checkSnakeSelfCollisions() {
    for (unsigned int i = 1; i <= score; i++) {
        if (snake_body[0] == snake_body[i]) {
            return 1;
        }
    }
    return 0;
}

unsigned char checkHeadAppleCollision() {
    return snake_body[0] == apple_position;
}

// Applies movement and game logic to all entities. These will be displayed in the next frame
void applyGameLogic() {
    clearFrame();
    updateBodyMovement();
    if (checkSnakeSelfCollisions()) {
        imprintLossScreen();
        pushFrame();
        __delay_ms(5000);
        resetGame();
    } else if (checkHeadAppleCollision()) {
        score++;
        pushAppleInSnakeBody();
        moveApple();
        clearFrame();
        applyPositionsToFrame();
        pushFrame();
    }
}