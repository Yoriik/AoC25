#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

class Manifold{
private:
    int numRow=0,numCol=0;
    std::vector<char> board;
    int splitCount=0;
public:
    Manifold();

    Manifold(const Manifold&)=default;
    Manifold(Manifold&&)=default;

    Manifold& operator=(const Manifold&)=default;
    Manifold& operator=(Manifold&&)=default;

    ~Manifold(){}

    void increaseBoardCapacity();
    int propagateAndCountSplits();
    friend std::ostream& operator<<(std::ostream&, const Manifold&);
    friend std::istream& operator>>(std::istream&, Manifold&);
    friend class ManifoldTimeline;
};

class ManifoldTimeline {
private:
    Manifold m;
    std::vector<long long> memo;

    long long countFrom(int row, int col) {
        if (row >= m.numRow || col < 0 || col >= m.numCol) return 0;

        int idx = row * m.numCol + col;

        // Bottom row reached
        if (row == m.numRow - 1) return 1;

        // memoization
        if (memo[idx] != -1) return memo[idx];

        char below = m.board[idx + m.numCol];
        long long total = 0;

        if (below == '.') {
            total += countFrom(row + 1, col);
        } else if (below == '^') {
            // split left and right
            if (col > 0) total += countFrom(row + 1, col - 1);
            if (col < m.numCol - 1) total += countFrom(row + 1, col + 1);
        }

        memo[idx] = total;
        return total;
    }

public:
    ManifoldTimeline(const Manifold& other) : m(other) {
        memo.resize(m.numRow * m.numCol, -1);
    }

    long long countTimelines() {
        // find the starting column (assume first row has 'S')
        for (int col = 0; col < m.numCol; col++) {
            if (m.board[col] == 'S') {
                return countFrom(0, col);
            }
        }
        return 0;
    }
};


Manifold::Manifold(){}

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
        for(int i = 0; i < mani.numCol; i++){
            mani.board.push_back(line[i]);                
        }
        mani.numRow++;
    }
    return is;
}


int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cout << "Expecting int as part of day." << std::endl;
        return -1;
    }
    if (*argv[1] == '1') {
        Manifold* m = new Manifold();
        std::cin >> *m;

        std::cout << "Number of Splits: " << m->propagateAndCountSplits() << std::endl;
    }
    if (*argv[1] == '2') {
        Manifold* m = new Manifold();
        std::cin >> *m;
        ManifoldTimeline tl(*m);
        
        std::cout << "Number of Timelines: " << tl.countTimelines() << std::endl;
    }
    return 0;
}