#pragma once
#include "../containers/HashTable.h"
#include <iostream>
#include <cassert>
#include <string>

void testHashTable()
{
    try {
        // Test 1: Create a HashTable
        HashTable<int, std::string> table;
        std::cout << "Test 1: HashTable creation successful.\n";

        // Test 2: Add elements
        table.add(1, "One");
        table.add(2, "Two");
        table.add(3, "Three");
        std::cout << "Test 2: Elements added successfully.\n";

        // Test 3: Get elements
        assert(table.get(1) == "One");
        assert(table.get(2) == "Two");
        assert(table.get(3) == "Three");
        std::cout << "Test 3: Elements retrieved successfully.\n";

        // Test 4: Contains key
        assert(table.containsKey(1) == true);
        assert(table.containsKey(4) == false);
        std::cout << "Test 4: Key existence check passed.\n";

        // Test 5: Update element
        table.update(1, "Uno");
        assert(table.get(1) == "Uno");
        std::cout << "Test 5: Element update successful.\n";

        // Test 6: Remove element
        table.remove(2);
        assert(table.containsKey(2) == false);
        try {
            table.get(2);
            assert(false); // Should not reach here
        } catch (const std::runtime_error &e) {
            assert(std::string(e.what()) == "Key not in Table");
        }
        std::cout << "Test 6: Element removal successful.\n";

        // Test 7: Rehashing
        for (int i = 4; i <= 20; i++) {
            table.add(i, "Value" + std::to_string(i));
        }
        assert(table.getCount() == 19); // Including previously added elements
        assert(table.get(20) == "Value20");
        std::cout << "Test 7: Rehashing successful.\n";

        // Test 8: Iterator functionality
        auto iterator = table.getIterator();
        int iteratedCount = 0;
        while (iterator->moveNext()) {
            std::cout << "Key: " << iterator->getCurrentKey()
                      << ", Value: " << iterator->getCurrentValue() << std::endl;
            iteratedCount++;
        }
        assert(iteratedCount == table.getCount());
        std::cout << "Test 8: Iterator functionality successful.\n";

        std::cout << "All tests passed!\n";

    } catch (const std::exception &e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
    }
}
