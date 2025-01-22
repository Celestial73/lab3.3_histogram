#include "Console.h"


void printSequence(std::shared_ptr<ds::Sequence<int>> sequence) {
    for (int i = 0; i < sequence->getLength(); i++) {
        std::cout << sequence->get(i) << " ";
    }
}

void printSequence(SharedPtr<ds::Sequence<int>> sequence) {
    for (int i = 0; i < sequence->getLength(); i++) {
        std::cout << sequence->get(i) << " ";
    }
}
void printSequence(SharedPtr<ds::Sequence<double>> sequence) {
    for (int i = 0; i < sequence->getLength(); i++) {
        std::cout << sequence->get(i) << " ";
    }
}

void printSequence(SharedPtr<ds::Sequence<Student>> sequence) {
    for (int i = 0; i < sequence->getLength(); i++) {
        Student s = sequence->get(i);
        std::cout << s.getName() <<
            " Age: " << s.getAge() <<
                " Score: "  << s.getAverageScore() <<
                    " Course: " << s.getCourse() << " \n";
    }
}