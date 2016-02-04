#include "../inc/tableformatter.hpp"

int main( int argc,
          char **argv )
{
  namespace tf = tableformatter;

  tf::TableFormatter formatter( 3, 10 );

  formatter.addHorizontalLine( '-' );
  formatter << "Hello beautiful world!";
  formatter << "Hello beautiful world!";
  formatter << "Hello beautiful world!";
  formatter.addHorizontalLine( '-' );

  std::cout << formatter.toString( ) << std::endl;
}

