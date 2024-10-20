#include <iostream>
#include <optional>

typedef int key_t;

// hashtable class
class HashTable {
	private:
		int size;

		std::optional<key_t>* table;

		// hash function
		int hash(key_t key) {
			return key % size;
		}
		
	public:
		// constructor
		HashTable(int size) : size(size) {
			table = new std::optional<key_t>[size]; // allocate memory for the table
			for (int i = 0; i < size; ++i) table[i] = std::nullopt; // mark all slots as empty
		}

		// copy constructor
		HashTable(const HashTable& other) : size(other.size) {
			table = new std::optional<key_t>[size];
			for (int i = 0; i < size; ++i) table[i] = other.table[i];
		}

		// copy assignment operator
		HashTable& operator=(const HashTable& other) {
			if (this != &other) {
				delete[] table;
				size = other.size;
				table = new std::optional<key_t>[size];
				for (int i = 0; i < size; ++i) table[i] = other.table[i];
			}

			return *this;
		}

		// insert
		void insert(key_t key) {
			int index = hash(key);

			// quadratic probing
			for (int i = 0; i < size; i++) {
				int new_index = (index + i * i) % size;

				// duplicate keys
				if (table[new_index] == key) {
					printf("Duplicate key insertion is not allowed\n"); 
					return;
				}

				// empty slot
				if (!table[new_index].has_value()) {
					table[new_index] = key;
					return;
				}
			}

			// printf("Max probing limit reached!\n");
		}

		// delete
		void remove(key_t key) {
			int index = hash(key);

			// quadratic probing
			for (int i = 0; i < size; i++)	{
				int new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					table[new_index] = std::nullopt;  // mark slot as empty
					return;
				}
			}

			// printf("Max probing limit reached!\n");
			printf("Element not found\n");
		}

		// search
		int search(key_t key) {
			int index = hash(key);

			// quadratic probing
			for (int i = 0; i < size; i++)	{
				int new_index = (index + i * i) % size;

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
			for (int i = 0; i < size; i++) {
				if (table[i].has_value()) printf("%d ", table[i]);
				else printf("- ");
			}

			printf("\n");
		}

		// destructor
		~HashTable() {
			delete[] table;
		};
};
