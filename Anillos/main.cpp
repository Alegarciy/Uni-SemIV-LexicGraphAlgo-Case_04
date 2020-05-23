#include <iostream>
#include "Anillo.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    Anillo * anillo = new Anillo(40);
    anillo->PrintPos();

    return 0;
}
