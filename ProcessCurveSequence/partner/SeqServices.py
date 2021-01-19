## @file SeqServices.py
#  @author Guiye Wu
#  @brief Provides the some functions to support CurveADT
#  @date 20 Feb 2018

## @brief Checks if the sequence is ascending
#  @details By comparing each value to the next value in the sequence to check
#           if it is ascending
#  @param X The input sequence
#  @return Return false if the sequence is not ascending, otherwise return true
def isAscending(X):
    for i in range(len(X)-1):
        if (X[i+1] < X[i]):
            return False
    return True

## @brief Checks if a value in the range of a sequence
#  @param X The input sequence
#  @param x The input value
#  @return Return true if the value is in the range, false otherwise.
def isInBounds(X,x):
    return ((X[0] <= x) and (x <= X[len(X)-1]))

## @brief Linear interpolation
#  @details Uses formula (y2-y1)/(x2-x1)*(x-x1)+y1 to find the approximation of
#           y value that is corresponding to the input x value
#  @param x1 The input value x1
#  @param y1 The input value y1
#  @param x2 The input value x2
#  @param y2 The input value y2
#  @param x The input value x
#  @return The result y value
def interpLin(x1,y1,x2,y2,x):
    return (y2-y1)/(x2-x1)*(x-x1)+y1

## @brief Quadratic interpolation
#  @details Uses formula y1+(y2-y0)/(x2-x0)(x-x1)+(y2-2y1+y0)/(2(x2-x1)^2)(x-x1)^2
#           to find the approximation of y value that is corresponding to the
#           input x value
#  @param x0 The input value x0
#  @param y0 The input value y0
#  @param x1 The input value x1
#  @param y1 The input value y1
#  @param x2 The input value x2
#  @param y2 The input value y2
#  @param x The input value x
#  @return The result y value
def interpQuad(x0,y0,x1,y1,x2,y2,x):
    return y1+(y2-y0)/(x2-x0)*(x-x1)+(y2-2*y1+y0)/(2*(x2-x1)**2)*(x-x1)**2

## @brief Finds the index of x in sequence X
#  @param X The input sequence X
#  @param x The input value x
#  @return The index of x in X
def index(X,x):
    for i in range(len(X)-1):
        if ((X[i] <= x) and (x <= X[i+1])):
            return i


