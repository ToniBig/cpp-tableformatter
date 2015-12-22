#include "../include/tableformatter.hpp"

int main( int argc,
          char **argv )
{
  tableformatter::TableFormatter formatter( 4, 8 );

  formatter.addHorizontalLine( '=' );
  formatter << std::fixed << 1.23 << std::scientific << 1.23 << std::hex << 123 << std::oct << 123;
  formatter << std::fixed << 1.23 << std::scientific << 1.23 << std::hex << 123 << std::oct << 123;
  formatter << std::fixed << 1.23 << std::scientific << 1.23 << std::hex << 123 << std::oct << 123;
  formatter.addHorizontalLine( '-' );
  formatter << std::fixed << 1.23 << std::scientific << 1.23 << std::hex << 123 << std::oct << 123;
  formatter << std::fixed << 1.23 << std::scientific << 1.23 << std::hex << 123 << std::oct << 123;
  formatter << std::fixed << 1.23 << std::scientific << 1.23 << std::hex << 123 << std::oct << 123;
  formatter.addHorizontalLine( '=' );

  std::cout << "output: \n" << formatter.toString( ) << std::endl;
}

