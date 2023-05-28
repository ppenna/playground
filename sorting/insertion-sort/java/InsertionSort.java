import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class InsertionSort {
    // Sorts a List using Insertion Sort.
    public static <E extends Comparable<E>> void sort(List<E> list) {
        // Element 0 is in its place. Start from element 1:
        for (int i = 1; i < list.size(); i++) {
            int j = i;
            E element = list.get(i);

            // Keep swapping until the element's place is found
            while (j > 0 && element.compareTo(list.get(j - 1)) < 0) {
                list.set(j, list.get(j - 1));
                j--;
            }

            // Assign the element to its place in the subarray
            list.set(j, element);
        }
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
