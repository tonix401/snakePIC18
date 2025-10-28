// led matrix
void imprintLossScreen(void);
void pushFrame(void);
void clearFrame(void);

//game logic
unsigned int snake_body[64];
unsigned int apple_position;
unsigned int score;

void applyGameLogic(void);
void applyPositionsToFrame(void);

// 7 seg
void updateScoreDisplay(unsigned int);