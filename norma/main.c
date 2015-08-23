#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* file = argv[1];
    FILE* f = fopen(file, "r");
    int n = 0;
    int m = 0;
    fscanf(f, "%d", &n);
    fscanf(f, "%d", &m);
    
    double** arr = (double**)calloc(n, n * sizeof(double*));
    int i = 0;
    for( ; i < n; i++) {
        arr[i] = (double*)calloc(m, m * sizeof(double));
    }
    int col = 0;
    fscanf(f, "%d", &col);
    for(i = 0; i < col; i++) {
        int a = 0;
        int b = 0;
        double value = 0;
        fscanf(f, "%d%d%lf", &a, &b, &value);
        arr[a][b] = value;
    }
    printf("%f", &arr[0][0]);
    
    
    return 0;
}

