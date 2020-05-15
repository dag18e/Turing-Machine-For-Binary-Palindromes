//This machine is a decider for binary palendromes

/*
Notes:
x is a marked character
a return of 0 means string was accepted
a return of 1 means string was rejected
*/



#include <iostream>
#include <string>
using namespace std;

int q0();         //start state
int q1();         //1 seen
int q2();         //0 seen
int q3();         //match seen
void print();     //prints the machine in its current state


int arrow = 0;    //which slot we're reading
string bin;       //the binary string

int main() {
  string bincopy;
  bool decision;
  bool con = true;

  while(con) {
    //get string from user
    cout << "Please enter a string of binary to see if it is a palindrome (q to exit): ";
    cin >> bin;

    //quit sim
    if(bin[0] == 'q' || bin[0] == 'Q') {
      con = false;
      break;
    }

    //save a copy of the string for outputting
    bincopy = bin;

    //concat a space character to the end so it can be processed correctly
    bin += (' ');

    //sim start
    while(1) {
      decision = q0();

      //in the language
      if(decision == 0) {
        cout << "The string " << bincopy << " is in the language.\n\n";
        break;
      }

      //not in the language
      else {
        cout << "The string " << bincopy << " is not in the language.\n\n";
        break;
      }
    }
    //sim end

    //reset arrow and string in case you want to try again
    bin = "";
    arrow = 0;
  }
}

//start state
int q0() {
  //find the first non x character by moving right one place at a time
  //Note: Only moves when character that is in the language was found
  while(bin[arrow] == 'x') {

    //element that is in the language was found
    if(bin[arrow] == '1' || bin[arrow] == '0' || bin[arrow] == 'x') {
      arrow++;
      print();
    }

    //element not in the language was found
    else {
      print();
      return 1;
    }
  }

  //if next space is space character, then 1 element palendrome
  if(bin[++arrow] == ' ')
    return 0;
  else
    arrow--;

  //if 1 go to q1
  if(bin[arrow] == '1') {
    //mark the element with an x
    bin[arrow] = 'x';

    print();

    return q1();
  }

  //if 0 go to q2
  else if(bin[arrow] == '0') {
    //mark the element with an x
    bin[arrow] = 'x';

    print();

    return q2();
  }

  //otherwise, a character not in the alphabet was found, so it's not in L
  else
    return 1;
}

//seen 1, attempt to match
int q1() {
  //if the spot one to the right of the current pos is an x, then it must be
  //a palindrome with an odd number of elements
  if(bin[++arrow] == 'x') {
    bin[arrow] = 'x';
    print();
    return q3();
  }


  //keep moving right one at a time until we find a space character
  while(bin[arrow] != ' ') {
    print();
    arrow++;
  }

  //keep moving left one at a time until we find a non x character
  while(bin[arrow] == 'x' || bin[arrow] == ' ') {
    print();
    arrow--;
  }

  //matching 1 was found
  if(bin[arrow] == '1') {
    //mark the match with an x
    bin[arrow] = 'x';

    print();

    return q3();
  }

  //something that isn't a 1 was found, so reject string
  else
    return 1;
}

//seen 0, attempt to match
int q2() {
  //if the spot one to the right of the current pos is an x, then it must be
  //a palindrome with an odd number of elements
  if(bin[++arrow] == 'x') {
    bin[arrow] = 'x';
    print();
    return q3();
  }

  //keep moving right one at a time until we find a space character
  while(bin[arrow] != ' ') {
    arrow++;
    print();
  }

  //keep moving left one at a time until we find a non x character
  while(bin[arrow] == 'x' || bin[arrow] == ' ') {
    arrow--;
    print();
  }

  //matching 1 was found
  if(bin[arrow] == '0') {
    //mark the match with an x
    bin[arrow] = 'x';

    print();

    return q3();
  }

  //something that isn't a 0 was found, so reject string
  else
    return 1;
}

//matched
int q3() {
  //check if the string has been entirely read
  if(bin[--arrow] == 'x') {
    print();
    return 0;
  }

  //keep moving left one at a time until we get to the start of the tape
  while(arrow != 0) {
    arrow--;
    print();
  }

  return q0();
}

void print() {
  string arrstr = "";

  cout << endl << bin << endl;

  //fills in a bunch of spaces to print out the arrow
  for(int i = 0; i < arrow; i++) {
    arrstr += ' ';
  }
  arrstr += '^';

  cout << arrstr << endl;
}
