#include "GameState.h"
#include "config.h"
#include <iostream>

GameState::GameState() {
    //ctor
}

GameState::~GameState() {
    //dtor
}

void GameState::reset() {
    m_round = 0;
}

int GameState::nowPlayer() const {
    return m_round % 2 ? WHITE_PLAYER : BLACK_PLAYER;
}

int GameState::nowRound() const {
    return m_round;
}

void GameState::toNextRound() {
    ++m_round;
}

void GameState::render() const {
    std::cout << "NowRound: " << nowRound() << "\t";
    std::cout << "NowPlayer: " << nowPlayer();
    if (nowPlayer() == BLACK_PLAYER) std::cout << "(" << BLACK_CHAR << ")" << "\n";
    else std::cout << "(" << WHITE_CHAR << ")" << "\n";
}
