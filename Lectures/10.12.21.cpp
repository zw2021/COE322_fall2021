//
// Created by huang on 10/12/2021.
//
#include <tuple>
using std::pair;
using std::make_pair;
using std::tuple;
using std::make_tuple;

#include <variant>
using std::variant;
using std::get_if;
using std::get;
using std::bad_variant_access;
using std::visit;

using quadratic = tuple<double,double,double>;

double discriminant (quadratic coefficient)
{
    auto [a,b,c] = coefficient;
    return(b*b - 4*a*c);
}

bool discriminant_zero(quadratic coeffcient){
    auto [a,b,c] = coeffcient;
    if (b*b - 4*a*c == 0)
        return true;
    else
        return false;
}

double compute_roots(coefficient){
    make_tuple(0., 2.5, 0.);
}
int main(){
    auto [] = coefficient;
    return 0;
}