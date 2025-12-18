#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>

class Junction{
private:
  int X,Y,Z;
public:
  Junction():X{0},Y{0},Z{0}{}
  Junction(const Junction&)=default;
  Junction(Junction&&)=default;

  Junction& operator=(const Junction&) = default;
  Junction& operator=(Junction&&)=default;

  bool operator==(const Junction&)const;
  bool operator!=(const Junction&)const;

  friend std::ostream& operator<<(std::ostream&, Junction&);
  friend std::istream& operator>>(std::istream&, Junction&);
  friend class Network;
  void read(const std::string);
};

bool Junction::operator==(const Junction& junction)const{
  if(this->X == junction.X && this->Y == junction.Y && this->Z == junction.Z)
    return true;
  return false;
}

bool Junction::operator!=(const Junction& junction)const{
  return !(*this==junction);
}

std::ostream& operator<<(std::ostream& os, Junction& junction){
  os << junction.X << " " << junction.Y << " " << junction.Z << std::endl;
  return os;
}
std::istream& operator>>(std::istream& is, Junction& junction){
  /*
  int cnt = 0, commaIndex = 0;
  bool valid = true;
  do{
    if(line[cnt]==',' && commaIndex != 0){
      valid = false;
    }
    if(line[cnt]==',' && commaIndex == 0){
      commaIndex = cnt;
    }
    cnt++;
  }while((long unsigned)(cnt) < line.size() && valid);
  cnt--;

  junction.X = std::stoi(line.substr(0,commaIndex));
  junction.Y = std::stoi(line.substr(commaIndex+1,cnt));
  junction.Z = std::stoi(line.substr(cnt+1,line.size()));
  */
  return is;
}

void Junction::read(const std::string line){
  int cnt = 0, commaIndex = 0;
  bool valid = true;
  while((long unsigned)(cnt) < line.size() && valid){
    if(line[cnt]==',' && commaIndex != 0){
      valid = false;
    }
    if(line[cnt]==',' && commaIndex == 0){
      commaIndex = cnt;
    }
    cnt++;
  }
  cnt--;

  X = std::stoi(line.substr(0,commaIndex));
  Y = std::stoi(line.substr(commaIndex+1,cnt));
  Z = std::stoi(line.substr(cnt+1,line.size()));
}

class Node{
  Junction source;
  Junction sink;
  long double distance;
  friend class Network;
  friend class Circuit;
  bool junctionIsLinked(Junction&);

public:
  Node(){
    source = Junction();
    sink = Junction();
    distance = 0.0;
  }
  ~Node()=default;
  Node(const Node&)=default;
  Node(Node&&)=default;
  Node& operator=(const Node&)=default;
  Node& operator=(Node&&)=default;
  Junction& getSink(){return sink;}
  Junction& getSource(){return source;}

  bool operator<(const Node&)const;
  bool operator==(const Node&)const;


  friend std::ostream& operator<<(std::ostream&, Node&);
};

bool Node::junctionIsLinked(Junction& j){
  if(this->source == j) return true;
  if(this->sink == j) return true;
  return false;
}

bool Node::operator<(const Node& n)const{
  return distance < n.distance;
}

bool Node::operator==(const Node& n)const{
  return this->source == n.source && this->sink == n.sink && this->distance == n.distance;
}

std::ostream& operator<<(std::ostream& os, Node& n){
  os << n.source << n.sink << n.distance << std::endl;
  return os;
}

class Circuit{
  std::vector<Junction> junctionList;
public:
  Circuit(Node& start){
    junctionList.push_back(start.getSource());
    junctionList.push_back(start.getSink());
  }
  ~Circuit()=default;
  Circuit(const Circuit&)=default;
  Circuit(Circuit&&)=default;

  Circuit& operator=(const Circuit&)=default;
  Circuit& operator=(Circuit&&)=default;

  //bool operator==(const Circuit&);

  int size(){return junctionList.size();}
  bool addNode(Node&);
  bool contains(Junction&)const;
  bool sharesJunctionWith(Circuit&)const;

  bool operator<(Circuit& c){return (this->junctionList.size() > c.junctionList.size());}
  friend std::ostream& operator<<(std::ostream&, Circuit&);
  friend class Network;
};

bool Circuit::addNode(Node& n){
  //std::cout << "adding: " << n << " to Circuit: " << *this <<std::endl;
  for(auto j : junctionList){
    if(n.getSink() == j){
      if(std::find(junctionList.begin(), junctionList.end(), n.getSource()) == junctionList.end()){
        junctionList.push_back(n.getSource());
      }
      return true;
    }
    if(n.getSource() == j){
      if(std::find(junctionList.begin(), junctionList.end(), n.getSink()) == junctionList.end()){
        junctionList.push_back(n.getSink());
      }
      return true;
    }
  }
  return false;
}

bool Circuit::contains(Junction& junction)const{
  if(std::find(junctionList.begin(), junctionList.end(), junction) == junctionList.end()){
    return false;
  }
  return true;
}
bool Circuit::sharesJunctionWith(Circuit& circ)const{
  for(auto j1 : this->junctionList){
    for(auto j2 : circ.junctionList){
      if(j1 == j2)
        return true;
    }
  }
  return false;
}

std::ostream& operator<<(std::ostream& os, Circuit& c){
  /*
  if(c.size() > 0){
    os << c.junctionList[0].getSource() << std::endl;
    os << c.junctionList[0].getSink() << std::endl;
  }*/
  for(auto node : c.junctionList){
    os << node << std::endl;
  }
  return os;
}

class Network{
private:
  std::vector<Junction> junctionList;
  std::vector<Circuit> circuits;
  std::vector<Node> distances;
public:
  Network(){}
  Network(const Network&) = default;
  Network(Network&&) = default;
  Network& operator=(const Network&) = default;
  Network& operator=(Network&&) = default;
  
