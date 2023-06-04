#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

const int numPhilosophers = 5;
HANDLE philSemaphore;
bool forksAvailable[numPhilosophers];

enum PhilosopherState {
    THINKING,
    HUNGRY,
    EATING
};

PhilosopherState philosopherStates[numPhilosophers];

void Philosopher(int philosopherId) {
    int leftFork = philosopherId;
    int rightFork = (philosopherId + 1) % numPhilosophers;

    while (true) {
        // Философ думает
        philosopherStates[philosopherId] = THINKING;
        std::cout << "Philosopher " << philosopherId << " is thinking." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Философ голоден
        philosopherStates[philosopherId] = HUNGRY;
        std::cout << "Philosopher " << philosopherId << " is hungry." << std::endl;

        // Ожидание кушанья философа
        WaitForSingleObject(philSemaphore, INFINITE);

        // Проверяем свободные вилки
        while (!forksAvailable[leftFork] || !forksAvailable[rightFork]) {
            // Если нет ни одной свободной – освобождаем и начинаем снова
            ReleaseSemaphore(philSemaphore, 1, NULL);
            WaitForSingleObject(philSemaphore, INFINITE);
        }

        // Забираем вилки
        forksAvailable[leftFork] = false;
        forksAvailable[rightFork] = false;

        // Философ кушает
        philosopherStates[philosopherId] = EATING;
        std::cout << "Philosopher " << philosopherId << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Освобождаем вилки
        forksAvailable[leftFork] = true;
        forksAvailable[rightFork] = true;

        // Освобождаем поток
        ReleaseSemaphore(philSemaphore, 1, NULL);
    }
}

int main() {
    // Создаем семафор с начальным значением 2 (два философа начинаю кушанье, максимальное – количество философов)
    philSemaphore = CreateSemaphore(NULL, 2, numPhilosophers, NULL);

    // Освобождаем все вилки в самом начале
    for (int i = 0; i < numPhilosophers; ++i) {
        forksAvailable[i] = true;
    }

    // Создаем потоки философы 
    std::thread philosopherThreads[numPhilosophers];
    for (int i = 0; i < numPhilosophers; ++i) {
        philosopherThreads[i] = std::thread(Philosopher, i);
    }

    std::cout << "Dinner started!" << std::endl;

    std::cin.ignore();

    for (int i = 0; i < numPhilosophers; ++i) {
        philosopherThreads[i].join();
    }

    // Закрываем семафоры
    CloseHandle(philSemaphore);

    std::cout << "Dinner finished!" << std::endl;

    return 0;
}
