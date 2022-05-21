//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                  MP : DNA Splicing : Student Test Cases                  //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "dna_strand.hpp"
#include "doubly_linked_list.hpp"
#include "node.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Testing Constructors", "[Constructors}" ) {
  SECTION( "Vector Constructor" ) {
    std::vector<char> bad_vect = { 'a', 'c', 'g', 't', ' ', 'f' };
    std::vector<char> good_vect = { 'a', 'c', 't' };
    std::vector<char> one = { 'a' };
    REQUIRE_THROWS( DNAstrand( bad_vect ) );
    DNAstrand dgood = DNAstrand( good_vect );
    REQUIRE( dgood.get_head()->data == 'A' );
    REQUIRE( dgood.get_tail()->data == 'T' );
    REQUIRE( dgood.get_head()->prev == nullptr );
    REQUIRE( dgood.get_tail()->next == nullptr );
    DNAstrand done = DNAstrand( one );
    REQUIRE( done.get_head() == done.get_tail() );
    REQUIRE( done.get_head()->data == done.get_tail()->data );
    REQUIRE( done.get_head()->data == 'A' );
    REQUIRE( done.get_tail()->data == 'A' );
    REQUIRE( done.get_head()->prev == nullptr );
    REQUIRE( done.get_tail()->next == nullptr );
  }
  SECTION( "String Constructor" ) {
    std::string good = "atcgtaaattgta";
    std::string bad = "atta fttaa";
    std::string one = "t";
    REQUIRE_THROWS( DNAstrand( bad ) );
    DNAstrand goodstring = DNAstrand( good );
    DNAstrand onestrand = DNAstrand( one );
    REQUIRE( goodstring.get_head()->data == 'A' );
    REQUIRE( goodstring.get_tail()->data == 'A' );
    REQUIRE( onestrand.get_head() == onestrand.get_tail() );
    REQUIRE( onestrand.get_tail()->data == onestrand.get_head()->data );
  }
  SECTION( "Copy Constructor" ) {
    std::vector<char> vect = { 'a', 't', 'g', 'g', 'c', 'c' };
    std::string str = "atggcc";
    DNAstrand dsv = DNAstrand( vect );
    DNAstrand dss = DNAstrand( str );
    DNAstrand vectcopy = DNAstrand( dsv );
    DNAstrand stringcopy = DNAstrand( dss );
    REQUIRE( dsv.Str() == vectcopy.Str() );
    REQUIRE( dss.Str() == stringcopy.Str() );
  }
  SECTION( "Assignment operator" ) {
    std::vector<char> vect = { 'a', 't', 'g', 'g', 'c', 'c' };
    std::string str = "atggcc";
    DNAstrand dsv = DNAstrand( vect );
    DNAstrand dss = DNAstrand( str );
    DNAstrand vectcopy = dsv;
    DNAstrand stringcopy = dss;
    REQUIRE( dsv.Str() == vectcopy.Str() );
    REQUIRE( dss.Str() == stringcopy.Str() );
  }
}

TEST_CASE( "Testing Functionality", "[functionality]" ) {
  SECTION( "To String" ) {
    std::vector<char> vect = { 'a', 't', 'g', 'g', 'c', 'c' };
    std::string str = "atggcc";
    std::string one = "c";
    DNAstrand dsv = DNAstrand( vect );
    DNAstrand dss = DNAstrand( str );
    DNAstrand oneds = DNAstrand( one );
    REQUIRE( dsv.Str() == "ATGGCC" );
    REQUIRE( dss.Str() == "ATGGCC" );
    REQUIRE( oneds.Str() == "C" );
  }
  SECTION( "Splice IN" ) {
    std::vector<char> vect_sequence = {
        'c', 't', 'g', 'a', 'a', 't', 't', 'c', 'g' };
    std::vector<char> vect_pattern = { 'g', 'a', 'a', 't', 't', 'c' };
    std::vector<char> vect_tosplice = { 't', 'g', 'a', 't', 'c' };
    DNAstrand sequence = DNAstrand( vect_sequence );
    DNAstrand pattern = DNAstrand( vect_pattern );
    DNAstrand tosplice = DNAstrand( vect_tosplice );
    REQUIRE_THROWS( sequence.SpliceIn( sequence, tosplice ) );
    REQUIRE_THROWS( sequence.SpliceIn( pattern, sequence ) );
    REQUIRE_THROWS( sequence.SpliceIn( sequence, sequence ) );
    REQUIRE_THROWS( sequence.SpliceIn( tosplice, tosplice ) );
    REQUIRE_THROWS( sequence.SpliceIn( pattern, pattern ) );
    sequence.SpliceIn( pattern, tosplice );
    REQUIRE( sequence.Str() == "CTTGATCG" );
  }
}