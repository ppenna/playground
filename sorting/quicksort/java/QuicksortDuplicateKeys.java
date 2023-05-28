import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

// Quicksort can put all duplicate keys on the same side of the partition. When all keys are equal, ~1/2 N² compares.
// This implementation puts all duplicate keys in place, instead making the algorithm linear when all keys are equal.
public class QuicksortDuplicateKeys {
    // Sorts a list using 3-Way Partition Quicksort:
    public static <E extends Comparable<E>> void sort(List<E> list) {
        // The caller does not need to pass the beginning and end of the list,
        // but quicksort must keep track of pointers.
        int left = 0;
        int right = list.size() - 1;
        quicksort(list, left, right);
    }

    // Recursive sorting method.
    private static <E extends Comparable<E>> void quicksort(List<E> list, int left, int right) {
        // Base case for recursion. Insertion sort can be used instead after a cutoff for ~10-20% gains.
        if (left >= right) return;

        // There are many strategies to choose a pivot. We're going with a single random one.
        int pivot = chooseRandomPivot(left, right);

        // Every element between the indexes is the same, so they're all sorted.
        int[] partitionIndexes = partition(list, left, right, pivot);

        // Both partition indexes are sorted, so we must only sort up + - 1 from them.
        quicksort(list, left, partitionIndexes[0] - 1);
        quicksort(list, partitionIndexes[1] + 1, right);
    }

    // Chooses a pivot randomly. Could instead choose a median of random indexes, or a deterministic index.
    private static int chooseRandomPivot(int lowerBound, int upperBound) {
        // This method's upperbound is not inclusive, so we must add 1.
        return ThreadLocalRandom.current().nextInt(lowerBound, upperBound + 1);
    }

    // Partitions the list, so everything to the left is smaller than the pivot, everything to the right is greater
    // than the pivot, and everything in between is a duplicate of the pivot.
    private static <E extends Comparable<E>> int[] partition(List<E> list, int left, int right, int pivot) {
        // Puts the pivot at the beginning of the subarray.
        swap(list, left, pivot);
        E pivotElement = list.get(left);
        int i = left + 1;

        // Every case either increments 'i' or decrements 'right', making this linear.
        while (i <= right) {
            int compare = list.get(i).compareTo(pivotElement);

            // Smaller elements are sent to the left side.
            // Note the pivot might be sent to the middle of the list,
            // but in that case the element at left++ is a duplicate.
            if (compare < 0) swap(list, i++, left++);

            // Greater elements are sent to the right side.
            // Note 'i' is not incremented, because the element at 'i' is a new one never seen before.
            else if (compare > 0) swap(list, i, right--);

            // Duplicate elements are left where they are, and only swapped if new smaller elements show up later.
            else i++;
        }

        int[] partitionIndexes = new int[2];

        // Points to the first occurrence of the pivot.
        partitionIndexes[0] = left;

        // Points to the last occurrence of the pivot.
        partitionIndexes[1] = right;

        return partitionIndexes;
    }

    private static <E extends Comparable<E>> void swap (List<E> list, int i, int j) {
        E temp = list.get(i);
        list.set(i, list.get(j));
        list.set(j, temp);
    }

    private static List<Integer> createRandomIntegerArrayList(int size, int lowerBound, int upperBound) {
        List<Integer> list = new ArrayList<>(size);
        // Upper bound isn't usually inclusive, so add 1
        upperBound++;

        for (int i = 0; i < size; i++)
            list.add(ThreadLocalRandom.current().nextInt(lowerBound, upperBound));

        return list;
    }

    private static <E extends Comparable<E>> boolean isSorted(List<E> list) {
        for (int i = 1; i < list.size(); i++)
            if (list.get(i).compareTo(list.get(i - 1)) < 0) return false;
        return true;
    }

    // Prints before and after, and times the test.
    private static void test(int size, int lowerBound, int upperBound) {
        int MICROSECS_PER_NANOSECS = 1000;
        List<Integer> randomList = createRandomIntegerArrayList(size, lowerBound, upperBound);

        System.out.println("Random List:\n" + randomList);

        long start = System.nanoTime();
        sort(randomList);
        long end = System.nanoTime();

        assert isSorted(randomList);

        System.out.println("Sorted List:\n" + randomList);

        System.out.println("Time taken: " + (end - start) / MICROSECS_PER_NANOSECS + " us");
    }

    // Reads args and runs test
    public static void main(String[] args) {
        int size = 10;
        int lowerBound = 0;
        int upperBound = 99;

        // Optional parameter: size of the list, range of values
        if (args.length > 0) {
            try {
                size = Integer.parseInt(args[0]);
                if (size < 1)
                    throw new NumberFormatException();
            } catch (NumberFormatException e) {
                System.out.println("Error parsing the argument: enter a positive integer, or no arguments for the default 10 value.");
                System.exit(1);
            }
        }

        if (args.length == 3) {
            try {
                lowerBound = Integer.parseInt(args[1]);
                upperBound = Integer.parseInt(args[2]);
            } catch (NumberFormatException e) {
                System.out.println("Error parsing the bounds: enter integers, or no arguments for the default 0 and 99 bounds.");
                System.exit(2);
            }
        }

        test(size, lowerBound, upperBound);
    }
}
