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
        // With the current method I NEED TO DEEP COPY (Function is still O(N^2))
        bool* backupField = new bool[dimension*dimension];
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                backupField[x*dimension+y] = field[x*dimension+y];
            }
        }
        int numAlive = 0;
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                // Simple Check, North South West East
                // I have each if make sure that we won't go over bounds by placing the in the if before checking if alive 
                if(x!=0 && field[(x-1)*dimension+y]){
                    numAlive++;
                }
                if(x!=dimension-1 && field[(x+1)*dimension+y]){
                    numAlive++;
                }
                if(y!=0 && field[x*dimension+(y-1)]){
                    numAlive++;
                }
                if(y!=dimension-1 && field[x*dimension+(y+1)]){
                    numAlive++;
                }
                // Diagonal check, NW NE SW SE
                if(x!=0 && y!=0 && field[(x-1)*dimension+(y-1)]){
                    numAlive++;
                }
                if(x!=0 && y!=dimension-1 && field[(x-1)*dimension+(y+1)]){
                    numAlive++;
                }
                if(x!=dimension-1 && y!=0 && field[(x+1)*dimension+(y-1)]){
                    numAlive++;
                }
                if(x!=dimension-1 && y!=dimension-1 && field[(x+1)*dimension+(y+1)]){
                    numAlive++;
                }
                // NEED TO MAKE A COPY OF FIELD SO CHANGES DON'T IMPACT DOWN THE LINE
                if(field[x*dimension+y] && (numAlive < 2 || numAlive > 3)){
                    //Eventually it will be cell.Update()
                    backupField[x*dimension+y]=!field[x*dimension+y];
                    }
                if(!field[x*dimension+y] && (numAlive == 3)){
                    backupField[x*dimension+y]=!field[x*dimension+y];
                }
                numAlive=0;
            }
        }
        // I wanted to get rid of the pointer so I am ok with taking more time
        // I am currently working with small fields so it might be an issue later
        // Why am I doing this, I don't want this function to create a pointer that just floats around
        // Also feel like there is a risk there
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                field[x*dimension+y] = backupField[x*dimension+y];
            }
        }
        delete(backupField);
    };
};

int main(){
    cout << "CONWAYS GAME OF LIFE!\n";
    cell a;
    a.display();
    a.update();
    a.display();
    board b(5);
    b.display();
    b.update();
    cout<<endl;
    b.display();
    b.update();
    cout<<endl;
    b.display();
    return 0;
}