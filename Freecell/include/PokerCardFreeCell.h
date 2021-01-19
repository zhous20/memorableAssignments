///
/// \file PokerCardFreeCell.h
/// \author Shengchen Zhou
/// \brief The PokerCardFreeCell module (header)
/// \date 6 Apr 2018
///

#ifndef _POKERCARDFREECELL_H_
#define _POKERCARDFREECELL_H_

#include "PokerCardSeq.h"

class PokerCardPile;
class PokerCardFoundation;

///
/// PokerCardFreeCell type
///
class PokerCardFreeCell {
private:
    PokerCardSeq S; ///< The sequence of pokercards
public:
    ///
    /// \brief PokerCardFreeCell constructor
    ///
    PokerCardFreeCell();
    ///
    /// \brief Determine if the input pokercard can be appended to cell
    /// \param c The input pokercard
    /// \return True for an appendable input pokercard, false if not
    ///
    bool canAppendCard(PokerCard c);
    ///
    /// \brief Append the input pokercard to cell
    /// \param c The input pokercard
    /// \exception AddCardOp_Illegal if operation is illegal
    /// \return True for successful append operation, false if not
    ///
    void appendCard(PokerCard c);
    ///
    /// \brief Obtain the pokercard in cell
    /// \exception GetCardOp_Illegal if operation is illegal
    /// \return A pokercard
    ///
    PokerCard card();
    ///
    /// \brief Remove the pokercard from cell
    /// \exception RemoveCardOp_Illegal if operation is illegal
    ///
    void removeCard();
    ///
    /// \brief Obtain number of cards in cell
    /// \return a number
    ///
    unsigned int size();
    ///
    /// \brief Determine if able to move a pokercard to a freecell
    /// \param c The input freecell to recieve the pokercard
    /// \return True for possible move operation, false if not
    ///
    bool canMoveCard2(PokerCardFreeCell* c);
    ///
    /// \brief Move a pokercard to a freecell
    /// \param c The input freecell to recieve the pokercard
    /// \return True for successful move operation, false if not
    ///
    bool moveCard2(PokerCardFreeCell* c);
    ///
    /// \brief Determine if able to move a pokercard to a pile
    /// \param p The input pile to recieve the pokercard
    /// \return True for possible move operation, false if not
    ///
    bool canMoveCard2(PokerCardPile* p);
    ///
    /// \brief Move a pokercard to a pile
    /// \param p The input pile to recieve the pokercard
    /// \return True for successful move operation, false if not
    ///
    bool moveCard2(PokerCardPile* p);
    ///
    /// \brief Determine if able to move a pokercard to a foundation
    /// \param f The input foundation to recieve the pokercard
    /// \return True for possible move operation, false if not
    ///
    bool canMoveCard2(PokerCardFoundation* f);
    ///
    /// \brief Move a pokercard to a foundation
    /// \param f The input foundation to recieve the pokercard
    /// \return True for successful move operation, false if not
    ///
    bool moveCard2(PokerCardFoundation* f);
};

#endif
