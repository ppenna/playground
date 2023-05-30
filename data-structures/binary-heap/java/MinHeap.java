import java.util.NoSuchElementException;

// An efficient data type to get the minimum element.
public class MinHeap <E extends Comparable<E>> {
    // The heap is implemented as an array instead of a tree with nodes.
    private final int DEFAULT_CAPACITY = 8;
    private final int RESIZING_FACTOR = 2;
    private E[] heap;
    private int size;

    // Creating a heap adding n elements, one at a time, has n log n time complexity.
    public MinHeap () {
        heap = (E[]) new Comparable[DEFAULT_CAPACITY];
        size = 0;
        heap[0] = null;
    }

    // Creating a heap out of an array is more efficient, with only linear time complexity.
    public MinHeap (E[] array) {
        size = array.length;
        // Creates the heap with capacity for the entire array.
        // If insert operations are expected, then 2 * size is better.
        heap = (E[]) new Comparable[size + 1];
        System.arraycopy(array, 0, heap, 1, size);
        heap[0] = null;

        // Starting from the parent of the last element, going through all parents, perform sink operations.
        // This ensures no element is greater than its children.
        for (int i = size / 2; i >= 1; i--)
            sink(i);
    }

    // Inserts an element and maintains the heap invariant.
    public void insert(E e) {
        // Resizes the array, if it lacks capacity.
        if (size + 1 == heap.length) resize(size * RESIZING_FACTOR);

        // Inserts the element at the end of the heap.
        heap[++size] = e;

        // Swims the element up to maintain the heap invariant.
        swim(size);
    }

    // Removes the first element of the heap and returns it, maintaining the heap invariant. Resizes the heap if it's sparse.
    public E deleteMin() {
        // Cannot delete from an empty heap.
        if (isEmpty()) throw new NoSuchElementException();

        // Stores the element/
        E min = heap[1];

        // Puts the last element of the heap in the first place.
        swap(1, size);

        // Removes the min element.
        heap[size--] = null;

        // Sinks the former element to maintain the heap invariant.
        sink(1);

        // Resizes the array if it's less than 25% full.
        if (4 * size < heap.length && size > 1)
            resize(size * RESIZING_FACTOR);

        // Returns the min element.
        return min;
    }

    // Returns the min element without removing it.
    public E peek() {
        // Cannot peek into an empty heap.
        if (isEmpty()) throw new NoSuchElementException();

        return heap[1];
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

    // Ensures an element is either smaller than its parent, or it is the root.
    private void swim(int index) {
        int parentIndex = index / 2;

        while (parentIndex > 0 && greater(parentIndex, index)) {
            swap(index, parentIndex);
            index = parentIndex;
            parentIndex /= 2;
        }
    }

    // Ensures an element is smaller than its children, or it is a leaf.
    private void sink(int index) {
        for (int child = 2 * index; child <= size; child *= 2) {

            // Gets the smaller of the two children, or the left if they're the same.
            if (child < size && greater(child, child + 1))
                child++;

            // Stops when both children are greater than the element.
            if (!greater(index, child))
                break;

            swap(index, child);
            index = child;
        }
    }

    private void swap(int i, int j) {
        E temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    private boolean greater(int i, int j) {
        return heap[i].compareTo(heap[j]) > 0;
    }

    private void resize(int capacity) {
        E[] newHeap = (E[]) new Comparable[capacity];
        System.arraycopy(heap, 0, newHeap, 0, size + 1);
        heap = newHeap;
    }

    // Tests for correctness.
    public static void main(String[] args) {
        MinHeap<Integer> minHeap = new MinHeap<>();

        // Populates the heap.
        for (int i = 0; i < 10; i++)
            minHeap.insert(i);

        // Expected: 0 1 2 3 4 5 6 7 8 9.
        for (int i = 0; i < 10; i++)
            System.out.printf("%d ", minHeap.deleteMin());

    }
}
