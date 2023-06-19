#include <iostream>
#include <windows.h>
#include <chrono>

using namespace std;

int main() {
    SetConsoleOutputCP(65001);    // Установка кодовой страницы UTF-8 для вывода в консоли Windows

    bool run = true;              // Продолжать программу, пока эта переменная true
    int action;                   // Выбор пункта меню

    const int N = 100;            // Размерность массива
    int A[N], B[N];               // Отсортированный и неотсортированный массив
    bool arrayReady = false;      // Был ли сгенерирован массив для работы пунктов 2-8
    bool arraySorted = false;     // Был ли отсортирован массив для работы пунктов 3-7

    chrono::steady_clock::time_point start, end;       // Отсечки для замера затраченного времени

    do {
        cout << "\nДоступные действия:\n";
        cout << "-----------------------------------------------\n";
        cout << "1. Генерация массива\n";
        cout << "2. Сортировка массива\n";
        cout << "3. Поиск минимума и максимума\n";
        cout << "4. Поиск среднего между минимумом и максимумом\n";
        cout << "5. Подсчет элементов, меньше указанного числа\n";
        cout << "6. Подсчет элементов, больше указанного числа\n";
        cout << "7. Поиск указанного числа\n";
        cout << "8. Обмен местами указанных элементов\n";
        cout << "0. Выход\n";
        cout << "\nВыберите нужное действие: ";

        cin >> action;
        cin.sync();

        switch (action)
        {
        case 1:
            cout << "\nГенерация массива:";

            srand(time(0));               // Подготовка для генерации случайных чисел
            cout << "\nМассив: [ ";
            for (int i = 0; i < N; i++) {
                A[i] = B[i] = rand() % 100;
                cout << B[i] << " ";
            }
            cout << "]\n";

            arrayReady = true;
            arraySorted = false;

            break;        
        case 2:
            cout << "\nСортировка массива:";

            if (!arrayReady) {
                cout << "\nМассив не сгенерирован. Сначала выполните генерацию, выбрав пункт 1.\n";
            } else {
                int swap;
                bool swapped;

                start = chrono::steady_clock::now();

                for (int i = N-1; i > 0; i--) {
                    swapped = false;
                    for (int j = 0; j < i; j++) {
                        if (A[j] > A[j+1]) {
                            swap = A[j];
                            A[j] = A[j+1];
                            A[j+1] = swap;
                            swapped = true;
                        }
                    }
                    if (!swapped) break;
                }

                end = chrono::steady_clock::now();
               
                cout << "\nМассив: [ ";
                for (int i = 0; i < N; i++) {
                    cout << A[i] << " ";
                }
                cout << "]";

                cout << "\nВремя, затраченное на сортировку: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс\n";

                arraySorted = true;
            }

            break;        
        case 3:
            cout << "\nПоиск минимума и максимума:";
 
            if (!arrayReady) {
                cout << "\nМассив не сгенерирован. Сначала выполните генерацию, выбрав пункт 1.\n";
            } else if (!arraySorted) {
                cout << "\nМассив не отсортирован. Сначала выполните сортировку, выбрав пункт 2.\n";
            } else {
                int min, max;

                start = chrono::steady_clock::now();

                min = max = B[0];
                for (int i = 1; i < N; i++) {
                    if (B[i] < min) min = B[i];
                    if (B[i] > max) max = B[i];
                }

                end = chrono::steady_clock::now();
                cout << "\nМинимальный элемент: " << min;
                cout << "\nМаксимальный элемент: " << max;
                cout << "\nВремя, затраченное на поиск в неотсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс";

                start = chrono::steady_clock::now();
                
                min = A[0];
                max = A[N-1];

                end = chrono::steady_clock::now();
                cout << "\nВремя, затраченное на поиск в отсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс\n";
            }

           break;        
        case 4:
            cout << "\nПоиск среднего между минимумом и максимумом:";
 
            if (!arrayReady) {
                cout << "\nМассив не сгенерирован. Сначала выполните генерацию, выбрав пункт 1.\n";
            } else if (!arraySorted) {
                cout << "\nМассив не отсортирован. Сначала выполните сортировку, выбрав пункт 2.\n";
            } else {
                int min, max, mid;
                int C[N], cnt;                     // Массив для индексов найденных элементов, счетчик

                start = chrono::steady_clock::now();

                min = max = B[0];
                for (int i = 1; i < N; i++) {
                    if (B[i] < min) min = B[i];
                    if (B[i] > max) max = B[i];
                }
                mid = (max - min) / 2;
                cnt = 0;
                for (int i = 0; i < N; i++) {
                    if (B[i] == mid) C[cnt++] = i;
                }

                end = chrono::steady_clock::now();
                cout << "\nСреднее между минимумом и максимумом: " << mid;
                cout << "\nИндексы элементов с таким значением в неотсортированном массиве: ";
                for (int i = 0; i < cnt; i++) {
                    cout << C[i] << " ";
                }
                cout << "\nВремя, затраченное на поиск в неотсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс";

                start = chrono::steady_clock::now();
                
                min = A[0];
                max = A[N-1];
                mid = (max - min) / 2;
                cnt = 0;
                for (int i = 0; i < N; i++) {
                    if (A[i] == mid) C[cnt++] = i;
                }

                end = chrono::steady_clock::now();
                cout << "\nСреднее между минимумом и максимумом: " << mid;
                cout << "\nИндексы элементов с таким значением в отсортированном масиве: ";
                for (int i = 0; i < cnt; i++) {
                    cout << C[i] << " ";
                }
                cout << "\nВремя, затраченное на поиск в отсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс\n";
            }

            break;        
        case 5:
            cout << "\nПодсчет элементов, меньше указанного числа:";
      
            if (!arrayReady) {
                cout << "\nМассив не сгенерирован. Сначала выполните генерацию, выбрав пункт 1.\n";
            } else if (!arraySorted) {
                cout << "\nМассив не отсортирован. Сначала выполните сортировку, выбрав пункт 2.\n";
            } else {
                int cnt = 0;      // Количество найденных чисел
                int n;            // Вводимое число

                cout << "\nВведите целое число: ";
                cin >> n;
                cin.sync();

                for (int i = 0; i < N; i++) {
                    if (A[i] < n) cnt++;
                    else break;
                }

                cout << "Количество найденных чисел: " << cnt << "\n";
            }

        break;        
        case 6:
            cout << "\nПодсчет элементов, больше указанного числа:";
 
            if (!arrayReady) {
                cout << "\nМассив не сгенерирован. Сначала выполните генерацию, выбрав пункт 1.\n";
            } else if (!arraySorted) {
                cout << "\nМассив не отсортирован. Сначала выполните сортировку, выбрав пункт 2.\n";
            } else {
                int cnt = 0;      // Количество найденных чисел
                int n;            // Вводимое число

                cout << "\nВведите целое число: ";
                cin >> n;
                cin.sync();

                for (int i = N-1; i > - 1; i--) {
                    if (A[i] > n) cnt++;
                    else break;
                }

                cout << "Количество найденных чисел: " << cnt << "\n";
            }

            break;        
        case 7:
            cout << "\nПоиск указанного числа:";
 
            if (!arrayReady) {
                cout << "\nМассив не сгенерирован. Сначала выполните генерацию, выбрав пункт 1.\n";
            } else if (!arraySorted) {
                cout << "\nМассив не отсортирован. Сначала выполните сортировку, выбрав пункт 2.\n";
            } else {
                int found = -1;      // Индекс найденного элемента
                int n;               // Вводимое число

                cout << "\nВведите целое число: ";
                cin >> n;
                cin.sync();

                start = chrono::steady_clock::now();
                /* Бинарный поиск */
                int left = 0, right = N-1;   // Начальные границы для бинарного поиска
                int mid;                     // Среднее между границами
                while (left + 1 < right) {
                    mid = left + (right - left) / 2 + (right - left) % 2;
                    if (A[mid] == n) {
                        found = mid;
                        break;
                    } else if (n < A[mid]) {
                        right = mid;
                    } else {
                        left = mid;
                    }
                }
                end = chrono::steady_clock::now();

                if (found == -1) {
                    cout << "\nИскомое число не найдено в массиве";
                } else {
                    cout << "\nИскомое число найдено в массиве под индексом: " << found;
                }
                cout << "\nВремя, затраченное на поиск в отсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс";

                start = chrono::steady_clock::now();
                /* Поиск простым перебором */
                for (int i = 0; i < N; i++) {
                    if (A[i] == n) break;
                }
                end = chrono::steady_clock::now();
                cout << "\nВремя, затраченное на поиск в неотсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс\n";
            }

            break;        
        case 8:
            cout << "\nОбмен местами указанных элементов:";
 
            if (!arrayReady) {
                cout << "\nМассив не сгенерирован. Сначала выполните генерацию, выбрав пункт 1.\n";
            } else {
                int swap;                 // Переменная для замены
                int idx1, idx2;           // Вводимые индексы

                cout << "\nВведите первый индекс (0..99): ";
                cin >> idx1;
                cin.sync();
                cout << "Введите второй индекс (0..99): ";
                cin >> idx2;
                cin.sync();

                start = chrono::steady_clock::now();
                swap = B[idx1];
                B[idx1] = B[idx2];
                B[idx2] = swap;
                end = chrono::steady_clock::now();
                cout << "Время, затраченное на замену элементов: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "нс\n";
            }

           break;        
        case 0:
            cout << "\nПрограмма завершена!\n";
            run = false;
            break;        
        default:
            break;
        }
    }
    while (run);

    return 0;
}