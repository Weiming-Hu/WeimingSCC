#' WeimingSCC::SCC_igraph
#'
#' WeimingSCC::SCC_igraph computes the strongly
#' connected components using the package igraph.
#'
#' @author Weiming Hu \email{weiming@@psu.edu}
#'
#' @import igraph
#'
#' @param edge.list a 2-column matrix with the
#' first column being the tails and the second
#' being the heads.
#'
#' @return a list containing the leaders and sizes
#' of SCCs.
#'
SCC_igraph <- function (edge.list) {

	require(igraph)

	# Create igraph object
	graph <- graph(edges = as.vector(t(edge.list)))

	# Compute SCC
	ret <- components(graph, mode = "strong")

	return(ret)
}
