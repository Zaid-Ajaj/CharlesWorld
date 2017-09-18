#include <iostream>
#include <cmath>

using namespace std;

// Name: Ciske Harsema / s1010048 / Informatica
// Name: Zaid Ajaj / s4807561 / Informatica & Wiskunde


double square(double x)
{
    return x * x;
}

void printIterations(int i, double x, double a, double b)
{
    cout << "i = " << i << "\tx = " << x << "\ta = " << a << "\tb = " << b << endl;
}

// Assignment part 1.2
// Approximate the square-root value of v within an error of e using the Inclusion method
double inclusion(double e, double v)
{
    // used for printing the results of each iteration as per the requirements of the assignment
    int iterationCount = 0;
    // loop until you found the largest n such that
    // n * n <= v
    int n = 0;
    while (square(n + 1) <= v)
    {
        n = n + 1;
    }
    // if n * n == v then we are done
    if (abs(square(n) - v) <= e)
    {
        // square root found
        printIterations(0, n, n, n + 1);
        return n;
    }
    // define initial values for second iteration
    // where a * a < v <= b * b
    // this means that v is in the interval [a*a, b*b]
    // and x will be in the interval [a, b]
    double a = n;
    double b = a + 1;
    // x will be approximated as the average value of the interval
    double x = (a + b) / 2.0;
    // as long as the halting-condition has not been met
    // take better approximations of x until we have reached the desired accuracy
    while (abs(square(x) - v) >= e)
    {
        // print the results of the iterations as per the requirements of the assignment
        printIterations(iterationCount, x, a, b);
        if (square(x) < v)
        {
            // if x*x < v then this means that x < sqrt(v) so we have to increase the value of x
            // by increasing the lower bound a of the interval [a, b]
            // therefore we update the interval [a, b] into [(a + b) / 2, b] or simply [x, b],
            // because x = (a + b) / 2
            a = x;
        }
        else
        {
            // otherwise, x * x > v <=> x > sqrt(v) which means that we have to decrease the value of x
            // by decreasing the value of the upper bound b in the interval [a, b]
            // therefore, we update the interval [a, b] into [a, (a + b) / 2] or simply [a, x]
            // because x = (a + b) / 2
            b = x;
        }
        // now after narrowing the interval [a, b] down, we calculate a better approximation for x
        // by calculating the average of the lower (a) and upper (b) bounds of the interval
        x = (a + b) / 2.0;
        iterationCount = iterationCount + 1;
    }

    return x;
}

// Assignment part 1.3
// Approximate the square-root value of v within an error of e using the Newton-Raphson method
double newtonraphson(double e, double v)
{
    // used for printing the results of each iteration as per the requirements of the assignment
    int iterations = 0;
    // the initial approximation
    double x = 1;

    if (v > 1)
    {
        // loop until x becomes the largest number such that x * x <= v
        while (square(x + 1) <= v)
        {
            x = x + 1;
        }
    }

    if (abs(square(x) - v) <= e)
    {
        // then no extra iterations are needed and x is the answer
        cout << "i = " << iterations << "\tx = " << x;
        return x;
    }

    // as long as the halting-condition has not been met
    // take better approximations of x until we have reached the desired accuracy
    while(abs(square(x) - v) >= e)
    {
        // next value of x = previous value of x - f(x)/f'(x)
        // where f(x) = x^2 - v and f'(x) = 2x
        x = x - ((square(x) - v) / (2 * x));
        iterations = iterations + 1;
        cout << "i = " << iterations << "\tx = " << x << endl;
    }

    return x;
}

/*

Desktop Tests - Assignment Part 1.1
Below are the results of the functions used here

Inclusion(0.01, 0)
i = 0	x = 0	a = 0	b = 1
sqrt(0) = 0

NewtonRaphson(0.01, 0)
i = 1	x = 0.5
i = 2	x = 0.25
i = 3	x = 0.125
i = 4	x = 0.0625
sqrt(0) = 0.0625


Inclusion(0.01, 1)
i = 0	x = 1	a = 1	b = 2
sqrt(1) = 1

NewtonRaphson(0.01, 1)
i = 0	x = 1
sqrt(1) = 1


Inclusion(0.01, 0.25)
sqrt(0.25) = 0.5

NewtonRaphson(0.01, 0.25)
i = 1	x = 0.625
i = 2	x = 0.5125
i = 3	x = 0.500152
sqrt(0.25) = 0.500152


Inclusion(0.01, 16)
i = 0	x = 4	a = 4	b = 5
sqrt(16) = 4

NewtonRaphson(0.01, 16)
i = 0	x = 4
sqrt(16) = 4


Inclusion(0.01, 83)
i = 0	x = 9.5	    a = 9	b = 10
i = 1	x = 9.25	a = 9	b = 9.5
i = 2	x = 9.125	a = 9	b = 9.25
i = 3	x = 9.0625	a = 9	b = 9.125
i = 4	x = 9.09375	a = 9.0625	b = 9.125
i = 5	x = 9.10938	a = 9.09375	b = 9.125
i = 6	x = 9.11719	a = 9.10938	b = 9.125
i = 7	x = 9.11328	a = 9.10938	b = 9.11719
i = 8	x = 9.11133	a = 9.10938	b = 9.11328
sqrt(83) = 9.11035

NewtonRaphson(0.01, 83)
i = 1	x = 9.11111
i = 2	x = 9.11043
sqrt(83) = 9.11043

*/


/*

Algorithms comparisons - Assignment part 1.4

from the Desktop test results shown in the comment above we can infer that the inclusion method is more accurate than
Newton-Raphson method when dealing with small numbers (such as 0 and 0.25) but the Newton-Raphson method is much better for larger numbers
such as 83 as it converged faster (= required less iterations) than the inclusion method to find the approximation

*/

int main()
{

    // To reproduce the results used in the desktop tests
    // uncomment the code below

    /*
    double numbers[] = { 0, 1, 0.25, 16, 83 };
    for(int i = 0; i < 5; i++)
    {
        cout << "sqrt(" << numbers[i] << ") = " << inclusion(0.01, numbers[i]) << endl;
        cout << "sqrt(" << numbers[i] << ") = " << newtonraphson(0.01, numbers[i]) << endl;
        cout << "" << endl;
        cout << "" << endl;
    }
    */

    return 0;
}
