#include "catch.h"

#include "PokerCardFoundation.h"
#include "Exceptions.h"

#include "PokerCardFreeCell.h"
#include "PokerCardPile.h"

TEST_CASE("PokerCardFoundation constructor", "[pokercardfoundation]") {
    PokerCardFoundation();
}

TEST_CASE("PokerCardFoundation.canAppendCard", "[pokercardfoundation]") {
    PokerCardFoundation f;
    REQUIRE_FALSE(f.canAppendCard({Two, Diamonds}));
    REQUIRE_FALSE(f.canAppendCard({Three, Hearts}));
    REQUIRE_FALSE(f.canAppendCard({Four, Spades}));
    REQUIRE_FALSE(f.canAppendCard({Five, Clubs}));
    REQUIRE(f.canAppendCard({Ace, Spades}));
    REQUIRE(f.canAppendCard({Ace, Clubs}));
    REQUIRE(f.canAppendCard({Ace, Hearts}));
    REQUIRE(f.canAppendCard({Ace, Diamonds}));
    f.appendCard({Ace, Spades});
    REQUIRE_FALSE(f.canAppendCard({Two, Hearts}));
    REQUIRE_FALSE(f.canAppendCard({Two, Clubs}));
    REQUIRE_FALSE(f.canAppendCard({Two, Diamonds}));
    REQUIRE_FALSE(f.canAppendCard({Three, Spades}));
    REQUIRE_FALSE(f.canAppendCard({Four, Spades}));
    REQUIRE_FALSE(f.canAppendCard({Five, Spades}));
    REQUIRE(f.canAppendCard({Two, Spades}));
}

TEST_CASE("PokerCardFoundation.appendCard", "[pokercardfoundation]") {
    PokerCardFoundation f;
    REQUIRE_THROWS_AS(f.appendCard({Two, Diamonds}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Three, Hearts}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Four, Spades}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Five, Clubs}), AddCardOp_Illegal);
    f.appendCard({Ace, Spades});
    REQUIRE_THROWS_AS(f.appendCard({Two, Hearts}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Two, Clubs}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Two, Diamonds}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Three, Spades}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Four, Spades}), AddCardOp_Illegal);
    REQUIRE_THROWS_AS(f.appendCard({Five, Spades}), AddCardOp_Illegal);
    f.appendCard({Two, Spades});
}

TEST_CASE("PokerCardFoundation.card()", "[pokercardfoundation]") {
    PokerCardFoundation f;
    REQUIRE_THROWS_AS(f.card(0), GetCardOp_Illegal);
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE(f.card(0) == PokerCard(Ace, Spades));
    REQUIRE(f.card(1) == PokerCard(Two, Spades));
    REQUIRE(f.card(2) == PokerCard(Three, Spades));
    REQUIRE_THROWS_AS(f.card(3), GetCardOp_Illegal);
}

TEST_CASE("PokerCardFoundation.removeCard", "[pokercardfoundation]") {
    PokerCardFoundation f;
    REQUIRE_THROWS_AS(f.removeCard(), RemoveCardOp_Illegal);
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    f.removeCard();
    REQUIRE(f.card(0) == PokerCard(Ace, Spades));
    REQUIRE(f.card(1) == PokerCard(Two, Spades));
    REQUIRE_THROWS_AS(f.card(2), GetCardOp_Illegal);
    f.removeCard();
    REQUIRE(f.card(0) == PokerCard(Ace, Spades));
    REQUIRE_THROWS_AS(f.card(1), GetCardOp_Illegal);
    f.removeCard();
    REQUIRE_THROWS_AS(f.card(0), GetCardOp_Illegal);
}

TEST_CASE("PokerCardFoundation.size()", "[pokercardfoundation]") {
    PokerCardFoundation f;
    REQUIRE(f.size() == 0);
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE(f.size() == 3);
    f.removeCard();
    REQUIRE(f.size() == 2);
    f.appendCard({Three, Spades});
    REQUIRE(f.size() == 3);
}

TEST_CASE("PokerCardFoundation.canMoveCard2PokerCardFreeCell", "[pokercardpile]") {
    PokerCardFoundation f;
    PokerCardFreeCell c;
    REQUIRE_FALSE(f.canMoveCard2(&c));
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE(f.canMoveCard2(&c));
}

TEST_CASE("PokerCardFoundation.moveCard2PokerCardFreeCell", "[pokercardpile]") {
    PokerCardFoundation f;
    PokerCardFreeCell c;
    REQUIRE_FALSE(f.moveCard2(&c));
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE(f.moveCard2(&c));
    REQUIRE(f.card(0) == PokerCard(Ace, Spades));
    REQUIRE(f.card(1) == PokerCard(Two, Spades));
    REQUIRE(f.size() == 2);
    REQUIRE(c.card() == PokerCard(Three, Spades));
    REQUIRE_FALSE(f.moveCard2(&c));
}

TEST_CASE("PokerCardFoundation.canMoveCard2PokerCardPile", "[pokercardpile]") {
    PokerCardFoundation f;
    PokerCardPile p;
    REQUIRE_FALSE(f.canMoveCard2(&p));
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE(f.canMoveCard2(&p));
}

TEST_CASE("PokerCardFoundation.moveCard2PokerCardPile", "[pokercardpile]") {
    PokerCardFoundation f;
    PokerCardPile p;
    REQUIRE_FALSE(f.moveCard2(&p));
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE(f.moveCard2(&p));
    REQUIRE(f.card(0) == PokerCard(Ace, Spades));
    REQUIRE(f.card(1) == PokerCard(Two, Spades));
    REQUIRE(f.size() == 2);
    REQUIRE(p.card(0) == PokerCard(Three, Spades));
    REQUIRE(p.size() == 1);
    REQUIRE_FALSE(f.moveCard2(&p));
    p.init({{Seven, Diamonds}, {Jack, Clubs}, {Three, Hearts}});
    REQUIRE(f.moveCard2(&p));
}

TEST_CASE("PokerCardFoundation.canMoveCard2PokerCardFoundation", "[pokercardpile]") {
    PokerCardFoundation f;
    PokerCardFoundation f2;
    REQUIRE_FALSE(f.canMoveCard2(&f));
    REQUIRE_FALSE(f.canMoveCard2(&f2));
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE_FALSE(f.canMoveCard2(&f2));
}

TEST_CASE("PokerCardFoundation.moveCard2PokerCardFoundation", "[pokercardpile]") {
    PokerCardFoundation f;
    PokerCardFoundation f2;
    REQUIRE_FALSE(f.moveCard2(&f));
    REQUIRE_FALSE(f.moveCard2(&f2));
    f.appendCard({Ace, Spades});
    f.appendCard({Two, Spades});
    f.appendCard({Three, Spades});
    REQUIRE_FALSE(f.moveCard2(&f2));
    f.removeCard();
    f.removeCard();
    REQUIRE(f.moveCard2(&f2));
    REQUIRE(f.size() == 0);
    REQUIRE(f2.size() == 1);
    REQUIRE(f2.card(0) == PokerCard(Ace, Spades));
}
