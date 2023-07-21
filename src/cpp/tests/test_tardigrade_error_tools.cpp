/**
  * \file test_tardigrade_error_tools.cpp
  *
  * Tests for tardigrade_error_tools
  */

#include<tardigrade_error_tools.h>
#include<sstream>
#include<fstream>

#define BOOST_TEST_MODULE test_tardigrade_error_tools
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

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
    tardigradeErrorTools::replaceAll(test, "\n", "?");

    std::string result = "The quick? brown fox jum?ped over the ?lazy dog?";

    BOOST_CHECK( result == test );

}

BOOST_AUTO_TEST_CASE( testPrint ){
    /*!
     * Test of the print utility
     */

    //Setup redirect variables for stderr
    std::stringbuf buffer;
    cerr_redirect rd(&buffer);
    boost::test_tools::output_test_stream result;

    //Initialize test variables
    std::string answer;
    cerr_redirect guard( result.rdbuf() );

    //Initialize test error node stack
    tardigradeErrorTools::Node *n4 = new tardigradeErrorTools::Node("fxn4", "problem in addition\n");

    tardigradeErrorTools::Node *n3 = new tardigradeErrorTools::Node("fxn3", "error in fxn4\n");
    n3->addNext(n4);

    tardigradeErrorTools::Node *n2 = new tardigradeErrorTools::Node("fxn2", "error in fxn3\n");
    n2->addNext(n3);

    tardigradeErrorTools::Node n1("fxn1", "error in fxn2\n");
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

    //Test print utility
    //Test print with headers
    answer = header + body + footer;
    n1.print( );
    BOOST_CHECK( result.is_equal(answer) );

    //Check for no header
    answer = body;
    n1.print( false );
    BOOST_CHECK( result.is_equal(answer) );

    //Test of the print utility using safe pointers
    //Initialize test error node stack
    std::unique_ptr< tardigradeErrorTools::Node > safe_n4;
    safe_n4.reset( new tardigradeErrorTools::Node("fxn4", "problem in addition\n") );

    std::unique_ptr< tardigradeErrorTools::Node > safe_n3;
    safe_n3.reset( new tardigradeErrorTools::Node("fxn3", "error in fxn4\n") );
    safe_n3->addNext(safe_n4);

    std::unique_ptr< tardigradeErrorTools::Node > safe_n2;
    safe_n2.reset( new tardigradeErrorTools::Node("fxn2", "error in fxn3\n") );
    safe_n2->addNext(safe_n3);

    tardigradeErrorTools::Node safe_n1("fxn1", "error in fxn2\n");
    safe_n1.addNext(safe_n2);

    //Test print with headers
    answer = header + body + footer;
    safe_n1.print( );
    BOOST_CHECK( result.is_equal(answer) );

    //Check for no header
    answer = body;
    safe_n1.print( false );
    BOOST_CHECK( result.is_equal(answer) );

}

BOOST_AUTO_TEST_CASE( test_printNestedExceptions ){

    boost::test_tools::output_test_stream result;

    //Initialize test variables
    std::string answer = "1 : error 1\n0 : error 2\n";
    cerr_redirect guard( result.rdbuf() );
    
    try{
        try{
            throw std::runtime_error( "error 1" );
        }
        catch( std::exception &e ){
            std::throw_with_nested( std::logic_error( "error 2" ) );
        }
    }
    catch( std::exception &e ){
        tardigradeErrorTools::printNestedExceptions( e );
    }
    catch(...){
        BOOST_CHECK( false );
    }

    BOOST_CHECK( result.is_equal( answer ) );

}

void badFunction( ){
    TARDIGRADE_ERROR_TOOLS_CATCH( throw std::logic_error( "oops" ) );
}

void containsBadFunction( ){
    TARDIGRADE_ERROR_TOOLS_CATCH( badFunction( ) );
}

void goodFunction( ){
    return;
}

tardigradeErrorTools::Node* goodNodeFunction( ){
    return NULL;
}

tardigradeErrorTools::Node* badNodeFunction( ){
    return new tardigradeErrorTools::Node( __func__, "oops" );
}

tardigradeErrorTools::Node* containsBadNodeFunction( ){
    tardigradeErrorTools::Node *error = badNodeFunction( );
    if ( error ){
        tardigradeErrorTools::Node *result = new tardigradeErrorTools::Node( __func__, "error 2");
        result->addNext( error );
        return result;
    }
    return NULL;
}

BOOST_AUTO_TEST_CASE( test_form_stacktrace ){

    boost::test_tools::output_test_stream result;

    //Initialize test variables
    cerr_redirect guard( result.rdbuf( ) );

    TARDIGRADE_ERROR_TOOLS_CATCH( goodFunction( ) );

    try{
        TARDIGRADE_ERROR_TOOLS_CATCH( containsBadFunction( ) );
    }
    catch( std::exception &e ){
        tardigradeErrorTools::printNestedExceptions( e );
    }

    BOOST_CHECK( !result.is_empty( ) );

}

BOOST_AUTO_TEST_CASE( test_form_node_stacktrace ){

    boost::test_tools::output_test_stream result;

    cerr_redirect guard( result.rdbuf( ) );

    TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER( goodNodeFunction( ) );

    try{
        TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER( containsBadNodeFunction( ) );
    }
    catch( std::exception &e ){
        std::cerr << e.what( ) << "\n";
    }

    BOOST_CHECK( !result.is_empty( ) );

}
