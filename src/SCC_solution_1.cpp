#include <set>
#include <vector>
#include <iostream>
#include <functional>

// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

namespace solution_1 {

using value_type = int;

vector<value_type> heads;
vector<value_type> tails;

struct SCC {
	vector<bool> explored;
	vector<value_type> leaders;
	vector<value_type> finishings;

	value_type counter = 0;
};

// This function is a recursive function for DFS.
void DFS_recursive(
		const vector<value_type> & tails,
		const vector<value_type> & heads,
		value_type node, value_type leader,
		SCC & scc) {
	value_type index, next_node;

	// Mark the cuurect node as explored
	scc.explored.at(node - 1) = true;

	// Set the leader of this current node
	scc.leaders.at(node - 1) = leader;

	auto it = find(tails.begin(), tails.end(), node);
	while (it != tails.end()) {
		index = distance(tails.begin(), it);
		next_node = heads.at(index);

		if (!scc.explored.at(next_node - 1)) {
			DFS_recursive(tails, heads, next_node, leader, scc);
		}

		it = find(it+1, tails.end(), node);
	}

	// Record the finishing time
	scc.counter++;
	scc.finishings.at(node - 1) = scc.counter;
}
}

// [[Rcpp::export]]
NumericVector DFS_recursive_R(
		NumericVector tails_R,
		NumericVector heads_R, int node) {

	using namespace solution_1;

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

	DFS_recursive(tails, heads, node, node, scc);

	NumericVector finishing_R = wrap(scc.finishings);
	return (finishing_R);
}

// [[Rcpp::export]]
NumericVector SCC_solution_1(
		NumericVector tails_R,
		NumericVector heads_R,
		bool verbose = false) {

	using namespace solution_1;

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

	if (verbose)
		cout << "Processing the 1st DFS loop ..." << endl;

	for (auto node : nodes) {
		if (!scc.explored.at(node - 1)) {

			// Note that the graph direction is reversed
			DFS_recursive(heads, tails, node, node, scc);

		}
	}

	if (verbose)
		cout << "Rename nodes by the finishing time ..." << endl;

	for (value_type i = 0; i < tails.size(); i++) {
		tails[i] = scc.finishings.at(tails[i]-1);
		heads[i] = scc.finishings.at(heads[i]-1);
	}

	if (verbose)
		cout << "Processing the 2nd DFS loop ..." << endl;
	scc.explored.clear();
	scc.explored.resize(nodes.size(), false);

	scc.counter = 0;
	for (auto node : nodes) {
		if (!scc.explored.at(node - 1)) {
			DFS_recursive(tails, heads, node, node, scc);
		}
	}

	NumericVector leaders_R = wrap(scc.leaders);
	return (leaders_R);
}
