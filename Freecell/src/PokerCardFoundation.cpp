///
/// \file PokerCardFoundation.cpp
/// \author Shengchen Zhou
/// \brief The PokerCardFoundation module (source)
/// \date 6 Apr 2018
///

#include "PokerCardFoundation.h"
#include "Exceptions.h"

#include "PokerCardFreeCell.h"
#include "PokerCardPile.h"

using namespace std;

PokerCardFoundation::PokerCardFoundation() {}

bool PokerCardFoundation::canAppendCard(PokerCard c) {
    if (this->S.size() != 0) {
        PokerCard lc = this->S.lastCard();
        if (lc.s() != c.s()) {
            return false;
        }
        if (lc.r() - c.r() != -1) {
            return false;
        }
    } else {
        if (c.r() != Ace) {
            return false;
        }
    }
    return true;
}

void PokerCardFoundation::appendCard(PokerCard c) {
    if (!canAppendCard(c)) {
        throw AddCardOp_Illegal();
    }
    this->S.addCard(c);
}

void PokerCardFoundation::removeCard() {
    if (this->S.size() == 0) {
        throw RemoveCardOp_Illegal();
    }
    this->S.removeLastCard();
}

unsigned int PokerCardFoundation::size() { return this->S.size(); }

bool PokerCardFoundation::canMoveCard2(PokerCardFreeCell* c) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return c->canAppendCard(C);
    }
    return false;
}

bool PokerCardFoundation::moveCard2(PokerCardFreeCell* c) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        if (c->canAppendCard(C)) {
            c->appendCard(C);
            this->S.removeLastCard();
            return true;
        }
    }
    return false;
}

bool PokerCardFoundation::canMoveCard2(PokerCardPile* p) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return p->canAppendCard(C);
    }
    return false;
}

bool PokerCardFoundation::moveCard2(PokerCardPile* p) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        if (p->canAppendCard(C)) {
            p->appendCard(C);
            this->S.removeLastCard();
            return true;
        }
    }
    return false;
}

bool PokerCardFoundation::canMoveCard2(PokerCardFoundation* f) {
    if (this == f) {
        return false;
    }
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return f->canAppendCard(C);
    }
    return false;
}

bool PokerCardFoundation::moveCard2(PokerCardFoundation* f) {
    if (this == f) {
        return false;
    }
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        if (f->canAppendCard(C)) {
            f->appendCard(C);
            this->S.removeLastCard();
            return true;
        }
    }
    return false;
}

PokerCard PokerCardFoundation::card(unsigned int i) { return this->S.card(i); }
