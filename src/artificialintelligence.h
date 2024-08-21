#ifndef ARTIFICIAL_INTELLIGENCE_H
#define ARTIFICIAL_INTELLIGENCE_H

#include "../../Tetris/src/scene.h"
#include "outcome.h"
#include "gamestate.h"
#include "heuristicvalue.h"

class ArtificialIntelligence : public QObject
{
    Q_OBJECT
public:
    explicit ArtificialIntelligence(Scene *_scene, QObject *parent = nullptr);

    Outcome findBestOutcome(GameState &state);
    void movePiece(Outcome &bestOutcome, Shape *shape, Shape *previewToUpdate);

private:
    HeuristicValue evaluatePosition(const QList<Block *> blocks, GameState &state);
    Outcome printOutcomeFromPosition(int bestPosition, int bestRotation, GameState::ShapeCategory shape);
    int countFullRows(QList<Block *> allBlocks);

    Scene *scene;
    bool secondShape;
};

#endif // ARTIFICIAL_INTELLIGENCE_H