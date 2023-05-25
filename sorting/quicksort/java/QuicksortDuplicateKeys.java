import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

// Quicksort can put all duplicate keys on the same side of the partition. When all keys are equal, ~1/2 N² compares.
// This implementation puts all duplicate keys in place, instead making the algorithm linear when all keys are equal.
public class QuicksortDuplicateKeys {
    // The caller does not neet to pass the beginning and end of the list,
    // but quicksort must keep track of pointers.
    public static <E extends Comparable> void sort(List<E> list) {
        int left = 0;
        int right = list.size() - 1;
        quicksort(list, left, right);
    }

    private static <E extends Comparable> void quicksort(List<E> list, int left, int right) {
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

    private static int chooseRandomPivot(int lowerBound, int upperBound) {
        // This method's upperbound is not inclusive, so we must add 1.
        return ThreadLocalRandom.current().nextInt(lowerBound, upperBound + 1);
    }

    private static <E extends Comparable> int[] partition(List<E> list, int left, int right, int pivot) {
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

    private static <E extends Comparable> void swap (List<E> list, int i, int j) {
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

    private static <E extends Comparable> boolean isSorted(List<E> list) {
        for (int i = 1; i < list.size(); i++)
            if (list.get(i).compareTo(list.get(i - 1)) < 0) return false;
        return true;
    }

    private static void test(int size, int lowerBound, int upperBound) {
        List<Integer> randomList = createRandomIntegerArrayList(size, lowerBound, upperBound);

        System.out.println("Random List:\n" + randomList);

        long start = System.nanoTime();
        sort(randomList);
        long end = System.nanoTime();

        assert isSorted(randomList);

        System.out.println("Sorted List:\n" + randomList);

        System.out.println("Time taken: " + (end - start) / 1000 + " us");
    }

    public static void main(String[] args) {
        Integer size = 10;
        Integer lowerBound = 0;
        Integer upperBound = 99;

        // Optional parameter: size of the list, range of values
        if (args.length > 0) {
            try {
                size = Integer.parseInt(args[0]);
                if (size < 1) {
                    size = 10;
                    throw new NumberFormatException();
                }
            } catch (NumberFormatException e) {
                System.out.println("Error parsing the argument: enter a positive integer.\nCreating a list with 10 integers.");
            }
        }

        if (args.length == 3) {
            try {
                lowerBound = Integer.parseInt(args[1]);
                upperBound = Integer.parseInt(args[2]);
            } catch (NumberFormatException e) {
                lowerBound = 0;
                System.out.println("Error parsing the bounds.\nLower bound: 0; Upper bound: 99.");
            }
        }

        test(size, lowerBound, upperBound);
    }
}
