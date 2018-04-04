// c4bot.cpp
// Aswin van Woudenberg & Rendall Schijven

#include "c4bot.h"
#include "node.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>

void C4Bot::run() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::vector<std::string> command = split(line, ' ');
		if (command[0] == "settings") {
			setting(command[1], command[2]);
		} else if (command[0] == "update" && command[1] == "game") {
			update(command[2], command[3]);
		} else if (command[0] == "action" && command[1] == "move") {
			move(std::stoi(command[2]));
		} else {
			std::cerr << "Unknown command: " << line << std::endl;
		}
	}
}

/**
 * Function that computes move patterns by playing my alpha beta algorithm against a random move generator.
 * To run this call it from main.cpp instead of C4Bot.run.
 */
void C4Bot::createPatterns() {
    //Loop that executes the program i times. Every loop 1 board is solved.
    for(int i = 0; i < 30000; i++)
    {
        State testState = { { { { Player::None } } } };
        bool first = true;
        std::vector<int> moveSaver;
        std::vector<Move> moves = getMoves(testState);

        while(moves.size() != 0)
        {
            Move m;
            //For even numbers let alpha beta algorithm start
            if(i % 2 == 0)
            {
                if(getCurrentPlayer(testState) == Player::X)
                {
                    if(first) {
                        m = 3;
                        first = false;
                    }
                    else m = alphaBeta(testState, 10);
                } else{
                    m = *select_randomly(moves.begin(), moves.end());
                }
            }
            //For odd numbers let the random move generator start.
            else
            {
                if(getCurrentPlayer(testState) == Player::O)
                {
                    if(testState[5][3] == Player::None) m = 3;
                    else m = alphaBeta(testState, 10);
                } else{
                    m = *select_randomly(moves.begin(), moves.end());
                }
            }

            //Run the selected move on the test board
            testState = doMove(testState, m);

            //Save the selected move
            moveSaver.push_back(m);

            //Update moves
            moves = getMoves(testState);
        }

        //Create a new filestream which either opens the file if it exists or creates it and ads the output to the end of the file.
        //File will be located in cmake-build-debug.
        std::ofstream algoStart;
        algoStart.open("algoStart.txt", std::ios_base::app);

        //Write the move vectors to the file
        algoStart << "{";
        for(std::vector<int>::const_iterator i = moveSaver.begin(); i != moveSaver.end(); i++){
            if(i == moveSaver.end() - 1) algoStart << *i;
            else algoStart << *i << ",";
        }
        algoStart << "},";

        //Close the filestream
        algoStart.close();
    }
}

/**
 * Function that calculates the first few moves to increase the speed of the bot.
 * It uses a library of moves defined in c4bot.h where it checks if playing those
 * moves on an empty board results in the same board which is being played.
 * In this case the function returns the next move from the library.
 * @param: The current playing board.
 * @param: The id of my bot.
 *
 * @return The move to be played
 */
Move C4Bot::startingMoves(const State board, int myBot)
{
    //Standard first move.
    if(round == 1 && myBot == 0 || round == 1 && myBot == 1 && state[5][3] == Player::None) return 3;

    //Loop through each move vector in the library and check if it`s alike to the current board.
    for(std::vector<int> moves : startLibrary)
    {
        State temp = { { { { Player::None } } } };

        for(int i = 0; i < moves.size() - 1; i++)
        {
            temp = doMove(temp, moves[i]);
            if(temp == board && i % 2 == 0 && myBot == 1) return moves[i + 1];
            else if(temp == board && i % 2 != 0 && myBot == 0) return moves[i + 1];
        }
    }

    //If no results were found in the library run the alphaBeta algorithm.
    return alphaBeta(state, 8);
}

//Start alpha beta
/**
 * This function evaluates the state of the board. It does so by using an
 * evaluation table defined in c4bot.h which gives points for a "chip" on a board position.
 * If it`s the opponents chip points get decreased if it`s the players chip points increase.
 * @param: The current player ie minimizing or maximizing.
 * @param: The current status of the playing board.
 *
 * @return The score of the board
 */
int C4Bot::evaluate(const Player player, const State board)
{
    Player opponent = (player == Player::X) ? Player::O : Player::X;

    if(getWinner(board) == player) return 10000;
    if(getWinner(board) == opponent) return -10000;

    int utility = 138;
    int score = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            if (board[i][j] == player)
                score += C4Bot::evalTable[i][j];
            else if (board[i][j] == opponent)
                score -= C4Bot::evalTable[i][j];
    return utility + score;
}

