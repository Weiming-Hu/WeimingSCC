#include <set>
#include <ctime>
#include <vector>
#include <iostream>
#include <functional>

// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

namespace solution_4 {

    using value_type = int;

    vector<value_type> heads;
    vector<value_type> tails;
    
    vector< vector<value_type> > adjacency_list;

    struct SCC {
        vector<bool> explored;
        vector<value_type> leaders;
        vector<value_type> finishings;

        value_type counter = 0;
    };

    // This function generates the adjacency list of a
    // graph from the vectors tails and heads.
    //
    void generate_adjacency_list(
            const set< value_type, greater<value_type> > nodes,
            const vector<value_type> & tails,
            const vector<value_type> & heads,
            vector< vector<value_type> > & adjacency_list) {

        adjacency_list.resize(nodes.size());

        for (size_t index = 0; index < tails.size(); index++) {
            adjacency_list.at(tails[index] - 1).push_back(heads[index]);
        }
    }

    // This function is a recursive function for DFS.
    void DFS_recursive(
            const vector<value_type> & tails,
            const vector<value_type> & heads,
            value_type node, value_type leader,
            SCC & scc) {

        // Mark the cuurect node as explored
        scc.explored.at(node - 1) = true;

        // Set the leader of this current node
        scc.leaders.at(node - 1) = leader;

        auto children = adjacency_list.at(node - 1);

        for (const auto & child : children) {
            if (!scc.explored.at(child - 1)) {
                DFS_recursive(tails, heads, child, leader, scc);
            }
        }

        // Record the finishing time
        scc.counter++;
        scc.finishings.at(node - 1) = scc.counter;
    }
}

// [[Rcpp::export]]
NumericVector SCC_solution_4(
        NumericVector tails_R,
        NumericVector heads_R,
        bool verbose = false) {

    using namespace solution_4;

    clock_t begin = clock();

    SCC scc;

    // Convert SEXP type to STL type
    tails = as< vector<value_type> >(tails_R);
    heads = as< vector<value_type> >(heads_R);

    // Calculate the total number of nodes
    set< value_type, greater<value_type> > nodes(
            tails.begin(), tails.end());
    nodes.insert(heads.begin(), heads.end());

    // Resize vectors to the number of nodes
    scc.explored.resize(nodes.size(), false);
    scc.leaders.resize(nodes.size(), 0);
    scc.finishings.resize(nodes.size(), 0);

    clock_t check_point_prepare = clock();

    if (verbose)
        cout << "Generate adjacency list ..." << endl;

    scc.counter = 0;
    adjacency_list.clear();
    generate_adjacency_list(nodes, heads, tails, adjacency_list);

    clock_t check_point_generate_list_1 = clock();

    if (verbose)
        cout << "Processing the 1st DFS loop ..." << endl;

    for (auto node : nodes) {
        if (!scc.explored.at(node - 1)) {

            // Note that the graph direction is reversed
            DFS_recursive(heads, tails, node, node, scc);

        }
    }

    clock_t check_point_DFS_finishing = clock();

    if (verbose)
        cout << "Rename nodes by the finishing time ..." << endl;

    for (value_type i = 0; i < tails.size(); i++) {
        tails[i] = scc.finishings.at(tails[i]-1);
        heads[i] = scc.finishings.at(heads[i]-1);
    }

    clock_t check_point_rename = clock();

    scc.explored.clear();
    scc.explored.resize(nodes.size(), false);

    if (verbose)
        cout << "Generate adjacency list ..." << endl;

    scc.counter = 0;
    adjacency_list.clear();
    generate_adjacency_list(nodes, tails, heads, adjacency_list);

    clock_t check_point_generate_list_2 = clock();

    if (verbose)
        cout << "Processing the 2nd DFS loop ..." << endl;
    for (auto node : nodes) {
        if (!scc.explored.at(node - 1)) {
            DFS_recursive(tails, heads, node, node, scc);
        }
    }

    clock_t check_point_DFS_leader = clock();

    if (verbose) {
        double elapsed_prepare = double(
                check_point_prepare - begin) / CLOCKS_PER_SEC;
        double elapsed_list_1 = double(
                check_point_generate_list_1 - check_point_prepare) / CLOCKS_PER_SEC;
        double elapsed_DFS_finishing = double(
                check_point_DFS_finishing - check_point_generate_list_1) / CLOCKS_PER_SEC;
        double elapsed_rename = double(
                check_point_rename - check_point_DFS_finishing) / CLOCKS_PER_SEC;
        double elapsed_list_2 = double(
                check_point_generate_list_2 - check_point_rename) / CLOCKS_PER_SEC;
        double elapsed_DFS_leader = double(
                check_point_DFS_leader - check_point_rename) / CLOCKS_PER_SEC;
        double elapsed_total = double(
                check_point_DFS_leader - begin) / CLOCKS_PER_SEC;

        cout << endl << setprecision(3)
            << "Preprocessing: " << elapsed_prepare << " s("
            << elapsed_prepare/elapsed_total * 100 << "%)" << endl
            << "Generating adjacency list: " << elapsed_list_1 << " s("
            << elapsed_list_1/elapsed_total * 100 << "%)" << endl
            << "Computing finishing times: " << elapsed_DFS_finishing << " s("
            << elapsed_DFS_finishing/elapsed_total * 100 << "%)" << endl
            << "Renaming nodes: " << elapsed_rename << " s("
            << elapsed_rename/elapsed_total * 100 << "%)" << endl
            << "Generating adjacency list: " << elapsed_list_2 << " s("
            << elapsed_list_2/elapsed_total * 100 << "%)" << endl
            << "Computing the leaders: " << elapsed_DFS_leader << " s("
            << elapsed_DFS_leader/elapsed_total * 100 << "%)" << endl
            << "Total time: " << elapsed_total << " s("
            << elapsed_total/elapsed_total * 100 << "%)" << endl;
    }

    NumericVector leaders_R = wrap(scc.leaders);
    return (leaders_R);
}
