#include <iostream>
#include <cmath>
#include <chrono>
#include <omp.h>

double func(double x) {
    return sin(x); // Função a ser integrada, por exemplo, sin(x)
}

double integrate_serial(double a, double b, long n) {
    double h = (b - a) / n;
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < n; i++) {
        double x = a + i * h + h / 2.0;
        sum += func(x);
    }

    return sum * h;
}

int main() {
    double a = 0.0;
    double b = 3.141592653589793; // Intervalo de 0 a π (aproximadamente)
    long n = 6000000000; // Número de subintervalos

    auto start_time = std::chrono::high_resolution_clock::now();
    double result = integrate_serial(a, b, n);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Resultado da integral: " << result << std::endl;

    return 0;
}