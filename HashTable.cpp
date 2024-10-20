#include <iostream>
#include <optional>

#define KEY_T int
#define EMPTY -1

template <typename T> class type_name {
public:
    static const char *name;
};

#define DECLARE_TYPE_NAME(x) template<> const char *type_name<x>::name = #x;
#define GET_TYPE_NAME(x) (type_name<typeof(x)>::name)

DECLARE_TYPE_NAME(int);
DECLARE_TYPE_NAME(long);
DECLARE_TYPE_NAME(int);
DECLARE_TYPE_NAME(long long);
DECLARE_TYPE_NAME(unsigned int);


// hashtable class
class HashTable {
	private:
		int size;

		KEY_T* table;

		// hash function
		int hash(KEY_T key) {
			return key % size;
		}
		
	public:
		// constructor
		HashTable(int size) : size(size) {
			table = new KEY_T[size]; // allocate memory for the table
			for (int i = 0; i < size; ++i) table[i] = EMPTY; // mark all slots as empty

			printf("Initialize -> size=%zu\n", size);
			printTable();
		}

		// insert
		void insert(KEY_T key) {
			int index = hash(key);

			printf("Insert -> key=%d:%s\n", key, GET_TYPE_NAME(key));

			// quadratic probing
			for (int i = 0; i < size; i++) {
				int new_index = (index + i * i) % size;

				// duplicate keys
				if (table[new_index] == key) {
					printf("Duplicate key insertion is not allowed\n"); 
					return;
				}

				// empty slot
				if (table[new_index] == EMPTY) {
					table[new_index] = key;
					return;
				}
			}

			// printf("Max probing limit reached!\n");
		}

		// delete
		void remove(KEY_T key) {
			int index = hash(key);

			printf("Remove -> key=%d:%s\n", key, GET_TYPE_NAME(key));

			// quadratic probing
			for (int i = 0; i < size; i++)	{
				int new_index = (index + i * i) % size;

				// key found
				if (table[new_index] == key) {
					table[new_index] = EMPTY;  // mark slot as empty
					return;
				}
			}

			// printf("Max probing limit reached!\n");
			printf("Element not found\n");
		}

		// search
		int search(KEY_T key) {
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
			printf("Print -> ");
			
			for (int i = 0; i < size; i++) {
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
