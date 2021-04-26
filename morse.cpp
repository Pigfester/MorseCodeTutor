/**********************************************************
 * Morse.cpp
 * Author:
 *    Sam Hammond
 * Date:
 *    April 2021
 * Summary:
 *    -Demonstrates proper functionality in storing the
 *       morse-code dictionary as a Binary Tree.
 *    -Accepts user input in form of dots and dashes with
 *       two individual keys.
 *    -Interperets the entered character by navigating the
 *       Binary Tree.
 *    -Shows other characters with same base pattern.
**********************************************************/

#include <stdio.h>
#include <string.h>
#include "BNode.h"

#define LEN 5//max characters to read per line

/**********************************************************
 * ToDo's:
 *    
**********************************************************/

BNode <char> * morseTreeRoot;

//Prototype methods
void buildMorseBinaryTree();
void pollKeys(string *, char, char);
void pollKeyPrep(char *, char *);
void translate(string);
/**********************************************************
 * main: my main main!
 *    builds Binary Tree
 *    demonstrates Binary Tree stores Morse Code properly
 *    Promps user for desired dot/dash keys
 *    Enters a loop interperating string of input
 *       Prompts user for input
 *       interperets; displays characters with same base
 *       enter 'q' to exit
**********************************************************/
int main() {
   buildMorseBinaryTree();
   displayLVR(morseTreeRoot);
   cout << "\n\n";
   //cout << "Size: " << sizeBTree(morseTreeRoot) << endl;//Should be 40
   char dot = '.';
   char dash = '-';
   pollKeyPrep(&dot, &dash);

   while (true) {
      string keyPresses;
      pollKeys(&keyPresses, dot, dash);

      //Quit if 'q' was pressed first
      if (keyPresses[0] == 'q') {
         cout << "done\n";
         break;
      }

      cout << "Your input:\t " << keyPresses << endl;
      translate(keyPresses);
   }
}

void translate(string in) {
   BNode <char> * temp = morseTreeRoot;
   for (int i = 0; i < in.length() && temp != NULL; i++) {
      if (in[i] == '.') {
         temp = temp->pLeft;
      }
      else if (in[i] == '-') {
         temp = temp->pRight;
      }
      else if (in[i] == ' ') {
         cout << "Non dot or dash character\n";
         break;
      }
   }
   if (temp == NULL || temp->data == ' ') {
      cout << "Invalid entry\n";
   }
   else {
      cout << "\tInterpereted:\t" << temp->data << endl
           << "\tPossibilites:\t" << temp << endl;
   }
}

void pollKeyPrep(char * dot, char * dash) {
   cout << "What is your key choice for\n";
   cout << "\tdot:\t";
   cin >> dot;
   cout << "\tdash:\t";
   cin >> dash;
   cin.ignore();
}

void pollKeys(string * keys, char dot, char dash) {
   cout << "\nEnter Morse code; or (q)uit: ";
   string input;
   getline(cin, input);

   if (input[0] == 'q') {
      cout << "Closing...";
      *keys = 'q';
      return;
   }
   //Only read up to LEN (#define) characters
   for (int i = 0; i < input.length() && i < LEN; i++) {
      if (input[i] == dot) {
         *keys += '.';
      }
      else if (input[i] == dash) {
         *keys += '-';
      }
      else {
         *keys += ' ';
      }
   }
}

