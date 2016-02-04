CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

#------------------------------------------------------------------------------
# SET BUILD TYPE
#------------------------------------------------------------------------------
SET( CMAKE_BUILD_TYPE "" CACHE STRING "" )
SET_PROPERTY ( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS DEBUG RELEASE RELWITHDEBINFO MINSIZEREL NONE ) 

PROJECT ( tableprinter CXX ) 

SET ( CMAKE_CXX_FLAGS "-std=c++11" )

#------------------------------------------------------------------------------
# TESTING
#------------------------------------------------------------------------------

SET ( TESTSOURCES test/catch_main.cpp test/cellformatter_test.cpp test/tableformatter_test.cpp  )
ADD_EXECUTABLE ( ${PROJECT_NAME}_testrunner ${TESTSOURCES} )

ADD_CUSTOM_TARGET ( 
run_${PROJECT_NAME}_tests 
${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_testrunner
COMMENT "Running tests for ${PROJECT_NAME}" VERBATIM 
)
  
# build runner before execution if changes have been made to sources
ADD_DEPENDENCIES ( run_${PROJECT_NAME}_tests 
                   ${PROJECT_NAME}_testrunner )
                   
#------------------------------------------------------------------------------
# EXAMPLES
#------------------------------------------------------------------------------

ADD_EXECUTABLE ( example1 example/example1.cpp )
ADD_EXECUTABLE ( example2 example/example2.cpp )
ADD_EXECUTABLE ( example3 example/example3.cpp )
