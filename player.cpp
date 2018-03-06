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

    // determine time -rona
    time_t t1 = time(0);
	
    // Opponent's move -cathy
    if (opponentsMove != nullptr) {
        board->doMove(opponentsMove, o_side);
    }

    // Our move -cathy
    Move *move = this->getMove();
    if (move != nullptr) {
        board->doMove(move, p_side);
    }

    time_t t2 = time(0);
    
    if (1000 * difftime(t2, t1) > msLeft and msLeft != -1) {
	cerr << "Timeout error" << endl;
        return nullptr;
    }

    return move;
}

Move *Player::getMove() {

    // Declarations
    Board *copy;
    Board *copy2;
    Move *max = new Move(-1, -1);
    Move *current = new Move(-1, -1);
    Move *current2 = new Move(-1, -1);
    int max_count = 0, max_count2 = 100, curr_count = 0;

    // Loop through player's moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            current->setX(i);
            current->setY(j);

            // Check if valid
            if (board->checkMove(current, p_side) == true) {

                max_count2 = 100;
                copy = board->copy();
                copy->doMove(current, p_side);

                // Loop through opponent's moves
                for (int i2 = 0; i2 < 8; i2++) {
                    for (int j2 = 0; j2 < 8; j2++) {

                        current2->setX(i2);
                        current2->setY(j2);

                        // Check if valid
                        if (copy->checkMove(current2, o_side) == true) {

                            copy2 = copy->copy();
                            copy2->doMove(current2, o_side);

                            // Find opponent's move (min player color)
                            curr_count = copy2->count(p_side);

                            if (curr_count < max_count2) {
                                max_count2 = curr_count;
                            }

                        }
                    }
                }

                // Update running best move
                if (max_count2 > max_count) {
                    max->setX(i);
                    max->setY(j);
                    max_count = max_count2;
                }
            }
        }
    }

    // We have no valid moves
    if (max->getX() == -1) {
        return nullptr;
    }

    return max;
}
