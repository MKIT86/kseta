/*
g++ -o smart_pointers -std=c++14 -pthread -g -Wall -Wextra -Wpedantic -Werror smart_pointers.cpp
*/
#include <iostream>
#include <memory>

class IntegerStore1 {
public:

    IntegerStore1() : i(new int(0)) { }
    IntegerStore1(const IntegerStore1&) = delete;
    IntegerStore1& operator=(const IntegerStore1&) = delete;
    ~IntegerStore1() {
        if(i != nullptr) {
            delete i;
        }
    }

    void put(int* newValue) {
        i = newValue;
    }

   int* get() { return i; }

private:
    int* i;
};

class IntegerStore2 {
public:
    IntegerStore2() : i(new int(0)) { }
    IntegerStore2(const IntegerStore2&) = delete;
    IntegerStore2& operator=(const IntegerStore2&) = delete;
    ~IntegerStore2() {
        if(i != nullptr) {
            delete i;
        }
    }

    void set(int* newValue) {
        i = newValue;
    }

    int* get() { return i; }

private:
    int* i;
};

void useCaseOne(){
  std::cout << "*** useCaseOne *** " << std::endl;
  // This use case contains a memory leak
  IntegerStore1 store;
  auto p_anInteger = new int(3);
  std::cout << "IntegerStore contains " << *(store.get()) << std::endl;
  store.put(p_anInteger);
  std::cout << "IntegerStore contains " << *(store.get()) << std::endl;
  // ops, we didn't delete the created integer
}

void useCaseTwo() {
  std::cout << "*** useCaseTwo *** " << std::endl;
  // This use case will crash
  auto store = new IntegerStore2();
  auto anInteger = int(3);
  std::cout << "IntegerStore contains " << *(store->get()) << std::endl;
  store->set(&anInteger);
  // let's change the value
  anInteger = 5;
  // does the IntegerStore see the changed value?
  std::cout << "IntegerStore contains " << *(store->get()) << std::endl;
  delete store;
  std::cout << "The integer is " << anInteger << std::endl;
}


int main(){
  useCaseOne();
  useCaseTwo();

  return 0;
}
