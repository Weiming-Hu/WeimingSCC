// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <iostream>

using namespace Rcpp;
using namespace std;

namespace maxRecursive {
    size_t count = 0;
}

void recursive_call() {
    maxRecursive::count++;
    cout << "cout " << maxRecursive::count++ << endl;

    recursive_call();
}

// [[Rcpp::export]]
int get_maximum_recursive_calls() {

    try {
        recursive_call();
    } catch (...) {
        cout << "Error occurs at count " << maxRecursive::count << endl;
    }

    return (maxRecursive::count);
}
