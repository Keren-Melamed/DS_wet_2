#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <exception>

class AVLTreeException : public std::runtime_error {
public:
    AVLTreeException(const std::string& msg) : runtime_error(msg) {}
};

class NodeAlreadyExists : public AVLTreeException {
public:
    NodeAlreadyExists() : AVLTreeException("AVLTree Error: adding a node that already exists") {}
};

class BadAllocation : public AVLTreeException {
public:
    BadAllocation() : AVLTreeException("AVLTree Error: allocation failed") {}
};

class NodeDoesntExist : public AVLTreeException {
public:
    NodeDoesntExist() : AVLTreeException("AVLTree Error: node doesnt exist"){}
};

class InvalidKey : public std::exception {};

class InvalidNode : public std::exception {};

#endif