#include "player.hpp"

// Ignore this line

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    // Set board -cathy
    board = new Board();

    // Set sides -cathy
    p_side = side;
    if (p_side == WHITE) {
        o_side = BLACK;
    } else {
        o_side = WHITE;
    }

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    // Opponent's move -cathy
    if (opponentsMove != nullptr) {
        board->doMove(opponentsMove, o_side);
    }

    // Our move -cathy
    Move *move = this->getMove();
    if (move != nullptr) {
        board->doMove(move, p_side);
    }

    return move;
}

Move *Player::getMove() {

    // Random move pick -cathy
    Move *move = new Move(-1, -1);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            move->setX(i);
            move->setY(j);

            if (board->checkMove(move, p_side) == true) {
                return move;
            }
        }
    }

    return nullptr;
}
