#include <iostream>
#include <string>
#include <cfloat>
#include <fstream>
#include <Dijkstra.h>

using namespace std;

void file_to_matrix(double**, int, string);

int main()
{
    int matrix_size = 10;
    double **weights_matrix = new double* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
        weights_matrix[i] = new double [matrix_size];

    file_to_matrix(weights_matrix, matrix_size, "example2.txt");//  matrix_size = 6 "example1.txt" or matrix_size = 10 "example2.txt"

    Dijkstra obj(matrix_size, weights_matrix);

    while(true)
    {
        int start, finish;
        cout <<"Enter start:"<<endl;
        cin >> start;
        cout <<"Enter finish:"<<endl;
        cin >> finish;
        obj.print_way(start, finish);
    }
    return 0;
}

void file_to_matrix(double** matrix, int matrix_size, string file_name)
{
    string buf;
    ifstream file(file_name);

    for(int i = 0; i < matrix_size; i++)
    {
        for(int j= 0; j < matrix_size; j++)
        {
            getline(file, buf);
            if(buf == "-")
            {
                matrix[i][j] = -1.0;;
            }
            else if(buf == "i")
            {
                matrix[i][j] = DBL_MAX;
            }
            else
            {
                matrix[i][j] = atof(buf.c_str());
            }
        }
    }
    file.close();
}
