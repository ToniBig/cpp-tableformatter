// --- Internal Includes ---
#include "../inc/tableformatter.hpp"

// --- System Includes ---
#include "catch.hpp"

using namespace tableformatter;

TEST_CASE("CellFormatter")
{
  CellFormatter cellFormatter( 7 );
  cellFormatter.paddingCharacter = '+';
  StringVector input { "Hello", "World" };

  SECTION("Top aligment"){

  SECTION( "Left alignment with + padding" )
  {
    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "Hello++" );
    CHECK( result[1] == "World++" );
    CHECK( result[2] == "+++++++" );
    CHECK( result[3] == "+++++++" );
  }

  SECTION( "Right alignment with + padding" )
  {
    cellFormatter.horizontalAlignment=HORIZONTAL::RIGHT;

    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "++Hello" );
    CHECK( result[1] == "++World" );
    CHECK( result[2] == "+++++++" );
    CHECK( result[3] == "+++++++" );
  }

  SECTION( "Center alignment with + padding" )
  {
    cellFormatter.horizontalAlignment=HORIZONTAL::CENTER;

    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "+Hello+" );
    CHECK( result[1] == "+World+" );
    CHECK( result[2] == "+++++++" );
    CHECK( result[3] == "+++++++" );
  }
}

  SECTION("Middle aligment"){
  cellFormatter.verticalAlignement=VERTICAL::MIDDLE;

  SECTION( "Left alignment with + padding" )
  {
    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "+++++++" );
    CHECK( result[1] == "Hello++" );
    CHECK( result[2] == "World++" );
    CHECK( result[3] == "+++++++" );
  }

  SECTION( "Right alignment with + padding" )
  {
    cellFormatter.horizontalAlignment=HORIZONTAL::RIGHT;

    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "+++++++" );
    CHECK( result[1] == "++Hello" );
    CHECK( result[2] == "++World" );
    CHECK( result[3] == "+++++++" );
  }

  SECTION( "Center alignment with + padding" )
  {
    cellFormatter.horizontalAlignment=HORIZONTAL::CENTER;

    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "+++++++" );
    CHECK( result[1] == "+Hello+" );
    CHECK( result[2] == "+World+" );
    CHECK( result[3] == "+++++++" );
  }
}
  SECTION("Bottom aligment"){
  cellFormatter.verticalAlignement=VERTICAL::BOTTOM;

  SECTION( "Left alignment with + padding" )
  {
    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "+++++++" );
    CHECK( result[1] == "+++++++" );
    CHECK( result[2] == "Hello++" );
    CHECK( result[3] == "World++" );
  }

  SECTION( "Right alignment with + padding" )
  {
    cellFormatter.horizontalAlignment=HORIZONTAL::RIGHT;

    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "+++++++" );
    CHECK( result[1] == "+++++++" );
    CHECK( result[2] == "++Hello" );
    CHECK( result[3] == "++World" );
  }

  SECTION( "Center alignment with + padding" )
  {
    cellFormatter.horizontalAlignment=HORIZONTAL::CENTER;

    auto result = cellFormatter.formatCellContent(input, 4);

    CHECK( result.size() == 4);
    CHECK( result[0] == "+++++++" );
    CHECK( result[1] == "+++++++" );
    CHECK( result[2] == "+Hello+" );
    CHECK( result[3] == "+World+" );
  }
}
}
