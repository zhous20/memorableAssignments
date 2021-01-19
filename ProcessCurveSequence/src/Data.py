## @file Data.py
#  @author Shengchen Zhou
#  @brief The data module
#  @date 15 Feb 2018


from Exceptions import Full, IndepVarNotAscending, InvalidIndex, OutOfDomain
from SeqServices import isInBounds, interpLin, index
from CurveADT import CurveT


## @brief Data class
#  @details It's assumed that Data.init() is called before any other access program
class Data:
    MAX_SIZE = 10  # the maximum size constant

    ## @brief Initializer of the Data type
    @staticmethod
    def init():
        Data.S = []
        Data.Z = []

    ## @brief Append a curve and a scalar value
    #  @param s The input curve
    #  @param z The input value
    #  @exception Full if the Data reaches its capacity
    #  @exception IndepVarNotAscending if Data.Z cannot be in ascending order
    #   after appended with the input z
    @staticmethod
    def add(s, z):
        if len(Data.S) == Data.MAX_SIZE:
            raise Full()
        if len(Data.Z) > 0:
            if Data.Z[-1] >= z:
                raise IndepVarNotAscending()
        Data.S.append(s)
        Data.Z.append(z)

    ## @brief Pick a curve
    #  @param i The index
    #  @exception InvalidIndex if i isn't a valid index of Data.S
    #  @return The Curve
    @staticmethod
    def getC(i):
        if i < 0:
            raise InvalidIndex()
        if i >= len(Data.S):
            raise InvalidIndex()
        s = Data.S[i]
        return s

    ## @brief Calculate the y at the input x and input z
    #  @param x The input x
    #  @param z The input z
    #  @exception OutOfDomain if input z is not in the domain of Data.Z
    #  @return The y
    @staticmethod
    def eval(x, z):
        if isInBounds(Data.Z, z) is False:
            raise OutOfDomain()
        j = index(Data.Z, z)
        xj = Data.Z[j]
        yj = Data.S[j].eval(x)
        xj1 = Data.Z[j + 1]
        yj1 = Data.S[j + 1].eval(x)
        y = interpLin(xj, yj, xj1, yj1, z)
        return y

    ## @brief Slice data
    #  @param x The input x
    #  @param i The order
    #  @return The curve
    @staticmethod
    def slice(x, i):
        Y = []
        for j in range(len(Data.S)):
            s = Data.S[j]
            y = s.eval(x)
            Y.append(y)
        s = CurveT(Data.Z, Y, i)
        return s
