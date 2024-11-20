#include <mpi/mpi.h>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <chrono>
#include "include/help.h"


/// @brief Функция слияния логических половинок
/// @param A массив, у которого половинки A[p..q] и A[q+1..r] отсортированы
/// @param p левая граница
/// @param q центр
/// @param r правая граница
void merge(int32_t *A, int32_t p, int32_t q, int32_t r) {
    int32_t n1 = q - p + 1, n2 = r - q;
    int32_t *L = new int32_t[n1 + 1];
    int32_t *R = new int32_t[n2 + 1];

    for (int32_t i = 0; i < n1; ++i) L[i] = A[p + i];
    for (int32_t j = 0; j < n2; ++j) R[j] = A[q + j + 1];
    L[n1] = INT32_MAX;
    R[n2] = INT32_MAX;

    for (int k = p, i = 0, j = 0; k <= r; ++k) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            ++i;
        } else {
            A[k] = R[j];
            ++j;
        }
    }

    delete[] L;
    delete[] R;
}

/// @brief Сортировка слиянием
/// @param A массив
/// @param p левая граница
/// @param r правая граница
void mergeSort(int32_t *A, int32_t p, int32_t r) {
    if (p < r) {
        int32_t q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

/// @brief Функция для распараллеливания сортировки
/// @param arr Массив
/// @param n Размер массива
/// @param rank Ранг процесса
/// @param size Количество процессов
void parallelMergeSort(int32_t *arr, int32_t n, int rank, int size) {
    int32_t local_n = n / size; // Число элементов на процесс
    int32_t *local_arr = new int32_t[local_n];

    // Распределяем массив между процессами
    MPI_Scatter(arr, local_n, MPI_INT32_T, local_arr, local_n, MPI_INT32_T, 0, MPI_COMM_WORLD);

    // Локальная сортировка
    mergeSort(local_arr, 0, local_n - 1);

    // Собираем отсортированные массивы
    MPI_Gather(local_arr, local_n, MPI_INT32_T, arr, local_n, MPI_INT32_T, 0, MPI_COMM_WORLD);

    // Последовательное слияние на процессе 0
    if (rank == 0) {
        for (int i = 1; i < size; ++i) {
            merge(arr, 0, i * local_n - 1, (i + 1) * local_n - 1);
        }
    }

    delete[] local_arr;
}


int32_t main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int32_t *arr = nullptr;
    int32_t n;

    if (rank == 0) {
        tool::read_input("./src/input.txt", arr, n);
    }

    // Передаём размер массива всем процессам
    MPI_Bcast(&n, 1, MPI_INT32_T, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        arr = new int32_t[n]; // Выделяем память для других процессов
    }

    std::chrono::_V2::steady_clock::time_point begin;
    if (rank == 0) {
        // замер времени
        begin = std::chrono::steady_clock::now();
    }

    // Запускаем параллельную сортировку
    parallelMergeSort(arr, n, rank, size);

    if (rank == 0) {
        //tool::print_array(arr, n);
    }

    if (rank == 0) {
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
        std::cout << "Time: " << elapsed_ms.count() << "ms;\n";
    }

    MPI_Finalize();
    return 0;
}
