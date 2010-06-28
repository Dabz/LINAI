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
//         Author:  Gasparina Damien (http://lamada.eu, gaspar_d@epita.fr)
//        Company:  Epita
//
// =====================================================================================

#include "interface.h"

using boost::asio::ip::tcp;

int launch_client(std::string server, int port) {
    try{
        board grid = board_create_empty();
        char player = 0;

        std::cout << "Connect to " << server << " with port: " << port << std::endl;

        // Try to connect to the server
        boost::asio::io_service ios;
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(server), port);
        tcp::socket socket(ios);
        socket.connect(endpoint);

        boost::array<char, 1> buff;
        boost::array<reject_info, 4> buff_err;
        boost::array<chess_info, 1> buff_play;

        boost::system::error_code error;

        // True if we must start the game
        bool play = false, game_started = false;
        reject_info serv_err;
        unsigned int len;

        while (1)
        {
            // Receive Data
            len = socket.read_some(boost::asio::buffer(buff), error);
            if (len >= sizeof(char)) {
                switch ( (char) buff.data()[0]) {
                    case COMM_MSG_FIRST:
                        play = true;
                        player = 0;
                        std::cout << "I am the first player" << std::endl;
                        break;
                    case COMM_MSG_SECOND:
                        play =false;
                        player = 1;
                        std::cout << "I am the second player" << std::endl;
                        break;
                    case COMM_MSG_GAME_START:
                        game_started = true;
                        break;
                    case COMM_MSG_WIN:
                        game_started = false;
                        std::cerr << "Gratz u won bro" << std::endl;
                        return 1;
                        break;
                    case COMM_MSG_LOSE:
                        game_started = false;
                        std::cerr << "U lost dude" << std::endl;
                        return -1;
                        break;
                    case COMM_MSG_DRAW:
                        game_started = false;
                        std::cerr << "WTFU, Draw ?" << std::endl;
                        return 0;
                        break;
                    case COMM_MSG_TIMEOUT:
                        game_started = false;
                        std::cerr << "Timeout ... fag" << std::endl;
                        return -1;
                        break;

                    case COMM_MSG_CHESS:
                        len = socket.read_some(boost::asio::buffer(buff_play), error);
                        if (len == 8) {
                            chess_info tmp = buff_play.data()[0];
                            if (tmp.color == player) {
                                std::cout << "I take X: " << (int) tmp.row << ", Y: " << (int) tmp.col << std::endl;
                                grid[(int) tmp.row][(int) tmp.col] = player ? ENNEMY : COMPUTER;
                            }
                            else {
                                std::cout << "Ennemy take X: " << (int) tmp.row << ", Y: " << (int) tmp.col << std::endl;
                                grid[(int) tmp.row][(int) tmp.col] = player ? COMPUTER : ENNEMY;
                                play = true;
                            }
                            print_board(grid);
                        }
                        break;
                    case COMM_MSG_REJECTED:
                        len = socket.read_some(boost::asio::buffer(buff_err), error);
                        serv_err = buff_err.data()[0];
                        // TODO H&&LE errorS
                        break;

                    case COMM_MSG_ACCEPT:
                        break;

                    default:
                        std::cerr << "Command not recognized" << std::endl;
                        break;
                }
                if (play && game_started) {
                    play_next_move(grid, player, socket, buff, buff_err);
                    play = false;
                }
            }
            if (!game_started) {
                require_game_start(socket);
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
            return 0;
    }
}

void play_next_move(board grid, char player, tcp::socket& socket,
                    boost::array<char, 1>& buff, boost::array<reject_info, 4>& buff_err ) {

    tree_node res;
    if (player)
        res = alpha_beta(DEPTH, grid, ENNEMY);
    else
        res = alpha_beta(DEPTH, grid, COMPUTER);
    char msg = COMM_MSG_CHESS;

    chess_info to_send;
    to_send.color = player;
    to_send.row = (char) res.move.x;
    to_send.col = (char) res.move.y;

    bool resend = false;

    do {
        socket.send(boost::asio::buffer((void*)&msg, 1));
        socket.send(boost::asio::buffer((void*)&to_send, sizeof(chess_info)));

        resend = false;

        socket.read_some(boost::asio::buffer(buff));
        msg = buff.data()[0];
        reject_info serv_err;
        if (msg == COMM_MSG_REJECTED) {
            socket.read_some(boost::asio::buffer(buff_err));
            serv_err = buff_err.data()[0];
            if (serv_err.reason == REJECT_REASON_INVALID_CHESS) {
                //std::cout << "Message rejected, Reason invalid chess" << std::endl;
            }
            else if(serv_err.reason == REJECT_REASON_UNWANTED) {
                //std::cout << "Message rejected, Why have you played bro ?" << std::endl;
            }
            if (serv_err.solution == SOLUTION_ACTION_REPEAT) {
                resend = true;
            }
        }
    }while (resend);
}

bool require_game_start(tcp::socket& socket) {
    char msg = COMM_MSG_GAME_REQUIRE_START;
    socket.send(boost::asio::buffer((void*)&msg, 1));
    return false;
}
