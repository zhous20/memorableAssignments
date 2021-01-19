///
/// \file GameDeck.cpp
/// \author Shengchen Zhou
/// \brief The GameDeck module (source)
/// \date 6 Apr 2018
///

#include <algorithm>

#include "Exceptions.h"
#include "GameDeck.h"

using namespace std;

GameDeck::GameDeck() {}

GameDeck::GameDeck(PokerCardFreeCell c[], PokerCardPile p[],
                   PokerCardFoundation f[]) {
    for (int i = 0; i < NC; ++i) {
        this->C[i] = c[i];
    }
    for (int i = 0; i < NP; ++i) {
        this->P[i] = p[i];
    }
    for (int i = 0; i < NF; ++i) {
        this->F[i] = f[i];
    }
}

void GameDeck::init() {
    vector<PokerCard> c;

    for (int r = Ace; r != King + 1; ++r) {
        for (int s = Diamonds; s != Spades + 1; ++s) {
            c.push_back({static_cast<PokerCardRankT>(r),
                         static_cast<PokerCardSuitT>(s)});
        }
    }

    random_shuffle(c.begin(), c.end());

    vector<vector<PokerCard>> p(NP);

    for (unsigned int i = 0; i < c.size(); i += NP) {
        for (unsigned int j = 0, k = i; j < NP && k < c.size(); ++j, ++k) {
            p[j].push_back(c[k]);
        }
    }

    for (unsigned int i = 0; i < NP; ++i) {
        this->P[i].init(p[i]);
    }
}

PokerCardFreeCell GameDeck::cell(unsigned int i) {
    if (i + 1 > NC) {
        throw Ind_Illegal();
    }
    return this->C[i];
}

PokerCardPile GameDeck::pile(unsigned int i) {
    if (i + 1 > NP) {
        throw Ind_Illegal();
    }
    return this->P[i];
}

PokerCardFoundation GameDeck::foundation(unsigned int i) {
    if (i + 1 > NF) {
        throw Ind_Illegal();
    }
    return this->F[i];
}

bool GameDeck::canFreeCell2FreeCell(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NC) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NC) {
        throw Ind_Illegal();
    }
    return this->C[i1].canMoveCard2(&this->C[i2]);
}

bool GameDeck::freeCell2FreeCell(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NC) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NC) {
        throw Ind_Illegal();
    }
    return this->C[i1].moveCard2(&this->C[i2]);
}

bool GameDeck::canPile2Pile(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NP) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NP) {
        throw Ind_Illegal();
    }
    return this->P[i1].canMoveCard2(&this->P[i2]);
}

bool GameDeck::pile2Pile(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NP) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NP) {
        throw Ind_Illegal();
    }
    return this->P[i1].moveCard2(&this->P[i2]);
}

bool GameDeck::canFreeCell2Pile(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NC) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NP) {
        throw Ind_Illegal();
    }
    return this->C[i1].canMoveCard2(&this->P[i2]);
}

bool GameDeck::freeCell2Pile(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NC) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NP) {
        throw Ind_Illegal();
    }
    return this->C[i1].moveCard2(&this->P[i2]);
}

bool GameDeck::canPile2FreeCell(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NP) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NC) {
        throw Ind_Illegal();
    }
    return this->P[i1].canMoveCard2(&this->C[i2]);
}

bool GameDeck::pile2FreeCell(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NP) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NC) {
        throw Ind_Illegal();
    }
    return this->P[i1].moveCard2(&this->C[i2]);
}

bool GameDeck::canFreeCell2Foundation(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NC) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NF) {
        throw Ind_Illegal();
    }
    return this->C[i1].canMoveCard2(&this->F[i2]);
}

bool GameDeck::freeCell2Foundation(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NC) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NF) {
        throw Ind_Illegal();
    }
    return this->C[i1].moveCard2(&this->F[i2]);
}

bool GameDeck::canPile2Foundation(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NP) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NF) {
        throw Ind_Illegal();
    }
    return this->P[i1].canMoveCard2(&this->F[i2]);
}

bool GameDeck::pile2Foundation(unsigned int i1, unsigned int i2) {
    if (i1 + 1 > NP) {
        throw Ind_Illegal();
    }
    if (i2 + 1 > NF) {
        throw Ind_Illegal();
    }
    return this->P[i1].moveCard2(&this->F[i2]);
}

bool GameDeck::validMoves() {
    for (int i1 = 0; i1 < NP; ++i1) {
        for (int i2 = 0; i2 < NP; ++i2) {
            if (i1 != i2) {
                if (canPile2Pile(i1, i2)) {
                    return true;
                }
            }
        }
    }
    for (int i1 = 0; i1 < NP; ++i1) {
        for (int i2 = 0; i2 < NC; ++i2) {
            if (canPile2FreeCell(i1, i2)) {
                return true;
            }
        }
    }
    for (int i1 = 0; i1 < NC; ++i1) {
        for (int i2 = 0; i2 < NP; ++i2) {
            if (canFreeCell2Pile(i1, i2)) {
                return true;
            }
        }
    }
    for (int i1 = 0; i1 < NP; ++i1) {
        for (int i2 = 0; i2 < NF; ++i2) {
            if (canPile2Foundation(i1, i2)) {
                return true;
            }
        }
    }
    for (int i1 = 0; i1 < NC; ++i1) {
        for (int i2 = 0; i2 < NF; ++i2) {
            if (canFreeCell2Foundation(i1, i2)) {
                return true;
            }
        }
    }
    return false;
}

bool GameDeck::Winning() {
    for (int i = 0; i < NC; ++i) {
        if (this->C[i].size() != 0) {
            return false;
        }
    }
    for (int i = 0; i < NP; ++i) {
        if (this->P[i].size() != 0) {
            return false;
        }
    }
    return true;
}
