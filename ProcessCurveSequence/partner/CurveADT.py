## @file CurveADT.py
#  @author Guiye Wu
#  @brief Provides the CurveT ADT class for representing a curve
#  @date 20 Feb 2018

from SeqServices import *
from Exceptions import *

## @brief An ADT that represents a curve, the clas only provides the information
##  of the curve, not modifying.
class CurveT:
    global MAX_ORDER
    # maximum order is 2
    MAX_ORDER = 2
    
    global DX
    # let dx be 1e-3
    DX = 1*10**(-3)

    ## @brief CurveT constructor
    #  @details Initilizes a curve using a sequence of x values, a sequence of 
    #           y values and its order (1 or 2). The minimum value of x, the
    #           maximum value of x, the order of the curve and the function f(x)
    #           are initilized into minx, maxx, o and f respectively, the f(x)
    #           use interp function to find out the y value that corresponding to
    #           x.
    #  @param X The sequence of x values
    #  @param Y The sequence of y values
    #  @param i The order of the curve
    #  @exception IndepVarNotAscending Raise an error when the input sequence
    #             of x value is not ascending
    #  @exception SeqSizeMismatch Raise an error when the size of X and Y are not
    #             the same.
    #  @exception InvalidInterpOrder Raise an error when i is not 1 or 2
    def __init__(self,X,Y,i):
        if (not isAscending(X)):
            raise IndepVarNotAscending("Independent Variables are not ascending")
        if (len(X) != len(Y)):
            raise SeqSizeMismatch("X and Y are not the same size")
        if (i < 1 or i > MAX_ORDER):
            raise InvalidInterpOrder("Order is out of range")
        self.minx = X[0]
        self.maxx = X[len(X)-1]
        self.o = i
        self.f = lambda v : interp(X,Y,self.o,v)

    ## @brief Gets the minimum value of x in the x sequence
    #  @return The minimum x value
    def minD(self):
        return self.minx

    ## @brief Gets the maximum value of x in the x sequence
    #  @return The maximum x value
    def maxD(self):
        return self.maxx

    ## @brief Gets the order of the curve
    #  @return The the order of the curve
    def order(self):
        return self.o

    ## @brief Calculates and return the corresponding y value by the input x value
    #  @details The output value is calculated by f(x) which is initialized in
    #           CurveT.
    #  @param x The input x value
    #  @return The y value that corresponding to the input x
    def eval(self,x):
        if not (self.minx <= x and x <= self.maxx):
            raise OutOfDomain("The input value is not in the range")
        return self.f(x)

    ## @brief Calculateds the differential value by input x with DX
    #  @details Uses the formula (f(x+DX)-f(x))/DX with DX = 1e-3
    #  @param x The input value x
    #  @return The output dfdx which is the differential of x
    #  @exception OutOfDomain Raise an error when input x is out of the range of
    #             sequence x.
    def dfdx(self,x):
        if not (self.minx <= x and x <= self.maxx):
            raise OutOfDomain("The input value is not in the range")
        return (self.f(x+DX)-self.f(x))/DX

    ## @brief Calculateds the second differential value by input x with DX
    #  @details Uses the formula (f(x+2DX)-2f(x+DX)+f(x))/(DX*DX) with DX = 1e-3
    #  @param x The input value x
    #  @return The output d2fdx2 which is the second differential of x
    #  @exception OutOfDomain Raise an error when input x is out of the range of
    #             sequence x.
    def d2fdx2(self,x):
        if not (self.minx <= x and x <= self.maxx):
            raise OutOfDomain("The input value is not in the range")
        return (self.f(x+2*DX)-2*self.f(x+DX)+self.f(x))/(DX*DX)

## @brief The function interp which uses linear interpolation mehtod or quadratic
#         interpolation method.
#  @details If the curve order is 1, uses the linear interpolation to find the
#           approximation y value with x values sequence, y values sequence and
#           the input v, if the curve order is 2, uses the quadratic interpolation.
#  @param X The sequence of x values
#  @param Y The sequence of y values
#  @param o The order of the curve
#  @param v The input value v
#  @return The result by using linear or quadratic interpolation
def interp(X,Y,o,v):
    i = index(X,v)
    if o == 1:
        return interpLin(X[i],Y[i],X[i+1],Y[i+1],v)
    elif o == 2:
        return interpQuad(X[i-1],Y[i-1],X[i],Y[i],X[i+1],Y[i+1],v)

