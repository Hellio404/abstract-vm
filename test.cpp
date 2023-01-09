#include <iostream>

void fn(double a) {
    std::cout << "double" << std::endl;
}



void fn(long long a) {
    std::cout << "long long" << std::endl;
}

int main()
{
    int8_t a = 69;
    fn(a);
}