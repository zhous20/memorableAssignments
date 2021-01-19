///
/// \file PokerCard.h
/// \author Shengchen Zhou
/// \brief The PokerCard module (header)
/// \date 6 Apr 2018
///

#ifndef _POKERCARD_H_
#define _POKERCARD_H_

#include "PokerCardMetaTypes.h"

///
/// PokerCard type
///
class PokerCard {
private:
    PokerCardRankT R; ///< The rank of pokercard
    PokerCardSuitT S; ///< The suit of pokercard
public:
    ///
    /// \brief PokerCard constructor
    /// \param r The input rank of pokercard
    /// \param s The input suit of pokercard
    ///
    PokerCard(PokerCardRankT r, PokerCardSuitT s);
    ///
    /// \brief Obtain the rank of pokercard
    /// \return The rank
    ///
    PokerCardRankT r();
    ///
    /// \brief Obtain the suit of pokercard
    /// \return The suit
    ///
    PokerCardSuitT s();
    ///
    /// \brief Obtain the color of pokercard
    /// \return The color
    ///
    PokerCardColrT c();
    ///
    /// \brief Equality check
    /// \param c The input pokercard
    /// \return True if current pokercard is the same as the input one, false if not
    ///
    bool operator==(PokerCard c) const;
};

#endif
