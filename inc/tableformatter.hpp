#pragma once

// --- Standard Includes ---
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

namespace tableformatter
{

typedef std::vector<std::string> StringVector;

namespace internal
{

inline void assert( bool statement,
                    const std::string& message )
{
  if ( !statement )
  {
    throw std::runtime_error( message );
  }
}

inline StringVector splitAtLineBreaks( const std::string& cellString )
{
  std::istringstream cellStream( cellString );

  StringVector lines;

  while ( !cellStream.eof( ) )
  {
    std::string line;
    getline( cellStream, line );
    lines.push_back( line );
  }

  return lines;
}

} // namespace internal

enum class HORIZONTAL
{
  LEFT, CENTER, RIGHT
};

enum class VERTICAL
{
  TOP, MIDDLE, BOTTOM
};

struct CellFormatter
{
  size_t width;
  char paddingCharacter = ' ';
  HORIZONTAL horizontalAlignment = HORIZONTAL::LEFT;
  VERTICAL verticalAlignement = VERTICAL::TOP;

  CellFormatter( size_t _width );

  StringVector formatCellContent( const StringVector& unformattedCellChunks,
                                  size_t maximumNumberOfRows );
};

typedef std::vector<CellFormatter> CellFormatterVector;

struct RowStream
{
  StringVector getData( ) const
  {
    return cells;
  }

  void clear( )
  {
    cells.clear( );
    stream.str( std::string( ) );
    stream.clear( );
  }

  size_t getNumberOfColumns( ) const
  {
    return cells.size( );
  }

  template<typename T>
  RowStream& operator<<( T input )
  {
    stream << input;

    cells.push_back( stream.str( ) );

    stream.str( std::string( ) );
    stream.clear( );

    return *this;
  }

  RowStream& operator<<( std::ios_base& (*func)( std::ios_base& ) )
  {
    func( stream );

    return *this;
  }

private:
  std::vector<std::string> cells;
  std::stringstream stream;
};

class TableFormatter
{
public:
  TableFormatter( size_t _numberOfColumns,
                  size_t _columnWidth );

  TableFormatter( const CellFormatterVector& CellFormatters );

  void setCellFormatter( const CellFormatter& cellFormatter,
                         size_t column );

  void setColumnDelimiter( const std::string& delimiter,
                           size_t columnBoundary );

  void addRow( const StringVector& row );

  StringVector createChunks( std::string cellString,
                             size_t columnWidth );

  std::string toString( );

  size_t getTableWidth( ) const;

  void clearData( );

  void addHorizontalLine( const char& character = '-' );

  template<typename T>
  RowStream& operator<<( const T& input );

private:
  explicit TableFormatter( const TableFormatter& );
  TableFormatter& operator=( const TableFormatter& );
  void digestRowStream( );

