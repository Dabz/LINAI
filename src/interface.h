// =====================================================================================
//
//       Filename:  interface.h
//
//    Description:
//
//        Version:  1.0
//        Created:  05/26/2010 04:43:49 PM
//       Revision:  none
//       Compiler:  g++
//
//         AUTHOR:  Gasparina Damien (http://lamada.eu, gaspar_d@epita.fr)
//        Company:  Epita
//
// =====================================================================================

#ifndef INTERFACE_H
#define INTERFACE_H

#include        <iostream>
#include		<boost/asio.hpp>
#include		<boost/array.hpp>
#include        <string>
#include        "data.h"
#include        "alpha_beta.h"
#include		"display.h"

using boost::asio::ip::tcp;

#define COMM_MSG_DONOTHING          0  //do nothing, ignore it!
#define COMM_MSG_REJECTED           1  //last request is rejected
#define COMM_MSG_ACCEPT             2  //last request is accepted
#define COMM_MSG_FIRST              3  //go first when the game starts
#define COMM_MSG_SECOND             4  //go second when the game starts
#define COMM_MSG_GAME_REQUIRE_START 5  //request for game start
#define COMM_MSG_GAME_START         6  //game start
#define COMM_MSG_CHESS              7  //information for chess
#define COMM_MSG_TIMEOUT            8  //time out when one peer takes too many time in a bout
#define COMM_MSG_WIN                9  //win
#define COMM_MSG_LOSE               10 //lose
#define COMM_MSG_DRAW               11 //draw
#define REJECT_REASON_UNWANTED             1
#define REJECT_REASON_INVALID_CHESS        2
#define SOLUTION_NOACTION      0 //no action needed
#define SOLUTION_ACTION_REPEAT 1 //please repeat this action with required parameters

enum chess_color{
    Chess_Clr_Black = 0,
    Chess_Clr_White = 1
};

struct reject_info{
    char reason;    //can be REJECT_REASON_UNWANTED or REJECT_REASON_INVALID_CHESS
    char solution;  //can be SOLUTION_NOACTION or SOLUTION_ACTION_REPEAT
    char parameter; //can be one of the command begin with COMM_MSG_
    char reserved;  //not used
};

struct chess_info{
	char index;       //index for the chess, the client do not need to fill this field
    char color;       //color of the chess
    char row;         //row of the chess
    char col;         //col of the chess
    char reserved[4]; //reserved, just ignore it
};

int launch_client(std::string server, int port);

void play_next_move(board grid, char player, tcp::socket& socket,
					boost::array<char, 1>& buff, boost::array<reject_info, 4>& buff_err );

bool require_game_start(tcp::socket& socket);

#endif
