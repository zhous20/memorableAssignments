#include "catch.h"

#include "PokerCard.h"

TEST_CASE("PokerCard constructor", "[pokercard]") {
    for (int r = Ace; r != King; ++r) {
        for (int s = Diamonds; s != Spades; ++s) {
            PokerCard(static_cast<PokerCardRankT>(r),
                      static_cast<PokerCardSuitT>(s));
        }
    }
}

TEST_CASE("PokerCard.r", "[pokercard]") {
    for (int r = Ace; r != King; ++r) {
        for (int s = Diamonds; s != Spades; ++s) {
            PokerCard c(static_cast<PokerCardRankT>(r),
                        static_cast<PokerCardSuitT>(s));
            REQUIRE(c.r() == r);
        }
    }
}

TEST_CASE("PokerCard.s", "[pokercard]") {
    for (int r = Ace; r != King; ++r) {
        for (int s = Diamonds; s != Spades; ++s) {
            PokerCard c(static_cast<PokerCardRankT>(r),
                        static_cast<PokerCardSuitT>(s));
            REQUIRE(c.s() == s);
        }
    }
}

TEST_CASE("PokerCard.c", "[pokercard]") {
    for (int r = Ace; r != King; ++r) {
        for (int s = Diamonds; s != Spades; ++s) {
            PokerCard c(static_cast<PokerCardRankT>(r),
                        static_cast<PokerCardSuitT>(s));
            if (s == Diamonds || s == Hearts)
                REQUIRE(c.c() == Red);
            else
                REQUIRE(c.c() == Black);
        }
    }
}
