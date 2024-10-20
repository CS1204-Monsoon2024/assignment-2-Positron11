#include <iostream>
#include <optional>

// hashtable class
class HashTable {
	private:
		int size;
		float load = 0.0;
		float alpha = 0.8;

		std::optional<int>* table;

		// hash function
		int hash(int key) {
			return key % size;
		}
		
	public:
		// constructor
		HashTable(int size) : size(size) {
			table = new std::optional<int>[size]; // allocate memory for the table
			for (int i = 0; i < size; ++i) table[i] = std::nullopt; // mark all slots as empty
		}

		// insert
		void insert(int key) {
			int index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < (size + 1) / 2; i++) {
				int new_index = (index + i * i) % size;

				// duplicate keys
				if (table[new_index] == key) {
					printf("Duplicate key insertion is not allowed\n"); 
					return;
				}

				// empty slot
				if (!table[new_index].has_value()) {
					table[new_index] = key;
					load += (float) 1 / size;
					return;
				}
			}

			printf("Max probing limit reached!");
		}

		// delete
		void remove(int key) {
			int index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < (size + 1) / 2; i++)	{
				int new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					table[new_index] = std::nullopt;  // mark slot as empty
					load -= 1.0 / size;
					return;
				}
			}

			printf("Max probing limit reached!\n");
			printf("Element not found\n");
		}

		// search
		int search(int key) {
			int index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < (size + 1) / 2; i++)	{
				int new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					return new_index;
				}
			}
			
			printf("Max probing limit reached!\n");
			return -1;
		}

		// print table
		void printTable() {
			for (size_t i = 0; i < size; i++) {
				if (table[i].has_value()) printf("%d ", table[i]);
				else printf("- ");
			}
		}

		// destructor
		~HashTable() {
			delete[] table;
		};
};
