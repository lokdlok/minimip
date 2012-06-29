#include <iostream>
#include <vector>
#include <map>

class FriendlyModel {
    public:
        int ncols;
        int nrows;
        std::map<int, double> lbs;
        std::map<int, double> ubs;
        std::vector<std::map<int, double>* > rows;
        std::map<int, double> Z;
        double obj_coef;
        std::map<int, bool> integer_vars;
} ;

class MinimipModel {
    public:
        int ncols;
        int nrows;
        std::map<int, double> rhs;
        std::vector<std::map<int, double>* > rows;
        std::map<int, double> Z;
        std::map<int, bool> integer_vars;
} ;
