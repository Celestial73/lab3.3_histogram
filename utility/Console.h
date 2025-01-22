#pragma once
#include "../containers/Sequence.h"
#include "../pointers/UniquePtr.h"
#include <iostream>
#include "../data/Student.h"
#include <memory>

void printSequence(std::shared_ptr<ds::Sequence<int>> sequence);
void printSequence(SharedPtr<ds::Sequence<int>> sequence);
void printSequence(SharedPtr<ds::Sequence<double>> sequence);
void printSequence(SharedPtr<ds::Sequence<Student>> sequence);