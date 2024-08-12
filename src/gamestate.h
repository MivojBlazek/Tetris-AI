#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../Tetris/src/block.h"
#include "../../Tetris/src/shape.h"

#include <QList>


class GameState : public QObject
{
    Q_OBJECT
public:
    explicit GameState(QList<Block *> blocks_, Shape *fallingShape_, Shape *nextShape_, Shape *holdShape_, QObject *parent = nullptr);

private:
    QList<Block *> blocks;
    Shape *fallingShape;
    Shape *nextShape;
    Shape *holdingShape;
};

#endif // GAMESTATE_H