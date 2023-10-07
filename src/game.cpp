#include "game.hpp"

#ifdef WIN32
#include <Windows.h>

bool key_is_pressed(int key) {
    return GetAsyncKeyState(key);
}

#define KEY_ESCAPE VK_ESCAPE

#else
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h> 

bool key_is_pressed(KeySym ks) {
    Display* dpy = XOpenDisplay(":0");
    char keys_return[32];
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, ks);
    bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    XCloseDisplay(dpy);
    return isPressed;
}

#define KEY_ESCAPE XK_Escape

#endif

Game::Game(sf::RenderWindow& otherWindow) {
    window = &otherWindow;
    board = new Board;
    paused = false;
    hasEnded = false;
}

void Game::drawAll() {
    window->clear();
    board->drawBoard(*window);
    apple.drawApple(*window);
    snake.drawSnake(*window);
    window->display();
}

bool Game::ateFruit() {
    if (snake.conflictsSnake(apple.getPos())) {
        return true;
    }
    return false;

}

void Game::doLogic() {
    if (key_is_pressed('W') && snake.getDir() != south) snake.setDir(north);
    else if (key_is_pressed('S') && snake.getDir() != north) snake.setDir(south);
    else if (key_is_pressed('D') && snake.getDir() != west) snake.setDir(east);
    else if (key_is_pressed('A') && snake.getDir() != east) snake.setDir(west);

    snake.moveSnake();
    if (ateFruit()) {
        srand((unsigned int)(time(NULL)));
        snake.addTail(snake.getLastTailPos());
        apple.newApple(float(rand() % boardSize), float(rand() % boardSize));
        while (snake.conflictsSnake(apple.getPos())) {
            apple.newApple(float(rand() % boardSize), float(rand() % boardSize));
        }
    }
    if (!snake.Alive()) {
        hasEnded = true;
    }
}

void Game::run() {
    if (!hasEnded) {
        if (key_is_pressed(KEY_ESCAPE) & 1) {
            paused = !paused;
        }
        if (!paused) {
            doLogic();
        }
        else {
            if (key_is_pressed('0')) {
                daristyle = !daristyle;
                snake.setDir(snake.getDir());
            }
        }
        drawAll();
    }
    else {
        window->close();
    }
}
