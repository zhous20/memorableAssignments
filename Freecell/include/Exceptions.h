///
/// \file Exceptions.h
/// \author Shengchen Zhou
/// \brief The Exception module
/// \date 6 Apr 2018
///

#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

///
/// Ind_Illegal Type
///
class Ind_Illegal : public std::exception {
    const char* what() const throw() { return "Illegal index"; }
};

///
/// GetCardOp_Illegal Type
///
class GetCardOp_Illegal : public std::exception {
    const char* what() const throw() { return "Illegal get-card operation"; }
};

///
/// RemoveCardOp_Illegal Type
///
class RemoveCardOp_Illegal : public std::exception {
    const char* what() const throw() { return "Illegal remove-card operation"; }
};

///
/// AddCardOp_Illegal Type
///
class AddCardOp_Illegal : public std::exception {
    const char* what() const throw() { return "Illegal add-card operation"; }
};

#endif
