/* 
 * 
 * veque::veque test suite.
 * 
 * Additionally, valgrind claims there is no bad behavior throughout this usage.
 *
 *  Copyright (C) 2019 Drew Dormann
 * 
 */

#include <cstdint> 
#include <string> 
#include <unordered_set> 
#include <string> 
#include <functional> 
#include "catch.hpp"
#include "test_types.h"

TEMPLATE_PRODUCT_TEST_CASE( "large end growth", "[veque::veque][template]", (StdVeque, GrumpyVeque, PropogatingGrumpyVeque, AllocCountingVeque), (
        (int,veque::fast_resize_traits), (int,veque::std_vector_traits), (int,veque::no_reserve_traits), (int,front_vector_traits), 
        (std::string,veque::fast_resize_traits), (std::string,veque::std_vector_traits), (std::string,veque::no_reserve_traits), (std::string,front_vector_traits), 
        (double,veque::fast_resize_traits), (double,veque::std_vector_traits), (double,veque::no_reserve_traits), (double,front_vector_traits), 
        (LargeTrivialObject,veque::fast_resize_traits), (LargeTrivialObject,veque::std_vector_traits), (LargeTrivialObject,veque::no_reserve_traits), (LargeTrivialObject,front_vector_traits), 
        (NonTrivialObject,veque::fast_resize_traits), (NonTrivialObject,veque::std_vector_traits), (NonTrivialObject,veque::no_reserve_traits), (NonTrivialObject,front_vector_traits), 
        (ThrowingMoveConstructObject,veque::fast_resize_traits), (ThrowingMoveConstructObject,veque::std_vector_traits), (ThrowingMoveConstructObject,veque::no_reserve_traits), (ThrowingMoveConstructObject,front_vector_traits), 
        (ThrowingMoveAssignObject,veque::fast_resize_traits), (ThrowingMoveAssignObject,veque::std_vector_traits), (ThrowingMoveAssignObject,veque::no_reserve_traits), (ThrowingMoveAssignObject,front_vector_traits), 
        (ThrowingMoveObject,veque::fast_resize_traits), (ThrowingMoveObject,veque::std_vector_traits), (ThrowingMoveObject,veque::no_reserve_traits), (ThrowingMoveObject,front_vector_traits)
        ) )
{
    typename TestType::size_type size = 5;
    TestType v( size );

    REQUIRE( v.size() == size );
    REQUIRE( v.capacity() >= size );
    
    SECTION( "push_back" )
    {
        typename TestType::value_type val{};
        for ( int i = 0; i < 2'000; ++i )
        {
            v.push_back( val );
            ++size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        while ( v.size() )
        {
            v.pop_back();
            --size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        REQUIRE( 0 == size );
        REQUIRE( v.empty() );
    }
    
    SECTION( "emplace_back" )
    {
        for ( int i = 0; i < 2'000; ++i )
        {
            v.emplace_back();
            ++size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        while ( v.size() )
        {
            v.pop_back();
            --size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        REQUIRE( 0 == size );
        REQUIRE( v.empty() );
    }
    SECTION( "push_front" )
    {
        typename TestType::value_type val{};
        for ( int i = 0; i < 2'000; ++i )
        {
            v.push_front( val );
            ++size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        while ( v.size() )
        {
            v.pop_back();
            --size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        REQUIRE( 0 == size );
        REQUIRE( v.empty() );
    }
    SECTION( "emplace_front" )
    {
        for ( int i = 0; i < 2'000; ++i )
        {
            v.emplace_front();
            ++size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        while ( v.size() )
        {
            v.pop_back();
            --size;
            REQUIRE( v.size() == size );
            REQUIRE( v.capacity() >= size );
        }
        REQUIRE( 0 == size );
        REQUIRE( v.empty() );
    }
}
