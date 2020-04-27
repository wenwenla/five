#include <iostream>
#include "RLServer.h"
#include <windows.h>
#include "GameState.h"
#include "Board.h"

using namespace std;


class GameMain {
public:
    void render() {
        SetConsoleCursorPosition(stdout_handle, topLeft);
        game_state.render();
        board.render();
        if (m_winner != NO_PLAYER) {
            cout << "(" << (m_winner == BLACK_PLAYER ? BLACK_CHAR : WHITE_CHAR) << ") WIN!\n";
            cout << "Please restart the app to play a new game." << endl;
        }
    }

    bool processEvent() {
        ReadConsoleInput(stdin_handle, &input_record, 1, &input_cnt);
        if (input_record.EventType == MOUSE_EVENT && input_record.Event.MouseEvent.dwEventFlags == RIGHTMOST_BUTTON_PRESSED) {
            COORD pos = input_record.Event.MouseEvent.dwMousePosition;

            int r = pos.Y / 2 - 1, c = pos.X / 2;
            if (r < 0 || r >= 15 || c < 0 || c >= 15) return false;
            if (board.getState(r, c) != NO_PLAYER) return false;
            if (m_winner != NO_PLAYER) return false;

            board.setState(game_state.nowPlayer(), r, c);

            m_winner = board.getWinner();

            game_state.toNextRound();
            return true;
        }
        return false;
    }

    void run() {
        render();
        while (true) {
            bool need_render = processEvent();
            if (need_render) {
                render();
            }
        }
    }
private:
    HANDLE stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    INPUT_RECORD input_record;
    DWORD input_cnt = 0;
    COORD topLeft = {0, 0};
    GameState game_state;
    Board board;

    Board::StateType m_winner = NO_PLAYER;
};


int main() {
//    auto game = GameMain();
//    game.run();
    auto server = RLServer();
    server.run();
    return 0;
}
