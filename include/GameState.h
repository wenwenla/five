#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState {
public:
    GameState();
    virtual ~GameState();

    void reset();

    int nowRound() const;
    int nowPlayer() const;
    void toNextRound();
    virtual void render() const;
private:
    int m_round = 0;
};

#endif // GAMESTATE_H
