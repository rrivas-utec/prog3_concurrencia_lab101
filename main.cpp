#include <iostream>
#include <thread>
#include <cmath>
using namespace std;

void fun_1() {
    cout << "Fun #1, Hilo #: " << this_thread::get_id() << endl;
}

void fun_2() {
    cout << "Fun #2, Hilo #: " << this_thread::get_id() << endl;
}

void fun_3() {
    cout << "Fun #3, Hilo #: " << this_thread::get_id() << endl;
}

void ejemplo_1() {
    cout << "Ejemplo_1, Hilo #: " << this_thread::get_id() << endl;
    thread t1(fun_1);
    thread t2;
    t2 = thread(fun_2);
    thread t3;
    t3 = thread(fun_3);

    t1.join();
    t2.join();
    t3.detach();
    cout << "Ejecucion Exitosa\n";
}

void saludar(const string name) {
    cout << "Hola " << name << "!!!\n";
}

void ejemplo_2() {
    thread t1;
    t1 = thread(saludar, "Jose"); // Parametro por copia
    t1.join();
}

void sumar_1 (int a, int b, int* ptr_total) {
    *ptr_total = a + b;
}

void sumar_2 (int a, int b, int& total) {
    total = a + b;
}

void ejemplo_3a() {
    int total = 0;
    thread t1(sumar_1, 10, 40, &total);
    t1.join();
    cout << total << endl;
}

void ejemplo_3b() {
    int total = 0;
    thread t1(sumar_2, 10, 40, ref(total));
    t1.join();
    cout << total << endl;
}

void ejemplo_lambda() {
    int x = 10;
    int y = 40;
    // La declaracion del lambda
    auto lambda = [x](){ // [=|&|var1,var2|&var1, &var2]
        cout << x << endl;
    };
    // Llamada
    lambda();

    auto lambda2 = [](int a, int b) {
        return a + b;
    };
    cout << lambda2(1, 300) << endl;
}

void ejemplo_4() {
    int total = 0;
    thread t1([&total](){ sumar_2(10, 20, total); });
    t1.join();
    cout << total << endl;
}

class point_t {
    int x = 0;
    int y = 0;
public:
    point_t(int x, int y): x(x), y(y) {}
    void show() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
    void calculate_distance(int x2, int y2, double& distance) const {
        distance = sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2));
    }
};

void ejemplo_5() {
    point_t p1(10, 40);
    point_t p2(40, 80);
    thread t1;
    t1 = thread(&point_t::show, &p1);
    t1.join();
    double distance = 0;
    thread t2(&point_t::calculate_distance, &p2, 80, 160, ref(distance));
    t2.join();
    cout << distance << endl;
}

int main() {
    cout << "Main Hilo #: " << this_thread::get_id() << endl;
//    ejemplo_1();
//    ejemplo_2();
//    ejemplo_3a();
//    ejemplo_3b();
//    ejemplo_lambda();
//    ejemplo_4();
    ejemplo_5();
    return 0;
}
