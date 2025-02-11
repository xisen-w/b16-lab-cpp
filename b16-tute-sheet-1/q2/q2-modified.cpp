#include <iostream>

using namespace std;

// Calculate remainder when dividing num by divisor
int calculateRemainder(int num, int divisor) {
    while (num >= divisor) {
        num = num - divisor; // In this case num wouldn't be negative.
    }
    return num;
}

int main() {
    int num = 10;
    int result = calculateRemainder(num, 4);
    cout << result << endl;
    return 0;
}   