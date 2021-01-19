#include "catch.h"

#include "PokerCardFreeCell.h"
#include "Exceptions.h"

#include "PokerCardFoundation.h"
#include "PokerCardPile.h"

TEST_CASE("PokerCardFreeCell constructor", "[pokercardfreecell]") {
    PokerCardFreeCell();
}

TEST_CASE("PokerCardFreeCell.canAppendCard", "[pokercardfreecell]") {
    PokerCardFreeCell c;
    REQUIRE(c.canAppendCard({Ace, Spades}));
    REQUIRE(c.canAppendCard({Two, Diamonds}));
    REQUIRE(c.canAppendCard({Three, Hearts}));
    REQUIRE(c.canAppendCard({Four, Spades}));
    c.appendCard({Ace, Spades});
    REQUIRE_FALSE(c.canAppendCard({Ace, Spades}));
    REQUIRE_FALSE(c.canAppendCard({Two, Diamonds}));
    REQUIRE_FALSE(c.canAppendCard({Three, Hearts}));
    REQUIRE_FALSE(c.canAppendCard({Four, Spades}));
}

TEST_CASE("PokerCardFreeCell.appendCard", "[pokercardfreecell]") {
    PokerCardFreeCell c;
    c.appendCard({Two, Diamonds});
    REQUIRE_THROWS_AS(c.appendCard({Three, Diamonds}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(c.appendCard({Three, Hearts}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(c.appendCard({Four, Spades}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(c.appendCard({Five, Clubs}), AddCardOp_Illegal);
}

TEST_CASE("PokerCardFreeCell.card()", "[pokercardfreecell]") {
    PokerCardFreeCell c;
    REQUIRE_THROWS_AS(c.card(), GetCardOp_Illegal);
    c.appendCard({Ace, Spades});
    REQUIRE(c.card() == PokerCard(Ace, Spades));
}

TEST_CASE("PokerCardFreeCell.removeCard", "[pokercardfreecell]") {
    PokerCardFreeCell c;
    REQUIRE_THROWS_AS(c.removeCard(), RemoveCardOp_Illegal);
    c.appendCard({Ace, Spades});
    c.removeCard();
    REQUIRE_THROWS_AS(c.card(), GetCardOp_Illegal);
    REQUIRE_THROWS_AS(c.removeCard(), RemoveCardOp_Illegal);
}

TEST_CASE("PokerCardFreeCell.size()", "[pokercardfreecell]") {
    PokerCardFreeCell c;
    REQUIRE(c.size() == 0);
    c.appendCard({Ace, Spades});
    REQUIRE(c.size() == 1);
    c.removeCard();
    REQUIRE(c.size() == 0);
}

TEST_CASE("PokerCardFreeCell.canMoveCard2PokerCardFreeCell", "[pokercardpile]") {
    PokerCardFreeCell c;
    PokerCardFreeCell c2;
    REQUIRE_FALSE(c.canMoveCard2(&c));
    REQUIRE_FALSE(c.canMoveCard2(&c2));
    c.appendCard({Jack, Hearts});
    REQUIRE(c.canMoveCard2(&c2));
}

TEST_CASE("PokerCardFreeCell.moveCard2PokerCardFreeCell", "[pokercardpile]") {
    PokerCardFreeCell c;
    PokerCardFreeCell c2;
    REQUIRE_FALSE(c.moveCard2(&c));
    REQUIRE_FALSE(c.moveCard2(&c2));
    c.appendCard({Jack, Hearts});
    REQUIRE(c.moveCard2(&c2));
    REQUIRE(c.size() == 0);
    REQUIRE(c2.card() == PokerCard(Jack, Hearts));
    c.appendCard({Queen, Diamonds});
    REQUIRE_FALSE(c.moveCard2(&c2));
}

TEST_CASE("PokerCardFreeCell.canMoveCard2PokerCardPile", "[pokercardpile]") {
    PokerCardFreeCell c;
    PokerCardPile p;
    REQUIRE_FALSE(c.canMoveCard2(&p));
    c.appendCard({Jack, Hearts});
    REQUIRE(c.canMoveCard2(&p));
}

TEST_CASE("PokerCardFreeCell.moveCard2PokerCardPile", "[pokercardpile]") {
    PokerCardFreeCell c;
    PokerCardPile p;
    REQUIRE_FALSE(c.moveCard2(&p));
    c.appendCard({Jack, Hearts});
    REQUIRE(c.moveCard2(&p));
    REQUIRE(c.size() == 0);
    REQUIRE(p.card(0) == PokerCard(Jack, Hearts));
    REQUIRE(p.size() == 1);
    p.init({{Ace, Hearts}, {Three, Diamonds}, {Jack, Spades}});
    c.appendCard({Jack, Hearts});
    REQUIRE_FALSE(c.moveCard2(&p));
    c.removeCard();
    c.appendCard({Ten, Spades});
    REQUIRE_FALSE(c.moveCard2(&p));
    c.removeCard();
    c.appendCard({Ten, Hearts});
    REQUIRE(c.moveCard2(&p));
}

TEST_CASE("PokerCardFreeCell.canMoveCard2PokerCardFoundation", "[pokercardpile]") {
    PokerCardFreeCell c;
    PokerCardFoundation f;
    REQUIRE_FALSE(c.canMoveCard2(&f));
    c.appendCard({Jack, Clubs});
    REQUIRE_FALSE(c.canMoveCard2(&f));
    c.removeCard();
    c.appendCard({Ace, Clubs});
    REQUIRE(c.canMoveCard2(&f));
}

TEST_CASE("PokerCardFreeCell.moveCard2PokerCardFoundation", "[pokercardpile]") {
    PokerCardFreeCell c;
    PokerCardFoundation f;
    REQUIRE_FALSE(c.moveCard2(&f));
    c.appendCard({Jack, Clubs});
    REQUIRE_FALSE(c.moveCard2(&f));
    c.removeCard();
    c.appendCard({Ace, Clubs});
    REQUIRE(c.moveCard2(&f));
    REQUIRE(c.size() == 0);
    REQUIRE(f.card(0) == PokerCard(Ace, Clubs));
    REQUIRE(f.size() == 1);
}
