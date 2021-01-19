///
/// \file PokerCardSeq.h
/// \author Shengchen Zhou
/// \brief The PokerCardSeq module (header)
/// \date 6 Apr 2018
///

#ifndef _POKERCARDSEQ_H_
#define _POKERCARDSEQ_H_

#include <vector>

#include "PokerCard.h"

///
/// PokerCardSeq type
///
class PokerCardSeq {
private:
    std::vector<PokerCard> S; ///< The array of pokercards
public:
    ///
    /// \brief PokerCardSeq constructor
    ///
    PokerCardSeq();
    ///
    /// \brief Initialize pokercards in sequence
    /// \param s The input pokercards array
    ///
    void init(std::vector<PokerCard> s);
    ///
    /// \brief Obtain the last pokercard in sequence
    /// \exception GetCardOp_Illegal if operation is illegal
    /// \return A pokercard
    ///
    PokerCard lastCard();
    ///
    /// \brief Obtain a pokercard in sequence
    /// \param i The input index for pokercard in sequence
    /// \exception GetCardOp_Illegal if operation is illegal
    /// \return A pokercard
    ///
    PokerCard card(unsigned int i);
    ///
    /// \brief Add a pokercard to the sequence end
    /// \param c The input pokercard
    ///
    void addCard(PokerCard c);
    ///
    /// \brief Remove the last pokercard from sequence
    /// \exception RemoveCardOp_Illegal if operation is illegal
    ///
    void removeLastCard();
    ///
    /// \brief Obtain number of cards in sequence
    /// \return a number
    ///
    unsigned int size();
};

#endif
