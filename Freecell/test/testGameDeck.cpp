#include "catch.h"

#include "GameDeck.h"

TEST_CASE("GameDeck - no valid moves - 1", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    c[0].appendCard({Five, Clubs});
    c[1].appendCard({Ten, Hearts});
    c[2].appendCard({Eight, Spades});
    c[3].appendCard({Jack, Spades});

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    p[0].init({{Four, Hearts}});
    p[1].init({{Ten, Diamonds}});
    p[2].init({{King, Clubs}});
    p[3].init({{Six, Clubs}});
    p[4].init({{Three, Hearts}});
    p[5].init({{Three, Diamonds}});
    p[6].init({{Ten, Spades}});
    p[7].init({{Queen, Spades}});

    GameDeck gamedeck(c, p, f);

    REQUIRE_FALSE(gamedeck.validMoves());
}

TEST_CASE("GameDeck - no valid moves - 2", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    c[0].appendCard({Five, Clubs});
    c[1].appendCard({Ten, Hearts});
    c[2].appendCard({Eight, Spades});
    c[3].appendCard({Jack, Spades});

    f[0].appendCard({Ace, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    p[0].init({{Four, Hearts}});
    p[1].init({{Ten, Diamonds}});
    p[2].init({{Two, Spades}});
    p[3].init({{Six, Clubs}});
    p[4].init({{Three, Hearts}});
    p[5].init({{Three, Diamonds}});
    p[6].init({{Ten, Spades}});
    p[7].init({{Queen, Spades}});

    GameDeck gamedeck(c, p, f);

    REQUIRE(gamedeck.validMoves());
}

TEST_CASE("GameDeck - no valid moves - 3", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    c[0].appendCard({Ace, Diamonds});
    c[1].appendCard({Ten, Hearts});
    c[2].appendCard({Eight, Spades});
    c[3].appendCard({Jack, Spades});

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    p[0].init({{Four, Hearts}});
    p[1].init({{Ten, Diamonds}});
    p[2].init({{King, Clubs}});
    p[3].init({{Six, Clubs}});
    p[4].init({{Three, Hearts}});
    p[5].init({{Three, Diamonds}});
    p[6].init({{Ten, Spades}});
    p[7].init({{Queen, Spades}});

    GameDeck gamedeck(c, p, f);

    REQUIRE(gamedeck.validMoves());
}

TEST_CASE("GameDeck - no valid moves - 4", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    c[0].appendCard({Five, Clubs});
    c[1].appendCard({Ten, Hearts});
    c[2].appendCard({Eight, Spades});
    c[3].appendCard({Jack, Spades});

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    p[0].init({{Four, Hearts}});
    p[1].init({{Ten, Diamonds}});
    p[2].init({{King, Diamonds}});
    p[3].init({{Six, Clubs}});
    p[4].init({{Three, Hearts}});
    p[5].init({{Three, Diamonds}});
    p[6].init({{Ten, Spades}});
    p[7].init({{Queen, Spades}});

    GameDeck gamedeck(c, p, f);

    REQUIRE(gamedeck.validMoves());
}

TEST_CASE("GameDeck - move between columns", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    p[0].init({{Four, Hearts}});
    p[1].init({{Ten, Diamonds}});
    p[2].init({{King, Diamonds}});
    p[3].init({{Six, Clubs}});
    p[4].init({{Jack, Hearts}});
    p[5].init({{Three, Clubs}});
    p[6].init({{Ten, Spades}});
    p[7].init({{Queen, Spades}});

    GameDeck gamedeck(c, p, f);

    REQUIRE_FALSE(gamedeck.pile2Pile(0, 1));
    REQUIRE_FALSE(gamedeck.pile2Pile(1, 2));
    REQUIRE_FALSE(gamedeck.pile2Pile(2, 3));
    REQUIRE_FALSE(gamedeck.pile2Pile(3, 4));
    REQUIRE_FALSE(gamedeck.pile2Pile(4, 5));
    REQUIRE_FALSE(gamedeck.pile2Pile(5, 6));
    REQUIRE_FALSE(gamedeck.pile2Pile(6, 7));
    REQUIRE(gamedeck.pile2Pile(4, 7));
    REQUIRE(gamedeck.pile2Pile(5, 0));
    REQUIRE_FALSE(gamedeck.pile2Pile(4, 7));
    REQUIRE_FALSE(gamedeck.pile2Pile(5, 0));
}

TEST_CASE("GameDeck - moving to free cell - 1", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    c[0].appendCard({Five, Clubs});
    c[1].appendCard({Ten, Hearts});
    c[2].appendCard({Eight, Spades});
    c[3].appendCard({Jack, Spades});

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    p[0].init({{Four, Hearts}});
    p[1].init({{Ten, Diamonds}});
    p[2].init({{King, Diamonds}});
    p[3].init({{Six, Clubs}});
    p[4].init({{Three, Hearts}});
    p[5].init({{Three, Diamonds}});
    p[6].init({{Ten, Spades}});
    p[7].init({{Queen, Spades}});

    GameDeck gamedeck(c, p, f);

    REQUIRE_FALSE(gamedeck.pile2FreeCell(0, 0));
    REQUIRE_FALSE(gamedeck.pile2FreeCell(3, 2));
    REQUIRE_FALSE(gamedeck.pile2FreeCell(7, 3));
}

TEST_CASE("GameDeck - moving to free cell - 2", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    c[0].appendCard({Five, Clubs});
    c[3].appendCard({Jack, Spades});

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    p[0].init({{Four, Hearts}});
    p[1].init({{Ten, Diamonds}});
    p[2].init({{King, Diamonds}});
    p[3].init({{Six, Clubs}});
    p[4].init({{Three, Hearts}});
    p[5].init({{Three, Diamonds}});
    p[6].init({{Ten, Spades}});
    p[7].init({{Queen, Spades}});

    GameDeck gamedeck(c, p, f);

    REQUIRE(gamedeck.pile2FreeCell(0, 1));
    REQUIRE(gamedeck.pile2FreeCell(3, 2));
}

TEST_CASE("GameDeck - winning game board - 1", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    GameDeck gamedeck(c, p, f);

    REQUIRE(gamedeck.Winning());
}

TEST_CASE("GameDeck - winning game board - 2", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    p[6].init({{Four, Hearts}});

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    GameDeck gamedeck(c, p, f);

    REQUIRE_FALSE(gamedeck.Winning());
}

TEST_CASE("GameDeck - winning game board - 3", "[gamedeck]") {
    PokerCardFreeCell c[GameDeck::NC];
    PokerCardPile p[GameDeck::NP];
    PokerCardFoundation f[GameDeck::NF];

    c[3].appendCard({Jack, Spades});

    f[0].appendCard({Ace, Spades});
    f[0].appendCard({Two, Spades});
    f[1].appendCard({Ace, Clubs});
    f[1].appendCard({Two, Clubs});

    GameDeck gamedeck(c, p, f);

    REQUIRE_FALSE(gamedeck.Winning());
}
