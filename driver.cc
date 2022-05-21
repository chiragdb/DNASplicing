#include <iostream>
#include <string>
#include <vector>

#include "dna_strand.hpp"
#include "doubly_linked_list.hpp"

using namespace std;

int main() {
  std::vector<char> vect;
  for ( size_t i = 0; i < 15; ++i ) {
    vect.push_back( 'a' );
    vect.push_back( 'T' );
    vect.push_back( 't' );
    vect.push_back( 'g' );
  }
  std::vector<char> one_value = { 'C' };
  DNAstrand ds_vect = DNAstrand( vect );
  DNAstrand ds_one = DNAstrand( one_value );
  std::cout << "multiple: " << ds_vect.Str() << std::endl;
  std::cout << "one: " << ds_one.Str() << std::endl;
}
