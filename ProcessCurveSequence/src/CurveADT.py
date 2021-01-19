## @file CurveADT.py
#  @author Shengchen Zhou
#  @brief The curve ADT module
#  @date 15 Feb 2018


from Exceptions import IndepVarNotAscending, SeqSizeMismatch, InvalidInterpOrder, OutOfDomain
from SeqServices import isAscending, isInBounds, interpLin, interpQuad, index
from copy import copy


## @brief CurveT ADT class
#  @details It's assumed that the user will not request function
#   evaluations that would cause the interpolation to select index
#   values outside of where the function is defined
class CurveT:
    MAX_ORDER = 2  # the maximum order constant
    DX = 1e-3  # the delta x constant

    ## @brief Constructor of the CurveT type
    #  @details Construct a CurveT instance
    #  @param X The input x sequence
    #  @param Y The input y sequence
    #  @param i The input order
    #  @exception IndepVarNotAscending if X is not in ascending order
    #  @exception SeqSizeMismatch if X and Y don't have the same size
    #  @exception InvalidInterpOrder if i is an invalid interpolation order
    def __init__(self, X, Y, i):
        if isAscending(X) is False:
            raise IndepVarNotAscending()
        elif len(X) != len(Y):
            raise SeqSizeMismatch()
        elif i <= 0:
            raise InvalidInterpOrder()
        elif i > CurveT.MAX_ORDER:
            raise InvalidInterpOrder()

        self.minx = X[0]
        self.maxx = X[-1]
        self.o = i

        X = copy(X)
        Y = copy(Y)

        def f(x):
            y = interp(X, Y, i, x)
            return y
        self.f = f

    ## @brief Obtain the smallest x
    #  @return The smallest x
    def minD(self):
        return self.minx

    ## @brief Obtain the greatest x
    #  @return The greatest x
    def maxD(self):
        return self.maxx

    ## @brief Obtain the order
    #  @return The order
    def order(self):
        return self.o

    ## @brief Calculate the y at the input x
    #  @param x The input x
    #  @exception OutOfDomain if x is not in the domain of X
    #  @return The y
    def eval(self, x):
        if x < self.minx:
            raise OutOfDomain()
        if x > self.maxx:
            raise OutOfDomain()
        y = self.f(x)
        return y

    ## @brief Calculate the first derivative at the input x
    #  @param x The input x
    #  @exception OutOfDomain if x is not in the domain of X
    #  @return The 1st derivative at the input x
    def dfdx(self, x):
        if x < self.minx:
            raise OutOfDomain()
        if x > self.maxx:
            raise OutOfDomain()
        numerator = self.f(x + CurveT.DX) - self.f(x)
        denominator = CurveT.DX
        rc = numerator / denominator
        return rc

    ## @brief Calculate the second derivative at the input x
    #  @param x The input x
    #  @exception OutOfDomain if x is not in the domain of X
    #  @return The 2nd derivative at the input x
    def d2fdx2(self, x):
        if x < self.minx:
            raise OutOfDomain()
        if x > self.maxx:
            raise OutOfDomain()
        numerator = (self.f(x + CurveT.DX * 2) - self.f(x + CurveT.DX) +
                     self.f(x) - self.f(x + CurveT.DX))
        denominator = CurveT.DX ** 2
        rc = numerator / denominator
        return rc


## @brief Conduct a linear interpolation
#  @param X The input x sequence
#  @param Y The input y sequence
#  @param o The input order
#  @param v The input v
#  @return The y as the interpolated result with regards to the input v
def interp(X, Y, o, v):
    i = index(X, v)

    xi = X[i]
    yi = Y[i]
    xi1 = X[i + 1]
    yi1 = Y[i + 1]

    if o == 1:
        y = interpLin(xi, yi, xi1, yi1, v)
    elif i > 0:
        xi_1 = X[i - 1]
        yi_1 = Y[i - 1]
        y = interpQuad(xi_1, yi_1, xi, yi, xi1, yi1, v)
    else:
        xi2 = X[i + 2]
        yi2 = Y[i + 2]
        y = interpQuad(xi, yi, xi1, yi1, xi2, yi2, v)

    return y
