#ifndef ARTIFICIAL_INTELLIGENCE_H
#define ARTIFICIAL_INTELLIGENCE_H

#include "outcome.h"
#include "gamestate.h"

class ArtificialIntelligence : public QObject
{
    Q_OBJECT
public:
    explicit ArtificialIntelligence(QObject *parent = nullptr);

    Outcome findBestOutcome(const GameState &state) const;
    void movePiece(const Outcome &bestOutcome);
};

#endif // ARTIFICIAL_INTELLIGENCE_H