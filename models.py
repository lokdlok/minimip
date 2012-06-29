from Numberjack import *
from OsiGlpk import Solver

def modelOne():
    X = VarArray(2, 0.0, float('inf'))
    return X, Model(Maximise(6*X[0] + 5*X[1]),
                               X[0] +   X[1] <=  5,
                             3*X[0] + 2*X[1] <= 12)

def modelTwo():
    X = VarArray(2, 0.0, float('inf'))
    return X, Model(Maximise(6*X[0] + 8*X[1]),
                               X[0] +   X[1] <= 10,
                             2*X[0] + 3*X[1] <= 25,
                               X[0] + 5*X[1] <= 35)

def modelThree():
    X = VarArray(3, 0.0, float('inf'))
    return X, Model(Maximise(60*X[0] +  30*X[1] +  20*X[2]),
                              2*X[0] + 1.5*X[1] + 0.5*X[2]<=  8,
                              8*X[0] +   6*X[1] +     X[2]<= 48,
                              4*X[0] +   2*X[1] + 1.5*X[2]<= 20,
                                           X[1]           <=  5)

for (X,model) in [modelOne(), modelTwo(), modelThree()]:
    s = Solver(model)
    s.setVerbosity(0)
    if s.solve():
        print X
    else:
        print "FAIL"
