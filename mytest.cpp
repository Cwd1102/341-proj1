#include "csr.h"

class Tester {
public:
	bool testCompress(int row, int cols, int nums[], int size) {
		CSR test;
		test.compress(row, cols, nums, size);
		bool isEmpty = false;

		for (int i = 0; i < size; i++) {
			if (nums[i] != 0) {
				isEmpty = true;
			}
		}

		if (test.empty()) {
			return false;
		}

		if (!isEmpty) {
			int colSize = sizeof(*test.m_col_index) / sizeof(int);
			int rowSize = sizeof(*test.m_row_index) / sizeof(int);
			int valueSize = sizeof(*test.m_values) / sizeof(int);
		
			for (int i = 0; i < colSize; i++) {
				if (test.m_col_index[i] != 0) {
					return false;
				}
			}
			for (int i = 0; i < rowSize; i++) {
				if (test.m_row_index[i] != 0) {
					return false;
				}
			}
			for (int i = 0; i < valueSize; i++) {
				if (test.m_values[i] != 0) {
					return false;
				}
			}
		}

		if ((row * cols) < size) {
			if (test.m_col_index[test.m_nonzeros] != 0) {
				return false;
			}
		
		}

		if ((row * cols) > size) {
			if (test.m_row_index[row] == 0) {
				return false;
			}
		
		}
		return true;
	
	}

	bool testOverload(int row, int cols, int nums[], int size) {
		CSR test;
		test.compress(row, cols, nums, size);
		CSR test3(test);

		if (!(test == test3)) {
			return false;
		}
		return true;
	}

	bool testGetAt(int row, int cols, int nums[], int size) {
		CSR test;
		test.compress(row, cols, nums, size);
		int nonZeros = 0;
		int colNum = 0;
		int rowNum = 0;

		
		if ((row * cols) == 0) {
			if (test.getAt(size / 2, size / 2) != 0) {
				return false;
			}

		}
		else {

			for (int i = 0; i < size; i++) {
				if (nums[i] != 0) {
					if (test.getAt(rowNum, colNum) == nums[i]) {
						return true;
					}
					else {
						return false;
					}

				}
				
				colNum++;

				if (colNum == cols) {
					colNum = 0;
					rowNum++;
				}


			}
		}
	}

	bool testOverloaded() {
		int array1[] = { 0,10,0,20,0,0,30,40,0,0,50,0,60,0,70,80 };
		int array2[] = {0,0,100,0,200,0,300,0,0,400,500,0};
		CSR list1;
		CSR list2;
		list1.compress(4, 4, array1, 16);
		list2.compress(3, 4, array2, 12);
		CSRList test;
		test.insertAtHead(list1);
		test.insertAtHead(list2);
		CSRList test1(test);

		if (!(test == test1)) {
			return false;
		}

		CSRList test2;
		CSRList test3(test1);
		if (!(test1 == test3)) {
			return false;
		}

	}
private:

};

int main() {
	Tester test1;
	int array1[16]{ 0 };
	int array2[] = { 10,20,0,30,40,0,0,50,60,70,0,80 };


	if (test1.testCompress(4, 4, array1, 16)) {
	}
	else {
		cout << "Test compress error case failed" << endl;
	}
	if (test1.testCompress(3, 4, array2, 12)) {
	}
	else {
		cout << "Test compress normal case failed" << endl;
	}
	if (!test1.testCompress(0, 0, array2, 12)) {
	}
	else {
		cout << "Test compress error case failed" << endl;
	}
	int array3[]{ 0,20,40,0,0,60,0,80,100,0,120,0 };

	if (test1.testOverload(3, 4, array3, 12)) {
	}
	else {
		cout << "Test overloaded  normal copy constructor failed" << endl;
	}
	if (test1.testOverload(3, 3, array3, 12)) {
	}
	else {
		cout << "Test overloaded error copy constructor failed" << endl;
	}
	if (test1.testOverload(0, 0, array3, 12)) {
	}
	else {
		cout << "Test overloaded error copy constructor failed" << endl;
	}
	if (test1.testOverload(5, 4, array3, 12)) {
	}
	else {
		cout << "Test overloaded error copy constructor failed" << endl;
	}

	try {
		test1.testGetAt(3, 4, array3, 12);
	}
	catch (runtime_error& e) {
		cout << "Test getat error failed" << endl;
	}

	try {
		test1.testGetAt(0, 0, array3, 12);
		cout << "Test getat error failed" << endl;
	}
	catch (runtime_error& e) {
		cout << "getAt threw exception, Passed" << endl;
	}

	if (test1.testOverloaded()) {
	}
	else {
		cout << "test overloaded failed" << endl;
	}



	cout << "Testing Complete" << endl;
	return 0;
}