///
/// \file PokerCardFreeCell.cpp
/// \author Shengchen Zhou
/// \brief The PokerCardFreeCell module (source)
/// \date 6 Apr 2018
///

#include "PokerCardFreeCell.h"
#include "Exceptions.h"

#include "PokerCardFoundation.h"
#include "PokerCardPile.h"

using namespace std;

PokerCardFreeCell::PokerCardFreeCell() {}

bool PokerCardFreeCell::canAppendCard(PokerCard c) {
    if (this->S.size() != 0) {
        return false;
    }
    return true;
}

void PokerCardFreeCell::appendCard(PokerCard c) {
    if (!canAppendCard(c)) {
        throw AddCardOp_Illegal();
    }
    this->S.addCard(c);
}

void PokerCardFreeCell::removeCard() {
    if (this->S.size() == 0) {
        throw RemoveCardOp_Illegal();
    }
    this->S.removeLastCard();
}

unsigned int PokerCardFreeCell::size() { return this->S.size(); }

bool PokerCardFreeCell::canMoveCard2(PokerCardFreeCell* c) {
    if (this == c) {
        return false;
    }
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return c->canAppendCard(C);
    }
    return false;
}

bool PokerCardFreeCell::moveCard2(PokerCardFreeCell* c) {
    if (this == c) {
        return false;
    }
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

bool PokerCardFreeCell::canMoveCard2(PokerCardPile* p) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return p->canAppendCard(C);
    }
    return false;
}

bool PokerCardFreeCell::moveCard2(PokerCardPile* p) {
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

bool PokerCardFreeCell::canMoveCard2(PokerCardFoundation* f) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return f->canAppendCard(C);
    }
    return false;
}

bool PokerCardFreeCell::moveCard2(PokerCardFoundation* f) {
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

PokerCard PokerCardFreeCell::card() {
    return this->S.card(0);
}
