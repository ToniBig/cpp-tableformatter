// --- Internal Includes ---
#include "../inc/tableformatter.hpp"

// --- System Includes ---
#include "catch.hpp"

using namespace tableformatter;

TEST_CASE("TablePrinter")
{
  SECTION( "Three non breaking lines" ){
  TableFormatter formatter( 3, 5 );

  formatter.addRow(
      { "foo", "bar", "hi"});
  formatter.addRow(
      { "foo", "bar", "hi"});
  formatter.addRow(
      { "foo", "bar", "hi"});

  formatter.setColumnDelimiter( "<>", 2 );

  CHECK(formatter.getTableWidth()==20);

  auto result = formatter.toString( );

  std::string reference =
  "|foo  |bar  <>hi   |\n"
  "|foo  |bar  <>hi   |\n"
  "|foo  |bar  <>hi   |\n";

  CHECK( reference == result );
}

SECTION("One breaking line")
{
  std::string reference =
  "|=========|=========|=========|\n"
  "|Hello    |Hello    |Hello    |\n"
  "|World    |World    |World    |\n"
  "|---------|---------|---------|\n";

  TableFormatter formatter(3, 9);
  formatter.addHorizontalLine('=');
  formatter.addRow(
      { " Hello World", " Hello World ", "Hello World "});
  formatter.addHorizontalLine();

  auto result = formatter.toString();

  CHECK( reference == result );
}

SECTION("Use stream operator")
{
  TableFormatter formatter(3, 4);
  formatter << "abc" << "abc" << "abc" << "abc" << "abd";
  auto result = formatter.toString();

  std::string reference =
  "|abc |abc |abc |\n"
  "|abc |abd |    |\n";

  CHECK( reference == result );
}

SECTION("Use stream operator with line delimiter")
{
  TableFormatter formatter(3, 4);
  formatter << "abc" << "abc" << "abc" << "abc" << "abd";
  formatter.addHorizontalLine('*');
  formatter << "abc" << "abc" << "abc" << "abc" << "abd";
  auto result = formatter.toString();

  std::string reference =
  "|abc |abc |abc |\n"
  "|abc |abd |    |\n"
  "|****|****|****|\n"
  "|abc |abc |abc |\n"
  "|abc |abd |    |\n";

  CHECK( reference == result );

  formatter.clearData();

  result = formatter.toString();
  CHECK( "" == result );
}

SECTION("Simple usage")
{
  TableFormatter formatter(3, 10);

  formatter.addHorizontalLine('-');
  formatter << "Hello beautiful world!";
  formatter << "Hello beautiful world!";
  formatter << "Hello beautiful world!";
  formatter.addHorizontalLine('-');

//  std::cout << formatter.toString() << std::endl;
}

}
