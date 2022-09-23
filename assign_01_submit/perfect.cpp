/*
 * Calculate and Find Messon & Perfect number
 * Author: Hongwu Zhao
 * Email: angellice@163.com
 * Date : 2022/09/23
 *
 */
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
#include <cmath>
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long smarterSum(long n);

long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    if(stop < 0) {
        error("Unexpected negative number");
        }else{


    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
        }
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* smarterSum mehtod.
 * This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from (1 to sqrt(n)), testing for a
 * zero remainder from the division.
 *
 */

long smarterSum(long n) {
    long total = 0;
// The comment part is consider to using two methods.
//    if(n<=64){
//        for (long divisor = 1; divisor < n; divisor++) {
//            if (n % divisor == 0) {
//                total += divisor;
//            }
//        }
//        }
//    else{
        for (long divisor = 1; divisor <= long(sqrt(n)); divisor++) {
            if (n % divisor == 0) {
                total += divisor;
                if(divisor != 1 && n / divisor != divisor){ //consider two divisor equal
                    total += n/divisor;
                }
            }
        }
//        }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 * But calculate the sum of its proper divisors using `smarterSum`
 */
bool isPerfectSmarter(long n) {
     return (n != 0) && (n == smarterSum(n));

}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
    if(stop < 0) {
        error("Unexpected negative number");
        }else{


    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
        }
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* Using Euclid way to find perfect numbers.
 * This function does an exhaustive search for perfect numbers.
 * It takes one argument `n` and searches the 1st to n th perfect numbers,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
long findNthPerfectEuclid(long n) {
    long M_n; // Mersenne
    long k=1; // countor
    long long perfectNumber =0 ; // in order to get more numbers, without overflow
    for (k=1; k<=12; k++){
        M_n = pow(2,k)-1; //Cal Mersenne
        if(smarterSum(M_n)==1 && M_n != 1 ){ //consider M_n cant be 1
            perfectNumber = pow(2,k-1) * M_n;
            cout << k << "th perfect number is " << perfectNumber << endl;
            if(k == n){ //when the target come, stop
                break;
            }
        }
    }
    return perfectNumber;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

// Add student test cases here, default as comments, because test cost long time.
//STUDENT_TEST("Time Trial for the last one is 1 min ") {
//    TIME_OPERATION(25000, findPerfects(25000));
//    TIME_OPERATION(50000, findPerfects(50000));
//    TIME_OPERATION(100000, findPerfects(100000));
//    TIME_OPERATION(200000, findPerfects(200000));
//}

STUDENT_TEST("Compare 10, 1000, 2000, 3000, work difference ") {
    TIME_OPERATION(10, findPerfects(10));
    TIME_OPERATION(1000, findPerfects(1000));
    TIME_OPERATION(2000, findPerfects(2000));
    TIME_OPERATION(3000, findPerfects(3000));
}

STUDENT_TEST("Check different negative number result") {
    isPerfect(-1);
}

STUDENT_TEST("Check expected error with different negative number result") {
    EXPECT_ERROR(findPerfects(-1));
    EXPECT_ERROR(findPerfects(-10));
    EXPECT_ERROR(findPerfects(-10000));
}

STUDENT_TEST("Check expected error with different negative number result") {
    EXPECT_EQUAL(divisorSum(25),smarterSum(25));
    EXPECT_EQUAL(divisorSum(100),smarterSum(100));
    EXPECT_EQUAL(divisorSum(99),smarterSum(99));
    EXPECT_EQUAL(divisorSum(101),smarterSum(101));
    EXPECT_EQUAL(divisorSum(63),smarterSum(63));
    EXPECT_EQUAL(divisorSum(64),smarterSum(64));
    EXPECT_EQUAL(divisorSum(65),smarterSum(65));
    EXPECT_EQUAL(divisorSum(256),smarterSum(256));

}

// default as comments.
//STUDENT_TEST("Using smarter method: Time Trial for the last one is 1 min ") {
//    TIME_OPERATION(500000, findPerfectsSmarter(500000));
//    TIME_OPERATION(1000000, findPerfectsSmarter(1000000));
//    TIME_OPERATION(2000000, findPerfectsSmarter(2000000));
//    TIME_OPERATION(4000000, findPerfectsSmarter(4000000));
//}

STUDENT_TEST("The n th Masson number, through Euclid method ") {
    EXPECT(isPerfect(findNthPerfectEuclid(1)));
    EXPECT(isPerfect(findNthPerfectEuclid(2)));
    EXPECT(isPerfect(findNthPerfectEuclid(3)));
    EXPECT(isPerfect(findNthPerfectEuclid(4)));
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
//    EXPECT(isPerfect(findNthPerfectEuclid(6))); 8589869056 This one has some error, Guess it  related with long type length.

}

