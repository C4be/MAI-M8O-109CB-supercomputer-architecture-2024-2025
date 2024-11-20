#include "./include/help.h"


/// @brief Преобразуем число к int32_t и проверяем, требуется ли округление вниз
/// @param num число с плавающей точкой
/// @return округленное вниз число
int32_t tool::floor(double num) {
    int32_t intPart = static_cast<int32_t>(num);
    if (num < 0 && num != static_cast<double>(intPart)) {
        return intPart - 1;
    }
    return intPart;
}

void tool::print_array(int32_t *arr, int32_t n) {
    std::cout << "\nArray:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

void tool::read_input(const char* filename, int32_t*& arr, int32_t& n) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file >> n;  // Считываем количество элементов

    arr = new int32_t[n];  // Выделяем память под массив
    for (int i = 0; i < n; ++i) {
        file >> arr[i];  // Считываем элементы массива
    }

    file.close();  // Закрываем файл
}