#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

void shuffleBags(int Boxes[], int N);
void wait(int seconds);
void eliminate(int array[]);
bool previouslyOpened(int i);
void gameRound(int array[]);
void makeOffer();
void clean(int* openedBoxes);

//global variables
int openedBoxes[10] = {0};
int boxSelected;
int counter = 10;
int boxSum;
int couldWin;
int Boxes[10] = { 1,5,10,20,50,100,1000,10000,100000,1000000 };
int rangeCheck;
char repeatGame = 'y';


int main() {

    //loop game
    
    while (repeatGame == 'y' || repeatGame == 'Y') {
        cout << "Shuffling";
        clean(openedBoxes);
        shuffleBags(Boxes, 10);
        for (int i = 0; i < 2; i++) {
            wait(1);
            cout << "...";
        }
        cout << endl;
        gameRound(Boxes);
        cout << "Do you want to play again?";
        cin >> repeatGame;
        system("CLS");
    }
    


}

void shuffleBags(int Boxes[], int N) {//used to shuffle the bags
    int index;
    int temp;

    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        index = rand() % 10; 
        temp = Boxes[i];
        Boxes[i] = Boxes[index];
        Boxes[index] = temp;
    }
}

void wait(int seconds) {//used to add some time before game start
    clock_t endwait;
    endwait = clock() + seconds + CLOCKS_PER_SEC;
    while (clock() < endwait) {}
}

void eliminate(int array[]) {//reveals the value of the bag
    cout << "This bag contains AED  " << array[boxSelected] << endl;
}

bool previouslyOpened(int i) {//checks if a bag was already opened
    if (openedBoxes[i] == 1) {
        return true;
    }
    else {
        openedBoxes[i] = 1;
        return false;
    }
}

void clean(int* openedBoxes) {//cleans the values and resets them
    for (int i = 0; i < 10; i++)
    {
        openedBoxes[i] = 0;
    }
}

void gameRound(int array[]) {//starts the game, callls makeoffer when needed
    int tries = 0;
    int deal;

    
        while (tries < 4) {
            cout << "Please choose a box: ";
            cin >> rangeCheck;
            boxSelected = rangeCheck - 1;
            boxSum = boxSum + Boxes[boxSelected];
            if (previouslyOpened(boxSelected)) {
                cout << "Box already opened!" << endl;
            }

            else if (rangeCheck < 1 || rangeCheck > 10) {
                cout << "Not in range!" << endl;
                cin.clear();
                cin.ignore(123, '\n');  

            }
            else {
                if (tries < 1) {
                    couldWin = array[boxSelected];
                    tries++;
                }
                else {
                    eliminate(array);
                    counter--;
                    tries++;
                }
            }
        }
        makeOffer();
        while (tries >= 4 && tries < 7) {
            cout << "Please choose a box: ";
            cin >> rangeCheck;
            boxSelected = rangeCheck - 1;
            boxSum = boxSum + Boxes[boxSelected];
            if (previouslyOpened(boxSelected)) {
                cout << "Box already opened!" << endl;
            }

            else if (rangeCheck < 1 || rangeCheck > 10) {
                cout << "Not in range!" << endl;
                cin.clear();
                cin.ignore(123, '\n');

            }
            else {
                eliminate(array);
                counter--;
                tries++;
            }
        }
        makeOffer();
        while (tries >= 7 && tries < 9) {
            cout << "Please choose a box: ";
            cin >> rangeCheck;
            boxSelected = rangeCheck - 1;
            boxSum = boxSum + Boxes[boxSelected];

            if (previouslyOpened(boxSelected)) {
                cout << "Box already opened!" << endl;
            }

            else if (rangeCheck < 1 || rangeCheck > 10) {
                cout << "Not in range!" << endl;
                cin.clear();
                cin.ignore(123, '\n');

            }
            else {
                eliminate(array);
                counter--;
                tries++;
            }
        }
        makeOffer();
        while (tries == 9) {
            int swapBox = 0;
            char finalBag;
            cout << "Do you want to open your chosen box or swap? (Y to open, N to swap)";
            cin >> finalBag;

            for (int i = 0; i < 10; i++) {
                if (previouslyOpened(i) == false) {
                    swapBox = i;
                }
            }
            if (finalBag == 'Y' || finalBag == 'y') {
                cout << "You won AED " << couldWin;
            }
            else if (finalBag == 'N' || finalBag == 'n') {
                cout << "You won AED " << Boxes[swapBox];
                
            }
            tries++;

        }
        
    


    
}

void makeOffer() {//creates a banker offer
    char acceptOffer;
    int total = 1111186;
    int bankerOffer = total - boxSum / counter;
    cout << "The banker's offer is AED " << bankerOffer << endl;
    cout << "Would you like to accept the offer? (Y if yes, N if no)";
    cin >> acceptOffer;
    if (acceptOffer == 'Y' || acceptOffer == 'y') {
        cout << "You have won AED " << bankerOffer << endl;
        cout << "You could have won AED " << couldWin;

    }
    else if (acceptOffer == 'N' || acceptOffer == 'n') {
        cout << "You have rejected the offer." << endl;
    }
}
