#include <iostream>
using namespace std;

class cell{
    private:
    bool alive;

    public:
    cell(){
        alive = false;
    };
    cell(bool a){
        alive = a;
    };
    void update(){
        alive = !alive;
    };
    void display(){ // not needed atm just want to mess around
        cout<<alive<<endl;
    };
};

class board{
    private:
    int dimension;
    bool **field; //eventually implement a dynamic array but for the momment lets just focus on implementing the basics
    
    public:
    board(int d){
        dimension = d;
        // Create the field (eventually this should be read in from a file)
    };
    void display(){
        //2d for loops that prints the board state
    };
    void update(){
        //2d for loop that checks enforces the rules
    };
};

int main(){
    cout << "CONWAYS GAME OF LIFE!\n";
    cell a;
    a.display();
    a.update();
    a.display();
    return 0;
}