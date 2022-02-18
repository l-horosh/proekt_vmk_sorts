#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



enum TYPE {
    SORTED = 0,
    RE_SORTED,
    RANDOM
};


long long int * gen_mass (int n, int type) {
    long long int * a = (long long int *) calloc (n, sizeof(long long int));
    if (type == SORTED) {
        for (int i = 0; i < n; i++){
            a[i] = i;
        }
    }
    else if (type == RE_SORTED) {
        for (int i = n - 1; i >= 0; i--){
            a[i] = n - i;
        }
    }
    else if (type == RANDOM) {
        int module = 1000;
        srand(time(NULL));
        for (int i = 0; i < n; i++){
            a[i] = rand() % (2 * module) - module;
        }
    }
    return a;
}

void print_mass (long long int * x, int n){
    for (int i = 0; i < n; i++){
        printf("%Ld ", x[i]);
    }
    printf("\n");
}

void ShElL (long long int * x, int n, long int * comp, long int * swap){
    int shag, i, j;
    long long int tmp;
    for (shag = n / 2; shag > 0; shag /= 2){
        for (i = shag; i < n; i++){
            tmp = x[i];
            for (j = i; j >= shag; j -= shag){
                *comp += 1;
                if (abs(tmp) > abs(x[j - shag])){
                    x[j] = x [j - shag];
                    *swap += 1;
                }
                else {
                    break;
                }
            }
            x[j] = tmp;
        }
    }
}

void q_sort (long long int * x, int n, long int * comp, long int * swap) {
    int i, j;
    i = 0;
    j = n - 1;
    long long int mid = abs (x[n / 2]);
     while (i <= j) {
        while (abs (x[i]) > mid) {
            i += 1;
            *comp += 1;
        }
        while (abs (x[j]) < mid) {
            j -= 1;
            *comp += 1;
        }
        *comp += 1;
        if (i <= j) {
            long long int tmp = x[i];
            x[i] = x[j];
            x[j] = tmp;
            i += 1;
            j -= 1;
            *swap += 1;
        }
    }

    if (j > 0) {
        q_sort(x, j+1, comp, swap);
    }
    if (i < n) {
        q_sort(&x[i], n-i, comp, swap);
    }
}



int main (void){
    long int comp = 0;
    long int swap = 0;
    int n = 10000;
    long long int * d = gen_mass(n, RANDOM);
    print_mass(d, n);
    printf ("----------------------------\n");
    q_sort(d, n, &comp, &swap);
    print_mass(d, n);
    printf("%ld ", swap);
    printf("%ld", comp);
    free(d);
    return 0;
}