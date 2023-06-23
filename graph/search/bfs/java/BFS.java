import java.util.ArrayDeque;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

// A class that explores a graph starting from a source node.
public class BFS {
    private final int source;
    // An auxiliary array to prevent visiting the same node twice.
    private final boolean[] visited;
    // An auxiliary array to keep track of the path taken to reach a node.
    private final int[] edgeTo;

    public BFS(Graph graph, int source) {
        this.source = source;
        visited = new boolean[graph.V()];
        edgeTo = new int[graph.V()];
        search(graph, source);
    }

    // If the node was visited, then there is a path between the source and the node.
    public boolean hasPathTo(int v) {
        return visited[v];
    }

    // Returns a path from the source to node v.
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v))
            return null;

        // We'll look from the end to the beginning, so use a stack to reverse the order.
        Stack<Integer> path = new Stack<>();

        while (v != source) {
            path.push(edgeTo[v]);
            v = edgeTo[v];
        }
        path.push(source);

        return path;
    }

    // Searches the graph starting from node s.
    private void search(Graph G, int s) {
        // Create auxiliary queue to ensure FIFO order.
        Queue<Integer> queue = new ArrayDeque<>();

        // Initialize the queue and mark the origin as visited.
        queue.add(s);
        visited[s] = true;

        while (!queue.isEmpty()) {
            // Get the next node to explore.
            int current = queue.remove();
            // Add its neighbors to the queue.
            for (Integer neighbor : G.adjacentTo(current)) {
                if (visited[neighbor])
                    continue;
                visited[neighbor] = true;
                // Record the path taken to reach the node.
                edgeTo[neighbor] = current;
                queue.add(neighbor);
            }
        }
    }

    // Undirected Graph representation.
    private class Graph {
        private final List<Integer>[] adjacencyLists;
        private int edges;

        public Graph(int numberOfVertices) {
            adjacencyLists = (LinkedList<Integer>[]) new LinkedList[numberOfVertices];
            for (int v = 0; v < numberOfVertices; v++)
                adjacencyLists[v] = new LinkedList<>();
            edges = 0;
        }

        // Since it's an undirected graph, add edges to both adjacency lists.
        public void addEdge(int v, int w) {
            adjacencyLists[v].add(w);
            adjacencyLists[w].add(v);
            // Increment the number of edges by 1.
            edges++;
        }

        // Returns all neighbors of v.
        public Iterable<Integer> adjacentTo(int v) {
            return adjacencyLists[v];
        }

        // Returns the number of vertices.
        public int V() {
            return adjacencyLists.length;
        }

        // Returns the number of edges.
        public int E() {
            return edges;
        }

        // Returns the degree of vertex v in graph G.
        public static int degree(Graph G, int v) {
            return G.adjacencyLists[v].size();
        }

        // Returns the largest degree of a graph.
        public static int maxDegree(Graph G) {
            int maxDegree = 0;
            for (int v = 0; v < G.V(); v++)
                if (maxDegree < degree(G, v))
                    maxDegree = degree(G, v);
            return maxDegree;
        }
    }
}
