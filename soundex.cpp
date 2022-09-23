/*
 * Reproduce the process of `Soundex` algorithm
 * Author: Hongwu Zhao
 * Email: angellice@163.com
 * Date : 2022/09/23
 *
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result = "\0";
    charToString(s[0]);
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

/* This function is intended to encode letters to `Soundex`
 * by the following Algorithm:
 *
 * A/E/I/O/U/W/Y    ---> 0
 * B/F/P/V          ---> 1
 * C/G/J/K/Q/S/X/Z  ---> 2
 * D/T              ---> 3
 * L                ---> 4
 * M/N              ---> 5
 * R                ---> 6
 */
string encodeLetters(string s) {
    string result ;
    for(int i = 0; i < s.length(); i++){
        if(s.at(i) == 'A' || s.at(i) =='E' ||s.at(i) =='I' ||s.at(i) =='O' || s.at(i) =='U' ||
                s.at(i) =='H' ||s.at(i) =='W' || s.at(i) =='Y' ||s.at(i) =='a' ||s.at(i) =='e' ||
                s.at(i) =='i' || s.at(i) =='o' || s.at(i) =='u' || s.at(i) =='h' ||s.at(i) =='w' ||
                s.at(i) =='y' ){
            s.replace(i,1,"0");
        }else if(s.at(i) == 'B' || s.at(i) =='F' || s.at(i) =='P' || s.at(i) =='V' ||
                 s.at(i) =='b' || s.at(i) =='f' || s.at(i) =='p' || s.at(i) =='v'){
            s.replace(i,1,"1");
        }else if(s.at(i) == 'C' || s.at(i) =='G' || s.at(i) =='J' || s.at(i) =='K' ||
                 s.at(i) =='Q' || s.at(i) =='S' || s.at(i) =='X' || s.at(i) =='Z' ||
                 s.at(i) =='c' || s.at(i) =='g' || s.at(i) =='j' || s.at(i) =='k' ||
                 s.at(i) =='q' || s.at(i) =='s' || s.at(i) =='x' || s.at(i) =='z'){
            s.replace(i,1,"2");
        }else if(s.at(i) == 'D' || s.at(i) =='T' ||s.at(i) =='d' || s.at(i) =='t'){
            s.replace(i,1,"3");
        }else if(s.at(i) == 'L' || s.at(i) =='l'){
            s.replace(i,1,"4");
        }else if(s.at(i) == 'M' || s.at(i) =='N' || s.at(i) =='m' || s.at(i) =='n'){
            s.replace(i,1,"5");
        }else{
            s.replace(i,1,"6");
        }
        result += s[i];
    }

    return result;
}

/* This function is intended to delete the duplication numbers
 */
string deleteDuplication(string s) {
    string result;
    for(int i=1; i<s.length(); i++){ //delete from left to right
        if(s.at(i)==s.at(i-1)){
            s.erase(i,1);
            for(int j=s.length()-1; j>0;j--){ //delete from right to left
                if(s.at(j)==s.at(j-1)){
                    s.erase(j,1);
                }
            }
        }
    }
    result = s;
    return result;
}

/* This function is intended to replace the first code by the first alphabet of surname.
 * Make the alphabet as capital.
 */
string replaceFirstLetter(string sur, string s ) {
    string result;
    string tmp = charToString( ::toupper(sur.at(0))); //get the first alphabet of surname, change to capital
    result = s.replace(0,1,tmp); //Do the replace process
    return result;
}


/* This function is intended to delete all the zero in `Soundex` code.
 */
string deleteZero(string s) {
    string result;

    for(int i=0; i<s.length(); i++ ){ //delete from left to right
        if(s.at(i) == '0'){
            s.erase(i,1); //delete process
            for(int j =s.length()-1; j>0; j--){ //delete from right to left
                if(s.at(j)== '0'){
                    s.erase(j,1);
                }
            }
        }
    }
    result = s;
    return result;
}

/* This function is intended to make sure the `Soundex` code as 4 letters stand.
 */

string addToFour(string s) {
    string result;
    if(s.length()<4){ //if less than 4, add 0
        long tmp= 4-s.length();
         s.append(tmp,'0');
    }else if(s.length()>4){ //if greater than 4, delete from tail
        s.erase(4);
    }

    result = s;
    return result;
}

/* This function is intended to achieve the `Soundex` algorithm.
 *
 */
string soundex(string s) {
    string sur =s;
    string result;

    result = addToFour(deleteZero(replaceFirstLetter(sur, deleteDuplication(encodeLetters(removeNonLetters(s))))));
    // 6->stand four **5-> del 0** 4->replace 1st letter **3->del dupli code **2-> encode**1->rem non-letter
    return result;
}


/* This function is intended to using the `Soundex` algorithm make a search system.
 *
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;
    while(true){ // make usr repeat type
        string s = getLine("Please type the surname you wanna search: ");
        string usrType = soundex(s); //change usr tpye to Soundex code
        Vector<string> usrOutput;
        for(int i = 0; i <databaseNames.size(); i++){ //compare the usr code with database
            string tmp = soundex(databaseNames[i]);
            if(usrType == tmp){ //if the code match, save
               usrOutput.add(databaseNames[i]);
            }
        }
        usrOutput.sort(); //sort the usr result
        for(int i =0 ; i< usrOutput.size(); i++){ //print the result
                cout << usrOutput[i] << endl;
        }
    }


    // The names in the database are now stored in the provided
    // vector named databaseNames

}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here
STUDENT_TEST("Student Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "9Planet";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "  tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}

STUDENT_TEST("Encode the letters") {
    string s = "c";
    string result = encodeLetters(s);
    EXPECT_EQUAL(result, "2");
    s = "Planet";
    result = encodeLetters(s);
    EXPECT_EQUAL(result, "140503");
    s = "tLdr";
    result = encodeLetters(s);
    EXPECT_EQUAL(result, "3436");
}

STUDENT_TEST("Delete duplication code") {
    string s = "322";
    string result = deleteDuplication(s);
    EXPECT_EQUAL(result, "32");
    s = "4222221";
    result = deleteDuplication(s);
    EXPECT_EQUAL(result, "421");
    s = "115588";
    result = deleteDuplication(s);
    EXPECT_EQUAL(result, "158");
    s = "13355577779";
    result = deleteDuplication(s);
    EXPECT_EQUAL(result, "13579");
}
STUDENT_TEST("Replace sur first capital letter") {
    string s = "4321";
    string sur = "Zhao";
    string result = replaceFirstLetter(sur, s);
    EXPECT_EQUAL(result, "Z321");
}

STUDENT_TEST("Delete all zero") {
    string s = "Z0020";
    string result = deleteZero(s);
    EXPECT_EQUAL(result, "Z2");
}

STUDENT_TEST("Add 0 to four code") {
    string s = "Z2";
    string result = addToFour(s);
    EXPECT_EQUAL(result, "Z200");
}
