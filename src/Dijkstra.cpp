#include "Dijkstra.h"
#include <iostream>
#include <cfloat>
#include <string>

using namespace std;

Dijkstra::Dijkstra(int matrix_size, double** weights_matrix)
{
    this->matrix_size = matrix_size;
    this->weights_matrix = weights_matrix;

    solution_matrix = new double* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
        solution_matrix[i] = new double [matrix_size];

    way_vector = new string [matrix_size];
}

Dijkstra::~Dijkstra()
{
    for (int i = 0; i < matrix_size; i++)
    {
        delete[] weights_matrix[i];
        delete[] solution_matrix[i];
    }

    delete[] weights_matrix;
    delete[] solution_matrix;
    delete[] way_vector;
}

void Dijkstra::print()
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

void Dijkstra:: print_way(int start, int finish)
{
    if(start < 0 || start >= matrix_size || finish < 0 || finish >= matrix_size)
    {
        cout << "Wrong input! Try again." << endl << endl;
    }
    else
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
        cout << "Path: " << way_vector[finish] << endl << endl;
    }

}

void Dijkstra::calculate()
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

void Dijkstra::preparing()
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

void Dijkstra::row_descent(int row, int current, double current_value)
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

void Dijkstra::set_way(int row, int current)
{
    for(int j = 0; j < matrix_size; j++)
    {
        if(solution_matrix[row+1][j] < solution_matrix[row][j] && solution_matrix[row+1][j] != -1.0)
        {
            way_vector[j] = way_vector[current] + " -> " + to_string(j);
        }
    }
}

int Dijkstra::get_index_of_min_value(int row, int current, double current_value)
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
