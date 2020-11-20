#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <string>

using namespace std;

class Dijkstra
{
private:
    int start_point;
    int matrix_size;
    double** weights_matrix;
    double** solution_matrix;
    string*  way_vector;
public:
    Dijkstra(int, double**);
    ~Dijkstra();
    void print();
    void print_way(int, int);
private:
    void calculate();
    void preparing();
    void row_descent(int, int, double);
    void set_way(int, int);
    int get_index_of_min_value(int, int, double);
};

#endif // DIJKSTRA_H
