from sympy import *
from copy import deepcopy as copy
from math import ceil, floor

def addslack(A, b, c):
    nslacks = A.rows
    lol = A.row_join(diag(*[1 for i in xrange(nslacks)]))
    cl = c.col_join(Matrix([0.0 for i in xrange(nslacks)]))
    return Matrix(lol), b, Matrix(cl)

def printModel(A, b, c):
    print "A:\n", A
    print "b:\n", b
    print "c:\n", c.T

def simplex(A, b, c, I=None):
    row_vars = range(A.cols-A.rows, A.cols)
    theta = [0.0 for i in xrange(A.cols)]
    cmz = [0.0 for i in xrange(A.cols)]
    
    while True:
        pv = 0
        pr = 0
        pe = 0.0

        for v in xrange(A.cols):
            s = (A[0:, v].T * Matrix([c[row_vars[r]]
                                for r in xrange(A.rows)]))[0]
            cmz[v] = c[v] - s
            if cmz[v] > cmz[pv]:
                pv = v

        if cmz[pv] <= 0.0: break

        for r in xrange(A.rows):
            if A[r, pv] > 0:
                theta[r] = b[r] / A[r,pv]
                if theta[r] < theta[pr]:
                    pr = r

        row_vars[pr] = pv
        pe = A[pr, pv]
        A[pr, 0:] /= pe
        b[pr] /= pe

        coef_b, coef_a = A[:pr, pv], A[pr+1:, pv]
        if len(coef_b) > 0:
            A[:pr, 0:] -= coef_b * A[pr, 0:]
            b[:pr, 0:] -= coef_b * b[pr, 0:]
        if len(coef_a) > 0:
            A[pr+1:, 0:] -= coef_a * A[pr, 0:]
            b[pr+1:, 0:] -= coef_a * b[pr, 0:]
        
    solution = [0 for i in xrange(A.cols)]
    for r in xrange(A.rows):
        solution[row_vars[r]] = b[r]
    return Matrix(solution)
    
def post(A,b,c,v,d,nb):
    coef = 1
    if d == '=':
        A,b,c = post(A,b,c,v,'<=',nb)
        return post(A,b,c,v,'>=',nb)
    elif d == '<=':
        coef = 1
    elif d == '>=':
        coef = -1

    coef = 1 if d == '<=' else -1
    A = A.col_join(Matrix([coef*int(i==v) for i in xrange(A.cols)]).T)
    A = A.row_join(Matrix([0 for i in xrange(A.rows-1)] + [1]))
    b = b.col_join(Matrix([coef*nb]))
    c = c.col_join(Matrix([0]))

    return A,b,c

def branchandbound(A, b, c, Z):
    A1,b1,c1 = copy(A), copy(b), copy(c)
    print "Solving relaxation"
    x = simplex(A1,b1,c1)
    fracs = [i for i in Z if x[i] - int(x[i]) != 0]

    if len(fracs) == 0:
        return x

    # Dumb heuristic
    f = fracs[0]
    print "trying", f," <= ", b1[f]
    A1, b1, c1 = post(copy(A), copy(b), copy(c),
                      f, '<=', floor(x[f]))
    x = branchandbound(A1,b1,c1,Z)
    if not x:
        print "trying -", f," <= ", b1[f]
        A1, b1, c1 = post(copy(A), copy(b), copy(c),
                          f, '>=', ceil(x[f]))
        x = branchandbound(A1,b1,c1,Z)
    
    return x

def solve(A, b, c, I=None, alg=simplex):
    A1, b1, c1 = addslack(copy(A), copy(b), copy(c))
    x = alg(A1, b1, c1, I)

    if not x:
        print 'LP is infeasible'
    else:
        if I == None:
            I = set()
        print 'Vertex', [int(v) if i in I else v for i,v in enumerate(x.T[:A.cols])], 'is optimal'
        print 'Optimal value is', (c1.T * Matrix(x[:c1.rows]))[0]

if __name__ == '__main__':
    A = Matrix([[1, 1],
                [3, 2]])
    b = Matrix([5, 12])
    c = Matrix([6, 5])

    # new example
    solve(A,b,c,None,simplex)
    solve(A,b,c,[0,1],branchandbound)
    
    # small example
    A = Matrix([[50, 24],
         [30, 33],
         [-1, 0],
         [0, -1]])
    b = Matrix([2400, 2100, -45, -5])
    c = Matrix([1, 1])

    # new example
    solve(A,b,c)
    solve(A,b,c, [0,1], branchandbound)

    A = Matrix([[-10,  -6, -9, -10],
                [  8,  -6, -5,  -5],
                [ -7,  -1, -9,   3],
                [ -1,  -4,  5,  10],
                [  1,   2,  0,  10],
                [  2,  -9,  3,  -8],
                [ -8,  -1, -8,   1],
                [  7, -10,  4,  -4],
                [-10,   2,  5,   8],
                [ -7,   9,  4,  -4],
                [ -1,   0,  0,   0],
                [  0,  -1,  0,   0],
                [  0,   0, -1,   0],
                [  0,   0,  0,  -1]])
    b = Matrix([9, 7, 3, 4, 8, 0, 3, 2, 4, 8, 0, 0, 0, 0])
    c = Matrix([2, -2, -3, 8])
    # currently fails to solve this one
    exit()
    solve(A, b, c)

