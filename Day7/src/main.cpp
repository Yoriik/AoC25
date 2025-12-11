#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>

class Manifold{
private:
    int numCol=0, numRow=0;
    std::vector<char> board;
    int splitCount=0;
public:
    Manifold();
    Manifold(const Manifold&)=default;
    Manifold(Manifold&&)=default;

    Manifold& operator=(const Manifold&)=default;
    Manifold& operator=(Manifold&&)=default;

    bool operator!=(const Manifold&)const;
    bool operator==(const Manifold&)const;
    
    
    void increaseBoardCapacity();
    int propagateAndCountSplits();
    long long getTimelineSize()const;

    friend std::ostream& operator<<(std::ostream&, const Manifold&);
    friend std::istream& operator>>(std::istream&, Manifold&);
    friend class TimelineHistory;
    friend struct ManifoldHash;
};

struct ManifoldHash {
    std::size_t operator()(Manifold const& m) const noexcept {
        std::size_t h = 0;

        for (char c : m.board) {
            h = h * 131 + c;
        }

        h ^= (std::size_t)m.numCol << 24;
        h ^= (std::size_t)m.numRow << 16;
        h ^= (std::size_t)m.splitCount;

        return h;
    }
};

struct State {
    std::vector<char> board;   // full board
    std::vector<int> active;   // frontier
};

struct StateHash {
    size_t operator()(State const& s) const noexcept {
        size_t h = 0;
        for (char c : s.board)
            h = h * 1315423911u + c;
        return h;
    }
};

struct StateEq {
    bool operator()(State const& a, State const& b) const noexcept {
        return a.board == b.board; // full board comparison ensures no duplicates
    }
};

class TimelineHistory {
public:
    std::unordered_set<State, StateHash, StateEq> done;
    const Manifold* base = nullptr;

    void propagate(const Manifold& start) {
        base = &start;

        // Initialize starting state
        State init;
        init.board = start.board;
        for (int i = 0; i < start.numCol * start.numRow; i++)
            if (start.board[i] == 'S')
                init.active.push_back(i);

        std::vector<State> q = {init};

        while (!q.empty()) {
            State s = q.back(); q.pop_back();

            // Avoid duplicates
            if (done.count(s)) continue;
            done.insert(s);

            // Separate straight falls and splits
            std::vector<int> straightFall, splits;
            for (int pos : s.active) {
                int below = pos + start.numCol;
                if (below >= start.numCol * start.numRow) continue;

                if (s.board[below] == '.') straightFall.push_back(below);
                else if (s.board[below] == '^') splits.push_back(below);
            }

            // Apply straight falls
            if (!straightFall.empty()) {
                State ns = s;
                ns.active.clear();
                for (int pos : straightFall) {
                    ns.board[pos] = '|';
                    ns.active.push_back(pos);
                }
                q.push_back(ns);
            }

            // Apply splits combinatorially
            if (!splits.empty()) {
                generateSplitStates(s, splits, 0, q);
            }
        }
    }

    long long getTimelineSize() const {
        return done.size();
    }

private:
    // Recursive function to generate all split combinations
    void generateSplitStates(const State& s, const std::vector<int>& splits, int idx, std::vector<State>& q) {
        if (idx == splits.size()) {
            // Push resulting state
            State ns = s;
            ns.active.clear();
            for (int i = 0; i < ns.board.size(); i++)
                if (ns.board[i] == '|') ns.active.push_back(i);
            if (!ns.active.empty()) q.push_back(ns);
            return;
        }

        int pos = splits[idx];
        int col = base->numCol;

        // Branch left if possible
        if (pos - 1 >= 0 && s.board[pos - 1] == '.') {
            State left = s;
            left.board[pos - 1] = '|';
            generateSplitStates(left, splits, idx + 1, q);
        }

        // Branch right if possible
        if (pos + 1 < s.board.size() && s.board[pos + 1] == '.') {
            State right = s;
            right.board[pos + 1] = '|';
            generateSplitStates(right, splits, idx + 1, q);
        }
    }
};

Manifold::Manifold(){}
/*
Manifold::Manifold(const Manifold& other): numCol(other.numCol), numRow(other.numRow), splitCount(other.splitCount){
    int size = numCol * numRow;
    board = new char[size];
    std::copy(other.board, other.board + size, board);
}

Manifold::Manifold(Manifold&& other)
    : numCol(other.numCol), numRow(other.numRow),
      board(other.board), splitCount(other.splitCount)
{
    other.board = nullptr;
}

Manifold& Manifold::operator=(const Manifold& other){
    if (this != &other) {
        delete[] board;
        numCol = other.numCol;
        numRow = other.numRow;
        splitCount = other.splitCount;

        int size = numCol * numRow;
        board = new char[size];
        std::copy(other.board, other.board + size, board);
    }
    return *this;
}
Manifold& Manifold::operator=(Manifold&& other){
    if(*this != other){
        numCol = other.numCol;
        numRow = other.numRow;
        board = other.board;
        
        other.board = nullptr;
    }
    return *this;
}
*/
bool Manifold::operator!=(const Manifold& other)const{
    return !(*this==other);
}

bool Manifold::operator==(Manifold const& other) const {
    if (numCol != other.numCol || numRow != other.numRow || splitCount != other.splitCount)
        return false;

    return board == other.board;   // vector comparison
}
/*
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
*/

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

std::istream& operator>>(std::istream& is, Manifold& mani) {
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(is, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
    }

    mani.numRow = lines.size();
    mani.numCol = lines[0].size();
    mani.board.resize(mani.numRow * mani.numCol);

    for (int r = 0; r < mani.numRow; r++) {
        for (int c = 0; c < mani.numCol; c++) {
            mani.board[r * mani.numCol + c] = lines[r][c];
        }
    }

    return is;
}
/*
void TimelineHistory::propagateOneTimeline(const Manifold& start) {
    // BFS of timelines, not per-cell linear recursion
    std::vector<Manifold> queue;
    queue.push_back(start);

    while (!queue.empty()) {
        Manifold m = queue.back();
        queue.pop_back();

        // If this final timeline already exists, skip it
        if (history.count(m)) continue;

        // Track all active falling positions
        std::vector<int> active;
        for (int i = 0; i < m.numCol * m.numRow; i++) {
            if (m.board[i] == '|' || m.board[i] == 'S')
                active.push_back(i);
        }

        bool branched = false;

        for (int pos : active) {
            int below = pos + m.numCol;
            if (below >= m.numCol * m.numRow) continue;

            if (m.board[below] == '.') {
                // Straight fall
                Manifold next = m;
                next.board[below] = '|';
                queue.push_back(std::move(next));
                branched = true;
            }
            else if (m.board[below] == '^') {
                // Split left
                Manifold left = m;
                left.splitCount++;
                if ((below - 1) >= 0)
                    left.board[below - 1] = '|';
                queue.push_back(std::move(left));

                // Split right
                Manifold right = m;
                right.splitCount++;
                if ((below + 1) < m.numCol * m.numRow)
                    right.board[below + 1] = '|';
                queue.push_back(std::move(right));

                branched = true;
            }
        }

        // If no branches happened, this is an end state → store it
        if (!branched) {
            history.insert(m);
        }
    }
}


long long TimelineHistory::getTimelineSize()const{
    return history.size();
}
*/

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
        Manifold m;
        std::cin >> m;
        TimelineHistory tl;
        tl.propagate(m);
        std::cout << tl.getTimelineSize() << std::endl;
    
    }
    return 0;
}