## @file CurveADT.py
#  @author Shengchen Zhou
#  @brief Provides the CurveT ADT class for representing curves.
#  @date 1/21/2018

import numpy as np
from SeqADT import *

## @brief An ADT that represents a curve
class CurveT:

  ## @brief CurveT constructor
  #  @details Initializes a CurveT object using a given input data file which
  #           have 2 columns of data, with each data entry in a row separated
  #           by a comma and a space, and each row separated by newline
  #  @param s The filename of input file contains the data represents a curve
  #  @param self The object pointer
  def __init__(self, s):
    self.__x = SeqT()
    self.__y = []
    with open(s, 'r') as f:
      for line in f.readlines():
        values = line.split(',')
        self.__x.add(self.__x.size(), float(values[0].strip()))
        self.__y.append(float(values[1].strip()))

  ## @brief Gets y value for the given x by using linear interpolation
  #  @param x The x coordinate
  #  @return The y coordinate
  def linVal(self, x):
    i = self.__x.indexInSeq(x)
    x1, y1 = self.__x.get(i), self.__y[i]
    x2, y2 = self.__x.get(i + 1), self.__y[i + 1]
    return y1 + (y2 - y1) * (x - x1) / (x2 - x1)

  ## @brief Gets y value for the given x by using quadratic interpolation
  #  @param x The x coordinate
  #  @return The y coordinate
  def quadVal(self, x):
    if self.__x.size() < 3:
      raise ValueError("Has only %d points" % self.__x.size())
    xp, yp = [], []
    for i in range(3):
      xp.append(self.__x.get(i))
      yp.append(self.__y[i])
    rhs1 = yp[1] + (yp[2] - yp[0]) * (x - xp[1]) / (xp[2] - xp[0])
    rhs2 = (yp[2] - 2 * yp[1] + yp[0]) * (x - xp[1]) ** 2 / (xp[2] - xp[1]) ** 2 / 2
    return rhs1 + rhs2

  ## @brief Gets y value for the given x by using best fit n degree polynomial interpolation
  #  @param n The degree of the polynomial
  #  @param x The x coordinate
  #  @return The y coordinate
  def npolyVal(self, n, x):
    xp, yp = np.array([]), np.array(self.__y)
    for i in range(self.__x.size()):
      xp = np.append(xp, self.__x.get(i))
    p = np.polyfit(xp, yp, n)
    res = 0.0
    for i in range(len(p)):
      res += p[i] * x ** (n - i)
    return res
