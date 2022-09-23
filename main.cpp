#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "perfect.h"
#include "soundex.h"
#include <time.h> //for checking the main func time
using namespace std;


int main() {
    clock_t start,end; //check the main func operate time
    start = clock();
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

//    findPerfects(40000);
    // Comment out the above line and uncomment below line 
    // to switch between running perfect.cpp and soundex.cpp
    soundexSearch("res/surnames.txt");

    cout << endl << "main() completed." << endl;
    end = clock();
    cout << "time = " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;
    return 0;
}


// Do not remove or edit below this line. It is here to to confirm that your code
// conforms to the expected function prototypes needed for grading
void confirmFunctionPrototypes() {
    long n = 0;
    bool b;
    string s;

    n = divisorSum(n);
    b = isPerfect(n);
    findPerfects(n);

    n = smarterSum(n);
    b = isPerfectSmarter(n);
    findPerfectsSmarter(n);

    n = findNthPerfectEuclid(n);

    s = removeNonLetters(s);
    s = soundex(s);
    soundexSearch(s);
}
