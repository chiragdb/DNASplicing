#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <cstdlib>  // provides definition for size_t, the maximum size of a theoretically possible object of any type
#include <iostream>
#include <string>
#include <vector>

#include "node.hpp"

class ValueNotFound {};
class ListEmpty {};

// template class definition for doubly linked list
// ...

// for template instantiation
// template function definitions

template <typename T>
class DoublyLinkedList {
public:
  DoublyLinkedList();

  DoublyLinkedList( T val );

  explicit DoublyLinkedList( const std::vector<T>& values );

  DoublyLinkedList( const DoublyLinkedList<T>& rhs );

  DoublyLinkedList<T>& operator=( const DoublyLinkedList<T>& rhs );

  ~DoublyLinkedList();

  T& back();
  T& front();
  void pop_back();
  void pop_front();

  void push_back( T val );
  void push_front( T val );

  void insert_at( size_t idx, T val );
  void erase_at( size_t idx );

  T& find( T val );

  void clear();

  size_t size() const { return size_; }
  bool empty() const { return ( head_ == nullptr ); };

  Node<T>* get_head() const { return head_; }
  Node<T>* get_tail() const { return tail_; }

  friend std::ostream& operator<<( std::ostream& os,
                                   const DoublyLinkedList& ll );

private:
protected:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  size_t size_ = 0;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList( T val ) {
  Node<T>* n = new Node<T>( val );
  n->next = nullptr;
  n->prev = nullptr;
  head_ = n;
  tail_ = n;
  size_++;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList( const std::vector<T>& values ) {
  if ( values.size() == 0 ) {
    DoublyLinkedList();
  } else if ( values.size() == 1 ) {
    Node<T>* n = new Node<T>( values.at( 0 ) );
    n->next = nullptr;
    n->prev = nullptr;
    head_ = n;
    tail_ = n;
    size_++;
  } else {
    Node<T>* first = new Node<T>( values.at( 0 ) );
    head_ = first;
    tail_ = first;
    size_ = size_ + 1;
    for ( size_t i = 1; i < values.size(); ++i ) {
      Node<T>* curr = new Node<T>( values.at( i ) );
      first->next = curr;
      curr->prev = first;
      tail_ = curr;
      first = curr;
      size_++;
    }
  }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList( const DoublyLinkedList<T>& rhs ) {
  if ( rhs.size_ == 0 ) {
    DoublyLinkedList();
  } else {
    T head_val = rhs.head_->data;
    Node<T>* temp = new Node<T>( head_val );
    head_ = temp;
    tail_ = temp;
    head_->prev = nullptr;
    tail_->next = nullptr;
    Node<T>* curr = head_;
    Node<T>* curr_copy = rhs.head_;
    size_++;
    while ( curr_copy->next != nullptr ) {
      curr_copy = curr_copy->next;
      T curr_data = curr_copy->data;
      curr->next = new Node<T>( curr_data );
      curr = curr->next;
      tail_ = curr;
      size_++;
    }
  }
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(
    const DoublyLinkedList<T>& rhs ) {
  if ( this == &rhs ) {
    return *this;
  }
  clear();
  if ( rhs.size_ == 0 ) {
    DoublyLinkedList();
  } else {
    T head_val = rhs.head_->data;
    Node<T>* n = new Node<T>( head_val );
    head_ = n;
    tail_ = n;
    head_->prev = nullptr;
    tail_->next = nullptr;
    Node<T>* curr = head_;
    Node<T>* curr_copy = rhs.head_;
    while ( curr_copy->next != nullptr ) {
      curr_copy = curr_copy->next;
      T curr_data = curr_copy->data;
      curr->next = new Node<T>( curr_data );
      curr = curr->next;
      tail_ = curr;
    }
    size_ = rhs.size_;
  }
  return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template <typename T>
T& DoublyLinkedList<T>::back() {
  if ( size_ == 0 ) {
    throw std::runtime_error( "list is empty" );
  }
  return tail_->data;
}

template <typename T>
T& DoublyLinkedList<T>::front() {
  if ( size_ == 0 ) {
    throw std::runtime_error( "list is empty" );
  }
  return head_->data;
}

template <typename T>
void DoublyLinkedList<T>::pop_back() {
  if ( size_ == 0 ) {
    throw std::runtime_error( "list is empty" );
  } else if ( size_ == 1 ) {
    delete tail_;
    head_ = nullptr;
    tail_ = nullptr;
    size_--;
  } else {
    Node<T>* n = tail_;
    tail_ = tail_->prev;
    tail_->next = nullptr;
    delete n;
    size_--;
  }
}

template <typename T>
void DoublyLinkedList<T>::pop_front() {
  if ( size_ == 0 ) {
    throw std::runtime_error( "list is empty" );
  } else if ( size_ == 1 ) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    size_--;
  } else {
    Node<T>* n = head_;
    head_ = head_->next;
    head_->prev = nullptr;
    delete n;
    size_--;
  }
}

template <typename T>
void DoublyLinkedList<T>::push_back( T val ) {
  Node<T>* n = new Node<T>( val );
  if ( size_ == 0 ) {
    n->next = nullptr;
    n->prev = nullptr;
    head_ = n;
    tail_ = n;
    size_++;
  } else {
    n->next = nullptr;
    n->prev = tail_;
    if ( tail_ != nullptr ) {
      tail_->next = n;
    }
    tail_ = n;
    size_++;
  }
}

template <typename T>
void DoublyLinkedList<T>::push_front( T val ) {
  Node<T>* n = new Node<T>( val );
  if ( size_ == 0 ) {
    n->next = nullptr;
    n->prev = nullptr;
    head_ = n;
    tail_ = n;
    size_++;
  } else {
    n->next = head_;
    n->prev = nullptr;
    if ( head_ != nullptr ) {
      head_->prev = n;
    }
    head_ = n;
    size_++;
  }
}

template <typename T>
void DoublyLinkedList<T>::insert_at( size_t idx, T val ) {
  if ( idx < 0 || idx > size_ ) {
    throw std::runtime_error( "invalid index" );
  }
  if ( idx == 0 ) {
    push_front( val );
  } else if ( idx == size_ ) {
    push_back( val );
  } else {
    Node<T>* curr = head_;
    for ( size_t i = 0; i < idx - 1; ++i ) {
      curr = curr->next;
    }
    Node<T>* n = new Node<T>( val );
    Node<T>* next_node = curr->next;
    curr->next = n;
    n->prev = curr;
    n->next = next_node;
    next_node->prev = n;
    size_++;
  }
}

template <typename T>
void DoublyLinkedList<T>::erase_at( size_t idx ) {
  if ( size_ == 0 ) {
    throw std::runtime_error( "called on an empty list" );
  }
  if ( idx < 0 || idx > size_ - 1 ) {
    throw std::runtime_error( "invalid index" );
  }
  if ( idx == 0 ) {
    pop_front();
  } else if ( idx == size_ - 1 ) {
    pop_back();
  } else {
    Node<T>* curr = head_;
    for ( size_t i = 0; i < idx; ++i ) {
      curr = curr->next;
    }
    Node<T>* next_node = curr->next;
    Node<T>* previous_node = curr->prev;
    previous_node->next = next_node;
    next_node->prev = previous_node;
    size_--;
  }
}

template <typename T>
T& DoublyLinkedList<T>::find( T val ) {
  Node<T>* curr = head_;
  while ( curr != nullptr ) {
    if ( curr->data == val ) {
      return curr->data;
    }
    if ( curr == tail_ ) {
      break;
    } else {
      curr = curr->next;
    }
  }
  throw std::runtime_error( "did not find the value" );
}

template <typename T>
void DoublyLinkedList<T>::clear() {
  while ( head_ ) {
    Node<T>* current = head_->next;
    delete head_;
    head_ = current;
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

// ostream& operator<<( ostream& os, const DoublyLinkedList& ll ) {
//   constexpr unsigned int width = 16;
//   os << "Doubly Linked List" << endl;
//   os << "Head: " << ll.head_ << "\t Tail: " << ll.tail_ << endl;
//   os << "Size: " << ll.size_ << endl;
//   if ( ll.head_ == nullptr ) return ( os << "Empty" << endl );
//   const Node* curr = ll.head_;
//   os << "Nodes (accessible from head to tail):" << endl << endl;
//   os << setw( width ) << setfill( ' ' ) << ' ' << ' '
//      << center( "prev", width - 1 ) << ' ' << center( "data", width - 1 ) <<
//      ' '
//      << center( "next", width - 1 ) << endl;
//   while ( curr != nullptr ) {
//     ostringstream oss;
//     oss << ( curr->prev );
//     string prev = oss.str();
//     oss.str( "" );
//     oss << ( curr->next );
//     string next = oss.str();
//     oss.str( "" );
//     oss << ( curr->data );
//     string data = oss.str();
//     oss.str( "" );
//     oss << curr;
//     string address = oss.str();
//     os << setw( width ) << setfill( ' ' ) << ' ' << '.' << setw( width )
//        << setfill( '-' ) << '.' << setw( width ) << '.' << setw( width ) <<
//        '.'
//        << endl;
//     os << setw( width ) << setfill( ' ' ) << center( address, width - 1 ) <<
//     '|'
//        << setw( width - 1 ) << setfill( ' ' ) << center( prev, width - 1 )
//        << '|' << setw( width - 1 ) << center( data, width - 1 ) << '|'
//        << setw( width - 1 ) << center( next, width - 1 ) << '|' << endl;
//     os << setw( width ) << setfill( ' ' ) << ' ' << '\'' << setw( width )
//        << setfill( '-' ) << '\'' << setw( width ) << '\'' << setw( width )
//        << '\'' << endl;
//     os << endl;
//     curr = curr->next;
//   }
//   return os;
// }

// char c = 'c';
// char& ref = c;

// std::string center( const std::string& str,
//                     decltype( str.length() ) col_width ) {
//   // quick and easy (but error-prone) implementation
//   decltype( str.length() ) padl = ( col_width - str.length() ) / 2;
//   decltype( str.length() ) padr = ( col_width - str.length() ) - padl;
//   string strf = string( padl, ' ' ) + str + string( padr, ' ' );
//   return strf;
// }

#endif