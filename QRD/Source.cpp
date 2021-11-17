#include <iostream>
#include <math.h>
using namespace std;
void Matrix_In(float a[4][4]){
    float x;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> x;
            a[i][j] = x;
        }
    }
}
void Matrix_Out(float a[4][4]) {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}
void Matrix_Mul(float Matrix_A[4][4], float Matrix_B[4][4], float Matrix_Result[4][4]) {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Matrix_Result[i][j] = 0;
            for (int k = 0; k < 4; k++)
                Matrix_Result[i][j] = Matrix_Result[i][j] + (Matrix_A[i][k] * Matrix_B[k][j]);
        }
    }
}
bool Check_Inverse_Condition(float Matrix[4][4]) {
    int count;
    for (int i = 0; i < 4; i++)
    {
        count = 0;
        for (int j = 0; j < 4; j++)
        {
            if (round(Matrix[i][j]) == 0)
                count++;
        }
        if (count == 4)
        {
            return false;
            break;
        }
    }
    return true;
}
void Inverse_Upper_Triangle_Matrix(float Matrix[4][4], float Matrix_Inverse[4][4]) {
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i > j)
            {
                Matrix_Inverse[i][j] = 0;
            }
            else if (i == j)
            {
                Matrix_Inverse[i][i] = float(1 / Matrix[i][i]);
            }
            else
            {
                Matrix_Inverse[i][j] = 0;
                for (int k = i; k < j; k++)
                {
                    Matrix_Inverse[i][j] = Matrix_Inverse[i][j] - Matrix[i][k+1] * Matrix_Inverse[k+1][j] * Matrix_Inverse[i][i];
                }
            }
        }
    }
}
void Identity_Matrix(float Matrix[4][4]) {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                Matrix[i][i] = 1;
            else
                Matrix[i][j] = 0;
        }
    }
}
void Transpose_Given_Rotation_Identity_Matrix(float Matrix_Transpose[4][4], int i, int j) {
    Matrix_Transpose[i][j] = (-1) * Matrix_Transpose[i][j];
    Matrix_Transpose[j][i] = (-1) * Matrix_Transpose[j][i];
}
void Transpose_Square_Matrix(float Matrix[4][4]) {
    float temp;
    for (int i = 1; i < 4; i++) 
    {
        for (int j = 0; j < i; j++) 
        {
            temp = Matrix[i][j];
            Matrix[i][j] = Matrix[j][i];
            Matrix[j][i] = temp;
        }
    }
}
void Equal(float Matrix_A[4][4], float Matrix_B[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Matrix_B[i][j] = Matrix_A[i][j];
        }
    }
}
int main() {
    float A[4][4], G[4][4], Q[4][4], R[4][4], QT[4][4], inA[4][4];
    int flag_Inv = 1, flag_For = 1;
    Identity_Matrix(G);
    Identity_Matrix(Q);
    Matrix_In(A);
    int i, j;
    for (i = 1; i < 4; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (A[i][j] != 0)
            {
                G[i][j] = float((-1)*A[i][j] / sqrt(pow(A[i][j], 2) + pow(A[j][j], 2)));
                G[j][i] = (-1)*G[i][j];
                G[i][i] = float(A[j][j] / sqrt(pow(A[i][j], 2) + pow(A[j][j], 2)));
                G[j][j] = G[i][i];
                Matrix_Mul(G, A, R);
                Equal(R, A);    

                if (!Check_Inverse_Condition(A))
                {
                    cout << "The determinant is 0, the matrix is not invertible.";
                    flag_Inv = 0;
                    flag_For = 0;
                    break;
                }
                else
                {
                    Transpose_Given_Rotation_Identity_Matrix(G, i, j);
                    Matrix_Mul(Q, G, QT);
                    Equal(QT, Q);
                    Identity_Matrix(G);
                }
            }
        }
        if (flag_For == 0)
        {
            break;
        }
    }
    if (flag_Inv == 1)
    {
        Inverse_Upper_Triangle_Matrix(A, R);
        Transpose_Square_Matrix(Q);
        Matrix_Mul(R, Q, inA);
        Matrix_Out(inA);
    }
    return 0;
}