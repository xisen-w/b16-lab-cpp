// Question 2: Function Side-Effects

#include <iostream>

using namespace std; 

int num,res; 
void r(int s) {
while (num>=0) { num = num-s; } num=num+s; res=num;} 
int main() { num = 10;
r(4); printf
("%d\n" , res
) ; }


