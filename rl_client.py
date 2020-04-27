import socket
import numpy as np


class RLEnv:

    def __init__(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.connect(('127.0.0.1', 12345))

    def reset(self):
        self._socket.send(b'0\n')
        data = self._socket.recv(1024).decode('utf8').split()
        state = np.zeros((15, 15), dtype=np.float32)
        p = 0
        for d in data[1]:
            state[p // 15, p % 15] = int(d)
            p += 1
        return state

    def step(self, action):
        row, col = action // 15, action % 15
        self._socket.send('1 {} {}\n'.format(row, col).encode('utf8'))
        data = self._socket.recv(1024).decode('utf8').split()
        state = np.zeros((15, 15), dtype=np.float32)
        p = 0
        for d in data[1]:
            state[p // 15, p % 15] = int(d)
            p += 1
        reward = float(data[2])
        done = data[3] == '1'
        return state, reward, done


def main():
    env = RLEnv()
    state = env.reset()
    done = False
    print(state)
    while not done:
        action = np.random.choice(list(range(15 * 15)))
        state, reward, done = env.step(action)
        print('State:\n{}, Reward: {}'.format(state, reward))


if __name__ == '__main__':
    main()


