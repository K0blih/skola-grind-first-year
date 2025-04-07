#include <iostream>
#include <cmath>
using namespace std;

class Queue {
public:
    int front = -1;
    int index = -1;
    int size;
    int* arr = nullptr;

    Queue(int size) {
        this->size = size;
        this->arr = new int[this->size];
    }

    ~Queue() {
        delete[] this->arr;
        this->arr = nullptr;
    }

    bool isEmpty() {
        if (front == -1) {
            return true;
        }
        else {
            return false;
        }
    }

    bool isFull() {
        if (index == size - 1) {
            return true;
        }
        else {
            return false;
        }
    }

    void push(int value) {
        if (isFull()) { return; }
        else {
            if (front == -1) {
                front = 0;
            }
            this->index++;
            this->arr[this->index] = value;
        }
    }

    int pop() {
        if (isEmpty()) { return -1; }
        else {
            int value = this->arr[front];
            if (front == index) {
                front = -1;
                index = -1;
            }
            else {
                front++;
            }
            return value;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue elements: ";
        for (int i = front; i <= index; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

class Sito {
public:
    int size;
    int* arr = nullptr;

    Sito(int size) {
        this->size = size - 1;
        this->arr = new int[this->size];
    }

    ~Sito() {
        delete[] this->arr;
        this->arr = nullptr;
    }

    void initSito() {
        for (int i = 0; i < this->size; i++) {
            arr[i] = i + 2;
        }
    }

    void loop() {
        for (int i = 0; i < this->size; i++) {
            if (arr[i] == 0) {
                continue;
            }

            for (int j = i + 1; j < this->size; j++) {
                if (arr[j] != 0 && arr[j] % arr[i] == 0) {
                    arr[j] = 0;
                }
            }
        }
    }

    void display() {
        cout << "Prime numbers: ";
        for (int i = 0; i < this->size; i++) {
            if (arr[i] != 0) {
                cout << arr[i] << " ";
            }
        }
        cout << endl;
    }
};

void eratosthenes(int N, int* L) {
    // Initialize array
    for (int i = 0; i <= N; i++) {
        L[i] = i;
    }

    // Mark 0 and 1 as non-prime
    L[0] = L[1] = 0;

    // Apply Sieve of Eratosthenes
    int sqrtN = (int)floor(sqrt((float)N));
    for (int p = 2; p <= sqrtN; p++) {
        if (L[p] != 0) {  // If p is prime
            // Mark all multiples of p as non-prime
            for (int j = p * p; j <= N; j += p) {
                L[j] = 0;
            }
        }
    }
}

void printPrimes(int* L, int N) {
    cout << "Prime numbers using eratosthenes function: ";
    for (int i = 2; i <= N; i++) {
        if (L[i] != 0) {
            cout << L[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    // Using the Sito class
    Sito sito = Sito(25);
    sito.initSito();
    sito.loop();
    sito.display();

    // Using the eratosthenes function
    int N = 25;
    int* L = new int[N + 1];
    eratosthenes(N, L);
    printPrimes(L, N);
    delete[] L;

    // Using the Queue class
    Queue queue(10);
    cout << "Queue demonstration:" << endl;
    cout << "Pushing values 1-5 to queue" << endl;
    for (int i = 1; i <= 5; i++) {
        queue.push(i);
    }
    queue.display();

    cout << "Popping values from queue" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Popped: " << queue.pop() << endl;
    }
    queue.display();

    return 0;
}