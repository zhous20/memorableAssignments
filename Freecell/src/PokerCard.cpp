///
/// \file PokerCard.cpp
/// \author Shengchen Zhou
/// \brief The PokerCard module (source)
/// \date 6 Apr 2018
///

#include "PokerCard.h"

PokerCard::PokerCard(PokerCardRankT r, PokerCardSuitT s) {
    this->R = r;
    this->S = s;
}

PokerCardRankT PokerCard::r() {
    return this->R;
}

PokerCardSuitT PokerCard::s() {
    return this->S;
}

PokerCardColrT PokerCard::c() {
    if (this->S == Diamonds || this->S == Hearts) {
        return Red;
    }
    return Black;
}

bool PokerCard::operator==(PokerCard c) const {
    return this->S == c.S && this->R == c.R;
}
