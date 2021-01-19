## @file SeqServices.py
#  @author Shengchen Zhou
#  @brief The sequence services module
#  @date 15 Feb 2018


from scipy import interpolate


## @brief Verify whether or not a input sequence is in ascending order
#  @param X The input sequence
#  @return True if the input sequence is in ascending order;
#   False if it isn't
def isAscending(X):
    rc = True  # the return code, defaults to True
    for i in range(len(X) - 1):
        xi, xi1 = X[i: i + 2]
        if xi1 < xi:  # non-ascending pair found
            rc = False
    return rc


## @brief Verify whether or not a input x is within the bounds of a input sequence
#  @details The input sequence is assumed to be in ascending order
#  @param X The input sequence
#  @param x The input x
#  @return True if the input x is within the bounds of the input sequence;
#   False if it isn't
def isInBounds(X, x):
    rc = True
    if x < X[0]:
        rc = False
    if x > X[-1]:
        rc = False
    return rc


## @brief Conduct a linear interpolation
#  @details Conduct a linear interpolation using two points.
#   The input two points are assumed to form a sequence
#   which should be in ascending order
#  @param x1 The x component of the input point #1
#  @param y1 The y component of the input point #1
#  @param x2 The x component of the input point #2
#  @param y2 The y component of the input point #2
#  @param x The x component of the to-be-determined point
#  @return The y component as the interpolated result with regards to the input x component
def interpLin(x1, y1, x2, y2, x):
    X = [x1, x2]
    Y = [y1, y2]
    f = interpolate.interp1d(X, Y, kind='linear')
    y = f(x)
    return y


## @brief Conduct a quadratic interpolation
#  @details Conduct a quadratic interpolation using three points.
#   The input three points are assumed to form a sequence
#   which should be in ascending order
#  @param x0 The x component of the input point #0
#  @param y0 The y component of the input point #0
#  @param x1 The x component of the input point #1
#  @param y1 The y component of the input point #1
#  @param x2 The x component of the input point #2
#  @param y2 The y component of the input point #2
#  @param x The x component of the to-be-determined point
#  @return The y component as the interpolated result with regards to the input x component
def interpQuad(x0, y0, x1, y1, x2, y2, x):
    X = [x0, x1, x2]
    Y = [y0, y1, y2]
    f = interpolate.interp1d(X, Y, kind='quadratic')
    y = f(x)
    return y


## @brief Get the index of a input x in a input sequence
#  @details An estimation approach is used if the input x is
#   not exactly one of the element inside the input sequence.
#   The input sequence is assumed to be in ascending order, and
#   the input x is assumed to be in bounds of the input sequence
#  @param X The input sequence
#  @param x The input x
#  @return The index of the input x
def index(X, x):
    rc = None
    for i in range(len(X) - 1):
        xi, xi1 = X[i: i + 2]
        if xi > x:
            continue
        if x >= xi1:
            continue
        rc = i
        break
    return rc
