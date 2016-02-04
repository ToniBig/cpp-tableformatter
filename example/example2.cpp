#include "../inc/tableformatter.hpp"

int main( int argc,
          char **argv )
{
  namespace tf = tableformatter;

  tf::CellFormatter column1( 3 );
  column1.horizontalAlignment = tf::HORIZONTAL::CENTER;
  column1.verticalAlignment = tf::VERTICAL::MIDDLE;

  tf::CellFormatter column2( 10 );
  column2.verticalAlignment = tf::VERTICAL::TOP;

  tf::CellFormatter column3( 12 );
  column3.horizontalAlignment = tf::HORIZONTAL::RIGHT;
  column3.verticalAlignment = tf::VERTICAL::BOTTOM;

  tf::CellFormatter column4( 12 );
  column4.horizontalAlignment = tf::HORIZONTAL::LEFT;

  tf::TableFormatter formatter( { column1, column2, column3, column4 } );

  formatter.setColumnDelimiter( "||", 1 );

  // Table header
  formatter << "#" << "Title" << "Band" << "Album";
  formatter.addHorizontalLine( '=' );

  formatter << 1 << "Guerilla Radio" << "Rage against the machine" << "Godzilla: The album";
  formatter.addHorizontalLine( '-' );
  formatter << 2 << "My own summer (Shove it)";
  formatter << "Deftones" << "Around the fur";
  formatter.addHorizontalLine( '-' );
  formatter << 3 << "Stinkfist" << "Tool" << "Aenima";
  formatter.addHorizontalLine( '-' );
  formatter << 4 << "After the eulogy" << "Boysetsfire";
  formatter.addHorizontalLine( '-' );

  std::cout << formatter.toString( ) << std::endl;
}

