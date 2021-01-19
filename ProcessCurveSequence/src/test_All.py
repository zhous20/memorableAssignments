## @file test_All.py
#  @author Shengchen Zhou
#  @brief The test module
#  @date 15 Feb 2018


from Exceptions import IndepVarNotAscending, SeqSizeMismatch, InvalidInterpOrder, OutOfDomain, InvalidIndex, Full
from SeqServices import isAscending, isInBounds, interpLin, interpQuad, index
from CurveADT import CurveT
from Data import Data
import pytest
import random
from scipy import interpolate
import numpy as np


def isCloseEnough(a, b, delta=1e-5):
    return abs(a - b) < 1e-5


def isSame(s1, s2):
    if s1.order() != s2.order():
        return False
    if isCloseEnough(s1.minD(), s2.minD()) is False:
        return False
    if isCloseEnough(s1.maxD(), s1.maxD()) is False:
        return False
    for x in np.linspace(s1.minD() + 1e-5, s1.maxD() - 1e-5, 6):
        if isCloseEnough(s1.eval(x), s2.eval(x)) is False:
            return False
    return True


@pytest.mark.parametrize('X', [
    [1.1, 2.1],
    [1.1, 1.1],
    [1.1, 2.1, 3.1],
    [1.1, 1.1, 2.1],
    [1.1, 2.1, 2.1],
    [1.1, 1.1, 1.1],
    [1.1, 2.1, 3.1, 4.1],
    [1.1, 1.1, 1.1, 1.1],
])
def test_SeqServices_isAscending(X):
    ''' pytest test case
    '''
    assert isAscending(X) is True
    X_bak = list(X)
    if len(set(X)) > 1:
        while True:
            random.shuffle(X)
            if X != X_bak:
                break
        assert isAscending(X) is False


@pytest.mark.parametrize('X', [
    [1.1, 2.1],
    [1.1, 1.1],
    [1.1, 2.1, 3.1],
    [1.1, 1.1, 1.1],
    [1.1, 2.1, 3.1, 4.1],
    [1.1, 1.1, 1.1, 1.1],
])
def test_SeqServices_isInBounds(X):
    ''' pytest test case
    '''
    x = random.uniform(X[0], X[-1])
    assert isInBounds(X, x) is True
    assert isInBounds(X, X[0]) is True
    assert isInBounds(X, X[-1]) is True
    x = random.uniform(X[0] - 10, X[0] - 1e-5)
    assert isInBounds(X, x) is False
    x = random.uniform(X[-1] + 1e-5, X[-1] + 10)
    assert isInBounds(X, x) is False


@pytest.mark.parametrize('x1,y1,x2,y2', [
    [1.1, 2.1, 3.1, 4.1],
    [1.1, 2.1, 2.1, 2.1],
])
def test_SeqServices_interpLin(x1, y1, x2, y2):
    ''' pytest test case
    '''
    x = x1
    assert isCloseEnough(interpLin(x1, y1, x2, y2, x), y1)
    f = interpolate.interp1d([x1, x2], [y1, y2], kind='linear')
    x = (x1 + x2) / 2
    assert isCloseEnough(interpLin(x1, y1, x2, y2, x), f(x))


@pytest.mark.parametrize('x0,y0,x1,y1,x2,y2', [
    [1.1, 2.34, 2.2, 3.19, 3.3, 2.83],
    [1.09, 2.7, 2.08, 1.31, 3.07, 2.32],
])
def test_SeqService_interpQuad(x0, y0, x1, y1, x2, y2):
    ''' pytest test case
    '''
    x = x1
    assert isCloseEnough(interpQuad(x0, y0, x1, y1, x2, y2, x), y1)
    f = interpolate.interp1d([x0, x1, x2], [y0, y1, y2], kind='quadratic')
    x = (x0 + x1) / 2
    assert isCloseEnough(interpQuad(x0, y0, x1, y1, x2, y2, x), f(x))
    x = (x1 + x2) / 2
    assert isCloseEnough(interpQuad(x0, y0, x1, y1, x2, y2, x), f(x))


