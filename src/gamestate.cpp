#include "gamestate.h"
#include "../../Tetris/src/block.h"
#include "../../Tetris/src/shape.h"

#include <QDebug>
#include <QList>

GameState::GameState(QList<Block *> blocks_, Shape *fallingShape_, Shape *nextShape_, Shape *holdShape_, QObject *parent)
    : QObject{parent}
{
    blocks = blocks_;
    fallingShape = fallingShape_;
    nextShape = nextShape_;
    holdingShape = holdShape_;
}