  void findShortestPath();
  void sortDistances(int);
  void build(int);

  void sortCircuits();
  long long multLargestCircuits(int)const;
  void combineCircuits();
  long long connectCircuits(long double);

  friend std::istream& operator>>(std::istream&, Network&);
  friend std::ostream& operator<<(std::ostream&, Network&);
};

void Network::findShortestPath(){
  for(std::vector<Junction>::iterator v = junctionList.begin(); v < junctionList.end(); v++){
    for(std::vector<Junction>::iterator w = v; w<junctionList.end(); w++){
        if(v != w){
          long double dx = (long double)v->X - (long double)w->X;
          long double dy = (long double)v->Y - (long double)w->Y;
          long double dz = (long double)v->Z - (long double)w->Z;

          long double distance = std::sqrt(dx*dx + dy*dy + dz*dz);
          Node n;
          n.source = *v;
          n.sink = *w;
          n.distance = distance;
          distances.push_back(n);
        }
    }
  }
}

void Network::sortDistances(int num){
  sort(distances.begin(), distances.end());
  
  distances.erase(distances.begin()+num,distances.end());
  return;
}
/*
void Network::build(){
  for(auto n : distances){
    size_t sz = circuits.size();
    if(sz == 0){
      Circuit circ(n);
      circuits.push_back(circ);
    }
    for (size_t i = 0; i < sz; ++i) {
        if (!circuits[i].addNode(n)) {
            Circuit circ(n);
            circuits.emplace_back(circ);
        }
    }
  }
  return;
}*/
void Network::build(int num){
  for(int i = 0; i < num; i++){
    size_t sz = circuits.size();
    Node n = distances[i];
    bool hasBeenAdded = false;
    if(sz == 0){
      Circuit circ(n);
      std::cout << "adding new circuit because size 0: " << circ << std::endl;
      circuits.push_back(circ);
    }else{
      for(size_t j = 0; j < sz; j++){
        if (circuits[j].addNode(n)) {
          hasBeenAdded = true;
        }
      }
      if(!hasBeenAdded){
        Circuit circ(n);
        std::cout << "adding new circuit: " << circ << std::endl;
        circuits.emplace_back(circ);
      }
    }
    combineCircuits();
  }
}

void Network::sortCircuits(){
  sort(circuits.begin(), circuits.end());
  return;
}

long long Network::multLargestCircuits(int num)const{
  long long sum = 1;
  int cnt = 0;
  for(auto c : circuits){
    if(num > cnt){
      sum *= c.size();
    }else{
      return sum;
    }
    cnt++;
  }
  return sum;
}

void Network::combineCircuits(){
  bool merged = true;
  while (merged) {
    merged = false;
    for (size_t i = 0; i < circuits.size() && !merged; ++i) {
      for (size_t j = i + 1; j < circuits.size(); ++j) {
        if (circuits[i].sharesJunctionWith(circuits[j])) {
          for (auto& v : circuits[j].junctionList) {
            if (!circuits[i].contains(v))
              circuits[i].junctionList.push_back(v);
          }
          circuits.erase(circuits.begin() + j);
          merged = true;
          break;
        }
      }
    }
  }
}

long long Network::connectCircuits(long double result){
  if(circuits.size() == 1) return result;
  Node n;
  n.distance = 0.0;
  size_t tmp;
  for(size_t c = 0; c <= circuits.size(); c++){
    for(size_t d = c+1; d <= circuits.size(); d++){
      for(auto j1 : circuits[c].junctionList){
        for(auto j2 : circuits[d].junctionList){
          long double dx = (long double)j1.X - (long double)j2.X;
          long double dy = (long double)j1.Y - (long double)j2.Y;
          long double dz = (long double)j1.Z - (long double)j2.Z;

          long double distance = std::sqrt(dx*dx + dy*dy + dz*dz);
          if(n.distance == 0.0 || n.distance > distance){
            tmp = c;
            n.source = j1;
            n.sink = j2;
            n.distance = distance;
          }
        }
      }
    }
  }
  //auto it = std::find(circuits.begin(), circuits.end(), *tmp);
  //auto position = std::distance(circuits.begin(), it) + 1;
  circuits[tmp].addNode(n);
  combineCircuits();
  return connectCircuits(n.source.X*n.sink.X);
}

std::istream& operator>>(std::istream& is, Network& nw){
  std::string line;
  while(std::getline(is,line)){
    Junction junction;
    junction.read(line);
    nw.junctionList.push_back(junction);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, Network& nw){
  os << "All Junctions: " << std::endl;
  for(auto j : nw.junctionList)
    os << j << std::endl;
  os << "Source to Sink and their distance: " << std::endl;
  for(auto n : nw.distances)
    os << n << std::endl;
  os << "All circuits: " << std::endl;
  for(auto c : nw.circuits)
    os << c << std::endl;
  return os;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Expecting 1 argument (day number).\n";
    return -1;
  }

  if (*argv[1] == '1') {
    Network n;
    std::cin >> n;
    n.findShortestPath();
    n.sortDistances(10);
    std::cout << n << std::endl;
    n.build(10);
    n.sortCircuits();
    std::cout << n.multLargestCircuits(3) << std::endl;
  }
  if (*argv[1] == '2') {
    
    Network n;
    std::cin >> n;
    n.findShortestPath();
    n.sortDistances(10);
    std::cout << n << std::endl;
    n.build(10);
    n.sortCircuits();
    std::cout << n.multLargestCircuits(3) << std::endl;
    std::cout << n.connectCircuits(0) << std::endl;
  }
  return 0;
}
