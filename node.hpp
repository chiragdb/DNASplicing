#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
  Node() = default;
  Node( T data ): data( data ) {}

  T data;
  Node* next = nullptr;
  Node* prev = nullptr;
};

#endif