// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"
///////////////CSR Class Implementation///////////////
CSR::CSR() {
    int* m_values = nullptr;       //array to store non-zero values
    int* m_col_index = nullptr;    //array to store column indices
    int* m_row_index = nullptr;    //array to store row indices 
    int m_nonzeros = 0;              //number of non-zero values
    int m_m = 0;                    //number of rows
    int m_n = 0;                    //number of columns
    CSR * m_next = nullptr;        //pointer to the next CSR object in linked list
}
CSR::~CSR() {
    delete[] m_col_index;
    delete[] m_row_index;
    delete[] m_values;
}
CSR::CSR(const CSR& rhs) {
    int m_nonzeros = rhs.m_nonzeros;      //number of non-zero values
    int m_m = rhs.m_m;                    //number of rows
    int m_n = rhs.m_n;                    //number of columns
    int* m_values = new int[m_nonzeros] {};
    int* m_col_index = new int[m_nonzeros] {};
    int* m_row_index = new int[sizeof(m_row_index) / sizeof(int)] {0};    //array to store row indices 
    CSR* m_next = nullptr;         //pointer to the next CSR object in linked list

    for (int i = 0; i < m_nonzeros; i++) {
        m_values[i] = rhs.m_values[i];    //array to store non-zero values
    }     

    for (int i = 0; i < m_nonzeros; i++) {
        m_col_index[i] = rhs.m_col_index[i]; //array to store column indices
    }

    for (int i = 0; i < (sizeof(*m_row_index) / sizeof(int)); i++) {
        m_row_index[i] = m_row_index[i];
    }


}
void CSR::clear() {
    delete[] m_col_index;
    delete[] m_row_index;
    delete[] m_values;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_values = nullptr;
}
bool CSR::empty() const {
    if ((m_col_index == nullptr)&&(m_row_index == nullptr)&&(m_values == nullptr)) {
        return true;
    }
    return false;
}
void CSR::compress(int m, int n, int array[], int arraySize) {
    int m_valuesCounter = 0;
    if ((m * n) == arraySize) {
        //VARABLE INIT
        if (m_col_index == nullptr) {
            m_col_index = new int[n] {0};
        }
        else {
            cout << "m_col_index already inited." << endl;
        }

        for (int i = 0; i < arraySize; i++) {
            if (array[i] != 0) {
                m_nonzeros++;
            }
        }

        if (m_row_index == nullptr) {
            m_row_index = new int[m_nonzeros] {0};
        }
        else {
            cout << "m_row_index already inited." << endl;
        }
        
        //POPULATING ARRAY
        if (m_values == nullptr) {
            m_values = new int[m_nonzeros] {};
            int colCounter = 0;
            int colIndex = 0;
            int rowIndex = 1;
            int numLoops = 0;

            if ((m * n) == arraySize) {
                numLoops = arraySize;
            }
            else if ((m * n) < arraySize) { // if matrix size is less than arraysize
                numLoops = (m * n);
            }
            else if ((m * n) > arraySize) { // if matrix size is greater than arraysize
                numLoops = arraySize;
            }

        
            for (int i = 0; i < numLoops; i++) {
                if (array[i] != 0) {
                    m_col_index[colIndex] = colCounter;
                    m_row_index[rowIndex]++;
                    m_values[colIndex] = array[i];
                    colIndex++;

                }
                colCounter++;

                if (colCounter > n - 1) {
                    colCounter = 0;
                    m_row_index[rowIndex + 1] = m_row_index[rowIndex];
                    rowIndex++;

                }
            }
        }
        
        /*
        if (m_values == nullptr) {
            int colIndex = 0;
            int rowIndex = 1;

            m_values = new int[m_nonzeros] {};
            for (int i = 0; i < arraySize; i++) {
                if (array[i] != 0) {
                    m_values[m_valuesCounter] = array[i];
                    m_col_index[colIndex] = colCounter;
                    m_row_index[rowIndex]++;
                    colIndex++;
                    m_valuesCounter++;
                }

                colCounter++;
                if (colCounter > (n - 1)) {
                    colCounter = 0;
                    m_row_index[rowIndex + 1] = m_row_index[rowIndex];
                    rowIndex++;
                }
            }
        }
        */
        //*****DEBUG BELOW*******
        
        cout << "Cols" << endl;
        for (int i = 0; i < m_nonzeros; i++) {
            cout << m_col_index[i] << " ";

        }
        cout << "\nrows" << endl;

        for (int i = 0; i < m + 1; i++) {
            cout << m_row_index[i] << " ";
        }
        cout << endl;
        //******DEBUG ABOVE***********
    }
    else {
        if ((m == 0)&&(n == 0)) {
            m_col_index = new int[0];
            m_row_index = new int[0];
            m_nonzeros = 0;

        }
    }
}
int CSR::getAt(int row, int  col) const {
    int colIndex = 0;
    int numInRow = 0;

    for (int i = 1; i < m_n ; i++) {
        if (row == i) {
            numInRow = m_row_index[i + 1] - colIndex;
            for (int j = 0; j < numInRow; j++) {
                if (m_col_index[(colIndex - 1) + j] == col) {
                    return m_values[(colIndex - 1) + j];
                }
            }

        }
        colIndex = m_row_index[i];
        
    }

    return 0;
}
bool CSR::operator==(const CSR& rhs) const {

    if (m_nonzeros != rhs.m_nonzeros) {
        return false;
    }
    
    if (m_m != rhs.m_m) {
        return false;
    }

    if (m_n != rhs.m_n) {
        return false;
    }

    for (int i = 0; i < m_nonzeros; i++) {
        if (m_values[i] != rhs.m_values[i]) {
            return false;
        }
    }

    for (int i = 0; i < m_nonzeros; i++) {
        if (m_col_index[i] != rhs.m_col_index[i]) {
            return false;
        }
    }

    for (int i = 0; i < sizeof(*m_row_index) / sizeof(int); i++) {
        if (m_row_index[i] != rhs.m_row_index[i]) {
            return false;
        }

    }

    return true;
}
int CSR::sparseRatio() {
    float temp = ((m_m * m_n) - m_nonzeros) / (m_m * m_n);

    return (int)(temp * 100);
}
void CSR::dump() {
    cout << endl;
    if (!empty()) {
        for (int i = 0; i < m_nonzeros; i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i = 0; i < m_nonzeros; i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i = 0; i < m_m + 1; i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

//////////////CSRList Class Implementation///////////////
CSRList::CSRList() {
    m_head = nullptr;
    m_size = 0;
}
CSRList::CSRList(const CSRList& rhs) {

}
CSRList::~CSRList() {

}
bool CSRList::empty() const {
    return true;
}
void CSRList::insertAtHead(const CSR& matrix) {
    CSR copy = matrix;

    if (m_head == nullptr) {
        m_head = &copy;
    }
    else {
        copy.m_next = m_head;
        m_head = &copy;
    }
}
void CSRList::clear() {

}

int CSRList::getAt(int CSRIndex, int row, int col) const {
    return -1;
}
bool CSRList::operator== (const CSRList& rhs) const {
    return true;
}
const CSRList& CSRList::operator=(const CSRList& rhs) {
    return *this;
}
int CSRList::averageSparseRatio() {
    return -1;
}
void CSRList::dump() {
    if (!empty()) {
        CSR* temp = m_head;
        while (temp != nullptr) {
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        cout << "Error: List is empty!" << endl;
}