  size_t numberOfColumns;
  CellFormatterVector cellFormatters;
  std::vector<StringVector> data;
  StringVector columnDelimiters;
  RowStream rowStream;
};

inline CellFormatter::CellFormatter( size_t _width ) :
        width( _width )
{
}

inline StringVector CellFormatter::formatCellContent( const StringVector& unformattedCellChunks,
                                                      size_t maximumNumberOfRows )
{
  /// Clarify vertical alignment

  size_t numberOfFilledRows = unformattedCellChunks.size( );
  size_t numberOfEmptyRows = maximumNumberOfRows - unformattedCellChunks.size( );
  auto formattedContent = StringVector( maximumNumberOfRows, std::string( width, paddingCharacter ) );

  size_t currentIndex = 0;

  if ( verticalAlignement == VERTICAL::TOP )
  {
  }
  else if ( verticalAlignement == VERTICAL::MIDDLE )
  {
    currentIndex = ( maximumNumberOfRows - numberOfFilledRows ) / 2;
  }
  else if ( verticalAlignement == VERTICAL::BOTTOM )
  {
    currentIndex = numberOfEmptyRows;
  }

  for ( const auto & line : unformattedCellChunks )
  {
    internal::assert( line.size( ) <= width, "Line is longer the width!" );

    std::string formattedLine;

    size_t paddingWidth = width - line.size( );

    if ( horizontalAlignment == HORIZONTAL::LEFT )
    {
      formattedLine = line + std::string( paddingWidth, paddingCharacter );
    }
    else if ( horizontalAlignment == HORIZONTAL::RIGHT )
    {
      formattedLine = std::string( paddingWidth, paddingCharacter ) + line;
    }
    else
    {
      short leftWidth = paddingWidth / 2;
      short rightWidth = paddingWidth - leftWidth;
      formattedLine = std::string( leftWidth, paddingCharacter ) + line + std::string( rightWidth, paddingCharacter );
    }

    formattedContent[currentIndex] = formattedLine;
    currentIndex++;
  }

  return formattedContent;
}

inline TableFormatter::TableFormatter( size_t _numberOfColumns,
                                       size_t _columnWidth ) :
        numberOfColumns( _numberOfColumns ),
        cellFormatters( numberOfColumns, _columnWidth ),
        columnDelimiters( numberOfColumns + 1, "|" )
{
}

inline TableFormatter::TableFormatter( const CellFormatterVector& CellFormatters ) :
        numberOfColumns( CellFormatters.size( ) ),
        cellFormatters( CellFormatters ),
        columnDelimiters( CellFormatters.size( ) + 1, "|" )
{
}

inline void TableFormatter::setCellFormatter( const CellFormatter& cellFormatter,
                                              size_t column )
{
  cellFormatters.at( column ) = cellFormatter;
}

inline void TableFormatter::setColumnDelimiter( const std::string& delimiter,
                                                size_t columnBoundary )
{
  columnDelimiters.at( columnBoundary ) = delimiter;
}

inline void TableFormatter::digestRowStream( )
{
  /// Digest rowStream first
  auto rowData = rowStream.getData( );
  rowStream.clear( );

  size_t numberOfRows = std::ceil( static_cast<double>( rowData.size( ) ) / numberOfColumns );
  auto start = rowData.begin( );

  for ( size_t i = 0; i < numberOfRows; ++i )
  {
    auto offset = std::min( numberOfColumns, static_cast<size_t>( std::distance( start, rowData.end( ) ) ) );
    StringVector currentRow( start, start + offset );

    auto gap = numberOfColumns - offset;
    for ( size_t j = 0; j < gap; ++j )
    {
      currentRow.push_back( "" );
    } // end of j-loop

    this->addRow( currentRow );
    start += numberOfRows + 1;
  } // end of i-loop
}

inline void TableFormatter::addRow( const StringVector& row )
{
  /// Digest rowStream first
  this->digestRowStream( );

  /// Add passed streams
  if ( row.size( ) != numberOfColumns )
  {
    throw std::runtime_error( "Number of columns does not match!" );
  }

  data.push_back( row );
}

inline StringVector TableFormatter::createChunks( std::string cellString,
                                                  size_t columnWidth )
{
  /// Remove multiple whitespace
  auto bothAreSpaces = [](char lhs, char rhs)
  { return (lhs == rhs) && (lhs == ' ');};

  auto new_end = std::unique( cellString.begin( ), cellString.end( ), bothAreSpaces );
  cellString.erase( new_end, cellString.end( ) );

  /// Split string at line breaks
  auto splitStrings = internal::splitAtLineBreaks( cellString );

  StringVector lines;

  for ( auto & splitString : splitStrings )
  {
    auto length = splitString.size( );

    /// Remove whiteSpace at beginning and end
    bool beginning = ( splitString[0] == ' ' );
    bool end = ( splitString[splitString.size( ) - 1] == ' ' );

    if ( beginning || end )
    {
      size_t start = beginning ? 1 : 0;
      length = start ? length - 1 : length;
      length = end ? length - 1 : length;
      splitString = splitString.substr( start, length );
    }

    while ( splitString.size( ) > columnWidth )
    {
      size_t spaceAt = 0;

      for ( size_t i = 0; i < splitString.size( ); ++i )
      {
        auto& character = splitString[i];

        if ( character == ' ' )
        {
          if ( i >= columnWidth )
          {
            break;
          }
          else
          {
            spaceAt = i;
          }
        }
      } // end of i-loop

      if ( spaceAt )
      {
        lines.push_back( splitString.substr( 0, spaceAt ) );
        length = splitString.size( ) - spaceAt;
        splitString = splitString.substr( spaceAt + 1, length );
      }
      else
      {
        lines.push_back( splitString.substr( 0, columnWidth ) );
        length = splitString.size( ) - columnWidth;
        splitString = splitString.substr( columnWidth - 1, length );
      }

      splitString = splitString.substr( 0, length );
    }

    lines.push_back( splitString );
  }

  return lines;
}

inline std::string TableFormatter::toString( )
{
  this->digestRowStream( );

  std::stringstream result;

  /// run over all rows
  for ( size_t iRow = 0; iRow < data.size( ); ++iRow )
  {
    auto& row = data[iRow];

    /// Create matrix of chunks out of each row
    std::vector<StringVector> unformattedRowChunks;
    unformattedRowChunks.reserve( numberOfColumns );
    size_t maximumNumberOfRows = 0;

    /// Tokenize the cell content and get maximum number of cells
    /// Find out the number of rows for each cell (vertical alignment!)
    for ( size_t iCell = 0; iCell < numberOfColumns; ++iCell )
    {
      auto& cellString = row[iCell];
      auto& cellFormatter = cellFormatters[iCell];

      StringVector cellChunks = createChunks( cellString, cellFormatter.width );

      maximumNumberOfRows = std::max( maximumNumberOfRows, cellChunks.size( ) );
      unformattedRowChunks.push_back( cellChunks );
    } // end of iCell-loop

    /// Create formatted cell content
    /// Create vector of chunks for each cell, all vectors should have the same length
    std::vector<StringVector> formattedRowChunks;
    formattedRowChunks.reserve( numberOfColumns );

    for ( size_t iCell = 0; iCell < numberOfColumns; ++iCell )
    {
      auto& unformattedCellChunks = unformattedRowChunks[iCell];
      auto& cellFormatter = cellFormatters[iCell];

      auto formattedCellChunks = cellFormatter.formatCellContent( unformattedCellChunks, maximumNumberOfRows );

      formattedRowChunks.push_back( formattedCellChunks );
    } // end of iCell-loop

    /// Print formatted cell content
    for ( size_t iCellRow = 0; iCellRow < maximumNumberOfRows; ++iCellRow )
    {
      /// Left delimiter
      result << columnDelimiters.front( );

      for ( size_t iCell = 0; iCell < numberOfColumns; ++iCell )
      {
        auto& cellRow = formattedRowChunks[iCell][iCellRow];

        result << cellRow << columnDelimiters[iCell + 1];
      } // end of iCell-loop

      result << "\n";

    } // end of iCellRow-loop
  } // end of iRow-loop

  return result.str( );
}

inline size_t TableFormatter::getTableWidth( ) const
{
  size_t width = 0;

  for ( const auto & delimiter : columnDelimiters )
  {
    width += delimiter.size( );
  }

  for ( const auto & formatter : cellFormatters )
  {
    width += formatter.width;
  }

  return width;
}

inline void TableFormatter::clearData( )
{
  data.clear( );
}

inline void TableFormatter::addHorizontalLine( const char& character )
{
  StringVector delimiterRow;

  for ( const auto & formatter : cellFormatters )
  {
    delimiterRow.push_back( std::string( formatter.width, character ) );
  }

  this->addRow( delimiterRow );
}

template<typename T>
RowStream& TableFormatter::operator <<( const T& input )
{
  rowStream << input;
  return rowStream;
}

} // namespace tableformatter
