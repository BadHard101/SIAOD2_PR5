#include <iostream>
#include <algorithm>
#include <fstream>

//Максимальное значение веса = 100
#define INF 101

using namespace std;

void printMatrix(int** matrix, int numberOfVert) {
    for(int i = 0; i < numberOfVert; i++) {
        for(int j = 0; j < numberOfVert; j++) {
            if(matrix[i][j] == INF) {
                cout << "INF" << " ";
            }
            else {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

//matrix - матрица смежности
void floydWarshall(int **matrix, int numberOfVert) {
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(int k = 0; k < numberOfVert; k++) {
        for(int i = 0; i < numberOfVert; i++) {
            for(int j = 0; j < numberOfVert; j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
}

int main(int argc, char** argv) {
    int menu;
    string path;

    cout << "How do you want to open the graph?" << endl
    << "1 - From file by path," << endl
    << "2 - Write it here." << endl
    << "Enter:";
    cin >> menu;
    cout << endl;

    int numberOfVert;
    //Матрица смежности с весами ребер графа(101 - ребра нет, 0 ребро в себя)
    int **matrix = (int**)malloc(sizeof(int)*numberOfVert);
    for(int i = 0; i < numberOfVert; i++) {
        matrix[i] = (int *) malloc(sizeof(int) * numberOfVert);
    }

    if (menu == 1) {
        cout << "Enter path:";
        cin >> path;
        //C:/Users/BadHard/CLionProjects/untitled1/matrix.txt
        ifstream file(path);
        file >> numberOfVert;
        cout << numberOfVert << endl;

        //Считываем матрицу весов ребер
        for(int i = 0; i < numberOfVert; i++)
            for(int j = 0; j < numberOfVert; j++)
                file >> matrix[i][j];
        file.close();
    } else if (menu == 2) {
        cout << "Use 101 as INF" << endl;
        cout << "Enter a number of nodes:";
        cin >> numberOfVert;
        cout << endl;

        //Считываем матрицу весов ребер
        for(int i = 0; i < numberOfVert; i++) {
            for(int j = 0; j < numberOfVert; j++) {
                cout << j+1 << " length for the " << i+1 << " node:";
                cin >> matrix[i][j];
                cout << endl;
            }
        }
    } else {
        cout << "Wrong answer";
        exit(0);
    }

    cout << "Old matrix:" << endl;
    printMatrix(matrix, numberOfVert);

    floydWarshall(matrix, numberOfVert);

    cout << "New matrix:" << endl;

    printMatrix(matrix, numberOfVert);

    return 0;
}
