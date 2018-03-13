#include "player.hpp"

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
    Board *copy1, *copy2, *copy3, *copy4;
    Move *best = new Move(-1, -1);
    Move *current1 = new Move(-1, -1);
    Move *current2 = new Move(-1, -1);
    Move *current3 = new Move(-1, -1);
    Move *current4 = new Move(-1, -1);
    double max1 = 0.0, min2 = 100.0, max3 = 0.0, min4 = 100.0, curr_count = 0.0;

    // We have no valid moves
    if (board->hasMoves(p_side) == false) {
        return nullptr;
    }

    // Loop through player's moves -- MAX1
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            current1->setX(i);
            current1->setY(j);

            // Check if valid
            if (board->checkMove(current1, p_side) == true) {

                copy1 = board->copy();
                copy1->doMove(current1, p_side);
                min2 = 100.0;

                // Loop through opponent's moves -- MIN2
                for (int i2 = 0; i2 < 8; i2++) {
                    for (int j2 = 0; j2 < 8; j2++) {

                        current2->setX(i2);
                        current2->setY(j2);

                        // Check if valid
                        if (copy1->checkMove(current2, o_side) == true) {

                            copy2 = copy1->copy();
                            copy2->doMove(current2, o_side);
                            max3 = 0.0;

                            // Loop through player's moves -- MAX3
                            for (int i3 = 0; i3 < 8; i3++) {
                                for (int j3 = 0; j3 < 8; j3++) {

                                    current3->setX(i3);
                                    current3->setY(j3);

                                    // Check if valid
                                    if (copy2->checkMove(current3, p_side) == true) {

                                        copy3 = copy2->copy();
                                        copy3->doMove(current3, p_side);
                                        min4 = 100.0;

                                        // Loop through opponent's moves -- MIN4
                                        for (int i4 = 0; i4 < 8; i4++) {
                                            for (int j4 = 0; j4 < 8; j4++) {

                                                current4->setX(i4);
                                                current4->setY(j4);

                                                // Check if valid
                                                if (copy3->checkMove(current4, o_side) == true) {

                                                    copy4 = copy3->copy();
                                                    copy4->doMove(current4, o_side);

                                                    // MINIMIZE
                                                    curr_count = copy4->count(p_side);

                                                    if (curr_count < min4) {
                                                        min4 = curr_count;
                                                    }

                                                }
                                            }
                                        }

                                        // MAXIMIZE
                                        if (min4 > max3) {
                                            max3 = curr_count;
                                        }
                                    }

                                }
                            }

                            // MINIMIZE
                            if (max3 < min2) {
                                min2 = max3;
                            }

                        }
                    }
                }

                // MAXIMIZE
                min2 += this->weight(current1, p_side);
                if (min2 >= max1) {
                    best->setX(i);
                    best->setY(j);
                    max1 = min2;
                }
            }
        }
    }

    return best;
}

double Player::weight(Move *move, Side side) {

    if (board->count(p_side) + board->count(o_side) > 20) {
        return 0.0;
    }

    double c_weight = 3.0, e_weight = 0.0;

    // Corners
    if (move->getX() % 8 == 0 && move->getY() % 8 == 0) {
        if (side == p_side)  {
            return c_weight;
        }
        return -c_weight;
    }

    // Adjacent to corners
    if (((move->getX() + 1) % 8 == 0 || (move->getX() - 1) % 8 == 0 ) && ((move->getY() + 1) % 8 == 0 || (move->getY() - 1) % 8 == 0)) {

        if (side == p_side) {
            return -c_weight;
        }
        return c_weight;
    }

    // Edges
    if (move->getX() % 8 == 0 || move->getY() % 8 == 0) {
        if (side == p_side)  {
            return e_weight;
        }
        return -e_weight;
    }

    return 0;
}
