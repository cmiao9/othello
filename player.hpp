#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *getMove();
    double weight(Move *move, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    // Board + player/opponent Side objects -cathy
    Board *board;
    Side p_side;
    Side o_side;

};

#endif
