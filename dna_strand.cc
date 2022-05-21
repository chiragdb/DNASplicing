#include "dna_strand.hpp"

#include <cctype>

DNAstrand::DNAstrand( const std::vector<char>& sequence ) {
  for ( char c : sequence ) {
    if ( c != 'A' && c != 'G' && c != 'C' && c != 'T' && c != 'a' && c != 'g' &&
         c != 'c' && c != 't' ) {
      DoublyLinkedList::clear();
      throw std::invalid_argument( "invalid character in sequence" );
    }
    char upper = toupper( c );
    push_back( upper );
  }
}

DNAstrand::DNAstrand( const std::string& sequence ) {
  for ( char c : sequence ) {
    if ( c != 'A' && c != 'G' && c != 'C' && c != 'T' && c != 'a' && c != 'g' &&
         c != 'c' && c != 't' ) {
      DoublyLinkedList::clear();
      throw std::invalid_argument( "invalid character in sequence" );
    }
    char upper = toupper( c );
    push_back( upper );
  }
}

DNAstrand::DNAstrand( const DNAstrand& rhs ): DoublyLinkedList( rhs ) {}

DNAstrand& DNAstrand::operator=( const DNAstrand& rhs ) {
  DoublyLinkedList<char>::operator=( rhs );
  return *this;
}

DNAstrand::~DNAstrand() { DoublyLinkedList::clear(); }

void DNAstrand::SpliceIn( const DNAstrand& pattern,
                          const DNAstrand& to_splice_in ) {
  if ( &pattern == &to_splice_in || &pattern == this ||
       &to_splice_in == this ) {
    throw std::runtime_error( "similar strands passed" );
  }
  std::string sequence_str = this->Str();
  std::string pattern_str = pattern.Str();
  int psize = pattern_str.size();
  std::string splice_str = to_splice_in.Str();
  std::string output = "";
  clear();
  for ( size_t i = 0; i < sequence_str.size(); ++i ) {
    if ( i + psize > sequence_str.size() ) {
      output += sequence_str.at( i );
      continue;
    }
    if ( ( sequence_str.substr( i, psize ) ) == pattern_str ) {
      output += splice_str;
      i = i + psize - 1;
    } else {
      output += sequence_str.at( i );
    }
  }
  for ( size_t i = 0; i < output.size(); ++i ) {
    push_back( output.at( i ) );
  }
}

std::string DNAstrand::Str() const {
  std::string output = "";
  Node<char>* curr = head_;
  while ( curr != nullptr ) {
    output += curr->data;
    curr = curr->next;
  }
  return output;
}

std::vector<char> ConvertUpper( std::vector<char> vect ) {
  for ( size_t i = 0; i < vect.size(); ++i ) {
    vect.at( i ) = toupper( vect.at( i ) );
  }
  return vect;
}

// std::ostream& operator<<( std::ostream& os, const
// DNAstrand& dna_strand ) {
//   return os;
// }
