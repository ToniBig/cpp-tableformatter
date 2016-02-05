#include "../inc/tableformatter.hpp"
#include <iomanip>

int main( int argc,
          char **argv )
{
  namespace tf = tableformatter;

  tf::TableFormatter formatter( 4, 14 );

  formatter << "i" << "x" << "x^2" << "x^2-x";

  tf::CellFormatter column1( 3 );
  column1.horizontalAlignment = tf::HORIZONTAL::CENTER;
  formatter.setCellFormatter( column1, 0 );

  formatter.addHorizontalLine( '-' );

  size_t steps = 10;

  for ( size_t i = 0; i < steps; ++i )
  {
    double x = 1.0 / steps * i;
    double x2 = x * x;
    double x2_x = x2 - x;

    formatter << i;
    formatter << std::setprecision( 4 ) << std::scientific << x;
    formatter << std::fixed << std::showpos << x2;
    formatter << std::setprecision( i ) << x2_x;

  } // end of i-loop

  formatter.addHorizontalLine( '-' );

  std::cout << formatter.toString( ) << std::endl;
}

