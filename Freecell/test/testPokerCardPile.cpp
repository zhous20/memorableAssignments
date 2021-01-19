#include "catch.h"

#include "PokerCardPile.h"
#include "Exceptions.h"

#include "PokerCardFoundation.h"
#include "PokerCardFreeCell.h"

TEST_CASE("PokerCardPile constructor", "[pokercardpile]") {
    PokerCardPile();
}

TEST_CASE("PokerCardPile.init", "[pokercardpile]") {
    PokerCardPile p;
    p.init({{Three, Diamonds}, {Jack, Spades}, {Ace, Hearts}});
    p.init({});
}

TEST_CASE("PokerCardPile.card()", "[pokercardpile]") {
    PokerCardPile p;
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE(p.card(1) == PokerCard(Ace, Hearts));
    REQUIRE(p.card(2) == PokerCard(Three, Diamonds));
    REQUIRE_THROWS_AS(p.card(3), GetCardOp_Illegal);
    p.init({});
    REQUIRE_THROWS_AS(p.card(0), GetCardOp_Illegal);
}

TEST_CASE("PokerCardPile.canAppendCard", "[pokercardpile]") {
    PokerCardPile p;
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE_FALSE(p.canAppendCard({Two, Diamonds}));
    REQUIRE_FALSE(p.canAppendCard({Two, Hearts}));
    REQUIRE_FALSE(p.canAppendCard({Three, Spades}));
    REQUIRE_FALSE(p.canAppendCard({Three, Clubs}));
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE(p.card(1) == PokerCard(Ace, Hearts));
    REQUIRE(p.card(2) == PokerCard(Three, Diamonds));
    REQUIRE_THROWS_AS(p.card(3), GetCardOp_Illegal);
    REQUIRE(p.canAppendCard({Two, Clubs}));
    REQUIRE_THROWS_AS(p.card(3), GetCardOp_Illegal);
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE(p.canAppendCard({Two, Spades}));
    REQUIRE_THROWS_AS(p.card(3), GetCardOp_Illegal);
    p.init({});
    REQUIRE(p.canAppendCard({Two, Spades}));
    p.init({});
    REQUIRE(p.canAppendCard({Ace, Hearts}));
}

TEST_CASE("PokerCardPile.appendCard", "[pokercardpile]") {
    PokerCardPile p;
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE_THROWS_AS(p.appendCard({Two, Diamonds}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(p.appendCard({Two, Hearts}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(p.appendCard({Three, Spades}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(p.appendCard({Three, Clubs}), AddCardOp_Illegal);
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE(p.card(1) == PokerCard(Ace, Hearts));
    REQUIRE(p.card(2) == PokerCard(Three, Diamonds));
    REQUIRE_THROWS_AS(p.card(3), GetCardOp_Illegal);
    p.appendCard({Two, Clubs});
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    p.appendCard({Two, Spades});
    REQUIRE(p.card(3) == PokerCard(Two, Spades));
    REQUIRE_THROWS_AS(p.card(4), GetCardOp_Illegal);
    p.init({});
    p.appendCard({Two, Spades});
    p.init({});
    p.appendCard({Ace, Hearts});
}

TEST_CASE("PokerCardPile.removeCard", "[pokercardpile]") {
    PokerCardPile p;
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    p.removeCard();
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE(p.card(1) == PokerCard(Ace, Hearts));
    REQUIRE_THROWS_AS(p.card(2), GetCardOp_Illegal);
    p.removeCard();
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE_THROWS_AS(p.card(1), GetCardOp_Illegal);
    p.removeCard();
    REQUIRE_THROWS_AS(p.card(0), GetCardOp_Illegal);
    REQUIRE_THROWS_AS(p.removeCard(), RemoveCardOp_Illegal);
}

TEST_CASE("PokerCardPile.size", "[pokercardpile]") {
    PokerCardPile p;
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE(p.size() == 3);
    p.appendCard({Two, Clubs});
    REQUIRE(p.size() == 4);
    p.removeCard();
    REQUIRE(p.size() == 3);
    p.init({});
    REQUIRE(p.size() == 0);
}

TEST_CASE("PokerCardPile.canMoveCard2PokerCardFreeCell", "[pokercardpile]") {
    PokerCardPile p;
    PokerCardFreeCell c;
    REQUIRE_FALSE(p.canMoveCard2(&c));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE(p.canMoveCard2(&c));
}


TEST_CASE("PokerCardPile.moveCard2PokerCardFreeCell", "[pokercardpile]") {
    PokerCardPile p;
    PokerCardFreeCell c;
    REQUIRE_FALSE(p.moveCard2(&c));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE(p.moveCard2(&c));
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE(p.card(1) == PokerCard(Ace, Hearts));
    REQUIRE(p.size() == 2);
    REQUIRE(c.card() == PokerCard(Three, Diamonds));
    REQUIRE_FALSE(p.moveCard2(&c));
}

TEST_CASE("PokerCardPile.canMoveCard2PokerCardPile", "[pokercardpile]") {
    PokerCardPile p;
    PokerCardPile p2;
    REQUIRE_FALSE(p.canMoveCard2(&p));
    REQUIRE_FALSE(p.canMoveCard2(&p2));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE(p.canMoveCard2(&p2));
}

TEST_CASE("PokerCardPile.moveCard2PokerCardPile", "[pokercardpile]") {
    PokerCardPile p;
    PokerCardPile p2;
    REQUIRE_FALSE(p.moveCard2(&p));
    REQUIRE_FALSE(p.moveCard2(&p2));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE(p.moveCard2(&p2));
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE(p.card(1) == PokerCard(Ace, Hearts));
    REQUIRE(p.size() == 2);
    REQUIRE(p2.card(0) == PokerCard(Three, Diamonds));
    REQUIRE(p2.size() == 1);
    REQUIRE_FALSE(p.moveCard2(&p2));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Two, Diamonds}});
    REQUIRE_FALSE(p.moveCard2(&p2));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Two, Spades}});
    REQUIRE(p.moveCard2(&p2));
}

TEST_CASE("PokerCardPile.canMoveCard2PokerCardFoundation", "[pokercardpile]") {
    PokerCardPile p;
    PokerCardFoundation f;
    REQUIRE_FALSE(p.canMoveCard2(&f));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE_FALSE(p.canMoveCard2(&f));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Two, Spades}});
    REQUIRE_FALSE(p.canMoveCard2(&f));
    p.init({{Jack, Spades}, {Three, Diamonds}, {Ace, Hearts}});
    REQUIRE(p.canMoveCard2(&f));
}

TEST_CASE("PokerCardPile.moveCard2PokerCardFoundation", "[pokercardpile]") {
    PokerCardPile p;
    PokerCardFoundation f;
    REQUIRE_FALSE(p.moveCard2(&f));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Three, Diamonds}});
    REQUIRE_FALSE(p.moveCard2(&f));
    p.init({{Jack, Spades}, {Ace, Hearts}, {Two, Spades}});
    REQUIRE_FALSE(p.moveCard2(&f));
    p.init({{Jack, Spades}, {Three, Diamonds}, {Ace, Hearts}});
    REQUIRE(p.moveCard2(&f));
    REQUIRE(p.card(0) == PokerCard(Jack, Spades));
    REQUIRE(p.card(1) == PokerCard(Three, Diamonds));
    REQUIRE(p.size() == 2);
    REQUIRE(f.card(0) == PokerCard(Ace, Hearts));
    REQUIRE(f.size() == 1);
}
