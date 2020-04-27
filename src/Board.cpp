#include "Board.h"
#include <iostream>

Board::Board() {
    reset();
}

Board::~Board() {
    //dtor
}

void Board::reset() {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            m_state[i][j] = EMPTY;
        }
    }
    m_total = 0;
}

Board::StateType Board::getState(int row, int col) const {
    return m_state[row][col];
}

void Board::setState(int player, int row, int col) {
    if (m_state[row][col] != EMPTY) {
        throw std::logic_error("Double add!");
    }
    m_state[row][col] = player;
    ++m_total;
}

Board::StateType Board::getWinner() const {
    for (int r = 0; r < 15; ++r) {
        for (int c = 4; c < 15; ++c) {
            int cnt[3] = {0};
            for (int k = 0; k < 5; ++k) {
                ++cnt[m_state[r][c - k]];
            }
            if (cnt[WHITE_PLAYER] == 5) return WHITE_PLAYER;
            if (cnt[BLACK_PLAYER] == 5) return BLACK_PLAYER;
        }
    }
    for (int c = 0; c < 15; ++c) {
        for (int r = 4; r < 15; ++r) {
            int cnt[3] = {0};
            for (int k = 0; k < 5; ++k) {
                ++cnt[m_state[r - k][c]];
            }
            if (cnt[WHITE_PLAYER] == 5) return WHITE_PLAYER;
            if (cnt[BLACK_PLAYER] == 5) return BLACK_PLAYER;
        }
    }
    for (int r = 4; r < 15; ++r) {
        for (int c = 4; c < 15; ++c) {
            int cnt[3] = {0};
            for (int k = 0; k < 5; ++k) {
                ++cnt[m_state[r - k][c - k]];
            }
            if (cnt[WHITE_PLAYER] == 5) return WHITE_PLAYER;
            if (cnt[BLACK_PLAYER] == 5) return BLACK_PLAYER;
        }
    }
    for (int r = 4; r < 15; ++r) {
        for (int c = 0; c < 10; ++c) {
            int cnt[3] = {0};
            for (int k = 0; k < 5; ++k) {
                ++cnt[m_state[r - k][c + k]];
            }
            if (cnt[WHITE_PLAYER] == 5) return WHITE_PLAYER;
            if (cnt[BLACK_PLAYER] == 5) return BLACK_PLAYER;
        }
    }
    return NO_PLAYER;
}

bool Board::isFull() const {
    return m_total == 15 * 15;
}

void Board::render() const {
    using std::cout;
    using std::endl;
    for (int i = 0; i < 15; ++i) {
        cout << "-------------------------------\n|";
        for (int j = 0; j < 15; ++j) {
            if (m_state[i][j] == EMPTY) cout << " ";
            else if (m_state[i][j] == BLACK) cout << "x";
            else cout << "o";
            cout << "|";
        }
        cout << "\n";
    }
    cout << "-------------------------------" << endl;
}
