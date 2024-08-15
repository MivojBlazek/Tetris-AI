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
    explicit ArtificialIntelligence(Scene *scene_, QObject *parent = nullptr);

    Outcome findBestOutcome(GameState &state);
    void movePiece(Outcome &bestOutcome, Shape *shape);

private:
    HeuristicValue evaluatePosition(const int dropHeight, GameState &state);
    Outcome printOutcomeFromPosition(int bestPosition, int bestRotation);

    Scene *scene;
};

#endif // ARTIFICIAL_INTELLIGENCE_H