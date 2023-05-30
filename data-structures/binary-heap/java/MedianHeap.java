/**
 * Dynamic median. Design a data type that supports insert in logarithmic time, find-the-median in constant time, and
 * remove-the-median in logarithmic time. If the number of keys in the data type is even, find/remove the lower median.
 **/
public class MedianHeap <E extends Comparable<E>> {
    // The greater half of the elements are stored in a MinHeap. This grants easy access to the upper median.
    // The smaller half of the elements are stored in a MaxHeap. This grants easy access to the lower median.
    // The MaxHeap's size is <= the MinHeap's size -> both the median or the lower median are always in the MaxHeap.
    private final MinHeap<E> minHeap;
    private final MaxHeap<E> maxHeap;

    public MedianHeap() {
        minHeap = new MinHeap<>();
        maxHeap = new MaxHeap<>();
    }

    public void insert(E e) {
        // If MaxHeap is longer, then we must add to the MinHeap to make them balanced.
        if (maxHeap.size() > minHeap.size()) {
            // Add directly to the MinHeap if it belongs in the greater half of the elements.
            if (e.compareTo(maxHeap.peek()) >= 0) {
                minHeap.insert(e);
                return;
            }

            // It belongs in the lower half, so insert it into the MaxHeap.
            maxHeap.insert(e);

            // To keep it balanced, remove from the MaxHeap and insert into the MinHeap.
            minHeap.insert(maxHeap.deleteMax());
            return;
        }

        // Both heaps have the same size, so we must add to the MaxHeap.
        // Add directly to the MaxHeap if it belongs in the lower half of the elements.
        if (e.compareTo(minHeap.peek()) <= 0) {
            maxHeap.insert(e);
            return;
        }

        // It belongs in the upper half, so insert it into the MinHeap.
        minHeap.insert(e);

        // To keep it balanced, remove from the MinHeap and insert into the MaxHeap.
        maxHeap.insert(minHeap.deleteMin());
    }

    public E findTheMedian() {
        return maxHeap.peek();
    }

    public E removeTheMedian() {
        E median = maxHeap.deleteMax();

        // Maintain the invariant: MaxHeap's size >= MinHeap's size.
        if (maxHeap.size() < minHeap.size())
            maxHeap.insert(minHeap.deleteMin());

        return median;
    }
}
