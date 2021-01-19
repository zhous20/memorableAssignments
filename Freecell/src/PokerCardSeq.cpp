///
/// \file PokerCardSeq.cpp
/// \author Shengchen Zhou
/// \brief The PokerCardSeq module (source)
/// \date 6 Apr 2018
///

#include "PokerCardSeq.h"
#include "Exceptions.h"

using namespace std;

PokerCardSeq::PokerCardSeq() {
}

void PokerCardSeq::init(vector<PokerCard> s) {
    this->S = s;
}

PokerCard PokerCardSeq::lastCard() {
    if (this->S.empty()) {
        throw GetCardOp_Illegal();
    }
    return this->S.back();
}

PokerCard PokerCardSeq::card(unsigned int i) {
    if (i + 1 > this->S.size()) {
        throw GetCardOp_Illegal();
    }
    return this->S[i];
}

void PokerCardSeq::removeLastCard() {
    if (this->S.empty()) {
        throw RemoveCardOp_Illegal();
    }
    this->S.pop_back();
}

void PokerCardSeq::addCard(PokerCard c) {
    this->S.push_back(c);
}

unsigned int PokerCardSeq::size() {
    return this->S.size();
}
