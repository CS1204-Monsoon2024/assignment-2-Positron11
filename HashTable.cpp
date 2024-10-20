#include <iostream>
#include <optional>
#include <math.h>

#define EMPTY -1
#define DELETED -2

typedef int key_t;

// prime checker helper function
bool isPrime(int x) {
	for (size_t i = 2; i <= (int) std::sqrt(x); i++) {
		if (x % i == 0) return false;
	}

	return true;	
}

// next prime helper function
int nextPrime(int x) {
	while (!isPrime(x)) x++;
	return x;
}

// hashtable class
class HashTable {
	private:
		int size;
		float load = 0.0;
		float alpha = 0.8;

		std::optional<key_t>* table;

		// hash function
		int hash(key_t key) {
			return key % size;
		}

		// resize table
		void resize() {
			HashTable ht(nextPrime(size * 2));

			// re-insert all existing keys into new table
			for (size_t i = 0; i < size; ++i) {
				if (table[i].has_value()) ht.insert(table[i].value());
			}

			*this = std::move(ht); // swap data
		}
		
	public:
		// constructor
		HashTable(int size) : size(size) {
			table = new std::optional<key_t>[size]; // allocate memory for the table
			for (size_t i = 0; i < size; ++i) table[i] = std::nullopt; // mark all slots as empty
		}

		// copy constructor
		HashTable(const HashTable& other) : size(other.size) {
			load = other.load;

			table = new std::optional<key_t>[size];
			for (size_t i = 0; i < size; ++i) table[i] = other.table[i];
		}

		// copy assignment constructor
		HashTable& operator=(const HashTable& other) {
			delete[] table;

			size = other.size;
			load = other.load;

			table = new std::optional<key_t>[size];
			for (size_t i = 0; i < size; ++i) table[i] = other.table[i];

			return *this;
		}

		float getLoad() {
			return load;
		}

		// insert
		void insert(key_t key) {
			size_t index = hash(key);

			if (load > alpha) resize();

			// quadratic probing
			for (size_t i = 0; i < size; i++) {
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
		}

		// delete
		void remove(key_t key) {
			size_t index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < size; i++)	{
				int new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					table[new_index] = std::nullopt;  // mark slot as empty
					load -= (float) 1 / size;
					return;
				}
			}

			printf("Element not found\n");
		}

		// search
		int search(key_t key) {
			size_t index = hash(key);

			// quadratic probing
			for (size_t i = 0; i < size; i++)	{
				int new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					return new_index;
				}
			}
			
			return -1;
		}

		// print table
		void printTable() {			
			for (size_t i = 0; i < size; i++) {
				if (table[i].has_value()) printf("%d ", table[i].value());
				else printf("- ");
			}

			printf("\n");
		}

		// destructor
		~HashTable() {
			delete[] table;
		};
};
