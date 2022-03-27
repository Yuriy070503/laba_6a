#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>

char buffer[BUFSIZ];

void infinitePause() {
    for (;;) {}
}

// вывод осуществляется в поток, связанный с логами
#define TIME_TEST(testCode, message) { \
clock_t start_time = clock () ; \
testCode \
clock_t end_time = clock () ;\
clock_t sort_time = end_time - start_time ; \
std :: clog << message << ": " \
<< ( double ) sort_time / CLOCKS_PER_SEC << std :: endl ; \
}

template<typename T>
void outputCollection(const T &obj) {
    for (auto elem: obj)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main() {
    setbuf(stdout, buffer);

    const char *filename = " tmp . txt ";
    std::ofstream file(filename); // выполняем создание файла

    TIME_TEST ({
                   for (int i = 0; i < 1000000; i++)
                       file << 'a' << std::endl;
               }, " Often buffer reset ");

    TIME_TEST ({
                   for (int i = 0; i < 1000000; i++)
                       file << 'a' << '\n';
               }, " Buffer opt ");

    file.close(); // закрываем файл
    std:: remove(filename); // удаляем временный файл

    return 0;
}


