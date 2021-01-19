#include "catch.h"

#include "PokerCardSeq.h"
#include "Exceptions.h"

TEST_CASE("PokerCardSeq constructor", "[pokercardseq]") {
    PokerCardSeq();
}

TEST_CASE("PokerCardSeq.init", "[pokercardseq]") {
    PokerCardSeq s;
    s.init({{Three, Diamonds}, {Jack, Spades}, {Ace, Hearts}});
    s.init({});
}

TEST_CASE("PokerCardSeq.lastCard", "[pokercardseq]") {
    PokerCardSeq s;
    s.init({{Three, Diamonds}, {Jack, Spades}, {Ace, Hearts}});
    REQUIRE(s.lastCard() == PokerCard(Ace, Hearts));
    s.init({});
    REQUIRE_THROWS_AS(s.lastCard(), GetCardOp_Illegal);
}

TEST_CASE("PokerCardSeq.card", "[pokercardseq]") {
    PokerCardSeq s;
    s.init({{Three, Diamonds}, {Jack, Spades}, {Ace, Hearts}});
    REQUIRE(s.card(0) == PokerCard(Three, Diamonds));
    REQUIRE(s.card(1) == PokerCard(Jack, Spades));
    REQUIRE(s.card(2) == PokerCard(Ace, Hearts));
    REQUIRE_THROWS_AS(s.card(3), GetCardOp_Illegal);
    s.init({});
    REQUIRE_THROWS_AS(s.card(0), GetCardOp_Illegal);
}

TEST_CASE("PokerCardSeq.addCard", "[pokercardseq]") {
    PokerCardSeq s;
    s.init({{Three, Diamonds}, {Jack, Spades}, {Ace, Hearts}});
    s.addCard({Five, Clubs});
    s.addCard({King, Spades});
    s.addCard({Two, Diamonds});
    REQUIRE(s.card(0) == PokerCard(Three, Diamonds));
    REQUIRE(s.card(1) == PokerCard(Jack, Spades));
    REQUIRE(s.card(2) == PokerCard(Ace, Hearts));
    REQUIRE(s.card(3) == PokerCard(Five, Clubs));
    REQUIRE(s.card(4) == PokerCard(King, Spades));
    REQUIRE(s.card(5) == PokerCard(Two, Diamonds));
    REQUIRE_THROWS_AS(s.card(6), GetCardOp_Illegal);
}

TEST_CASE("PokerCardSeq.removeLastCard", "[pokercardseq]") {
    PokerCardSeq s;
    s.init({{Three, Diamonds}, {Jack, Spades}, {Ace, Hearts}});
    s.removeLastCard();
    REQUIRE(s.card(0) == PokerCard(Three, Diamonds));
    REQUIRE(s.card(1) == PokerCard(Jack, Spades));
    REQUIRE_THROWS_AS(s.card(2), GetCardOp_Illegal);
    s.removeLastCard();
    REQUIRE(s.card(0) == PokerCard(Three, Diamonds));
    REQUIRE_THROWS_AS(s.card(1), GetCardOp_Illegal);
    s.removeLastCard();
    REQUIRE_THROWS_AS(s.card(0), GetCardOp_Illegal);
    s.init({});
    REQUIRE_THROWS_AS(s.removeLastCard(), RemoveCardOp_Illegal);
}

TEST_CASE("PokerCardSeq.size", "[pokercardseq]") {
    PokerCardSeq s;
    s.init({{Three, Diamonds}, {Jack, Spades}, {Ace, Hearts}});
    REQUIRE(s.size() == 3);
    s.addCard({Two, Diamonds});
    REQUIRE(s.size() == 4);
    s.removeLastCard();
    REQUIRE(s.size() == 3);
    s.init({});
    REQUIRE(s.size() == 0);
}