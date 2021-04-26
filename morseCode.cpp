#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "BNode.h"

/**********************************************************
 * ToDo's:
 *    Set dot/dash/space period definitions with #define
 *    Confirm cout works on Pico?
 *    Character Recognition
 *       Instantiate local BNode in main
 *       Move left/right upon each release of button
 *       Instantiate character, assign value of BNode
 *       Display character when space detected
 *    Word Recongition
 *       Instantiate string or char[] that can be appended
 *       Add each successful recongized character to word
 *    Speed Adjustment
 *       Adjust #defines
 *       Use hardware input (potentiometer, slide switches)
 *       Auto-detect human-baud rate
 *          Counter average history; identify '-', '.', ' '
**********************************************************/

#define LOOP_DELAY 50//milliseconds

const uint LED_PIN = 25;
const uint btn = 19;
BNode <char> * morseTreeRoot;

//Prototype methods
void setup();
void buildMorseBinaryTree();

/**********************************************************
 * main
 * 
 * My main man :)
**********************************************************/
int main() {
   setup();
   displayLVR(morseTreeRoot);
   cout << "\nSize: " << sizeBTree(morseTreeRoot) << endl;
   //These two could be consolidated to one variable: not used simultaneously
   int pressed = 0;
   int notPressed = 0;
   bool lastState = false;

   //All we are going to do is poll the button and count when pressed/notPressed
   while(true) {
      //If pushed
      if(gpio_get(btn)) {
         //If pushed since last poll
         if(!lastState) {
            lastState = true;
            notPressed = 0;
            cout << "Button was not Pressed for " << notPressed << "Seconds\n";
         }
         //Increment pressed Counter
         pressed += LOOP_DELAY;
      }
      //If released since last pull
      else if(lastState) {
         lastState = false;
         pressed = 0;
         cout << "Button Was Pressed for " << pressed << " Seconds\n";
         //Dash Detected
         if(pressed > 2000 && pressed < 3000) {
            cout << "Dash Interpereted\n";
         }
         //Dot Detected
         else if(pressed > 1000 && pressed > 500) {
            cout << "Dot Interpereted\n";
         }
         //Your a Noob: try again
         else {
            cout << "Unintelligent Input: Too long or too short\n";
         }
      }
      //If not pushed
      else {
         //Increment notPressed counter
         notPressed += LOOP_DELAY;

         //Space Detected
         if(notPressed > 3000) {
            //Reset notPressed counter
            notPressed = 0;
            cout << "Space Interpereted\n";
         }
      }

      //Sleep - blocking
      sleep_ms(LOOP_DELAY);
   }
}

void setup() {
   //bi_decl(bi_program_description("Learn Morse Code."));
   //bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
   stdio_init_all();
   gpio_init(LED_PIN);
   gpio_set_dir(LED_PIN, GPIO_OUT);
   gpio_init(btn);
   gpio_set_dir(btn, GPIO_IN);
   buildMorseBinaryTree();
}

/**********************************************************
 * buildMorseBinaryTree
 * 
 * Builds Binary tree of Morse Code Alphabet in Level-Order
 * Left direction indicates dot
 * Right direction indicates dash
 * root is a space
 * unused patterns but utlized link are indicated with '.'
**********************************************************/
void buildMorseBinaryTree() {
   //const string morseLVR = "5H4S.V3I.F.U..2E.L.R...A.P.W.J1 6B.D.X.N.C.K.Y.T7Z.G.Q.M8..O9.0";

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
   //Empty
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
}