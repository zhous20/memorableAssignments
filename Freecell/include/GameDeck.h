///
/// \file GameDeck.h
/// \author Shengchen Zhou
/// \brief The GameDeck module (header)
/// \date 6 Apr 2018
///

#ifndef _GAMEDECK_H_
#define _GAMEDECK_H_

#include "PokerCardFreeCell.h"
#include "PokerCardPile.h"
#include "PokerCardFoundation.h"

///
/// GameDeck type
///
class GameDeck {
private:
    PokerCardFreeCell C[4];   ///< The freecells
    PokerCardPile P[8];       ///< The piles
    PokerCardFoundation F[4]; ///< The foundations
public:
    ///
    /// \brief GameDeck constructor
    ///
    GameDeck();
    ///
    /// \brief GameDeck constructor
    /// \details Construct the game deck by all inputs.
    ///          All inputs should be proper and conform to game rules.
    ///          Don't call init() after this.
    /// \param c The input freecells
    /// \param p The input piles
    /// \param f The input foundations
    ///
    GameDeck(PokerCardFreeCell c[], PokerCardPile p[], PokerCardFoundation f[]);
    ///
    /// \brief Initialize pokercards
    /// \details This routine should be called only once
    ///
    void init();
    static const unsigned int NC = 4; ///< The number of cells
    static const unsigned int NP = 8; ///< The number of piles
    static const unsigned int NF = 4; ///< The number of foundations
    ///
    /// \brief Obtain a cell copy
    /// \param i The input index of cell
    /// \exception Ind_Illegal if the input index is illegal
    /// \return A cell
    ///
    PokerCardFreeCell cell(unsigned int i);
    ///
    /// \brief Obtain a pile copy
    /// \param i The input index of pile
    /// \exception Ind_Illegal if the input index is illegal
    /// \return A pile
    ///
    PokerCardPile pile(unsigned int i);
    ///
    /// \brief Obtain a foundation copy
    /// \param i The input index of foundation
    /// \exception Ind_Illegal if the input index is illegal
    /// \return A foundation
    ///
    PokerCardFoundation foundation(unsigned int i);
    ///
    /// \brief Determine if a card can be moved from freecell to freecell
    /// \param i1 The input sender freecell
    /// \param i2 The input reciever freecell
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for possible move operation, false if not
    ///
    bool canFreeCell2FreeCell(unsigned int i1, unsigned int i2);
    ///
    /// \brief Move a card from freecell to freecell
    /// \param i1 The input sender freecell
    /// \param i2 The input reciever freecell
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for successful move operation, false if not
    ///
    bool freeCell2FreeCell(unsigned int i1, unsigned int i2);
    ///
    /// \brief Determine if a card can be moved from pile to pile
    /// \param i1 The input sender pile
    /// \param i2 The input reciever pile
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for possible move operation, false if not
    ///
    bool canPile2Pile(unsigned int i1, unsigned int i2);
    ///
    /// \brief Move a card from pile to pile
    /// \param i1 The input sender pile
    /// \param i2 The input reciever pile
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for successful move operation, false if not
    ///
    bool pile2Pile(unsigned int i1, unsigned int i2);
    ///
    /// \brief Determine if a card can be moved from foundation to foundation
    /// \param i1 The input sender foundation
    /// \param i2 The input reciever foundation
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for possible move operation, false if not
    ///
    bool canFoundation2Foundation(unsigned int i1, unsigned int i2);
    ///
    /// \brief Move a card from foundation to foundation
    /// \param i1 The input sender foundation
    /// \param i2 The input reciever foundation
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for successful move operation, false if not
    ///
    bool foundation2Foundation(unsigned int i1, unsigned int i2);
    ///
    /// \brief Determine if a card can be moved from freecell to foundation
    /// \param i1 The input sender freecell
    /// \param i2 The input reciever foundation
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for possible move operation, false if not
    ///
    bool canFreeCell2Pile(unsigned int i1, unsigned int i2);
    ///
    /// \brief Move a card from freecell to foundation
    /// \param i1 The input sender freecell
    /// \param i2 The input reciever foundation
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for successful move operation, false if not
    ///
    bool freeCell2Pile(unsigned int i1, unsigned int i2);
    ///
    /// \brief Determine if a card can be moved from pile to freecell
    /// \param i1 The input sender pile
    /// \param i2 The input reciever freecell
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for possible move operation, false if not
    ///
    bool canPile2FreeCell(unsigned int i1, unsigned int i2);
    ///
    /// \brief Move a card from pile to freecell
    /// \param i1 The input sender pile
    /// \param i2 The input reciever freecell
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for successful move operation, false if not
    ///
    bool pile2FreeCell(unsigned int i1, unsigned int i2);
    ///
    /// \brief Determine if a card can be moved from pile to freecell
    /// \param i1 The input sender pile
    /// \param i2 The input reciever freecell
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for possible move operation, false if not
    ///
    bool canFreeCell2Foundation(unsigned int i1, unsigned int i2);
    ///
    /// \brief Move a card from pile to freecell
    /// \param i1 The input sender pile
    /// \param i2 The input reciever freecell
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for successful move operation, false if not
    ///
    bool freeCell2Foundation(unsigned int i1, unsigned int i2);
    ///
    /// \brief Determine if a card can be moved from pile to foundation
    /// \param i1 The input sender pile
    /// \param i2 The input reciever foundation
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for possible move operation, false if not
    ///
    bool canPile2Foundation(unsigned int i1, unsigned int i2);
    ///
    /// \brief Move a card from pile to foundation
    /// \param i1 The input sender pile
    /// \param i2 The input reciever foundation
    /// \exception Ind_Illegal if at least one of input indices are illegal
    /// \return True for successful move operation, false if not
    ///
    bool pile2Foundation(unsigned int i1, unsigned int i2);
    ///
    /// \brief Determine if there is a valid move
    /// \return True for there is a valid move, false if not
    ///
    bool validMoves();
    ///
    /// \brief Determine if the player has won
    /// \return True for the player has won, false if not
    ///
    bool Winning();
};

#endif
