#include "player.hpp"
#include <future> 
#include <chrono> 

// Othello project: Rona Yu, Cathy Miao
// CS2 WI 2018

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side s) {
	time_t timer1 = time(0);
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     
     // create a new board object 
     Board board = new Board();
     
     // set your (the player's) side 
     Side side = s; 
     
     time_t timer2 = time(0);
     if((timer2-timer1)>30){
		 cerr << "Timout in player construction" << endl; 
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
     
     if(msLeft == -1){
		 // no time limit
	 }
	 
	 else{
		 // time limit
		 time_t timer1 = time(0); // get the current time 

		// see if the board has a move
		if(this->board.hasMoves(this->side) == false){
			return nullptr;
		}
		else{
			// process the opponent's move
			// calculate your own move
		}
		
		// // after everything's done 
		time_t timer2 = time(0); 
		if((timer1 - timer2)>=(msLeft)/1000){
			cerr << "Timeout Error in doMove" << endl; 
		}
			
	}
}
