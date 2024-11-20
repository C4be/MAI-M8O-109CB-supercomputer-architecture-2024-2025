#include <iostream>
#include <chrono>

#include "include/help.h"

/// @brief Функция слияния логических половинок
/// @param A массив, у которого половинки A[p..q] и A[q+1..r] отсортированы
/// @param p левая граница
/// @param q центр
/// @param r правая граница
void merge(int32_t *A, int32_t p, int32_t q, int32_t r) {
    // размерности A[p..q] и A[q+1..r]
    int32_t n1 = q - p + 1, n2 = r - q; 

    // инициализируем временные массивы на куче и делаем копии диапозонов
    int32_t *L, *R;
    L = new int32_t[n1 + 1];
    R = new int32_t[n2 + 1];
    for (int32_t i = 0; i < n1; ++i) L[i] = A[p + i];
    for (int32_t j = 0; j < n2; ++j) R[j] = A[q + j + 1];
    L[n1] = INT32_MAX; // сигнальный элемент
    R[n2] = INT32_MAX; // сигнальный элемент

    for (int k = p, i = 0, j = 0; k <= r; ++k) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            ++i;
        } else {
            A[k] = R[j];
            ++j;
        }
    }

    // очистка кучи
    delete [] L;
    delete [] R;
}

/// @brief Сортировка слиянием
/// @param A массив
/// @param p левая граница
/// @param r правая граница
void mergeSort(int32_t *A, int32_t p, int32_t r) {
    if (p < r) {
        int32_t q = tool::floor(static_cast<double>(p + r) / 2);
        mergeSort(A, p, q); // рекурсивно считаем первую половину
        mergeSort(A, q + 1, r); // рекурсивно считаем вторую половину
        merge(A, p, q, r); // слияние
    }
}

int32_t main() {
    int32_t *arr = nullptr;
    int32_t n;

    // Чтение данных из файла
    tool::read_input("./src/input.txt", arr, n);

    // ход работы
    //tool::print_array(arr, n);

    auto begin = std::chrono::steady_clock::now();

    mergeSort(arr, 0, n - 1);

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
    std::cout << "Time: " << elapsed_ms.count() << "ms;\n";

    //tool::print_array(arr, n);

    delete [] arr;
    return 0;
}