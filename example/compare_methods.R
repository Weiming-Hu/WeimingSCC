# This is the main script that compares the stronly
# connected component results from different methods
#
# The first test case is igraph package. This package
# is used to provide the correct result. Meanwhile, this
# package is also optimized in performance.
#
# Solution 1 is the naive implementation of Kasaraju's
# algorithm using STL and recursive DFS algorithm.
#
# Solution 2 is another implementation of Kasaraju's
# algorithm using STL and non-recursive DFS algorithm.
# This implementation uses stack data structure to
# keep track of nodes.
#
# Solution 3 is the improved implementation of the solution
# 2. This implementation first generate the adjacency
# list to keep track of the child nodes instead of
# searching for child nodes every time.
#
# Solution 4 is the improved implementation of the solution
# 1. This implementation first generate the adjacency
# list to keep track of the child nodes instead of
# searching for child nodes every time.
#

library(WeimingSCC)
library(profmem)

# Whether to profile the memory usage
profile.memory <- F

# Whether to profile algorithm time
profile.time <- T

# Whether to print the progress of the algorithm
verbose <- T

# Select which data set to load

if (F) {
	# Small test case: this graph matches the
	# example used in the post with 8 edges and
	# 7 nodes.
	#
	data("edge_list_small-test")
	edge.list <- test
	rm(test)
}

if (F) {
	# Wiki vote directed graph case: this graph is
	# bigger than the above case, but not too big,
	# with 103689 edges and 7115 nodes.
	#
	# Source: https://snap.stanford.edu/data/wiki-Vote.html
	#
	data('edge_list_wiki-vote')
	edge.list <- vote
	rm(vote)
}

if (F) {
	# Twitter: this graph is the largest one with
	# 2420744 edges and 81306 nodes.
	#
	# Source: https://snap.stanford.edu/data/egonets-Twitter.html
	#
	data('edge_list_twitter')
	edge.list <- twitter
	rm(twitter)
}

if (F) {
	# Data from Coursera course - Algorithm by Stanford University with
	# 5105042 edges and 875714 nodes.
	data('edge_list_coursera')
	edge.list <- coursera
	rm(coursera)
}

if (T) {
	# Synthetic data that has a long path. This data set is specifically
	# created to generate stack overflow problem for Solution_4.
	#
	nrows <- 1000000
	edge.list <- matrix(nrow = nrows, ncol = 2)
	for (i in 1:nrows) {
		edge.list[i, ] <- c(i, i+1)
	}
}

####################################################
#        Use package igraph for correctness        #
####################################################
print("Running solution code using igraph ...")

if (profile.memory) {
	p <- profmem({
		ret <- SCC_igraph(edge.list)
	})
	print(p, expr = F)
}

if (profile.time) {
	system.time(ret <- SCC_igraph(edge.list))
} else {
	ret <- SCC_igraph(edge.list)
}


####################################################
#                 Use solution 1                   #
####################################################
if (F) {
	print("Running the solution code 1 ...")

	if (profile.memory) {
		p <- profmem({
			leaders_1 <- SCC_solution_1(edge.list[, 1],
																	edge.list[, 2])
		})
		print(p, expr = T)
	}

	if (profile.time) {
		system.time(leaders_1 <- SCC_solution_1(
			edge.list[, 1], edge.list[, 2]), verbose)
	} else {
		leaders_1 <- SCC_solution_1(edge.list[, 1], edge.list[, 2],
																verbose)
	}

	identical(length(unique(ret$membership)),
						length(unique(leaders_1)))
}


####################################################
#                 Use solution 2                   #
####################################################
if (F) {
	print("Running the solution code 2 ...")

	if (profile.memory) {
		p <- profmem({
			leaders_2 <- SCC_solution_2(edge.list[, 1],
																	edge.list[, 2])
		})
		print(p, expr = T)
	}

	if (profile.time) {
		system.time(leaders_2 <- SCC_solution_2(
			edge.list[, 1], edge.list[, 2]), verbose)
	} else {
		leaders_2 <- SCC_solution_2(edge.list[, 1], edge.list[, 2],
																verbose)
	}

	identical(length(unique(ret$membership)),
						length(unique(leaders_2)))
}

####################################################
#                 Use solution 3                   #
####################################################
if (T) {
	print("Running the solution code 3 ...")

	if (profile.memory) {
		p <- profmem({
			leaders_3 <- SCC_solution_3(edge.list[, 1],
																	edge.list[, 2])
		})
		print(p, expr = T)
	}

	if (profile.time) {
		system.time(leaders_3 <- SCC_solution_3(
			edge.list[, 1], edge.list[, 2]), verbose)
	} else {
		leaders_3 <- SCC_solution_3(edge.list[, 1], edge.list[, 2],
																verbose)
	}

	identical(length(unique(ret$membership)),
						length(unique(leaders_3)))
}

####################################################
#                 Use solution 4                   #
####################################################
if (T) {
	print("Running the solution code 4 ...")

	if (profile.memory) {
		p <- profmem({
			leaders_4 <- SCC_solution_4(edge.list[, 1],
																	edge.list[, 2])
		})
		print(p, expr = T)
	}

	if (profile.time) {
		system.time(leaders_4 <- SCC_solution_4(
			edge.list[, 1], edge.list[, 2]), verbose)
	} else {
		leaders_4 <- SCC_solution_4(edge.list[, 1], edge.list[, 2],
																verbose)
	}

	identical(length(unique(ret$membership)),
						length(unique(leaders_4)))
}
