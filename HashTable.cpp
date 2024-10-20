#include <iostream>
#include <optional>

#define EMPTY -1
#define DELETED -2

// hashtable class
class HashTable {
	private:
		size_t size;
		float load = 0.0;
		float alpha = 0.8;

		int* table;

		// hash function
		size_t hash(int key) {
			return key % size;
		}
		
	public:
		// constructor
		HashTable(size_t size) : size(size) {
			table = new int[size]; // allocate memory for the table
			for (int i = 0; i < size; ++i) table[i] = EMPTY; // mark all slots as empty
		}

		// insert
		void insert(int key) {
			size_t index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < (size + 1) / 2; i++) {
				size_t new_index = (index + i * i) % size;

				// duplicate keys
				if (table[new_index] == key) {
					printf("Duplicate key insertion is not allowed\n"); 
					return;
				}

				// empty slot
				if (table[new_index] == EMPTY) {
					table[new_index] = key;
					load += (float) 1 / size;
					return;
				}
			}

			// printf("Max probing limit reached!\n");
		}

		// delete
		void remove(int key) {
			size_t index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < (size + 1) / 2; i++)	{
				size_t new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					table[new_index] = EMPTY;  // mark slot as empty
					load -= 1.0 / size;
					return;
				}
			}

			// printf("Max probing limit reached!\n");
			printf("Element not found\n");
		}

		// search
		int search(int key) {
			size_t index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < (size + 1) / 2; i++)	{
				size_t new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					return new_index;
				}
			}
			
			// printf("Max probing limit reached!\n");
			return -1;
		}

		// print table
		void printTable() {
			for (size_t i = 0; i < size; i++) {
				if (table[i] != EMPTY) printf("%d ", table[i]);
				else printf("- ");
			}

			printf("\n");
		}

		// destructor
		~HashTable() {
			delete[] table;
		};
};
