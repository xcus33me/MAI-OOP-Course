#include "dyn_mem_resource.hpp"
#include "queue.hpp"

#include <iostream>

class ComplexType {
public:
    ComplexType(int id, const std::string name, double value)
        : id(id), name(name), value(value) {}

    friend std::ostream& operator<<(std::ostream& os, const ComplexType& obj) {
        os << "{ id: " << obj.id << ", name: " << obj.name << ", value: " << obj.value << " }";
        return os;
    }

private:
    int id;
    std::string name;
    double value;
};

int main() {
    Queue<int> simple_queue;
    simple_queue.Push(10);
    simple_queue.Push(20);
    simple_queue.Push(30);

    std::cout << "Queue of ints: " << std::endl;
    while (!simple_queue.Empty()) {
        std::cout << simple_queue.Front() << " ";
        simple_queue.Pop();
    }
    std::cout << std::endl;

    Queue<ComplexType> complex_queue;
    complex_queue.Push({1, "mango", 10.5});
    complex_queue.Push({1, "LLM - lotta lil money", 12.5});
    complex_queue.Push({2, "Kirkorov", 20.7});
    complex_queue.Push({3, "Solana", 30.9});

    std::cout << "Queue of complex types:" << std::endl;
    while (!complex_queue.Empty()) {
        std::cout << complex_queue.Front() << std::endl;
        complex_queue.Pop();
    }

    return 0;
}