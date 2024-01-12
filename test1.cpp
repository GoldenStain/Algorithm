import java.util.List;

public class GenericInsertionSort {
    public static <T extends Comparable<T>> void insertionSort(List<T> list) {
        for (int i = 1; i < list.size(); i++) {
            T current = list.get(i);
            int j = i - 1;

            // Find the position where current should be inserted
            while (j >= 0 && list.get(j).compareTo(current) > 0) {
                list.set(j + 1, list.get(j));
                j--;
            }

            // Insert current at the correct position
            list.set(j + 1, current);
        }
    }

    public static void main(String[] args) {
        // Test with a list of Integers
        List<Integer> intList = new ArrayList<>(Arrays.asList(3, 1, 4, 1, 5, 9));
        insertionSort(intList);
        System.out.println(intList);

        // Test with a list of Strings
        List<String> stringList = new ArrayList<>(Arrays.asList("banana", "apple", "cherry"));
        insertionSort(stringList);
        System.out.println(stringList);
    }
}

import java.util.Comparator;
import java.util.List;

public class GenericInsertionSortWithComparator {
    public static <T> void insertionSort(List<T> list, Comparator<? super T> comparator) {
        for (int i = 1; i < list.size(); i++) {
            T current = list.get(i);
            int j = i - 1;

            // Find the position where current should be inserted
            while (j >= 0 && comparator.compare(list.get(j), current) > 0) {
                list.set(j + 1, list.get(j));
                j--;
            }

            // Insert current at the correct position
            list.set(j + 1, current);
        }
    }

    public static void main(String[] args) {
        // Test with a list of Integers using a lambda expression as the Comparator
        List<Integer> intList = new ArrayList<>(Arrays.asList(3, 1, 4, 1, 5, 9));
        insertionSort(intList, (o1, o2) -> o1.compareTo(o2));
        System.out.println(intList);

        // Test with a list of Strings with custom Comparator
        List<String> stringList = new ArrayList<>(Arrays.asList("banana", "apple", "cherry"));
        insertionSort(stringList, new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                return o1.compareTo(o2);
            }
        });
        System.out.println(stringList);
    }
}
