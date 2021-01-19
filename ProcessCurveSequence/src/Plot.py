## @file Load.py
#  @author Shengchen Zhou
#  @brief The plot module
#  @details For plotting the user select the numbers of
#   subdivisions to be small enough that there will no be
#   an interpolation problem with then end points
#  @date 15 Feb 2018


from Exceptions import SeqSizeMismatch
import matplotlib.pyplot as plt
import numpy as np


## @brief Plot sequence
#  @param X The input sequence
#  @param Y The input sequence
def PlotSeq(X, Y):
    if len(X) != len(Y):
        raise SeqSizeMismatch()
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(X, Y, linestyle='None', marker='o')
    plt.show()


## @brief Plot curve
#  @param c The input curve
#  @param n The input points' amount
def PlotCurve(c, n):
    X = list(np.linspace(c.minD(), c.maxD(), n))
    del X[-1]
    if c.order() == 2:
        del X[0]
    Y = []
    for i in range(len(X)):
        y = c.eval(X[i])
        Y.append(y)
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(X, Y, linestyle='solid', marker='None')
    plt.show()