@pytest.mark.parametrize('X', [
    [1.1, 2.4],
    [1.01, 1.32],
    [1.9, 2.5, 3.87],
    [1.13, 1.43, 2.09],
    [1.72, 2.07, 2.51],
])
def test_SeqService_index(X):
    ''' pytest test case
    '''
    for i in range(len(X) - 1):
        if X[i + 1] != X[i]:
            assert index(X, X[i]) == i
            assert index(X, (X[i] + X[i + 1]) / 2) == i
            assert index(X, X[i + 1] - (X[i + 1] - X[i]) / 1e5) == i


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 0),
    ([1.1, 2.1], [3.1, 4.1], 3),
    ([2.1, 1.1], [3.1, 4.1], 1),
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 3.1], 2),
    ([1.1, 2.1], [3.1, 3.1, 3.1], 2),
])
def test_CurveT_init(X, Y, i):
    ''' pytest test case
    '''
    if isAscending(X) is False:
        with pytest.raises(IndepVarNotAscending):
            CurveT(X, Y, i)
    elif len(X) != len(Y):
        with pytest.raises(SeqSizeMismatch):
            CurveT(X, Y, i)
    elif i <= 0:
        with pytest.raises(InvalidInterpOrder):
            CurveT(X, Y, i)
    elif i > CurveT.MAX_ORDER:
        with pytest.raises(InvalidInterpOrder):
            CurveT(X, Y, i)
    else:
        CurveT(X, Y, i)


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 5.1], 2),
])
def test_CurveT_minD(X, Y, i):
    ''' pytest test case
    '''
    assert CurveT(X, Y, i).minD() == X[0]


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 5.1], 2),
])
def test_CurveT_maxD(X, Y, i):
    ''' pytest test case
    '''
    assert CurveT(X, Y, i).maxD() == X[-1]


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 5.1], 2),
])
def test_CurveT_order(X, Y, i):
    ''' pytest test case
    '''
    assert CurveT(X, Y, i).order() == i


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 3.1], 2),
])
def test_CurveT_eval(X, Y, i):
    ''' pytest test case
    '''
    s = CurveT(X, Y, i)

    with pytest.raises(OutOfDomain):
        s.eval(X[0] - 1e-5)
    with pytest.raises(OutOfDomain):
        s.eval(X[-1] + 1e-5)

    o = i

    for i in range(len(X) - 1):
        xi = X[i]
        yi = Y[i]
        if o == 1 or i > 0:
            assert isCloseEnough(s.eval(xi), yi)
        xi1 = X[i + 1]
        if o == 1:
            f = interpolate.interp1d(X[i: i + 2], Y[i: i + 2], kind='linear')
            assert isCloseEnough(s.eval((xi + xi1) / 2), f((xi + xi1) / 2))
        else:
            if i == 0:
                f = interpolate.interp1d(
                    X[i: i + 3], Y[i: i + 3], kind='quadratic')
            else:
                f = interpolate.interp1d(
                    X[i - 1: i + 2], Y[i - 1: i + 2], kind='quadratic')
            assert isCloseEnough(s.eval((xi + xi1) / 2), f((xi + xi1) / 2))


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 3.1], 2),
])
def test_CurveT_dfdx(X, Y, i):
    ''' pytest test case
    '''
    s = CurveT(X, Y, i)

    with pytest.raises(OutOfDomain):
        s.dfdx(X[0] - 1e-5)
    with pytest.raises(OutOfDomain):
        s.dfdx(X[-1] + 1e-5)

    for j in range(len(X) - 1):
        xj = X[j]
        deri = (s.eval(xj + CurveT.DX) - s.eval(xj)) / CurveT.DX
        assert isCloseEnough(s.dfdx(xj), deri)


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 3.1], 2),
])
def test_CurveT_d2fdx2(X, Y, i):
    ''' pytest test case
    '''
    s = CurveT(X, Y, i)

    with pytest.raises(OutOfDomain):
        s.d2fdx2(X[0] - 1e-5)
    with pytest.raises(OutOfDomain):
        s.d2fdx2(X[-1] + 1e-5)

    for j in range(len(X) - 1):
        xj = X[j]
        deri = (s.eval(xj + CurveT.DX * 2) - 2 *
                s.eval(xj + CurveT.DX) + s.eval(xj)) / (CurveT.DX ** 2)
        assert isCloseEnough(s.d2fdx2(xj), deri)


