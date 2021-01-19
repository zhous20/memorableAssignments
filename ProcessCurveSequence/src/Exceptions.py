## @file Exceptions.py
#  @author Shengchen Zhou
#  @brief The exceptions module
#  @date 15 Feb 2018


## @brief Full exception type
class Full(Exception):
    """ Indicate the container is full already,
        thus cannot accept more elements """
    pass


## @brief OutOfDomain exception type
class OutOfDomain(Exception):
    """ Indicate the input value is out of domain """
    pass


## @brief InvalidIndex exception type
class InvalidIndex(Exception):
    """ Indicate the given index is invalid """
    pass


## @brief SeqSizeMismatch exception type
class SeqSizeMismatch(Exception):
    """ Indicate the sequences' sizes are not the same """
    pass


## @brief InvalidInterpOrder exception type
class InvalidInterpOrder(Exception):
    """ Indicate the interpolation order is invalid """
    pass


## @brief IndepVarNotAscending exception type
class IndepVarNotAscending(Exception):
    """ Indicate the independant variable is not ascending """
    pass
