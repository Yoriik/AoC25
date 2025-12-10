#include <iostream>
#include <string>
#include <vector>
class Manifold{
private:
    int numRow=0,numCol=0;
    char* board;
    int splitCount=0;
public:
    Manifold();

    
    void increaseBoardCapacity();
    int propagateAndCountSplits();
    friend std::ostream& operator<<(std::ostream&, const Manifold&);
    friend std::istream& operator>>(std::istream&, Manifold&);
};

Manifold::Manifold(){}

void Manifold::increaseBoardCapacity(){
    char* newBoard = new char[numCol*(numRow+1)];
    if(numRow != 0){
        for(int i = 0; i < numCol*numRow; i++){
            newBoard[i] = board[i];
        }
        delete[] board;
    }
    board = newBoard;
}

int Manifold::propagateAndCountSplits(){
    for(int i = 0; i < numCol*numRow; i++){
        if(board[i] == '|' || board[i] == 'S'){
            if(board[i+numCol] == '.'){ //if tile below is '.' go straight
                board[i+numCol] = '|';
            }
            if(board[i+numCol] == '^'){ //if tile below is '^' split
                board[i+numCol-1] = '|';
                board[i+numCol+1] = '|';
                splitCount++;
            }
        }
    }
    return splitCount;
}

std::ostream& operator<<(std::ostream& os, const Manifold& mani){
    os << mani.numCol << " " << mani.numRow << std::endl;
    for(int i = 0; i < mani.numRow; i++){
        for(int j = 0; j < mani.numCol; j++){
            os << mani.board[i*mani.numCol+j];
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Manifold& mani){
    std::string line;
    while(std::getline(is,line)){
        if(mani.numCol == 0){
            mani.numCol = line.size();
        }
        mani.increaseBoardCapacity();
        for(int i = 0; i < mani.numCol; i++){
            mani.board[mani.numCol*mani.numRow+i] = line[i];                
        }
        mani.numRow++;
    }
    return is;
}


int main(){
    Manifold* m = new Manifold();
    std::cin >> *m;

    std::cout << "Number of Splits: " << m->propagateAndCountSplits() << std::endl;
    return 0;
}