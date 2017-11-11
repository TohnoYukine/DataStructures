// VectorUnitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE Vector Test
#include <boost\test\unit_test.hpp>
#include <boost\test\data\test_case.hpp>
#include <boost\test\data\monomorphic.hpp>
#include <boost\mpl\list.hpp>
#include <string>
#include <vector>

#define private public
#include "Vector.h"
#undef private

#define REGISTER_DATASET(Dataset) namespace boost { namespace unit_test { namespace data { namespace monomorphic { template<> struct is_dataset<Dataset> : boost::mpl::true_ {}; } } } }

namespace Data = boost::unit_test::data;
namespace DS = DataStructures;

using TestTypes = boost::mpl::list<int, std::string>;


BOOST_AUTO_TEST_SUITE(ConstructorTest)

BOOST_AUTO_TEST_CASE_TEMPLATE(Constructor_1_default_constructor, T, TestTypes)
{
	DS::Vector<T> vec;
	BOOST_TEST((vec.storage != nullptr));
}

BOOST_DATA_TEST_CASE(Constructor_3_n_default_int, Data::make({ 0,1,10,1000,100000 }), n)
{
	DS::Vector<int> vec(n);
	BOOST_TEST((vec.storage != nullptr));
}
BOOST_DATA_TEST_CASE(Constructor_3_n_default_string, Data::make({ 0,1,10,1000,100000 }), n)
{
	DS::Vector<std::string> vec(n);
	BOOST_TEST((vec.storage != nullptr));
}

BOOST_DATA_TEST_CASE(Constructor_2_n_copy_int, Data::make({ 0,1,10,1000,100000 }), n)
{
	DS::Vector<int> vec(n, 42);
	BOOST_TEST((vec.storage != nullptr));
}
BOOST_DATA_TEST_CASE(Constructor_2_n_copy_string, Data::make({ 0,1,10,1000,100000 }), n)
{
	DS::Vector<std::string> vec1(n, "Hello, world!");
	BOOST_TEST((vec1.storage != nullptr));
	DS::Vector<std::string> vec2(n, "");
	BOOST_TEST((vec2.storage != nullptr));
}

BOOST_AUTO_TEST_CASE(Constructor_4_range_int)
{
	std::vector<int> vec{ 1,2,3,4,5,6,7,8,9 };

	DS::Vector<int> vec1(vec.begin(), vec.end());
	BOOST_TEST((vec1.storage != nullptr));
	DS::Vector<int> vec2(vec.begin(), vec.begin());
	BOOST_TEST((vec2.storage != nullptr));
}
BOOST_AUTO_TEST_CASE(Constructor_4_range_string)
{
	std::vector<std::string> vec{ "Hello","World","C++" };

	DS::Vector<std::string> vec1(vec.begin(), vec.end());
	BOOST_TEST((vec1.storage != nullptr));
	DS::Vector<std::string> vec2(vec.begin(), vec.begin());
	BOOST_TEST((vec2.storage != nullptr));
}

BOOST_AUTO_TEST_CASE(Constructor_5_copy_constructor_int)
{
	DS::Vector<int> vec1;
	BOOST_REQUIRE((vec1.storage != nullptr));
	DS::Vector<int> cvec1(vec1);
	BOOST_TEST((cvec1.storage != nullptr));

	DS::Vector<int> vec2(3, 4);
	BOOST_REQUIRE((vec2.storage != nullptr));
	DS::Vector<int> cvec2(vec2);
	BOOST_TEST((cvec2.storage != nullptr));
}
BOOST_AUTO_TEST_CASE(Constructor_5_copy_constructor_string)
{
	DS::Vector<std::string> vec1;
	BOOST_REQUIRE((vec1.storage != nullptr));
	DS::Vector<std::string> cvec1(vec1);
	BOOST_TEST((cvec1.storage != nullptr));

	DS::Vector<std::string> vec2(30, "Hello");
	BOOST_REQUIRE((vec2.storage != nullptr));
	DS::Vector<std::string> cvec2(vec2);
	BOOST_TEST((cvec2.storage != nullptr));
}

BOOST_AUTO_TEST_CASE(Constructor_6_move_constructor_int)
{
	DS::Vector<int> vec1;
	BOOST_REQUIRE((vec1.storage != nullptr));
	DS::Vector<int> cvec1(std::move(vec1));
	BOOST_TEST((cvec1.storage != nullptr));
	BOOST_TEST(vec1.empty());

	DS::Vector<int> vec2(3, 4);
	BOOST_REQUIRE((vec2.storage != nullptr));
	DS::Vector<int> cvec2(std::move(vec2));
	BOOST_TEST((cvec2.storage != nullptr));
	BOOST_TEST(vec2.empty());
}
BOOST_AUTO_TEST_CASE(Constructor_6_move_constructor_string)
{
	DS::Vector<std::string> vec1;
	BOOST_REQUIRE((vec1.storage != nullptr));
	DS::Vector<std::string> cvec1(std::move(vec1));
	BOOST_TEST((cvec1.storage != nullptr));
	BOOST_TEST(vec1.empty());

	DS::Vector<std::string> vec2(3, "Hello");
	BOOST_REQUIRE((vec2.storage != nullptr));
	DS::Vector<std::string> cvec2(std::move(vec2));
	BOOST_TEST((cvec2.storage != nullptr));
	BOOST_TEST(vec2.empty());
}

BOOST_AUTO_TEST_CASE(Constructor_8_initializer_list_int)
{
	DS::Vector<int> vec1{};
	BOOST_REQUIRE((vec1.storage != nullptr));
	DS::Vector<int> vec2{ 1,2,3 };
	BOOST_REQUIRE((vec2.storage != nullptr));
}
BOOST_AUTO_TEST_CASE(Constructor_8_initializer_list_string)
{
	DS::Vector<std::string> vec1{};
	BOOST_REQUIRE((vec1.storage != nullptr));
	DS::Vector<std::string> vec2{ "Hello","World","C++" };
	BOOST_REQUIRE((vec2.storage != nullptr));
}

BOOST_AUTO_TEST_SUITE_END()