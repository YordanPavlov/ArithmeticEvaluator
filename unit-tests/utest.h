#include "cppunit/TestFixture.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include "cppunit/extensions/HelperMacros.h"

#include "node.h"

class EvaluatorTest : public CppUnit::TestFixture  {

  CPPUNIT_TEST_SUITE( EvaluatorTest );

  CPPUNIT_TEST( testInt1 );
  CPPUNIT_TEST( testInt2 );
  CPPUNIT_TEST( testInt3 );
  CPPUNIT_TEST( testIntSub2 );
  CPPUNIT_TEST( testIntDiv1 );

  CPPUNIT_TEST( testComplex1 );
  CPPUNIT_TEST( testComplex2 );
  CPPUNIT_TEST( testComplex3 );
  CPPUNIT_TEST( testComplex4 );
  CPPUNIT_TEST( testComplex5 );
  CPPUNIT_TEST( testComplex6 );
  CPPUNIT_TEST( testComplex7 );

  CPPUNIT_TEST(testTypo1);
  CPPUNIT_TEST(testTypo2);
  CPPUNIT_TEST(testTypo3);
  CPPUNIT_TEST(testTypo5);
  CPPUNIT_TEST(testTypo6);
  CPPUNIT_TEST(testTypo7);
  CPPUNIT_TEST(testTypo8);
  CPPUNIT_TEST(testTypo9);
  CPPUNIT_TEST(testTypo10);
  CPPUNIT_TEST(testTypo11);
  CPPUNIT_TEST(testTypo12);
  CPPUNIT_TEST(testTypo13);

  CPPUNIT_TEST(testDivZero1);
  CPPUNIT_TEST(testDivZero2);
  CPPUNIT_TEST(testDivZero3);

  CPPUNIT_TEST(testOverflow1);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();

  void tearDown();

  void testInt1();
  void testInt2();
  void testInt3();
  void testIntSub2();
  void testIntDiv1();

  void testComplex1();
  void testComplex2();
  void testComplex3();
  void testComplex4();
  void testComplex5();
  void testComplex6();
  void testComplex7();

  void testTypo1();
  void testTypo2();
  void testTypo3();
  void testTypo5();
  void testTypo6();
  void testTypo7();
  void testTypo8();
  void testTypo9();
  void testTypo10();
  void testTypo11();
  void testTypo12();
  void testTypo13();

  void testDivZero1();
  void testDivZero2();
  void testDivZero3();

  void testOverflow1();
};

