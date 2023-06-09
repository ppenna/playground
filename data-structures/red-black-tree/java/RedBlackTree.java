import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class RedBlackTree <Key extends Comparable<Key>, Value> {
    private static final boolean RED = true;
    private static final boolean BLACK = false;
    private Node root;

    private class Node {
        private final Key key;
        private Value value;
        private Node left, right;
        private int size;
        private boolean color;

        public Node(Key key, Value value) {
            this.key = key;
            this.value = value;
            size = 1;
            color = RED;
        }
    }

    private boolean isRed(Node node) {
        // Null links are black.
        if (node == null)
            return false;
        return node.color == RED;
    }

    // When a red link appears in the right child, rotate left.
    private Node rotateLeft(Node node) {
        // Let E be the parent node, and S be its right child with a red link. Store S.
        Node aux = node.right;
        // S's left child is between E and S, so it fits as the right child of E. Link it there.
        node.right = aux.left;
        // Now S has no left child. Since E is smaller, link it there.
        aux.left = node;
        // Ensure the link arriving in S is the same that was arriving at E.
        aux.color = node.color;
        // Now E's link to S is red.
        node.color = RED;

        // Updating the node's sizes. Update "node" first, as it is "aux"'s child:
        node.size = size(node.left) + size(node.right) + 1;
        aux.size = size(aux.left) + size(aux.right) + 1;

        // Returns S to update E's former parent's link.
        return aux;
    }

    // Temporarily lean right.
    private Node rotateRight(Node node) {
        // Let S be the parent node, and E be its left child with a red link. Store E.
        Node aux = node.left;
        // E's right child is between E and S, so it fits as the left child of S. Link it there.
        node.left = aux.right;
        // Now E has no right child. Since S is greater, link it there.
        aux.right = node;
        // Ensure the link arriving in E is the same that was arriving at S.
        aux.color = node.color;
        // Now S's link to E is red.
        node.color = RED;

        // Updating the node's sizes. Update "node" first, as it is "aux"'s child:
        node.size = size(node.left) + size(node.right) + 1;
        aux.size = size(aux.left) + size(aux.right) + 1;

        // Returns E to update S's former parent's link.
        return aux;
    }

    // Changes the colors of all links to a node. This is akin to splitting a 4-node in a 2-3 tree.
    private void flipColors(Node node) {
        node.color = RED;
        node.left.color = BLACK;
        node.right.color = BLACK;
    }

    // Stores value with associated key, or overwrites it if the key already exists.
    public void put(Key key, Value value) {
        // By convention, null values are deleted.
        if (value == null) {
            delete(key);
            return;
        }

        // Call to a recursive function to find where to put the key, and update its parent's children.
        root = put(root, key, value);
    }

    private Node put(Node node, Key key, Value value) {
        // We've reached an empty branch, so create a new node and store it there.
        if (node == null)
            return new Node(key, value);

        int compare = key.compareTo(node.key);

        // The key is smaller, so go left.
        // If it's a dead end, we'll store the new node.
        // If not, we'll store the same child.
        if (compare < 0)
            node.left = put(node.left, key, value);
            // The key is greater, so go right. Same thing.
        else if (compare > 0)
            node.right = put(node.right, key, value);
            // The key is the same, so merely update its value and return it to its parent.
        else
            node.value = value;

        // This is the trick behind Red Black trees:
        // When only the right child has a red link, rotate left.
        if (isRed(node.right) && !isRed(node.left))
            node = rotateLeft(node);
        // That might have lead to two red links in a row, or maybe the node was inserted on the left in a red node,
        // or colors flipped and there are now two reds in a row.
        // Either way, temporarily rotate right, so we can flip the colors.
        if (isRed(node.left) && isRed(node.left.left))
            node = rotateRight(node);
        // If it's all red, flip the colors.
        if (isRed(node.left) && isRed(node.right))
            flipColors(node);

        // Update the size of the subtree.
        // Note that due to the stacking nature of recursion, the leaves are updated first.
        node.size = 1 + size(node.left) + size(node.right);

        // This returns the node back to its parent.
        return node;
    }

    // Gets the value associated with the key, or null if the key doesn't exist in the tree.
    public Value get(Key key) {
        // Begin at the root.
        Node node = root;

        while (node != null) {
            int compare = key.compareTo(node.key);

            if (compare < 0)
                node = node.left;
            else if (compare > 0)
                node = node.right;
            else
                return node.value;
        }

        // Node is null, so dead end. The key doesn't exist.
        return null;
    }

    // Deletes the node with the associated key.
    public void delete(Key key) {
        // Known as Hibbard deletion. 3 cases based on number of children in the deleted node:
        // 0 children: set parent's link to null;
        // 1 child: replace parent's link to the child;
        // 2 children:
        //      a) Find the successor (node at the right subtree with no left child);
        //      b) Make the successor's right child the successor's parent's left child;
        //      c) Make the deleted node's children the successor's children;
        //      d) Link the deleted node's parent to the successor.
        root = delete(root, key);
    }

    private Node delete(Node node, Key key) {
        // Key not found.
        if (node == null)
            return null;

        int compare = key.compareTo(node.key);

        // If the key is smaller, go to the left.
        if (compare < 0)
            node.left = delete(node.left, key);

            // If the key is greater, go to the right.
        else if (compare > 0)
            node.right = delete(node.right, key);

            // We've found the key.
        else {
            // 1 child: link the node's parent to the lone child.
            // This also solves the 0 children case, since node.left/right are both null.
            if (node.left == null)
                return node.right;
            if (node.right == null)
                return node.left;

            // The node has 2 children.
            // Store the node to be deleted.
            Node aux = node;

            // a) Find the successor.
            node = min(aux.right);

            // b) Make the successor's right child the successor's parent's left child.
            // This is done by deleting the successor, by deleting the min on the right subtree.
            node.right = deleteMin(aux.right);

            // c) Make the deleted node's children the successor's children.
            // The right child was already linked above by storing deleteMin's return.
            // This links the left child.
            node.left = aux.left;

            // d) Link the deleted node's parent to the successor.
            // The "node" variable has been fully replaced. When it is returned, the link is updated,
            // and the deleted node is garbage collected.
        }


        node.size = 1 + size(node.left) + size(node.right);

        return node;
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public boolean isEmpty() {
        return root == null;
    }

    public int size() {
        return size(root);
    }

    private int size(Node node) {
        if (node == null)
            return 0;

        return node.size;
    }

    // Finds the smallest key.
    public Key min() {
        if (isEmpty())
            return null;

        return min(root).key;
    }

    private Node min(Node node) {
        // If there's a left child, there's a smaller key to the left.
        if (node.left != null)
            return min(node.left);

        // No left child means this is the min.
        return node;
    }

    // Finds the largest key.
    public Key max() {
        if (isEmpty())
            return null;

        return max(root).key;
    }

    private Node max(Node node) {
        if (node.right != null)
            return max(node.right);
        return node;
    }

    // Finds the largest key less than or equal to the key.
    public Key floor(Key key) {
        // Call to a recursive function to find the key.
        Node node = floor(root, key);
        return node == null ? null : node.key;
    }

    private Node floor(Node node, Key key) {
        // Dead end, so there's no key less than or equal to the key.
        if (node == null)
            return null;

        int compare = key.compareTo(node.key);

        // We've found the key.
        if (compare == 0)
            return node;

        // We couldn't find the key yet, but it might be in the left branch, since it's smaller.
        if (compare < 0)
            return floor(node.left, key);

        // We couldn't find the key, and it is greater than the current node.
        // Either the current node is the floor, or some node in the right branch is the floor,
        // since it is greater than the current, and might be smaller than the target key.
        Node potentialNode = floor(node.right, key);
        if (potentialNode != null)
            return potentialNode;
        return node;
    }

    // Finds the smallest key greater than or equal to the key.
    public Key ceiling(Key key) {
        Node node = ceiling(root, key);
        return node == null ? null : node.key;
    }

    private Node ceiling (Node node, Key key) {
        if (node == null)
            return null;

        int compare = key.compareTo(node.key);

        if (compare == 0)
            return node;

        if (compare > 0)
            return ceiling(node.right, key);

        Node potentialNode = ceiling(node.left, key);
        if (potentialNode != null)
            return potentialNode;
        return node;
    }

    // Returns number of keys smaller than the key.
    public int rank(Key key) {
        return rank(key, root);
    }

    private int rank(Key key, Node node) {
        // No nodes in this subtree.
        if (node == null)
            return 0;

        int compare = key.compareTo(node.key);

        if (compare < 0)
            return rank(key, node.left);

            // When the key is larger than the current node, add all nodes to the left of it,
            // as well as the current node, and explore the right subtree.
        else if (compare > 0)
            return rank(key, node.right) + 1 + size(node.left);

        return size(node.left);
    }

    // Returns key of rank k.
    public Key select(int k) {
        if (k < 0 || k >= size())
            throw new NoSuchElementException();
        return select(root, 0, k);
    }

    private Key select(Node node, int leftNodesExplored, int k) {
        // Get the number of elements in the subtree to the left of the node.
        int subtreeSize = size(node.left);

        // Adds the node's parent and all smaller nodes linked to it.
        int currentRank = subtreeSize + leftNodesExplored;

        // We're looking for a higher rank, so a larger number in the right subtree.
        // Pass the parent's rank + 1, so the child knows its starting rank.
        if (currentRank < k)
            return select(node.right, currentRank + 1, k);

        // We're looking for a smaller rank, so search in the left subtree. Don't add the parent to the current rank.
        if (currentRank > k)
            return select(node.left, leftNodesExplored, k);

        // Found the key.
        return node.key;
    }

    // Delete smallest key.
    public void deleteMin() {
        if (isEmpty())
            throw new NoSuchElementException();
        root = deleteMin(root);
    }

    private Node deleteMin(Node node) {
        // No left link means we've found the min.
        // Now replace the node with its right child, which is smaller than its parent.
        // There's no need to update the size, since the subtree is unchanged.
        // The garbage collector will then free it, since there's no reference to the min node.
        if (node.left == null)
            return node.right;

        // Keep going left to find the min element.
        node.left = deleteMin(node.left);

        // Update the size after deleting the min.
        // The stacking nature of recursion ensures the updates are made in the correct order.
        node.size = 1 + size(node.left) + size(node.right);

        return node;
    }

    // Delete largest key.
    public void deleteMax() {
        if (isEmpty())
            throw new NoSuchElementException();
        root = deleteMax(root);
    }

    private Node deleteMax(Node node) {
        if (node.right == null)
            return node.left;

        node.right = deleteMax(node.right);

        node.size = 1 + size(node.left) + size(node.right);

        return node;
    }

    // Number of keys in [lo..hi] (inclusive)
    public int size(Key lo, Key hi) {
        if (lo.compareTo(hi) > 0)
            return 0;

        // Get all keys smaller than or equal to hi.
        Key upperBound = floor(hi);
        int lowerThanHi = rank(upperBound) + 1;

        // Exclude all keys lower than lo.
        Key lowerBound = ceiling(lo);
        int lowerThanLo = rank(lowerBound);

        return lowerThanHi - lowerThanLo;
    }

    // Returns all keys in sorted order.
    public Iterable<Key> keys() {
        // Create an array that fits all the keys.
        List<Key> queue = new ArrayList<>(size());
        // Populates the queue.
        inOrder(root, queue);
        return queue;
    }

    // Traverses the tree in order and populates the queue.
    private void inOrder(Node node, List<Key> queue) {
        if (node == null)
            return;
        // Adds the left node, then the root, then the right node.
        inOrder(node.left, queue);
        queue.add(node.key);
        inOrder(node.right, queue);
    }

    // Returns keys in [lo..hi] (inclusive) in sorted order.
    public Iterable<Key> keys(Key lo, Key hi) {
        if (lo.compareTo(hi) > 0)
            return new ArrayList<>();

        // Create an array that fits all the keys.
        List<Key> queue = new ArrayList<>(size(lo, hi));
        // Populates the queue.
        inOrderWithComparison(root, queue, lo, hi);
        return queue;
    }

    private void inOrderWithComparison(Node node, List<Key> queue, Key lo, Key hi) {
        if (node == null)
            return;

        // If the key is smaller than lo, look in the right subtree only.
        if (lo.compareTo(node.key) > 0) {
            inOrderWithComparison(node.right, queue, lo, hi);
            return;
        }

        // If the key is greater than hi, look in the left subtree only.
        if (hi.compareTo(node.key) < 0) {
            inOrderWithComparison(node.left, queue, lo, hi);
            return;
        }

        // This key is between lo and hi. Make sure to add it in the correct place, and explore both subtrees.
        inOrderWithComparison(node.left, queue, lo, hi);
        queue.add(node.key);
        inOrderWithComparison(node.right, queue, lo, hi);
    }

    public static void main(String[] args) {
        RedBlackTree<Integer, String> tree = new RedBlackTree<>();

        assert tree.isEmpty();

        assert tree.size() == 0;

        tree.put(1, "one");
        tree.put(2, "two");
        tree.put(3, "three");
        tree.put(4, "four");
        tree.put(5, "five");
        tree.put(6, "six");
        tree.put(7, "seven");
        tree.put(8, "eight");
        tree.put(9, "nine");
        tree.put(10, "ten");
        tree.put(11, "eleven");
        tree.put(12, "twelve");

        assert tree.size() == 12;

        assert tree.rank(5) == 4;

        assert tree.min() == 1;

        assert tree.max() == 12;

        assert tree.get(5).equals("five");

        assert tree.contains(5);

        tree.delete(5);

        assert !tree.contains(5);

        assert tree.size() == 11;

        assert tree.floor(5) == 4;

        assert tree.ceiling(5) == 6;

        assert tree.floor(4) == 4;

        assert tree.select(4) == 6;

        tree.deleteMin();
        tree.deleteMax();

        assert tree.size(0, 7) == 5;

        List<Integer> expectedKeys = List.of(2, 3, 4, 6, 7, 8, 9, 10, 11);
        List<Integer> keys = (List) tree.keys();
        for (int i = 0; i < keys.size(); i++)
            assert expectedKeys.get(i).equals(keys.get(i));

        expectedKeys = List.of(3, 4, 6, 7, 8, 9, 10);
        keys = (List) tree.keys(3, 10);
        for (int i = 0; i < keys.size(); i++)
            assert expectedKeys.get(i).equals(keys.get(i));
    }
}