/**
 * Recursive function that scores a position using the alpha beta algorithm.
 * @param: The current playing board.
 * @param: The current player.
 * @param: The search depth
 * @param: The value of the maximizing player
 * @Param: The value of the minimizing player
 *
 * @return The score and move to be played.
 */
std::vector<int> C4Bot::minimax(const State &board, const Player &player, int depth, int alpha, int beta)
{
    //Get all the possible moves
    std::vector<Move> moves = getMoves(board);

    //If there is only one move left, return this move
    if(moves.size() == 1) return {0, moves.at(0)};

    int score;
    int bestMove = -1;

    //If max depth has been reached, score the board using the evaluation function
    if(depth == 0){
        score = evaluate(player, board);
        return {score,bestMove};
    }
    else
    {
        depth--;

        //For each move in moves
        for(Move m: moves)
        {
            //Apply the move to a temporary board.
            State tempboard = doMove(board, m);;

            //If player is maximizing player
            if(player == Player::O)
            {
                //Call recursively with the opposite player.
                score = minimax(tempboard, Player::X, depth, alpha, beta)[0];

                //If the score is greater than alpha, alpha becomes score and bestmove is current move.
                if(score > alpha)
                {
                    alpha = score;
                    bestMove = m;
                }
            }
            //If player is minimizing player
            else
            {
                score = minimax(tempboard, Player::O, depth, alpha, beta)[0];

                if(score < beta)
                {
                    beta = score;
                    bestMove = m;
                }
            }
            //Alpha beta pruning
            if(alpha >= beta) break;
        }
        //If current player is player O return alpha and best move, else return beta and best move.
        return {(player == Player::O) ? alpha : beta, bestMove};
    }
}

/**
 * Function that calls the alpha beta algorithm and returns the move or returns random move
 * if output from the algorithm was not correct.
 * @param: The current playing board.
 * @param: The search depth
 *
 * @return The move to be played
 */
Move C4Bot::alphaBeta(const State &board, int depth)
{
    //Get the move using alpha beta algorithm.
    Move result = minimax(board, getCurrentPlayer(board), depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())[1];

    //If alpha beta algorithm fails to provide correct output return a random move.
    std::vector<Move> moves = getMoves(board);
    return {(result != -1) ? result : *select_randomly(moves.begin(), moves.end())};
}
//End alpha beta

