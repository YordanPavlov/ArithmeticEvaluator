#include <cmath>

#include "cppunit/TestFixture.h"
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include "cppunit/extensions/HelperMacros.h"

#include "parser.h"
#include "utest.h"


using namespace parser;


CPPUNIT_TEST_SUITE_REGISTRATION( EvaluatorTest );

  void EvaluatorTest::setUp()
  {
  }

  void EvaluatorTest::tearDown()
  {
  }

  void EvaluatorTest::testInt1()
  {
      std::string line = "(5 + 6)";

      Parser parser;
      parser.parseInput(line);
      BaseNodePtr& parentOperand = parser.getResult();
      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::ADD == rootNode->type);
      CPPUNIT_ASSERT( 11 == rootNode->solve());
  }

  void EvaluatorTest::testInt2()
  {
      std::string line = "5";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::SIMPLE == rootNode->type);
      CPPUNIT_ASSERT( 5 == rootNode->solve());
  }

  void EvaluatorTest::testInt3()
  {
      std::string line = "(5)";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::SIMPLE == rootNode->type);
      CPPUNIT_ASSERT( 5 == rootNode->solve());
  }

  void EvaluatorTest::testIntSub2()
  {
      std::string line = "(5-6)";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::SUB == rootNode->type);
      CPPUNIT_ASSERT( -1 == rootNode->solve());
  }

  void EvaluatorTest::testIntDiv1()
  {
      std::string line = "(9 / 3)";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::DIV == rootNode->type);
      CPPUNIT_ASSERT( 3 == rootNode->solve());
  }

  void EvaluatorTest::testComplex1()
  {
      std::string line = "( 1 + 2) * 2";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::MUL == rootNode->type);
      CPPUNIT_ASSERT( 6 == rootNode->solve());
  }

  void EvaluatorTest::testComplex2()
  {
      std::string line = "2 - ( 1 + 1)";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::SUB == rootNode->type);
      CPPUNIT_ASSERT( 0 == rootNode->solve());
  }

  void EvaluatorTest::testComplex3()
  {
      std::string line = "3 / ( 2 - 0)";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::DIV == rootNode->type);
      CPPUNIT_ASSERT( 1.5 == rootNode->solve());
  }

  void EvaluatorTest::testComplex4()
  {
      std::string line = "(3 - 1) / (2 - 1)";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::DIV == rootNode->type);
      CPPUNIT_ASSERT( 2 == rootNode->solve());
  }

  void EvaluatorTest::testComplex5()
  {
      std::string line = "((((3 - 1) - 1) - 1) / (2 - 1))";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::DIV == rootNode->type);
      CPPUNIT_ASSERT( 0 == rootNode->solve());
  }

  void EvaluatorTest::testComplex6()
  {
      std::string line = "  (4 + 5 * (7 - 3)) - 2";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::SUB == rootNode->type);
      CPPUNIT_ASSERT( 22 == rootNode->solve());
  }

  void EvaluatorTest::testComplex7()
  {
      std::string line = "4+5+7/2";

      Parser parser;
      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::ADD == rootNode->type);
      CPPUNIT_ASSERT( 12.5 == rootNode->solve());
  }

   void EvaluatorTest::testTypo1()
  {
      std::string line = "( 1 + x)) = 1";

      std::string expectedStr("Unexpected character x");

      try
      {
          Parser parser;
          parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo2()
  {
      std::string line = "( 1 + 4)( = 1";

      std::string expectedStr("The order or literals is not met.");

      try
      {
          Parser parser;
          parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo3()
  {
      std::string line = "( 1 + 6) = 1)";

      std::string expectedStr("Unexpected character =");

      try
      {
          Parser parser;
          parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo5()
  {
      std::string line = "1 + -2";

      std::string expectedStr("The order or literals is not met.");

      try
      {
          Parser parser;
          parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo6()
  {
      std::string line = "(-5)";

      std::string expectedStr("Operator parsed at start of expression.");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo7()
  {
      std::string line = "(-5 - 6)";

      std::string expectedStr("Operator parsed at start of expression.");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo8()
  {
      std::string line = "(15 / 5)";

      std::string expectedStr("The order or literals is not met.");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }


  void EvaluatorTest::testTypo9()
  {
      std::string line = "2(1-2)";

      std::string expectedStr("The order or literals is not met.");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo10()
  {
      std::string line = "1 * -5";

      std::string expectedStr("The order or literals is not met.");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo11()
  {
      std::string line = "1 / -5";

      std::string expectedStr("The order or literals is not met.");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo12()
  {
      std::string line = "1 / 5 +";

      std::string expectedStr("Last token in expression is not an operand.");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testTypo13()
  {
      std::string line = "test";

      std::string expectedStr("Unexpected character t");
      Parser parser;
      try
      {
        parser.parseInput(line);
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testDivZero1()
  {
      std::string line = "5 / 0";

      std::string expectedStr("Division by zero.");
      Parser parser;

      parser.parseInput(line);
      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::DIV == rootNode->type);
      try
      {
        rootNode->solve();
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testDivZero2()
  {
      std::string line = "5 / ( 5 -5 )";

      std::string expectedStr("Division by zero.");
      Parser parser;
      parser.parseInput(line);

      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::DIV == rootNode->type);
      try
      {
        rootNode->solve();
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testDivZero3()
  {
      std::string line = "5 / ( 0 * 5 )";

      std::string expectedStr("Division by zero.");
      Parser parser;
      parser.parseInput(line);

      const BaseNodePtr& parentOperand = parser.getResult();

      CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
      ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
      BaseNode* rootNode = complex->treeifyComplex();
      CPPUNIT_ASSERT( NodeType::DIV == rootNode->type);
      try
      {
        rootNode->solve();
      }
      catch(std::runtime_error& ex)
      {
          CPPUNIT_ASSERT(expectedStr == ex.what());
          return;
      }
      CPPUNIT_FAIL("Expected exception was not thrown");
  }

  void EvaluatorTest::testOverflow1()
  {
    std::string line = "9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
     9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*\
9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9*9";

    Parser parser;
    parser.parseInput(line);

    const BaseNodePtr& parentOperand = parser.getResult();

    CPPUNIT_ASSERT( NodeType::COMPLEX == parentOperand->type );
    ComplexOperand* complex = static_cast<ComplexOperand*>(parentOperand.get());
    BaseNode* rootNode = complex->treeifyComplex();
    CPPUNIT_ASSERT( NodeType::MUL == rootNode->type);

    std::string expectedStr("Too big values. Integer overflow.");
    try
    {
      rootNode->solve();
    }
    catch(std::runtime_error& ex)
    {
        CPPUNIT_ASSERT(expectedStr == ex.what());
        return;
    }
    CPPUNIT_FAIL("Expected exception was not thrown");
  }

int main( int, char **)
{
  // Get the top level suite from the registry
  CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CPPUNIT_NS::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Run the test.
  bool wasSucessful = runner.run();

  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;

}
