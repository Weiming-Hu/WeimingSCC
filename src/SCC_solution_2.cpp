#include <set>
#include <ctime>
#include <stack>
#include <vector>
#include <iomanip>
#include <iostream>
#include <functional>

// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

namespace solution_2 {

using value_type = int;

vector<value_type> heads;
vector<value_type> tails;

struct SCC {
	vector<bool> explored;
	vector<value_type> leaders;
	vector<value_type> finishings;

	value_type counter;
};

// This function is not recursive, but uses iterative
// approach and manages the nodes to visit using a
// stack data structure.
//
void DFS_nonrecursive(
		const vector<value_type> & tails,
		const vector<value_type> & heads,
		value_type node, value_type leader,
		SCC & scc) {

	// Create a stack to keep track of nodes
	stack<value_type> nodes_to_visit;

	if (!scc.explored.at(node - 1)) {
		nodes_to_visit.push(node);
	}

	while(!nodes_to_visit.empty()) {

		bool finished = true;

		node = nodes_to_visit.top();

		if (!scc.explored.at(node - 1)) {
			// Mark the next node as visited
			scc.explored.at(node - 1) = true;
			scc.leaders.at(node - 1) = leader;

			// Find the elements from the right beginning
			// so that the exact same finishing time can
			// be generated with the recursive method
			//
			auto it = find(tails.rbegin(), tails.rend(), node);
			while (it != tails.rend()) {
				// size_t index = distance(tails.begin(), it);
				size_t index = distance(it+1, tails.rend());
				value_type next_node = heads.at(index);

				if (!scc.explored.at(next_node - 1)) {
					nodes_to_visit.push(next_node);

					// This node introduces new child node
					// so thie node will be kept in the stack
					//
					finished = false;
				}

				it = find(it + 1, tails.rend(), node);
			}
		}

		if (finished) {
			// If the node does not introduce any new children
			nodes_to_visit.pop();

			if (scc.finishings.at(node - 1) == 0) {
				// If the node finishing time has not been calculated yet
				scc.counter = scc.counter + 1;
				scc.finishings[node-1] = scc.counter;
			}
		}
	}
}
}

// [[Rcpp::export]]
NumericVector SCC_solution_2(
		NumericVector tails_R,
		NumericVector heads_R,
		bool verbose = false) {

	clock_t begin = clock();

	using namespace solution_2;

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
		cout << "Processing the 1st DFS loop ..." << endl;

	scc.counter = 0;
	for (auto node : nodes) {
		if (!scc.explored.at(node - 1)) {

			// Note that the graph direction is reversed
			DFS_nonrecursive(heads, tails, node, node, scc);

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

	if (verbose)
		cout << "Processing the 2nd DFS loop ..." << endl;
	scc.explored.clear();
	scc.explored.resize(nodes.size(), false);

	scc.counter = 0;
	for (auto node : nodes) {
		if (!scc.explored.at(node - 1)) {
			DFS_nonrecursive(tails, heads, node, node, scc);
		}
	}

	clock_t check_point_DFS_leader = clock();

	if (verbose) {
		double elapsed_prepare = double(
			check_point_prepare - begin) / CLOCKS_PER_SEC;
		double elapsed_DFS_finishing = double(
			check_point_DFS_finishing - check_point_prepare) / CLOCKS_PER_SEC;
		double elapsed_rename = double(
			check_point_rename - check_point_DFS_finishing) / CLOCKS_PER_SEC;
		double elapsed_DFS_leader = double(
			check_point_DFS_leader - check_point_rename) / CLOCKS_PER_SEC;
		double elapsed_total = double(
			check_point_DFS_leader - begin) / CLOCKS_PER_SEC;

		cout << setprecision(3)
       << "Preprocessing: " << elapsed_prepare << " s("
       << elapsed_prepare/elapsed_total * 100 << "%)" << endl
       << "Computing finishing times: " << elapsed_DFS_finishing << " s("
       << elapsed_DFS_finishing/elapsed_total * 100 << "%)" << endl
       << "Renaming nodes: " << elapsed_rename << " s("
       << elapsed_rename/elapsed_total * 100 << "%)" << endl
       << "Computing the leaders: " << elapsed_DFS_leader << " s("
       << elapsed_DFS_leader/elapsed_total * 100 << "%)" << endl;
	}

	NumericVector leaders_R = wrap(scc.leaders);
	return (leaders_R);
}

