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

using namespace tf;

tf::TableFormatter formatter(3, 10);

formatter.addHorizontalLine('-');
formatter << "Hello beautiful world!";
formatter << "Hello beautiful world!";
formatter << "Hello beautiful world!";
formatter.addHorizontalLine('-');

std::cout << formatter.toString() << std::endl;
```

```
|----------|----------|----------|
|Hello     |Hello     |Hello     |
|beautiful |beautiful |beautiful |
|world!    |world!    |world!    |
|----------|----------|----------|
```

## Todo

* Add more documentation
