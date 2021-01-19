///
/// \file PokerCardPile.cpp
/// \author Shengchen Zhou
/// \brief The PokerCardPile module (source)
/// \date 6 Apr 2018
///

#include "PokerCardPile.h"
#include "Exceptions.h"

#include "PokerCardFreeCell.h"
#include "PokerCardFoundation.h"

using namespace std;

PokerCardPile::PokerCardPile() {
}

void PokerCardPile::init(vector<PokerCard> s) {
    this->S.init(s);
}

bool PokerCardPile::canAppendCard(PokerCard c) {
    if (this->S.size() != 0) {
        PokerCard lc = this->S.lastCard();
        if (lc.c() == c.c()) {
            return false;
        }
        if (lc.r() - c.r() != 1) {
            return false;
        }
    }
    return true;
}

void PokerCardPile::appendCard(PokerCard c) {
    if (!canAppendCard(c)) {
        throw AddCardOp_Illegal();
    }
    this->S.addCard(c);
}

void PokerCardPile::removeCard() {
    if (this->S.size() == 0) {
        throw RemoveCardOp_Illegal();
    }
    this->S.removeLastCard();
}

unsigned int PokerCardPile::size() {
    return this->S.size();
}

bool PokerCardPile::canMoveCard2(PokerCardFreeCell* c) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return c->canAppendCard(C);
    }
    return false;
}

bool PokerCardPile::moveCard2(PokerCardFreeCell* c) {
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

bool PokerCardPile::canMoveCard2(PokerCardPile* p) {
    if (this == p) {
        return false;
    }
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return p->canAppendCard(C);
    }
    return false;
}

bool PokerCardPile::moveCard2(PokerCardPile* p) {
    if (this == p) {
        return false;
    }
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

bool PokerCardPile::canMoveCard2(PokerCardFoundation* f) {
    if (this->S.size() != 0) {
        PokerCard C = this->S.lastCard();
        return f->canAppendCard(C);
    }
    return false;
}

bool PokerCardPile::moveCard2(PokerCardFoundation* f) {
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

PokerCard PokerCardPile::card(unsigned int i) {
    return this->S.card(i);
}
