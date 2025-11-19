#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int row;
    int col;
    int value;
} Triple;

typedef struct
{
    Triple data[100];
    int rows;
    int cols;
    int terms;
} SparseMatrix;

void InputMatrix(SparseMatrix* A)
{
    scanf("%d %d %d", &A->rows, &A->cols, &A->terms);
    for(int i = 0; i < A->terms; i++)
    {
        scanf("%d %d %d", &A->data[i].row, &A->data[i].col, &A->data[i].value);
        A->data[i].row--;
        A->data[i].col--;
    }
}

void OutputMatrix(SparseMatrix A)
{
    printf("%d\n", A.rows);
    printf("%d\n", A.cols);
    printf("%d\n", A.terms);

    for(int i = 0; i < A.terms; i++)
    {
        printf("%d,%d,%d\n", A.data[i].row + 1, A.data[i].col + 1, A.data[i].value);
    }
}

void TransposeMatrix(SparseMatrix A, SparseMatrix* AT)
{
    AT->rows = A.cols;
    AT->cols = A.rows;
    AT->terms = A.terms;

    int *count = (int *)malloc(A.cols * sizeof(int)); // 记录每一列的非零元素个数
    int *start = (int *)malloc(A.cols * sizeof(int));  // 记录每一列的非零元素在 B 中的起始位置
    
    for(int i = 0; i < A.cols; i++)
        count[i] = 0;
    for(int i = 0; i < A.terms; i++)
        count[A.data[i].col]++;
    
    for(int i = 1; i < A.cols; i++)
        start[i] = start[i-1] + count[i-1];

    for(int i = 0; i < A.terms; i++)
    {
        int j = A.data[i].col;
        int p = start[j];

        AT->data[p].row = A.data[i].col;
        AT->data[p].col = A.data[i].row;
        AT->data[p].value = A.data[i].value;

        start[j]++;
    }

    free(count);
    free(start);
}

void MultiplyMatrix(SparseMatrix A, SparseMatrix B, SparseMatrix* C)
{
    C->rows = A.rows;
    C->cols = B.cols;
    C->terms = 0;

    if (A.terms == 0 || B.terms == 0)
        return;

    SparseMatrix BT;
    TransposeMatrix(B, &BT);
    int rowBegin = 0;
    int cur_row[B.cols];
    for(int i = 0; i < A.rows; i++)
    {
        memset(cur_row, 0, sizeof(cur_row));

        for(int j = rowBegin; j < A.terms && A.data[j].row == i; j++)
        {
            int colA = A.data[j].col;
            int valA = A.data[j].value;

            for(int k = 0; k < BT.terms; k++)
            {
                if(BT.data[k].col == colA)
                {
                    int rowB = BT.data[k].row;                
                    int valB = BT.data[k].value;           
                    cur_row[rowB] += valA * valB;
                }
            }
        }
        for(int h = 0; h < C->cols; h++)
        {
            if(cur_row[h] != 0)
            {
                C->data[C->terms].row = i;
                C->data[C->terms].col = h;
                C->data[C->terms].value = cur_row[h];
                C->terms++;
            }
        }
        
        while(rowBegin < A.terms && A.data[rowBegin].row == i)
            rowBegin++;
    }
}

int main()
{
    SparseMatrix A, B, C;

    InputMatrix(&A);
    InputMatrix(&B);

    MultiplyMatrix(A, B, &C);

    OutputMatrix(C);

    return 0;
}