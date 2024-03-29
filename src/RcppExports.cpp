// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// get_maximum_recursive_calls
int get_maximum_recursive_calls();
RcppExport SEXP _WeimingSCC_get_maximum_recursive_calls() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(get_maximum_recursive_calls());
    return rcpp_result_gen;
END_RCPP
}
// DFS_recursive_R
NumericVector DFS_recursive_R(NumericVector tails_R, NumericVector heads_R, int node);
RcppExport SEXP _WeimingSCC_DFS_recursive_R(SEXP tails_RSEXP, SEXP heads_RSEXP, SEXP nodeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type tails_R(tails_RSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type heads_R(heads_RSEXP);
    Rcpp::traits::input_parameter< int >::type node(nodeSEXP);
    rcpp_result_gen = Rcpp::wrap(DFS_recursive_R(tails_R, heads_R, node));
    return rcpp_result_gen;
END_RCPP
}
// SCC_solution_1
NumericVector SCC_solution_1(NumericVector tails_R, NumericVector heads_R, bool verbose);
RcppExport SEXP _WeimingSCC_SCC_solution_1(SEXP tails_RSEXP, SEXP heads_RSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type tails_R(tails_RSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type heads_R(heads_RSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(SCC_solution_1(tails_R, heads_R, verbose));
    return rcpp_result_gen;
END_RCPP
}
// SCC_solution_2
NumericVector SCC_solution_2(NumericVector tails_R, NumericVector heads_R, bool verbose);
RcppExport SEXP _WeimingSCC_SCC_solution_2(SEXP tails_RSEXP, SEXP heads_RSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type tails_R(tails_RSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type heads_R(heads_RSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(SCC_solution_2(tails_R, heads_R, verbose));
    return rcpp_result_gen;
END_RCPP
}
// generate_adjacency_list_R
List generate_adjacency_list_R(NumericVector tails_R, NumericVector heads_R);
RcppExport SEXP _WeimingSCC_generate_adjacency_list_R(SEXP tails_RSEXP, SEXP heads_RSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type tails_R(tails_RSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type heads_R(heads_RSEXP);
    rcpp_result_gen = Rcpp::wrap(generate_adjacency_list_R(tails_R, heads_R));
    return rcpp_result_gen;
END_RCPP
}
// DFS_nonrecursive_R
NumericVector DFS_nonrecursive_R(NumericVector tails_R, NumericVector heads_R, int node);
RcppExport SEXP _WeimingSCC_DFS_nonrecursive_R(SEXP tails_RSEXP, SEXP heads_RSEXP, SEXP nodeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type tails_R(tails_RSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type heads_R(heads_RSEXP);
    Rcpp::traits::input_parameter< int >::type node(nodeSEXP);
    rcpp_result_gen = Rcpp::wrap(DFS_nonrecursive_R(tails_R, heads_R, node));
    return rcpp_result_gen;
END_RCPP
}
// SCC_solution_3
NumericVector SCC_solution_3(NumericVector tails_R, NumericVector heads_R, bool verbose);
RcppExport SEXP _WeimingSCC_SCC_solution_3(SEXP tails_RSEXP, SEXP heads_RSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type tails_R(tails_RSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type heads_R(heads_RSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(SCC_solution_3(tails_R, heads_R, verbose));
    return rcpp_result_gen;
END_RCPP
}
// SCC_solution_4
NumericVector SCC_solution_4(NumericVector tails_R, NumericVector heads_R, bool verbose);
RcppExport SEXP _WeimingSCC_SCC_solution_4(SEXP tails_RSEXP, SEXP heads_RSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type tails_R(tails_RSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type heads_R(heads_RSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(SCC_solution_4(tails_R, heads_R, verbose));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_WeimingSCC_get_maximum_recursive_calls", (DL_FUNC) &_WeimingSCC_get_maximum_recursive_calls, 0},
    {"_WeimingSCC_DFS_recursive_R", (DL_FUNC) &_WeimingSCC_DFS_recursive_R, 3},
    {"_WeimingSCC_SCC_solution_1", (DL_FUNC) &_WeimingSCC_SCC_solution_1, 3},
    {"_WeimingSCC_SCC_solution_2", (DL_FUNC) &_WeimingSCC_SCC_solution_2, 3},
    {"_WeimingSCC_generate_adjacency_list_R", (DL_FUNC) &_WeimingSCC_generate_adjacency_list_R, 2},
    {"_WeimingSCC_DFS_nonrecursive_R", (DL_FUNC) &_WeimingSCC_DFS_nonrecursive_R, 3},
    {"_WeimingSCC_SCC_solution_3", (DL_FUNC) &_WeimingSCC_SCC_solution_3, 3},
    {"_WeimingSCC_SCC_solution_4", (DL_FUNC) &_WeimingSCC_SCC_solution_4, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_WeimingSCC(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
