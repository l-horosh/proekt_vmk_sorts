#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



enum TYPE { // создание констант для типа массива
    SORTED = 0,
    RE_SORTED,
    RANDOM
};


long long int * gen_mass (int n, int type) { // генерация массива
    long long int * a = (long long int *) calloc (n, sizeof(long long int)); // выделение памяти под массив
    if (type == RE_SORTED) { // создание сортированного массива
        for (int i = 0; i < n; i++){
            a[i] = i;
        }
    }
    else if (type == SORTED) { // создание сортированного массива в обратном порядке
        for (int i = n - 1; i >= 0; i--){
            a[i] = n - i;
        }
    }
    else if (type == RANDOM) { // создание рандомного массива
        int module = 1000;
        srand(time(NULL)); // инициализация рандомайзера
        for (int i = 0; i < n; i++){
            a[i] = rand() % (2 * module) - module; // сдвиг для отрицательных чисел
        }
    }
    return a;
}

void print_mass (long long int * x, int n){ // печать массива
    for (int i = 0; i < n; i++){
        printf("%Ld ", x[i]);
    }
    printf("\n");
}

void ShElL (long long int * x, int n, long int * comp, long int * swap){ // сортировка методом Шелла
    int shag, i, j; // берем индексы i, j, shag сортировки
    long long int tmp;
    for (shag = n / 2; shag > 0; shag /= 2){ // шаг уменьшается в 2 раза
        for (i = shag; i < n; i++){ // с определенным шагом пробегаемся по массиву
            tmp = x[i];
            for (j = i; j >= shag; j -= shag){ //сравниваем последовательные (предыдущие) элементы через шаг
                *comp += 1;
                if (abs(tmp) > abs(x[j - shag])){ // сравнение текущего 
                    x[j] = x [j - shag];
                    *swap += 1;
                }
                else { 
                    break;
                }
            }
            x[j] = tmp; // вставление текущего элемента
        }
    }
}

void q_sort (long long int * x, int n, long int * comp, long int * swap) { // быстрая сортировка
    int i, j; 
    i = 0; // начало массива
    j = n - 1; // конец массива
    long long int mid = abs (x[n / 2]); // опорный элемент
     while (i <= j) {
        while (abs (x[i]) > mid) { // ищем первый неподходящий элемент слева
            i += 1;
            *comp += 1;
        }
        while (abs (x[j]) < mid) { // ищем первый неподходящий элемент справа
            j -= 1;
            *comp += 1;
        }
        if (i < j) { // перестановка элементов
            long long int tmp = x[i];
            x[i] = x[j];
            x[j] = tmp;
            *swap += 1;
        }
        i += 1;
        j -= 1;
    }

    if (j > 0) {
        q_sort(x, j+1, comp, swap); // рекурсивный запуск от левой части массива
    }
    if (i < n) {
        q_sort(&x[i], n-i, comp, swap); // рекурсивный запуск от правой части масссива
    }
}


long long int * copy_of_mass (long long int * m, int n) {
    long long int * a = (long long int *) calloc (n, sizeof(long long int));
    for (int i = 0; i < n; i++) {
        a[i] = m[i];
    }
    return a;
}


int main (void){
    long int comp_1 = 0; // кол-во сравнений 
    long int swap_1 = 0; // кол-во перестановок
    long int comp_2 = 0; // кол-во сравнений 
    long int swap_2 = 0; // кол-во перестановок
    int n = 10; // длина массива
    long long int * d = gen_mass(n, SORTED);
    long long int * e = copy_of_mass(d, n);
    print_mass(d, n);
    printf ("----------------------------\n");
    print_mass(e, n);
    printf ("----------------------------\n");
    q_sort(d, n, &comp_1, &swap_1);
    ShElL(e, n, &comp_2, &swap_2);
    print_mass(d, n);
    printf ("----------------------------\n");
    print_mass(e, n);
    printf ("----------------------------\n");
    printf("q_sort_swap = %ld ", swap_1);
    printf("q_sort_comp = %ld\n", comp_1);
    printf("ShElL_swap = %ld ", swap_2);
    printf("ShElL_comp = %ld", comp_2);
    free(d); // освобождение выделенной памяти
    free(e);
    return 0;
}