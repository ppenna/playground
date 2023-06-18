import java.util.NoSuchElementException;

// An efficient data type to get the maximum element.
public class MaxHeap <E extends Comparable<E>> {
    // The heap is implemented as an array instead of a tree with nodes.
    private final int DEFAULT_CAPACITY = 8;
    private final int RESIZING_FACTOR = 2;
    private E[] heap;
    private int size;

    // Creating a heap adding n elements, one at a time, has n log n time complexity.
    public MaxHeap () {
        heap = (E[]) new Comparable[DEFAULT_CAPACITY];
        size = 0;
        heap[0] = null;
    }

    // Creating a heap out of an array is more efficient, with only linear time complexity.
    public MaxHeap (E[] array) {
        size = array.length;
        // Creates the heap with capacity for the entire array.
        // If insert operations are expected, then 2 * size is better.
        heap = (E[]) new Comparable[size + 1];
        System.arraycopy(array, 0, heap, 1, size);
        heap[0] = null;

        // Starting from the parent of the last element, going through all parents, perform sink operations.
        // This ensures no element is smaller than its children.
        for (int i = size / 2; i >= 1; i--)
            sink(i);
    }

    // Inserts an element and maintains the heap invariant.
    public void insert(E e) {
        // Resizes the array, if it lacks capacity.
        if (size + 1 == heap.length)
            resize(size * RESIZING_FACTOR);

        // Inserts the element at the end of the heap.
        heap[++size] = e;

        // Swims the element up to maintain the heap invariant.
        swim(size);
    }

    // Removes the first element of the heap and returns it, maintaining the heap invariant. Resizes the heap if it's sparse.
    public E deleteMax() {
        // Cannot delete from an empty heap.
        if (isEmpty())
            throw new NoSuchElementException();

        // Stores the element/
        E max = heap[1];

        // Puts the last element of the heap in the first place.
        swap(1, size);

        // Removes the max element.
        heap[size--] = null;

        // Sinks the former element to maintain the heap invariant.
        sink(1);

        // Resizes the array if it's less than 25% full.
        if (4 * size < heap.length && size > 1)
            resize(size * RESIZING_FACTOR);

        // Returns the max element.
        return max;
    }

    // Returns the max element without removing it.
    public E peek() {
        // Cannot peek into an empty heap.
        if (isEmpty())
            throw new NoSuchElementException();

        return heap[1];
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

    // Ensures an element is either greater than its parent, or it is the root.
    private void swim(int index) {
        int parentIndex = index / 2;

        while (parentIndex > 0 && less(parentIndex, index)) {
            swap(index, parentIndex);
            index = parentIndex;
            parentIndex /= 2;
        }
    }

    // Ensures an element is greater than its children, or it is a leaf.
    private void sink(int index) {
        // Gets the left child of the node.
        int child = 2 * index;

        while (child <= size) {
            // Gets the greater of the two children, or the left if they're the same.
            if (child < size && less(child, child + 1))
                child++;

            // Stops when both children are smaller than the element.
            if (!less(index, child))
                break;

            swap(index, child);

            // Now the element occupies the child's node in the tree.
            index = child;

            // Updates to the current node's left child.
            child *= 2;
        }
    }

    private void swap(int i, int j) {
        E temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    private boolean less(int i, int j) {
        return heap[i].compareTo(heap[j]) < 0;
    }

    private void resize(int capacity) {
        E[] newHeap = (E[]) new Comparable[capacity];
        System.arraycopy(heap, 0, newHeap, 0, size + 1);
        heap = newHeap;
    }

    // Tests for correctness.
    public static void main(String[] args) {
        MaxHeap<Integer> maxHeap = new MaxHeap<>();

        // Populates the heap.
        for (int i = 0; i < 10; i++)
            maxHeap.insert(i);

        // Expected: 9, 8, 7, 6, 5, 4, 3, 2, 1, 0.
        for (int i = 0; i < 10; i++)
            assert maxHeap.deleteMax().equals(9 - i);
    }
}
