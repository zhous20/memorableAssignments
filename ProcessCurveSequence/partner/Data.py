## @file Data.py
#  @author Guiye Wu
#  @brief Provides a data class to store or get the curve
#  @date 20 Feb 2018

from CurveADT import *
from SeqServices import *
from Exceptions import *

## @brief A class Data which is used to store or get the information of curves
#  @details Uses a sequence S to store the curveT, and Z to store the values z
class Data:

    # maximum size is 10
    MAX_SIZE = 10

    # empty sequences
    S = []
    Z = []

    ## @brief Initializes the sequence S and Z to be empty
    def init():
        Data.S = []
        Data.Z = []

    ## @brief Adds a curveT to S sequence and a z value to Z sequence
    #  @param s The curveT
    #  @param z The z value
    #  @exception FULL Raises error when the size of S sequence is full
    #  @exception IndepVarNotAscending Raise error when the input z is less than 
    #             the previous value
    def add(s,z):
        if len(Data.S) == Data.MAX_SIZE:
            raise FULL("Sequence of CurveT is full")
        if len(Data.Z) > 0:
            if z <= Data.Z[len(Data.Z)-1]:
                raise IndepVarNotAscending("Input value is too small")
        Data.S.append(s)
        Data.Z.append(z)

    ## @brief Gets the curveT in the index i of S sequence
    #  @param i The input index
    #  @return The curveT which in the index i of S sequence
    #  @exception InvalidIndex Raise error when the index is out of the range
    def getC(i):
        if not (0 <= i and i <= len(Data.S)-1):
            raise InvalidIndex("Index is not in the range")
        return Data.S[i]

    ## @brief Evaluate the value x with the index of z in Z and S sequence
    #  @details Uses linear interpolation to find the result, z is used to find
    #           the index of a curveT and a z values to do the calculation
    #  @param x The input value x
    #  @param z The input z value that in order to find the index in Z
    #  @return The result by using linear interpolation
    #  @exception OutOfDomain Raise error when input z is not in the range of
    #             Z sequence
    def eval(x,z):
        if not isInBounds(Data.Z,z):
            raise OutOfDomain("Input is out of domain")
        j = index(Data.Z,z)
        return interpLin(Data.Z[j],Data.S[j].eval(x),Data.Z[j+1],Data.S[j+1].eval(x),z)

    ## @brief Create a curveT
    #  @details The curveT is created with Z sequence to be x values and evaluation
    #           of input x of each curveT in S sequence to be y values and i to be
    #           the order
    #  @param x The input x value
    #  @param i The order of the curve
    #  @return A curveT
    def slice(x,i):
        Y = [Data.S[j].eval(x) for j in range(len(Data.Z))]
        return CurveT(Data.Z,Y,i)

    