/**********************************************************
 * buildMorseBinaryTree
 * 
 * Builds Binary tree of Morse Code Alphabet in Level-Order
 * Left direction indicates dot
 * Right direction indicates dash
 * root is a space
 * unused more code is indicate with a period ('.')
**********************************************************/
void buildMorseBinaryTree() {
   //const string aphabetLVR = "5H4S.V3I.F.U..2E.L.R...A.P.W.J1 6B.D.X.N.C.K.Y.T7Z.G.Q.M8..O9.0";
   cout << "Building Morse Binary Tree...";
   morseTreeRoot = new BNode<char>(' ');
   //First Layer
   BNode <char> * e = new BNode<char>('E');
   addLeft(morseTreeRoot, e);//.
   BNode <char> * t = new BNode<char>('T');
   addRight(morseTreeRoot, t);//-

   //Second Layer
   BNode <char> * i = new BNode<char>('I');
   addLeft(e, i);//..
   BNode <char> * a = new BNode<char>('A');
   addRight(e, a);//.-

   BNode <char> * n = new BNode<char>('N');
   addLeft(t, n);//-.
   BNode <char> * m = new BNode<char>('M');
   addRight(t, m);//--

   //Third Layer
   BNode <char> * s = new BNode<char>('S');
   addLeft(i, s);//...
   BNode <char> * u = new BNode<char>('U');
   addRight(i, u);//..-
   BNode <char> * r = new BNode<char>('R');
   addLeft(a, r);//.-.
   BNode <char> * w = new BNode<char>('W');
   addRight(a, w);//.--

   BNode <char> * d = new BNode<char>('D');
   addLeft(n, d);//-..
   BNode <char> * k = new BNode<char>('K');
   addRight(n, k);//-.-
   BNode <char> * g = new BNode<char>('G');
   addLeft(m, g);//--.
   BNode <char> * o = new BNode<char>('O');
   addRight(m, o);//---

   //Fourth Layer
   BNode <char> * h = new BNode<char>('H');
   addLeft(s, h);//....
   BNode <char> * v = new BNode<char>('V');
   addRight(s, v);//...-
   BNode <char> * f = new BNode<char>('F');
   addLeft(u, f);//..-.
   //Empty
   BNode <char> * uRight = new BNode<char>('.');
   addRight(u, uRight);//..--
   BNode <char> * l = new BNode<char>('L');
   addLeft(r, l);//.-..
   //Everything Right of r is empty
   BNode <char> * p = new BNode<char>('P');
   addLeft(w, p);//.--.
   BNode <char> * j = new BNode<char>('J');
   addRight(w, j);//.---

   BNode <char> * b = new BNode<char>('B');
   addLeft(d, b);//-...
   BNode <char> * x = new BNode<char>('X');
   addRight(d, x);//-..-
   BNode <char> * c = new BNode<char>('C');
   addLeft(k, c);//-.-.
   BNode <char> * y = new BNode<char>('Y');
   addRight(k, y);//-.--
   BNode <char> * z = new BNode<char>('Z');
   addLeft(g, z);//--..
   BNode <char> * q = new BNode<char>('Q');
   addRight(g, q);//--.-
   //Empty;
   BNode <char> * oLeft = new BNode<char>('.');
   addLeft(o, oLeft);//---.
   //Empty
   BNode <char> * oRight = new BNode<char>('.');
   addRight(o, oRight);//----

   //Fifth Layer
   BNode <char> * five = new BNode<char>('5');
   addLeft(h, five);//.....
   BNode <char> * four = new BNode<char>('4');
   addRight(h, four);//....-
   //vLeft is Empty
   BNode <char> * three = new BNode<char>('3');
   addRight(v, three);//...--
   //fLeft is Empty
   //fRight is Empty
   //uRight already defined
   //uLeftLeft is Empty
   BNode <char> * two = new BNode<char>('2');
   addRight(uRight, two);//..---
   //lLeft is Empty
   //lRight is Empty
   //Everything after rRight is empty
   //pLeft is Empty
   //pRight is Empty
   //jLeft is Empty
   BNode <char> * one = new BNode<char>('1');
   addRight(j, one);//.----

   BNode <char> * six = new BNode<char>('6');
   addLeft(b, six);//-....
   //bRight is Empty
   //xLeft is Empty
   //xRight is Empty
   //cLeft is Empty
   //cRight is Empty
   //yLeft is Empty
   //yRight is Empty
   BNode <char> * seven = new BNode<char>('7');
   addLeft(z, seven);//--...
   //zRight is Empty
   //qLeft is Empty
   //qRight is Empty
   //oLeft already defined
   BNode <char> * eight = new BNode<char>('8');
   addLeft(oLeft, eight);//---..
   //oRightRight is Empty
   //oRight already defined
   BNode <char> * nine = new BNode<char>('9');
   addLeft(oRight, nine);//----.
   BNode <char> * zero = new BNode<char>('0');
   addRight(oRight, zero);//-----
   cout << "done.\n";
}