/*//Begin monte carlo tree search
int C4Bot::getTimeElapsed() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();
}

double C4Bot::selectfn(Node* n) {
    double vi = n->getUtility();
    int ni = n->getVisits();
    int np = n->getParent()->getVisits();
    return (vi + sqrt(2 * log(np) / ni));
}

double C4Bot::selectfnOP(Node* n) { //modified UCT so that the more you visit a node, the greater the score
    double vi = n->getUtility();
    int ni = n->getVisits();
    int np = n->getParent()->getVisits();
    return (vi - sqrt(2 * log(np) / ni));
}

void C4Bot::backPropagate(Node* n, int score) {
    n->visit();
    n->addUtility(score);
    if (n->getParent()) {
        backPropagate(n->getParent(), score);
    }
}

int C4Bot::simulate(State s){
    Player winner = getWinner(s);
    if((winner == Player::O && your_botid == 0) || (winner == Player::X && your_botid == 1)){//lose
        return 0;
    } else if ((winner == Player::X && your_botid == 0) || (winner == Player::O && your_botid == 1)){ //win
        return 100;
    }
    std::vector<Move> moves = getMoves(s);
    if (moves.size() == 0){ //draw
        return 50;
    }
    Move best = moves.at(std::rand()%(moves.size()));
    s = doMove(s, best);
    return simulate(s);
}

void C4Bot::expand(Node* n) {
    std::vector<Move> moves = getMoves(state);
    for (size_t i = 0; i < moves.size(); i++) { //simulates player move
        State s = doMove(state, moves.at(i));
        Node* newNode = new Node(n, s, moves.at(i), 0, 0, 2);
        n->addChild(newNode);
        if (getWinner(s) == Player::None && getMoves(n->getState()).size() > 0) {
            std::vector<Move> movesOP = getMoves(s);
            for (size_t j = 0; j < movesOP.size(); j++) {
                State newState = doMove(s, movesOP.at(j));
                Node* newNodeOP = new Node(newNode, newState, movesOP.at(j), 0, 0, 1);
                newNode->addChild(newNodeOP);
            }
        }
    }
}

Node* C4Bot::select(Node* n) {
    if (n->getVisits() == 0 || getWinner(n->getState()) != Player::None || getMoves(n->getState()).size() == 0) { //no visits or is terminal
        return n;
    }
    Children* minList = n->getChildren();
    for (size_t i = 0; i < minList->size(); i++) { //if a min node hasn't been visited, visit a random child of its
        if (minList->at(i)->getVisits() == 0) {
            return (minList->at(i));
        }
    }
    double score = 0;
    Node* result = minList->at(0);
    for (size_t i = 0; i < minList->size(); i++) { //chooses the min node with the highest score
        double newScore = selectfn(minList->at(i));
        if (newScore > score && result->getChildren()->size() > 0) {
            score = newScore;
            result = minList->at(i);
        }
    }
    Children* maxList = result->getChildren();
    for (size_t i = 0; i < maxList->size(); i++) {
        if (maxList->at(i)->getVisits() == 0) {//if a max node hasn't been visited, select that one
            return maxList->at(i);
        }
    }
    double score2 = std::numeric_limits<double>::max();
    Node* finalResult = nullptr;
    for (size_t i = 0; i < maxList->size(); i++) { //all max nodes have been visited, select the one with the lowest score
        double newScore = selectfnOP(maxList->at(i));
        if (newScore < score2) {
            score2 = newScore;
            finalResult = maxList->at(i);
        }
    }
    return finalResult;
}

Move C4Bot::makeMove(int timeout) {
    // std::vector<Move> moves = getMoves(state);
    // return *select_randomly(moves.begin(), moves.end());

    std::vector<Move> moves = getMoves(state);
    if (moves.size() == 1) {
        return moves.at(0);
    }
    Node initial{ nullptr, state, 0, 0, 0, 1 };
    while (timeout - getTimeElapsed() > 500) {
        Node* current = select(&initial);
        expand(current);
        int score = simulate(current->getState());
        backPropagate(current, score);
    }
    double bestScore = 0;
    Move move(0);
    for(size_t i = 0; i<initial.getChildren()->size(); i++){
        if (initial.getChildren()->at(i)->getUtility() > bestScore){
            bestScore = initial.getChildren()->at(i)->getUtility();
            move = initial.getChildren()->at(i)->getMove();
        }
    }
    return move;
}
//End Monte carlo tree search*/

void C4Bot::move(int timeout) {
    //"C:\Users\renda\Desktop\c4ui.exe" "C:\Users\renda\Desktop\Git\four-in-a-row\cmake-build-debug\four-in-a-row.exe"

    //Monte carlo tree search
    //begin = std::chrono::steady_clock::now();
    //std::cout << "place_disc " << makeMove(time_per_move + 10000/30) << std::endl;

    //Alpha beta
    Move move;
    if(round <= 6){
        move = startingMoves(state, your_botid);
    }
    else if(round > 6)
    {
        int depth = 10;
        if(round % 2 == 0) depth += 1;
        move = alphaBeta(state, depth);
    }

    std::cout << "place_disc " << move << std::endl;

    //Original
	//std::vector<Move> moves = getMoves(state);
	//std::cout << "place_disc " << *select_randomly(moves.begin(), moves.end()) << std::endl;
}

void C4Bot::update(std::string &key, std::string &value) {
	if (key == "round") {
		round = std::stoi(value);
	} else if (key == "field") {
		int row = 0;
		int col = 0;
		std::vector<std::string> fields = split(value, ',');
		for (std::string &field : fields) {
			if (field == "0") {
				state[row][col] = Player::X; 
			} else if (field == "1") {
				state[row][col] = Player::O;
			} else {
				state[row][col] = Player::None;
			}
			col++;
			if (col == 7) {
				row++; 
				col = 0;
			}
		}
	}
}

void C4Bot::setting(std::string &key, std::string &value) {
	if (key == "timebank") {
		timebank = std::stoi(value);
	} else if (key == "time_per_move") {
		time_per_move = std::stoi(value);
	} else if (key == "player_names") {
		std::vector<std::string> names = split(value, ',');
		player_names[0] = names[0];
		player_names[1] = names[1];
	} else if (key == "your_bot") {
		your_bot = value;
	} else if (key == "your_botid") {
		your_botid = std::stoi(value);
	} else if (key == "field_columns") {
		field_columns = std::stoi(value);
	} else if (key == "field_rows") {
		field_rows = std::stoi(value);
	}
}

std::vector<std::string> C4Bot::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

