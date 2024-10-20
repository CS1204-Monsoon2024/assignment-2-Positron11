#include <iostream>
#include <optional>

#define KEY_T long long
#define EMPTY -1

// hashtable class
class HashTable {
	private:
		size_t size;
		float load = 0.0;
		float alpha = 0.8;

		KEY_T* table;

		// hash function
		size_t hash(KEY_T key) {
			return key % size;
		}
		
	public:
		// constructor
		HashTable(size_t size) : size(size) {
			table = new KEY_T[size]; // allocate memory for the table
			for (size_t i = 0; i < size; ++i) table[i] = EMPTY; // mark all slots as empty
		}

		// insert
		void insert(KEY_T key) {
			printf("Insert: (%lld\n)", key);
		}

		// delete
		void remove(KEY_T key) {
			printf("Remove: (%lld\n)", key);
		}

		// search
		size_t search(KEY_T key) {
			printf("Search: (%lld\n)", key);
		}

		// print table
		void printTable() {
			printf("Print table");
		}

		// destructor
		~HashTable() {
			delete[] table;
		};
};
