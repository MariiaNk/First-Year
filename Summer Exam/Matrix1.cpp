/*Написати функцію для обчислення матриці B = A^2, де для матриці А використано 
“прямокутно-зв’язне стисле зберігання”, а матриця B  зберігається традиційним чином у 
вигляді двовимірного масиву*/

/*Прямокутне зв`язане індексне зберігання використовує масиви покажчиків для рядків та стовпчиків.
Кожний вузол списку має два поля покажчиків – на наступний у рядку та наступний у стовпчику.*/

#include <iostream>
#define ROWS 3
#define COLUMN 3
using namespace std;

struct Node 
{
    int value;  
    int row, col;            
    Node* right;     
    Node* down;
    Node(int value, int row, int col) : 
        value(value), row(row), col(col), right(nullptr), down(nullptr) {}      
};

void pov2_SparseMatrix(Node* rowHeader[], Node* columnHeader[], int (&array)[ROWS][COLUMN])
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMN; j++)
            array[i][j] = 0;


    Node* columnPoiner = nullptr;
    for(int i = 0; i < ROWS; i++)
    {
        Node* rowPointer = rowHeader[i];
        while(rowPointer != nullptr)
        {
            int currentColumn = rowPointer->col;
            columnPoiner = columnHeader[currentColumn];
            while(columnPoiner != nullptr)
            {
                array[i][currentColumn] += rowPointer->value * columnPoiner->value;
                columnPoiner = columnPoiner->down;
            }
            rowPointer = rowPointer->right;
        }
    }
}

void insert(Node* rowHeaders[], Node* colHeaders[], int i, int j, int value) {
    Node* newNode = new Node(value, i, j);

    // Вставка в рядок
    if (rowHeaders[i] == nullptr || rowHeaders[i]->col > j) 
    {
        newNode->right = rowHeaders[i];
        rowHeaders[i] = newNode;
    } 
    else 
    {
        Node* temp = rowHeaders[i];
        while (temp->right != nullptr && temp->right->col < j) 
            temp = temp->right;
        newNode->right = temp->right;
        temp->right = newNode;
    }

    // Вставка в стовпчик
    if (colHeaders[j] == nullptr || colHeaders[j]->row > i) 
    {
        newNode->down = colHeaders[j];
        colHeaders[j] = newNode;
    } 
    else 
    {
        Node* temp = colHeaders[j];
        while (temp->down != nullptr && temp->down->row < i) 
            temp = temp->down;
        newNode->down = temp->down;
        temp->down = newNode;
    }
}

// Функція для перетворення звичайної матриці у розріджену матрицю з прямокутно-зв'язаним стисленим зберіганням
void createSparseMatrix(int matrix[ROWS][COLUMN], Node* rowHeaders[], Node* colHeaders[]) 
{
    for (int i = 0; i < ROWS; ++i) {
        rowHeaders[i] = nullptr;
    }
    for (int j = 0; j < COLUMN; ++j) {
        colHeaders[j] = nullptr;
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (matrix[i][j] != 0) {
                insert(rowHeaders, colHeaders, i, j, matrix[i][j]);
            }
        }
    }
}

int main()
{
    Node* rowHeader[ROWS];
    Node* columnHeader[COLUMN];

    int array [ROWS][COLUMN] = {
        5, 0, 0,
        0, 20, 0,
        0, 0, 6};

    createSparseMatrix(array, rowHeader, columnHeader);
    pov2_SparseMatrix(rowHeader, columnHeader, array);

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

}