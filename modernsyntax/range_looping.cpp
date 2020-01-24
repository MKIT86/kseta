/*
g++ -o range_looping -std=c++14 -pthread -g -Wall -Wextra -Wpedantic -Werror range_looping.cpp
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

class Tool {
public:
  Tool(): aMember(0) {
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
  };
  Tool(const Tool&) {
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
  }
  void print() const { std::cout << "tool" << std::endl; };

private:
  int aMember;
};

void rangeLoop(std::vector<Tool>& tools){
  for(const auto& tool : tools){
    tool.print();
  }
}

int main(){
  // create a vector of 5 Tools
  std::cout << "Creating tools" << std::endl;
  std::vector<Tool> tools(5);

  std::cout << "Start range looping" << std::endl;
  rangeLoop(tools);

  return 0;
}
