package union_find;

public class UnionFind {
    // Array indicating the root of the component each element is connected to.
    private int[] id;
    // The index of the root of the component indicates the whole component's size.
    private int[] size;
    // Auxiliary array for path compression.
    private int[] toCompress;

    public UnionFind(int n) {
        id = new int[n];
        size = new int[n];
        toCompress = new int[n];
        // Initialize every element to be the root of its own component,
        // and the size of each component to 1.
        for (int i = 0; i < n; i++) {
            id[i] = i;
            size[i] = 1;
        }
    }

    // Connects two components into a single one.
    public void union(int p, int q) {
        // Get the root of the components.
        p = find(p);
        q = find(q);

        // If the root is the same, the elements are already connected.
        if (p == q)
            return;

        // To keep the structure balanced with limited depth,
        // add the smaller component as a branch of the larger component.
        // Remember to increment the size of the resulting root.
        if (size[p] > size[q]) {
            // q's root is p, since p's component is bigger.
            id[q] = p;
            // p's component's size is incremented, since it now has all elements in the previous component.
            size[p] += size[q];
        } else {
            id[p] = q;
            size[q] += size[p];
        }
    }

    // Finds the root of the component to which an element is connected.
    public int find(int p) {
        // Count the number of iterations.
        int i = 0;

        // While the element is not the root of the component:
        while (p != id[p]) {
            // Remember the element.
            toCompress[i++] = p;
            // Get the element's parent.
            p = id[p];
        }

        // Now make all elements traversed point directly to the root.
        // Next time "find" is called, it will only take 1 iteration of the loop to find the root.
        for (int j = 0; j < i; j++)
            id[j] = p;

        // Return the root.
        return p;
    }

    // Checks if two elements are connected by checking if the root of both is the same.
    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    public static void main(String[] args) {
        UnionFind uf = new UnionFind(10);

        assert !uf.connected(0, 1);

        uf.union(0, 1);

        assert uf.connected(0, 1);

        assert uf.find(0) == 1;
    }
}
