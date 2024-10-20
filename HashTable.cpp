#include <iostream>
#include <optional>
using namespace std;

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
DECLARE_TYPE_NAME(size_t);
DECLARE_TYPE_NAME(long long);
DECLARE_TYPE_NAME(unsigned int);

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
			printf("Initialize with size %zu ( ", size);

			for (size_t i = 0; i < size; i++) {
				if (table[i] != EMPTY) printf("%lld ", table[i]);
				else printf("- ");
			}

			printf(")\n");
		}

		// insert
		void insert(KEY_T key) {
			printf("Insert -> %lld:", key);
			cout << GET_TYPE_NAME(key) << endl;
		}

		// delete
		void remove(KEY_T key) {
			printf("Remove -> %lld:", key);
			cout << GET_TYPE_NAME(key) << endl;
		}

		// search
		size_t search(KEY_T key) {
			printf("Search -> %lld:", key);
			cout << GET_TYPE_NAME(key) << " | ";
			return 0;
		}

		// print table
		void printTable() {
			printf("Print table\n");
		}

		// destructor
		~HashTable() {
			delete[] table;
		};
};
