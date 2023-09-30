// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"
///////////////CSR Class Implementation///////////////
CSR::CSR() {
    m_values = nullptr;       //array to store non-zero values
    m_col_index = nullptr;    //array to store column indices
    m_row_index = nullptr;    //array to store row indices 
    m_nonzeros = 0;              //number of non-zero values
    m_m = 0;                    //number of rows
    m_n = 0;                    //number of columns
    m_next = nullptr;        //pointer to the next CSR object in linked list
}
CSR::~CSR() {
    clear();
}
CSR::CSR(const CSR& rhs) {
    m_nonzeros = rhs.m_nonzeros;      //number of non-zero values
    m_m = rhs.m_m;                    //number of rows
    m_n = rhs.m_n;                    //number of columns
    m_values = new int[m_nonzeros] {0};
    m_col_index = new int[m_nonzeros] {0};
    m_row_index = new int[m_m + 1] {0};    //array to store row indices 

    m_next = nullptr;         //pointer to the next CSR object in linked list

    for (int i = 0; i < m_nonzeros; i++) {
        m_values[i] = rhs.m_values[i];    //array to store non-zero values
    }     

    for (int i = 0; i < m_nonzeros; i++) {
        m_col_index[i] = rhs.m_col_index[i]; //array to store column indices
    }

    for (int i = 0; i < rhs.m_m + 1; i++) {
        m_row_index[i] = rhs.m_row_index[i];
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
    m_m = m;
    m_n = n;

    int m_valuesCounter = 0;
    if ((m * n) == arraySize) {
        //VARABLE INIT


        for (int i = 0; i < arraySize; i++) {
            if (array[i] != 0) {
                m_nonzeros++;
            }
        }

        if (m_col_index == nullptr) {
            m_col_index = new int[m_nonzeros] {0};
        }
        else {
            cout << "m_col_index already inited." << endl;
        }

        if (m_row_index == nullptr) {
            m_row_index = new int[m_m + 1] {0};
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

            for (int i = 0; i < arraySize; i++) {
                if (array[i] != 0) {
                    m_col_index[colCounter] = i % m_n;
                    m_values[colCounter] = array[i];
                    colCounter++;
                    m_row_index[rowIndex]++;

                }
                colIndex++;

                if (colIndex == m_n) {
                    if (rowIndex < m_m) {
                        colIndex = 0;
                        m_row_index[rowIndex + 1] = m_row_index[rowIndex];
                        rowIndex++;
                    }
                }

            }
        }
        
        //*****DEBUG BELOW*******
        /*
        cout << "Cols" << endl;
        for (int i = 0; i < m_nonzeros; i++) {
            cout << m_col_index[i] << " ";

        }
        cout << "\nrows" << endl;

        for (int i = 0; i < m_m + 1; i++) {
            cout << m_row_index[i] << " ";
        }
        cout << endl;
        */
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
    //int colIndex = 0;
    //int numInRow = 0;
    int rowStart = m_row_index[row];
    int rowEnd = m_row_index[row + 1] - 1;

    for (int i = rowStart; i <= rowEnd ; i++) {
        if (m_col_index[i] == col) {
            return m_values[i];
        }
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

    for (int i = 0; i < (m_m + 1); i++) {
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
    CSR* temp = rhs.m_head;
    m_size = 0;

    while (temp != nullptr) {
        insertAtHead(*temp);
        temp = temp->m_next;
    }
}
CSRList::~CSRList() {
    CSR* temp = m_head;
    CSR* next = nullptr;

    while (temp != nullptr) {
        if (temp->m_next != nullptr) {
            next = temp->m_next;
            delete temp;
            temp = next;
        }
        else {
            delete temp;
            temp = nullptr;
        }
    
    }

}
bool CSRList::empty() const {
    if (m_head == nullptr) {
        return true;
    }
    else {
        return false;
    }
}
void CSRList::insertAtHead(const CSR& matrix) {
    CSR *node = new CSR(matrix);
    

    if (m_head == nullptr) {
        m_head = node;
        m_size++;
    }
    else {
        node->m_next = m_head;
        m_head = node;
        m_size++;
    }
}
void CSRList::clear() {
    CSR* temp = m_head;
    CSR* next = nullptr;

    while (temp != nullptr) {
        if (temp->m_next != nullptr) {
            next = temp->m_next;
            delete temp;
            temp = next;
        }
        else {
            delete temp;
            temp = nullptr;
        }

    }
    m_head = nullptr;
    m_size = 0;
}

int CSRList::getAt(int CSRIndex, int row, int col) const {
    int position = 0;
    CSR* temp = m_head;

    while (CSRIndex != (position - 1)) {
        if (position == CSRIndex) {
            return temp->getAt(row, col);
        }
        else {
            try {
                if (temp == nullptr) {
                    throw runtime_error("Exception Error: Object is not in the list!");
                }
                else {
                    temp = temp->m_next;
                    position++;
                }
            }
            catch (runtime_error& e) {
                throw e;
            }
        }
    }
    return -1;
}
bool CSRList::operator== (const CSRList& rhs) const {
    CSR *thisPtr = m_head;
    CSR* rhsPtr = rhs.m_head;

    while ((thisPtr != nullptr)) {
        if (thisPtr == rhsPtr) {}
        else {
            return false;
        }

        if (thisPtr != nullptr) {
            thisPtr = thisPtr->m_next;
        }
        else {
            cout << "thisPtr out of bounds!" << endl;
        }

        if (rhsPtr != nullptr) {
            rhsPtr = rhsPtr->m_next;
        }
        else {
            cout << "rhsPtr out of bounds!" << endl;
        }
    }

    return true;
}
const CSRList& CSRList::operator=(const CSRList& rhs) {
    CSR* temp = rhs.m_head;
    m_size = 0;

    while (temp != nullptr) {
        insertAtHead(*temp);
        temp = temp->m_next;
    }

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


