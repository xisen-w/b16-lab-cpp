## Question 2

(a) Explain what are function side-effects and why should they be avoided.

A: Function side-effects are when a function modifies a variable that is outside of its scope, like through the misuse of a pointer or global variable.

They should be avoided because they can lead to unexpected behaviour and also left the code vulnerable to external changes, modifications, and attacks. 

(b) Determine what the code below does, indicate its design flaws, and improve its design and presentation.

int num,res; void r(int s) {
while (num>=0) { num = num-s; } num=num+s; res=num;} int main() { num = 10;
r(4); printf
("%d\n" , res
) ; }

A: The code defines two variables: num and res. It then defines the function r that has no output and takes an integer s as input. The function then enters a while loop that decrements num by s until it is less than 0. It then adds s to num and assigns it to res. The main function initializes num to 10 and s to 4, calls the function r with s as the argument, and then prints the value of res. 

Given that 4 is the input of the function, the loop will run 3 times, decrementing num by 4 each time:
- First iteration: 10 -> 6
- Second iteration: 6 -> 2
- Third iteration: 2 -> -2
Then num becomes -2, and after adding s (4) back, the final value of num and res will be 2.

The code has several design flaws:
1. It uses global variables (num and res) which creates function side-effects
2. The function name 'r' is not descriptive
3. Poor code formatting makes it hard to read
4. The function's purpose (finding the remainder) is not clear from its implementation






