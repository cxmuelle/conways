#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


class cell{
    private:
    bool alive;
    string type; //type is added for when there are various types of cells (wall, zombie, etc)

    public:
    cell(){
        alive = false;
        type = 'n'; // n will stand for normal
    };
    cell(bool a){
        alive = a;
        type = 'n'; // n will stand for normal
    };
    cell(bool a, string s){
        alive = a;
        type = s;
    };
    
    string getType(){
        return this->type;
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
    vector<vector<bool>> field; 
    
    public:
    board(int d){
        dimension = d;
        field = vector<vector<bool>>(d,vector<bool>(d));
        // Create the field (eventually this should be read in from a file)
        // A current work around
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                field[x][y] = bool(rand()%2);
            }
        }
    };

    ~board(){ //whenever new, delete what was called
    };

    void display(){
        //2d for loops that prints the board state
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                cout<<field[x][y]<<" ";
            }
            cout<<endl;
        }
    };

    void update(){        
        // With the current method I NEED TO DEEP COPY (Function is still O(cN^2)) 
        // c = constant
        vector<vector<bool>>backupField(this->dimension,vector<bool>(this->dimension));
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                backupField[x][y] = field[x][y];
            }
        }
        int numAlive = 0;
        for(int x=0; x<dimension; ++x){
            for(int y=0; y<dimension; ++y){
                // Simple Check, North South West East
                // I have each if make sure that we won't go over bounds by placing the in the if before checking if alive 
                if(x!=0 && field[x-1][y]){
                    numAlive++;
                }
                if(x!=dimension-1 && field[(x+1)][y]){
                    numAlive++;
                }
                if(y!=0 && field[x][(y-1)]){
                    numAlive++;
                }
                if(y!=dimension-1 && field[x][(y+1)]){
                    numAlive++;
                }
                // Diagonal check, NW NE SW SE
                if(x!=0 && y!=0 && field[(x-1)][(y-1)]){
                    numAlive++;
                }
                if(x!=0 && y!=dimension-1 && field[(x-1)][(y+1)]){
                    numAlive++;
                }
                if(x!=dimension-1 && y!=0 && field[(x+1)][(y-1)]){
                    numAlive++;
                }
                if(x!=dimension-1 && y!=dimension-1 && field[(x+1)][(y+1)]){
                    numAlive++;
                }
                if(field[x][y] && (numAlive < 2 || numAlive > 3)){
                    //Eventually it will be cell.Update()
                    backupField[x][y]=!field[x][y];
                    }
                if(!field[x][y] && (numAlive == 3)){
                    backupField[x][y]=!field[x][y];
                }
                numAlive=0;
            }
        }
        field = backupField;
    };
};

int main(){
    cout << "CONWAYS GAME OF LIFE!\n";
    cell a;
    a.display();
    a.update();
    a.display();
    board b(5);
    int x = 0;
    // time to learn raylib, because to get the effect I want I think i need to use that 
    cout<< "Input the number of generations you desire to run:";
    cin>>x;
    cout<<endl;
    while(true){
        x = --x;
        if(x==0){
            break;
        }
        b.display();
        b.update();
        cout<<endl;   
    }
    return 0;
}