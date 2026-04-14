#include <iostream>
#include <cstdlib>
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
    bool* field; //eventually implement a dynamic array but for the momment lets just focus on implementing the basics
    
    public:
    board(int d){
        dimension = d;
        field = new bool[d*d];
        // Create the field (eventually this should be read in from a file)
        // A current work around
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                field[x*dimension+y] = bool(rand()%2);
            }
        }
    };

    ~board(){ //whenever new, delete what was called
        delete field;
    };

    void display(){
        //2d for loops that prints the board state
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                cout<<field[x*dimension+y]<<" ";
            }
            cout<<endl;
        }
    };
    void update(){
        //2d for loop that checks enforces the rules
        int numAlive = 0;
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                if(x!=0){
                    
                }
                if(x!=dimension-1){}
                if(y!=0){}
                if(y!=dimension-1){}
                if(x!=0 && y!=0){}
                if(x!=0 && y!=dimension-1){}
                if(x!=dimension-1 && y!=0){}
                if(x!=dimension-1 && y!=dimension-1){}

                if(field[x*dimension+y] && (numAlive < 2 || numAlive > 3)){
                    //Eventually it will be cell.Update()
                    field[x*dimension+y]=!field[x*dimension+y];
                    }
                else if(!field[x*dimension+y] && (numAlive == 3)){
                    field[x*dimension+y]=!field[x*dimension+y];
                }
                numAlive=0;
            }
        }
    };
};

int main(){
    cout << "CONWAYS GAME OF LIFE!\n";
    cell a;
    a.display();
    a.update();
    a.display();
    board b(10);
    b.display();
    return 0;
}