def test_Data_init():
    ''' pytest test case
    '''
    Data.init()
    with pytest.raises(InvalidIndex):
        Data.getC(0)


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 3.1], 2),
])
def test_Data_add(X, Y, i):
    ''' pytest test case
    '''
    Data.init()
    s = CurveT(X, Y, i)
    Data.add(s, 0)
    Data.init()
    z = 0
    for j in range(Data.MAX_SIZE):
        s = CurveT(X, Y, i)
        Data.add(s, z)
        z += 0.5
    with pytest.raises(Full):
        Data.add(s, z)
    Data.init()
    Data.add(s, z)
    with pytest.raises(IndepVarNotAscending):
        Data.add(s, z)
    z -= 1e-5
    with pytest.raises(IndepVarNotAscending):
        Data.add(s, z)


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 3.1], 2),
])
def test_Data_getC(X, Y, i):
    ''' pytest test case
    '''
    Data.init()
    z = 0
    for j in range(Data.MAX_SIZE):
        s = CurveT(X, Y, i)
        Data.add(s, z)
        for k in range(len(X)):
            X[k] += 2
        z += 1.1
    for j in reversed(range(Data.MAX_SIZE)):
        for k in range(len(X)):
            X[k] -= 2
        s1 = Data.getC(j)
        s2 = CurveT(X, Y, i)
        assert isSame(s1, s2)
    for j in range(-10, 0):
        with pytest.raises(InvalidIndex):
            Data.getC(j)
    for j in range(Data.MAX_SIZE, Data.MAX_SIZE + 10):
        with pytest.raises(InvalidIndex):
            Data.getC(j)


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 3.1], 2),
])
def test_Data_eval(X, Y, i):
    ''' pytest test case
    '''
    Data.init()
    Data_Z = []
    Data_S = []
    z = X[0]
    for z in np.linspace(X[0], X[-1], Data.MAX_SIZE):
        Data_Z.append(z)
        s = CurveT(X, Y, i)
        Data_S.append(s)
        Data.add(s, z)
        for k in range(len(X)):
            Y[k] += 1

    for i in range(Data.MAX_SIZE - 1):
        xi = Data_Z[i]
        xi1 = Data_Z[i + 1]
        for z in (xi, (xi + xi1) / 2):
            yi = Data_S[i].eval(xi)
            yi1 = Data_S[i + 1].eval(xi)
            y1 = Data.eval(xi, z)
            y2 = interpLin(xi, yi, xi1, yi1, z)
            assert isCloseEnough(y1, y2)
            yi = Data_S[i].eval((xi + xi1) / 2)
            yi1 = Data_S[i + 1].eval((xi + xi1) / 2)
            y1 = Data.eval((xi + xi1) / 2, z)
            y2 = interpLin(xi, yi, xi1, yi1, z)
            assert isCloseEnough(y1, y2)

    with pytest.raises(OutOfDomain):
        Data.eval(xi, Data_Z[0] - 1e-5)
    with pytest.raises(OutOfDomain):
        Data.eval(xi, Data_Z[-1] + 1e-5)


@pytest.mark.parametrize('X,Y,i', [
    ([1.1, 2.1], [3.1, 4.1], 1),
    ([1.1, 2.1, 3.1], [3.1, 4.1, 3.1], 2),
])
def test_Data_slice(X, Y, i):
    ''' pytest test case
    '''
    Data.init()
    Data_Z = []
    Data_S = []
    z = X[0]
    for z in np.linspace(X[0], X[-1], Data.MAX_SIZE):
        Data_Z.append(z)
        s = CurveT(X, Y, i)
        Data_S.append(s)
        Data.add(s, z)
        for k in range(len(X)):
            Y[k] += 1

    for i in range(len(X) - 1):
        xi = X[i]
        xi1 = X[i + 1]
        for x in (xi, (xi + xi1) / 2):
            Data_Y = []
            for j in range(len(Data_S)):
                s = Data_S[j]
                y = s.eval(x)
                Data_Y.append(y)
            s1 = Data.slice(x, 1)
            s2 = CurveT(Data_Z, Data_Y, 1)
            assert isSame(s1, s2)
