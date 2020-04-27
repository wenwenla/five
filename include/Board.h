#ifndef BOARD_H
#define BOARD_H

#include "config.h"

class Board {
public:
    using StateType = unsigned char;
    constexpr static StateType EMPTY = NO_PLAYER;
    constexpr static StateType BLACK = BLACK_PLAYER;
    constexpr static StateType WHITE = WHITE_PLAYER;
public:
    Board();
    virtual ~Board();
    void reset();
    StateType getState(int row, int col) const;
    void setState(int player, int row, int col);

    StateType getWinner() const;
    bool isFull() const;

    virtual void render() const;
private:
    StateType m_state[15][15];
    int m_total = 0;
};

#endif // BOARD_H
