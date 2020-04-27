#ifndef RLMSG_H
#define RLMSG_H

#include "Board.h"
#include <string>

/**
 *  Client Message processor
 *  1. Reset "0\n"
 *  2. Step  "1 row col\n"
**/

struct MsgInfo {
    enum Type {
        RESET,
        STEP
    } type;
    int row, col;
};

class RLMsg
{
public:
    RLMsg();
    virtual ~RLMsg();
    std::string generateResponse(MsgInfo request, Board& board);
    MsgInfo parseRequest(const std::string& msg);
};

#endif // RLMSG_H
