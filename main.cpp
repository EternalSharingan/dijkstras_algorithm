#include <iostream>
#include <string>
#include <cfloat>
#include <fstream>
#include <Dijkstra.h>

using namespace std;
//=
//_
void file_to_matrix(double**, int, string);

/*
class Dijkstra
{
private:
    int start_point;
    int matrix_size;
    double** weights_matrix;
    double** solution_matrix;
    string*  way_vector;
public:
    Dijkstra(int matrix_size, double** weights_matrix)
    {
        this->matrix_size = matrix_size;
        this->weights_matrix = weights_matrix;

        solution_matrix = new double* [matrix_size];
        for (int i = 0; i < matrix_size; i++)
            solution_matrix[i] = new double [matrix_size];

        way_vector = new string [matrix_size];
    }

    void print()
    {
        for(int i = 0; i < matrix_size; i++)
        {
            for(int j = 0; j < matrix_size; j++)
            {
                if(weights_matrix[i][j] == DBL_MAX)
                {
                    cout<<"inf ";
                }
                else if(weights_matrix[i][j] == -1.0)
                {
                    cout<<"- ";
                }
                else
                {
                    cout<<weights_matrix[i][j]<<" ";
                }
            }
            cout<<endl;
        }
    }

    void print_way(int start, int finish)
    {
        if(start != this->start_point)
        {
            this->start_point = start;
            calculate();
        }
        cout << "Path length: ";
        for(int i = matrix_size-1; i >= 0; i--)
        {
            if(solution_matrix[i][finish] == DBL_MAX)
            {
                cout << "Path doesn't exist" << endl;
                break;
            }
            else if(solution_matrix[i][finish] != -1.0)
            {
                cout << solution_matrix[i][finish] << endl;
                break;
            }
        }
        cout <<"Path: " << way_vector[finish]<<endl<<endl;
    }

private:
    void calculate()
    {
        preparing();

        solution_matrix[0][this->start_point] = 0.0;
        way_vector[this->start_point] = to_string(this->start_point);

        int current = this->start_point;
        double current_value = 0.0;

        for(int i = 0; i < matrix_size-1; i++)
        {
            row_descent(i, current, current_value);
            set_way(i, current);
            current = get_index_of_min_value(i, current, DBL_MAX);
            current_value = solution_matrix[i+1][current];
        }
    }

    void preparing()
    {
        for(int i = 0; i < matrix_size; i++)
        {
            for(int j = 0; j < matrix_size; j++)
            {
                solution_matrix[i][j] = 0.0;
            }
            way_vector[i] = "";
        }
        for(int i = 0; i < matrix_size ; i++)
            solution_matrix[0][i] = DBL_MAX;
    }

    void row_descent(int row, int current, double current_value)
    {
        for(int j = 0; j < matrix_size; j++)
        {
            if(j != current)
            {
                solution_matrix[row+1][j] = min(current_value+weights_matrix[current][j], solution_matrix[row][j]);
            }
            else
            {
                solution_matrix[row+1][j] = -1.0;
            }
        }
    }

    void set_way(int row, int current)
    {
        for(int j = 0; j < matrix_size; j++)
        {
            if(solution_matrix[row+1][j] < solution_matrix[row][j] && solution_matrix[row+1][j] != -1.0)
            {
                way_vector[j] = way_vector[current] + " -> " + to_string(j);
            }
        }
    }

    int get_index_of_min_value(int row, int current, double current_value)
    {
        for(int j = 0; j < matrix_size; j++)
        {
            if(j != current)
            {
                if(current_value > solution_matrix[row+1][j] && solution_matrix[row+1][j] != -1.0)
                {
                    current = j;
                    current_value = solution_matrix[row+1][j];
                }
            }
        }
        return current;
    }
};*/


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
