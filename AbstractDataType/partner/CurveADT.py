from SeqADT import *
from numpy import *

## @file CurveADT.py
#  @title CurveADT
#  @author Alexie McDonald
#  @date 2018-01-12

## @brief An Abstract Data Type that represents a curve in a cartesian x-y plane
#  @details A Curve ADT that contains methods involving the x and y values of the graph including linear, quadratic, and n-poly fit methods
class CurveT:
    ## @brief Curve Constructor
    #  @details Reads a set of values from an input file s and initialized the x and y array elements to their respective values
    #  @param s The string containing the name of the text file where the x and y values are stored
    #  @return A CurveT object that has an x and y array initialized to the values found in the file
    def __init__(self, s):
        self.__x = SeqT()
        self.__y = SeqT()
        f = open(s, "r")
        counter = 0;
        for i in f:
            arr = i.split(",");
            if ((arr[1])[-1] == "\n"):
                arr[1] = (arr[1])[:-1]
            self.__x.add(counter, float(arr[0]))
            self.__y.add(counter, float(arr[1]))
            counter+= 1
    ## @brief Estimate the value of y using linear interpolation
    #  @details Finds the values "surrounding" x (x1,y1,x2,y2) and uses them to calculate an estimated value for y at that x. Granted, that there are enough values preceeding and following x to get the values.
    #  @param x The x coordinate that the values are centered around (x1 and y1 are 1 behind x and x2 and y2 are 1 ahead of x)
    #  @return A y value estimated using linear interpolation for the corresponding x
    def linVal(self, x):
        xind = self.__x.indexInSeq(x)
        if (xind < 1 or self.__x.size() < 2 or self.__x.size() == (xind+1)):
            return "Invalid"
        else:
            x1 = self.__x.get(xind-1)
            y1 = self.__y.get(xind-1)
            x2 = self.__x.get(xind+1)
            y2 = self.__y.get(xind+1)
            y = (((y2-y1)/(x2-x1))*(x-x1)) + y1
        return y
    ## @brief Estimate the value of y using quadratic interpolation
    #  @details Finds the values "surrounding" x (x0,y0,x1,y1,x2,y2) and uses them to calculate an estimated value for y at that x. Granted, that there are enough values preceeding and following x to get the values.
    #  @param x The x coordinate that the values are centered around (x0 and y0 are 2 behind x, x1 and y1 are 1 behind x and x2 and y2 are 1 ahead of x)
    #  @return A y value estimated using quadratic interpolation for the corresponding x
    def quadVal(self,x):
        xind = self.__x.indexInSeq(x)
        if (xind < 2 or self.__x.size() < 3 or self.__x.size() == (xind+1)):
            return "Invalid"
        else:
            x0 = self.__x.get(xind-2)
            x1 = self.__x.get(xind-1)
            y1 = self.__y.get(xind-1)
            x2 = self.__x.get(xind+1)
            y2 = self.__y.get(xind+1)
            y0 = self.__y.get(xind-2)
            y = (((y2-y0)/(x2-x0))*(x-x1)) + y1 + ((y2 - 2*y1 + y0)/(2*((x2-x1)**2)))*((x-x1)**2)
            return y;
    ## @brief Estimate the value of y using regression to find the polynomial that minimizes error
    #  @details Takes the x and y arrays as input, then uses the numpy library function polyfit to generate a new array of coordinates that correspond to the best fit curve
    #  @param n The desired degree of the best fit polynomial
    #  @param x The x coordinate that the values are centered around
    #  @return A y value estimated using n-polynomial regression for the corresponding x
    def npolyVal(self, n, x):
        index = self.__x.indexInSeq(x);
        if (index == -1):
            return "Invalid"
        else:
            newx = array(self.__x._SeqT__state)
            newy = array(self.__y._SeqT__state)
            newarr = polyfit(newx, newy, n)
            y = 0;
            currenind = n;
            for i in newarr:
                y += i*(x**(currenind));
                currenind -= 1;
            return y;
