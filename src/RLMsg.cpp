#include "RLMsg.h"
#include "config.h"
#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <sstream>
#include <cassert>

static std::string __board_to_str(const Board& board) {
    std::string res;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            res += static_cast<char>(board.getState(i, j) + '0');
        }
    }
    return res;
}

static void __white_random_position(Board& board) {
    std::vector<std::pair<int, int>> vec;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board.getState(i, j) == NO_PLAYER) vec.push_back({i, j});
        }
    }
    auto pos = rand() % vec.size();
    board.setState(WHITE_PLAYER, vec[pos].first, vec[pos].second);
}

RLMsg::RLMsg() {
    //ctor
}

RLMsg::~RLMsg() {
    //dtor
}

std::string RLMsg::generateResponse(MsgInfo request, Board& board) {
    std::string res;
    if (request.type == MsgInfo::RESET) {
        std::cout << "[RESET]" << std::endl;
        board.reset();
        res = "0 " + __board_to_str(board) + "\n";
        return res;
    }

    int reward = 0, done = 0;
    if (board.getState(request.row, request.col) != NO_PLAYER) {
        // wrong position
        reward = -1;
        done = 1;
        res = "1 " + __board_to_str(board) + " " + std::to_string(reward) + " " + std::to_string(done) + "\n";
        return res;
    }

    //BLACK make decision
    board.setState(BLACK_PLAYER, request.row, request.col);
    int winner = board.getWinner();
    if (winner == BLACK_PLAYER) {
        //BLACK WIN
        reward = 1;
        done = 1;
        res = "1 " + __board_to_str(board) + " " + std::to_string(reward) + " " + std::to_string(done) + "\n";
        return res;
    }

    //TIE
    if (board.isFull()) {
        reward = 0;
        done = 1;
        res = "1 " + __board_to_str(board) + " " + std::to_string(reward) + " " + std::to_string(done) + "\n";
        return res;
    }

    //WHITH USE RANDOM POSITION
    __white_random_position(board);
    winner = board.getWinner();
    if (winner == WHITE_PLAYER) {
        //WHITE WIN
        reward = -1;
        done = 1;
        res = "1 " + __board_to_str(board) + " " + std::to_string(reward) + " " + std::to_string(done) + "\n";
        return res;
    }
    //TIE
    if (board.isFull()) {
        reward = 0;
        done = 1;
        res = "1 " + __board_to_str(board) + " " + std::to_string(reward) + " " + std::to_string(done) + "\n";
        return res;
    }
    reward = 0; done = 0;
    res = "1 " + __board_to_str(board) + " " + std::to_string(reward) + " " + std::to_string(done) + "\n";
    return res;
}

MsgInfo RLMsg::parseRequest(const std::string& msg) {
    std::stringstream ss(msg);
    MsgInfo ret;
    int msg_id;
    ss >> msg_id;
    if (msg_id == 0) {
        ret.type = MsgInfo::RESET;
    } else if (msg_id == 1) {
        ret.type = MsgInfo::STEP;
    } else {
        assert(false);
    }
    if (ret.type == MsgInfo::STEP) {
        ss >> ret.row >> ret.col;
    }
    return ret;
}
