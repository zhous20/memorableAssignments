## @file Load.py
#  @author Shengchen Zhou
#  @brief The load module
#  @date 15 Feb 2018


from CurveADT import CurveT
from Data import Data


## @brief Load data
#  @details It's assumed that the input file will match the given specification
#  @param s The input file's filename
def Load(s):
    Data.init()
    with open(s, 'r') as infile:
        i = 0
        for line in infile:
            if i == 0:
                Data_Z = line.split(',')
                __toFloat__(Data_Z)
                Xs = []
                Ys = []
                for j in range(len(Data_Z)):
                    Xs.append([])
                    Ys.append([])
                i += 1
            elif i == 1:
                curve_o = line.split(',')
                __toFloat__(curve_o)
                i += 1
            else:
                values = line.split(',')
                __toFloat__(values)
                for j in range(len(values)):
                    value = values[j]
                    if value is not None:
                        k = j // 2
                        if j % 2 == 0:
                            Xs[k].append(value)
                        else:
                            Ys[k].append(value)
        for j in range(len(Data_Z)):
            X = Xs[j]
            Y = Ys[j]
            s = CurveT(X, Y, curve_o[j])
            z = Data_Z[j]
            Data.add(s, z)


## @brief Convert list of string to list of floats in place
#  @param L the input list
def __toFloat__(L):
    for i in range(len(L)):
        if L[i].strip():
            L[i] = float(L[i])
        else:
            L[i] = None
