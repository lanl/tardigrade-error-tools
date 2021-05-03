/**
  * \file test_error_tools.cpp
  *
  * Tests for error_tools
  */

#include<error_tools.h>
#include<sstream>
#include<fstream>

#define BOOST_TEST_MODULE test_error_tools
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

struct cout_redirect{
    cout_redirect( std::streambuf * new_buffer)
        : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

    private:
        std::streambuf * old;
};

struct cerr_redirect{
    cerr_redirect( std::streambuf * new_buffer)
        : old( std::cerr.rdbuf( new_buffer ) )
    { }

    ~cerr_redirect( ) {
        std::cerr.rdbuf( old );
    }

    private:
        std::streambuf * old;
};

BOOST_AUTO_TEST_CASE( testReplaceAll ){
    /*!
     * Test of the replaceAll function
     */

    std::string test = "The quick\n brown fox jum\nped over the \nlazy dog\n";
    errorTools::replaceAll(test, "\n", "?");

    std::string result = "The quick? brown fox jum?ped over the ?lazy dog?";

    BOOST_CHECK( result == test );
}

BOOST_AUTO_TEST_CASE( testPrint ){
    /*!
     * Test of the print utility
     */

    //Setup redirect variables for stdout
    std::stringbuf buffer;
    cout_redirect rd(&buffer);
    boost::test_tools::output_test_stream result;

    //Initialize test variables
    std::string answer;
    cout_redirect guard( result.rdbuf() );

    //Initialize test error node stack
    errorTools::Node *n4 = new errorTools::Node("fxn4", "problem in addition\n");

    errorTools::Node *n3 = new errorTools::Node("fxn3", "error in fxn4\n");
    n3->addNext(n4);

    errorTools::Node *n2 = new errorTools::Node("fxn2", "error in fxn3\n");
    n2->addNext(n3);

    errorTools::Node n1("fxn1", "error in fxn2\n");
    n1.addNext(n2);

    //Construct expected strings
    std::string header = "\n***************\n"
                           "*    ERROR    *\n"
                           "***************\n\n";
    std::string body = "In function fxn1\n"
                       "\terror in fxn2\n"
                       "\t\n"
                       "In function fxn2\n"
                       "\terror in fxn3\n"
                       "\t\n"
                       "In function fxn3\n"
                       "\terror in fxn4\n"
                       "\t\n"
                       "In function fxn4\n"
                       "\tproblem in addition\n"
                       "\t\n";
    std::string footer = "\n***************************\n"
                           "*    END ERROR MESSAGE    *\n"
                           "***************************\n";

    //Test print with headers
    answer = header + body + footer;
    n1.print( );
    BOOST_CHECK( result.is_equal(answer) );

    //Check for no header
    answer = body;
    n1.print( false );
    BOOST_CHECK( result.is_equal(answer) );

}

BOOST_AUTO_TEST_CASE( safeTestPrint ){
    /*!
     * Test of the print utility using safe pointers
     */

    std::unique_ptr< errorTools::Node > n4;
    n4.reset( new errorTools::Node("fxn4", "problem in addition\n") );

    std::unique_ptr< errorTools::Node > n3;
    n3.reset( new errorTools::Node("fxn3", "error in fxn4\n") );
    n3->addNext(n4);

    std::unique_ptr< errorTools::Node > n2;
    n2.reset( new errorTools::Node("fxn2", "error in fxn3\n") );
    n2->addNext(n3);

    errorTools::Node n1("fxn1", "error in fxn2\n");
    n1.addNext(n2);

    boost::test_tools::output_test_stream result;
    {
        cerr_redirect guard( result.rdbuf() );
        n1.print( );
    }

    std::string answer = "\n***************\n"
                           "*    ERROR    *\n"
                           "***************\n\n"
                         "In function fxn1\n"
                         "\terror in fxn2\n"
                         "\t\n"
                         "In function fxn2\n"
                         "\terror in fxn3\n"
                         "\t\n"
                         "In function fxn3\n"
                         "\terror in fxn4\n"
                         "\t\n"
                         "In function fxn4\n"
                         "\tproblem in addition\n"
                         "\t\n"
                         "\n***************************\n"
                           "*    END ERROR MESSAGE    *\n"
                           "***************************\n";

    BOOST_CHECK( result.is_equal(answer) );
}
