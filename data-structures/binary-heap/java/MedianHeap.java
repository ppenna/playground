import java.util.Comparator;

/**
 * Dynamic median. Design a data type that supports insert in logarithmic time, find-the-median in constant time, and
 * remove-the-median in logarithmic time. If the number of keys in the data type is even, find/remove the lower median.
 **/
public class MedianHeap <E extends Comparable<E>> {
    // The greater half of the elements are stored in a MinHeap. This grants easy access to the upper median.
    // The smaller half of the elements are stored in a MaxHeap. This grants easy access to the lower median.
    // The MaxHeap's size is <= the MinHeap's size -> both the median or the lower median are always in the MaxHeap.
    private final BinaryHeap<E> minHeap;
    private final BinaryHeap<E> maxHeap;

    public MedianHeap() {
        minHeap = new BinaryHeap<E>(Comparator.reverseOrder());
        maxHeap = new BinaryHeap<E>(Comparator.naturalOrder());
    }

    public void insert(E e) {
        if (maxHeap.isEmpty()) {
            maxHeap.insert(e);
            return;
        }

        if (minHeap.isEmpty()) {
            maxHeap.insert(e);
            minHeap.insert(maxHeap.deleteRoot());
            return;
        }

        // If it's greater than the median, store it in the min heap.
        if (e.compareTo(findTheMedian()) > 0)
            minHeap.insert(e);
        // Since it's less than the median, store it in the max heap.
        else
            maxHeap.insert(e);

        // Maintain the invariants:
        //  . Both heaps are balanced with each other;
        //  . MaxHeap may have 1 more element.
        if (minHeap.size() > maxHeap.size())
            maxHeap.insert(minHeap.deleteRoot());
        else if (maxHeap.size() > minHeap.size() + 1)
            minHeap.insert(maxHeap.deleteRoot());
    }

    public E findTheMedian() {
        return maxHeap.peek();
    }

    public E removeTheMedian() {
        E median = maxHeap.deleteRoot();

        // Maintain the invariant: MaxHeap's size >= MinHeap's size.
        if (maxHeap.size() < minHeap.size())
            maxHeap.insert(minHeap.deleteRoot());

        return median;
    }

    // Tests for correctness.
    public static void main(String[] args) {
        MedianHeap<Integer> medianHeap = new MedianHeap<>();

        // Populates the heap.
        for (int i = 0; i < 10; i++)
            medianHeap.insert(i);

        // Expected: 4 5 3 6 2 7 1 8 0 9.
        Integer[] expectedOutput = {4, 5, 3, 6, 2, 7, 1, 8, 0, 9};

        for (int i = 0; i < 10; i++)
            assert medianHeap.removeTheMedian().equals(expectedOutput[i]);
    }
}
