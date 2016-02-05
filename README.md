# cpp-tableformatter
Simple table formatting for C++

[![Build Status](https://travis-ci.org/ToniBig/cpp-tableformatter.svg?branch=master)](https://travis-ci.org/ToniBig/cpp-tableformatter)

## Features

* Cell content is automatically into multiple lines if it extends the column width
* Columns can be formatted horizontally (left, center, right) and vertically (top, middle, bottom)
* Stream semantics are supported including stream manipulators
* Nested tables can easily be created 

## How to use it?

**cpp-tableformatter** is contained in a single header. Therefore, just add the header file `tableformatter.hpp` 
to your project and include it whereever you need it.

### A simple example

The following code creates a table with three columns with a width of 10 characters each. Note that the strings 
for each cell are automatically broken into individual chunks resulting rows with multiple cells.

```c++
#include "tableformatter.hpp"

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
```
This results in the following output:
```
|----------|----------|----------|
|Hello     |Hello     |Hello     |
|beautiful |beautiful |beautiful |
|world!    |world!    |world!    |
|----------|----------|----------|
```

### A slightly bigger example

The following code creates a table with four entirely different columns. To achive this, a `CellFormatter` is created for each column. The `CellFormatters` are then passed in an initializer list to the `TableFormatter` constructor, which takes a `CellFormatter`vector. The delimiter between the first and second column is customized. Note the different ways to fill the columns using the `<<` operator. Also only three entries have been provided in the last row before the horizontal line has been added. Thus, the row has been completed automatically with an empty cell. Emtpy cells within a row have to be added explicitly.

```c++
#include "tableformatter.hpp"

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
```
This results in the following output:
```
| # ||Title     |        Band|Album       |
|===||==========|============|============|
|   ||Guerilla  |        Rage|Godzilla:   |
| 1 ||Radio     | against the|The album   |
|   ||          |     machine|            |
|---||----------|------------|------------|
|   ||My own    |            |Around the  |
| 2 ||summer    |            |fur         |
|   ||(Shove it)|    Deftones|            |
|---||----------|------------|------------|
| 3 ||Stinkfist |        Tool|Aenima      |
|---||----------|------------|------------|
| 4 ||After the |            |            |
|   ||eulogy    | Boysetsfire|            |
|---||----------|------------|------------|
```

### A numerical example
This final example shows how stream manipulators can be used to format the content of a table conveniently. The main focus here is on formatting floating point numbers.
```c++
#include "tableformatter.hpp"
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
```
This results in the following output:
```
| i |x             |x^2           |x^2-x         |
|---|--------------|--------------|--------------|
| 0 |0.0000e+00    |+0.000000     |0             |
| 1 |1.0000e-01    |+0.010000     |-0.1          |
| 2 |2.0000e-01    |+0.040000     |-0.16         |
| 3 |3.0000e-01    |+0.090000     |-0.210        |
| 4 |4.0000e-01    |+0.160000     |-0.2400       |
| 5 |5.0000e-01    |+0.250000     |-0.25000      |
| 6 |6.0000e-01    |+0.360000     |-0.240000     |
| 7 |7.0000e-01    |+0.490000     |-0.2100000    |
| 8 |8.0000e-01    |+0.640000     |-0.16000000   |
| 9 |9.0000e-01    |+0.810000     |-0.090000000  |
|---|--------------|--------------|--------------|
```

## Todo

* Add more documentation
