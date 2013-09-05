//=================================================================================================
/*!
//  \file src/mathtest/sparsesubvector/ClassTest.cpp
//  \brief Source file for the SparseSubvector class test
//
//  Copyright (C) 2011 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. This library is free software; you can redistribute
//  it and/or modify it under the terms of the GNU General Public License as published by the
//  Free Software Foundation; either version 3, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
//  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along with a special
//  exception for linking and compiling against the Blaze library, the so-called "runtime
//  exception"; see the file COPYING. If not, see http://www.gnu.org/licenses/.
*/
//=================================================================================================


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <blaze/math/DynamicVector.h>
#include <blazetest/mathtest/sparsesubvector/ClassTest.h>


namespace blazetest {

namespace mathtest {

namespace sparsesubvector {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the SparseSubvector class test.
//
// \exception std::runtime_error Operation error detected.
*/
ClassTest::ClassTest()
   : vec_( 8UL )
{
   testConstructors();
   testAssignment();
   testAddAssign();
   testSubAssign();
   testMultAssign();
   testDivAssign();
   testSubscript();
   testIterator();
   testNonZeros();
   testReset();
   testAppend();
   testInsert();
   testErase();
   testScale();
   testFind();
   testLowerBound();
   testUpperBound();
   testIsDefault();
   testIsNan();
   testMinimum();
   testMaximum();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the SparseSubvector constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the SparseSubvector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testConstructors()
{
   test_ = "SparseSubvector constructor";

   initialize();

   for( size_t start=0UL; start<vec_.size(); ++start ) {
      for( size_t size=1UL; start+size<vec_.size(); ++size )
      {
         SVT subvector = sub( vec_, start, size );

         for( size_t i=0UL; i<size; ++i )
         {
            if( subvector[i] != vec_[start+i] ) {
               std::ostringstream oss;
               oss << " Test: " << test_ << "\n"
                   << " Error: Setup of sparse subvector failed\n"
                   << " Details:\n"
                   << "   Start = " << start << "\n"
                   << "   Size  = " << size  << "\n"
                   << "   Subvector:\n" << subvector << "\n"
                   << "   Vector:\n" << vec_ << "\n";
               throw std::runtime_error( oss.str() );
            }
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubvector assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the SparseSubvector class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAssignment()
{
   //=====================================================================================
   // Copy assignment
   //=====================================================================================

   {
      test_ = "SparseSubvector copy assignment (no aliasing)";

      initialize();

      VT vec( 10UL );
      vec[5] =  6;
      vec[6] = -8;

      SVT subvector = sub( vec, 5UL, 3UL );
      subvector = sub( vec_, 4UL, 3UL );

      checkSize    ( subvector,  3UL );
      checkNonZeros( subvector,  2UL );
      checkSize    ( vec_     ,  8UL );
      checkNonZeros( vec_     ,  4UL );
      checkSize    ( vec      , 10UL );
      checkNonZeros( vec      ,  2UL );

      if( subvector[0] != -3 || subvector[1] != 0 || subvector[2] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( -3 0 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec[0] !=  0 || vec[1] != 0 || vec[2] != 0 || vec[3] != 0 || vec[4] != 0 ||
          vec[5] != -3 || vec[6] != 0 || vec[7] != 4 || vec[8] != 0 || vec[9] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 0 0 0 0 0 -3 0 4 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "SparseSubvector copy assignment (aliasing)";

      initialize();

      SVT subvector = sub( vec_, 1UL, 3UL );
      subvector = sub( vec_, 4UL, 3UL );

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 2UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 4UL );

      if( subvector[0] != -3 || subvector[1] != 0 || subvector[2] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( -3 0 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != -3 || vec_[2] != 0 || vec_[3] != 4 ||
          vec_[4] != -3 || vec_[5] !=  0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 -3 0 4 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Dense vector assignment
   //=====================================================================================

   {
      test_ = "Dense vector assignment";

      initialize();

      SVT subvector = sub( vec_, 3UL, 4UL );

      blaze::DynamicVector<int,blaze::rowVector> vec( 4UL, 0 );
      vec[1] = 8;
      vec[3] = 9;

      subvector = vec;

      checkSize    ( subvector, 4UL );
      checkNonZeros( subvector, 2UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 3UL );

      if( subvector != vec ||
          subvector[0] != 0 || subvector[1] != 8 || subvector[2] != 0 || subvector[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 8 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] != 0 || vec_[1] != 1 || vec_[2] != 0 || vec_[3] != 0 ||
          vec_[4] != 8 || vec_[5] != 0 || vec_[6] != 9 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 1 0 0 8 0 9 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Sparse vector assignment
   //=====================================================================================

   {
      test_ = "Sparse vector assignment";

      initialize();

      SVT subvector = sub( vec_, 3UL, 4UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 4UL );
      vec[3] = 9;

      subvector = vec;

      checkSize    ( subvector, 4UL );
      checkNonZeros( subvector, 1UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 2UL );

      if( subvector != vec ||
          subvector[0] != 0 || subvector[1] != 0 || subvector[2] != 0 || subvector[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 0 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] != 0 || vec_[1] != 1 || vec_[2] != 0 || vec_[3] != 0 ||
          vec_[4] != 0 || vec_[5] != 0 || vec_[6] != 9 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 1 0 0 0 0 9 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubvector addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the SparseSubvector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAddAssign()
{
   //=====================================================================================
   // SparseSubvector addition assignment
   //=====================================================================================

   {
      test_ = "SparseSubvector addition assignment (no aliasing)";

      initialize();

      VT vec( 10UL );
      vec[5] =  6;
      vec[6] = -8;

      SVT subvector = sub( vec, 5UL, 3UL );
      subvector += sub( vec_, 4UL, 3UL );

      checkSize    ( subvector,  3UL );
      checkNonZeros( subvector,  3UL );
      checkSize    ( vec_     ,  8UL );
      checkNonZeros( vec_     ,  4UL );
      checkSize    ( vec      , 10UL );
      checkNonZeros( vec      ,  3UL );

      if( subvector[0] != 3 || subvector[1] != -8 || subvector[2] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 3 -8 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec[0] != 0 || vec[1] !=  0 || vec[2] != 0 || vec[3] != 0 || vec[4] != 0 ||
          vec[5] != 3 || vec[6] != -8 || vec[7] != 4 || vec[8] != 0 || vec[9] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 0 0 0 0 3 -8 4 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "SparseSubvector addition assignment (aliasing)";

      initialize();

      SVT subvector = sub( vec_, 1UL, 3UL );
      subvector += sub( vec_, 3UL, 3UL );

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 5UL );

      if( subvector[0] != -1 || subvector[1] != -3 || subvector[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( -1 -3 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != -1 || vec_[2] != -3 || vec_[3] != -2 ||
          vec_[4] != -3 || vec_[5] !=  0 || vec_[6] !=  4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 -1 -3 -2 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Dense vector addition assignment
   //=====================================================================================

   {
      test_ = "Dense vector addition assignment";

      initialize();

      SVT subvector( vec_, 1UL, 3UL );

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[0] =  2;
      vec[1] = -4;

      subvector += vec;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 5UL );

      if( subvector[0] != 3 || subvector[1] != -4 || subvector[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 3 -4 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 3 || vec_[2] != -4 || vec_[3] != -2 ||
          vec_[4] != -3 || vec_[5] != 0 || vec_[6] !=  4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 3 -4 -2 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Sparse vector addition assignment
   //=====================================================================================

   {
      test_ = "Sparse vector addition assignment";

      initialize();

      SVT subvector( vec_, 1UL, 3UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL );
      vec[0] =  2;
      vec[1] = -4;

      subvector += vec;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 5UL );

      if( subvector[0] != 3 || subvector[1] != -4 || subvector[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 3 -4 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 3 || vec_[2] != -4 || vec_[3] != -2 ||
          vec_[4] != -3 || vec_[5] != 0 || vec_[6] !=  4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 3 -4 -2 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubvector subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the SparseSubvector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testSubAssign()
{
   //=====================================================================================
   // SparseSubvector subtraction assignment
   //=====================================================================================

   {
      test_ = "SparseSubvector subtraction assignment (no aliasing)";

      initialize();

      VT vec( 10UL );
      vec[5] =  6;
      vec[6] = -8;

      SVT subvector = sub( vec, 5UL, 3UL );
      subvector -= sub( vec_, 4UL, 3UL );

      checkSize    ( subvector,  3UL );
      checkNonZeros( subvector,  3UL );
      checkSize    ( vec_     ,  8UL );
      checkNonZeros( vec_     ,  4UL );
      checkSize    ( vec      , 10UL );
      checkNonZeros( vec      ,  3UL );

      if( subvector[0] != 9 || subvector[1] != -8 || subvector[2] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 9 -8 -4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec[0] != 0 || vec[1] !=  0 || vec[2] !=  0 || vec[3] != 0 || vec[4] != 0 ||
          vec[5] != 9 || vec[6] != -8 || vec[7] != -4 || vec[8] != 0 || vec[9] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 0 0 0 0 9 -8 -4 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "SparseSubvector subtraction assignment (aliasing)";

      initialize();

      SVT subvector = sub( vec_, 1UL, 3UL );
      subvector -= sub( vec_, 3UL, 3UL );

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 5UL );

      if( subvector[0] != 3 || subvector[1] != 3 || subvector[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 3 3 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 3 || vec_[2] != 3 || vec_[3] != -2 ||
          vec_[4] != -3 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 3 3 -2 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Dense vector subtraction assignment
   //=====================================================================================

   {
      test_ = "Dense vector subtraction assignment";

      initialize();

      SVT subvector( vec_, 1UL, 3UL );

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[0] =  2;
      vec[1] = -4;

      subvector -= vec;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 5UL );

      if( subvector[0] != -1 || subvector[1] != 4 || subvector[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( -1 4 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != -1 || vec_[2] != 4 || vec_[3] != -2 ||
          vec_[4] != -3 || vec_[5] !=  0 || vec_[6] != 4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 -1 4 -2 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Sparse vector subtraction assignment
   //=====================================================================================

   {
      test_ = "Sparse vector subtraction assignment";

      initialize();

      SVT subvector( vec_, 1UL, 3UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL );
      vec[0] =  2;
      vec[1] = -4;

      subvector -= vec;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 5UL );

      if( subvector[0] != -1 || subvector[1] != 4 || subvector[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( -1 4 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != -1 || vec_[2] != 4 || vec_[3] != -2 ||
          vec_[4] != -3 || vec_[5] !=  0 || vec_[6] != 4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 -1 4 -2 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubvector multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the SparseSubvector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testMultAssign()
{
   //=====================================================================================
   // SparseSubvector multiplication assignment
   //=====================================================================================

   {
      test_ = "SparseSubvector multiplication assignment (no aliasing)";

      initialize();

      VT vec( 10UL );
      vec[5] =  6;
      vec[6] = -8;

      SVT subvector = sub( vec, 5UL, 3UL );
      subvector *= sub( vec_, 4UL, 3UL );

      checkSize    ( subvector,  3UL );
      checkNonZeros( subvector,  1UL );
      checkSize    ( vec_     ,  8UL );
      checkNonZeros( vec_     ,  4UL );
      checkSize    ( vec      , 10UL );
      checkNonZeros( vec      ,  1UL );

      if( subvector[0] != -18 || subvector[1] != 0 || subvector[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( -18 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec[0] !=   0 || vec[1] != 0 || vec[2] != 0 || vec[3] != 0 || vec[4] != 0 ||
          vec[5] != -18 || vec[6] != 0 || vec[7] != 0 || vec[8] != 0 || vec[9] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 0 0 0 0 -18 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "SparseSubvector multiplication assignment (aliasing)";

      initialize();

      SVT subvector = sub( vec_, 1UL, 3UL );
      subvector *= sub( vec_, 3UL, 3UL );

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 1UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 3UL );

      if( subvector[0] != -2 || subvector[1] != 0 || subvector[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( -2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != -2 || vec_[2] != 0 || vec_[3] != 0 ||
          vec_[4] != -3 || vec_[5] !=  0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 -2 0 0 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Dense vector multiplication assignment
   //=====================================================================================

   {
      test_ = "Dense vector multiplication assignment";

      initialize();

      SVT subvector( vec_, 1UL, 3UL );

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[0] =  2;
      vec[1] = -4;

      subvector *= vec;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 2UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 4UL );

      if( subvector[0] != 2 || subvector[1] != 0 || subvector[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 2 || vec_[2] != 0 || vec_[3] != 0 ||
          vec_[4] != -3 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 2 0 0 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Sparse vector multiplication assignment
   //=====================================================================================

   {
      test_ = "Sparse vector multiplication assignment";

      initialize();

      SVT subvector( vec_, 1UL, 3UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[0] =  2;
      vec[1] = -4;

      subvector *= vec;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 1UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 3UL );

      if( subvector[0] != 2 || subvector[1] != 0 || subvector[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 2 || vec_[2] != 0 || vec_[3] != 0 ||
          vec_[4] != -3 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 2 0 0 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Scalar multiplication assignment
   //=====================================================================================

   {
      test_ = "Scalar multiplication assignment";

      initialize();

      SVT subvector = sub( vec_, 1UL, 3UL );

      subvector *= 3;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 2UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 4UL );

      if( subvector[0] != 3 || subvector[1] != 0 || subvector[2] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 3 0 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 3 || vec_[2] != 0 || vec_[3] != -6 ||
          vec_[4] != -3 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 3 0 -6 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubvector division assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the division assignment operators of the SparseSubvector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testDivAssign()
{
   //=====================================================================================
   // Scalar division assignment
   //=====================================================================================

   {
      test_ = "Scalar division assignment";

      initialize();

      SVT subvector = sub( vec_, 1UL, 3UL );

      subvector /= 0.5;

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 2UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 4UL );

      if( subvector[0] != 2 || subvector[1] != 0 || subvector[2] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Division assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 2 0 -4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 2 || vec_[2] != 0 || vec_[3] != -4 ||
          vec_[4] != -3 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Division assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 2 0 -4 -3 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubvector subscript operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the subscript operator
// of the SparseSubvector class template. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void ClassTest::testSubscript()
{
   test_ = "SparseSubvector::operator[]";

   initialize();

   SVT subvector = sub( vec_, 1UL, 4UL );

   // Writing the first element
   subvector[1] = 9;

   checkSize    ( subvector, 4UL );
   checkNonZeros( subvector, 4UL );
   checkSize    ( vec_     , 8UL );
   checkNonZeros( vec_     , 5UL );

   if( subvector[0] != 1 || subvector[1] != 9 || subvector[2] != -2 || subvector[3] != -3 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 1 9 -2 -3 )\n";
      throw std::runtime_error( oss.str() );
   }

   if( vec_[0] !=  0 || vec_[1] != 1 || vec_[2] != 9 || vec_[3] != -2 ||
       vec_[4] != -3 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] !=  0 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << vec_ << "\n"
          << "   Expected result:\n( 0 1 9 -2 -3 0 4 0 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Writing the second element
   subvector[2] = 0;

   checkSize    ( subvector, 4UL );
   checkNonZeros( subvector, 3UL );
   checkSize    ( vec_     , 8UL );
   checkNonZeros( vec_     , 4UL );

   if( subvector[0] != 1 || subvector[1] != 9 || subvector[2] != 0 || subvector[3] != -3 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 1 9 0 0 )\n";
      throw std::runtime_error( oss.str() );
   }

   if( vec_[0] !=  0 || vec_[1] != 1 || vec_[2] != 9 || vec_[3] != 0 ||
       vec_[4] != -3 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << vec_ << "\n"
          << "   Expected result:\n( 0 1 9 0 -3 0 4 0 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Writing the third element
   subvector[3] = -8;

   checkSize    ( subvector, 4UL );
   checkNonZeros( subvector, 3UL );
   checkSize    ( vec_     , 8UL );
   checkNonZeros( vec_     , 4UL );

   if( subvector[0] != 1 || subvector[1] != 9 || subvector[2] != 0 || subvector[3] != -8 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( -2 9 0 -8 )\n";
      throw std::runtime_error( oss.str() );
   }

   if( vec_[0] !=  0 || vec_[1] != 1 || vec_[2] != 9 || vec_[3] != 0 ||
       vec_[4] != -8 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << vec_ << "\n"
          << "   Expected result:\n( 0 1 9 0 -8 0 4 0 )\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubvector iterator implementation.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the iterator implementation of the SparseSubvector class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIterator()
{
   initialize();

   // Counting the number of elements in first half of the vector
   {
      test_ = "Iterator subtraction";

      SVT subvector = sub( vec_, 0UL, 4UL );
      const size_t number( subvector.end() - subvector.begin() );

      if( number != 2UL ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid number of elements detected\n"
             << " Details:\n"
             << "   Number of elements         : " << number << "\n"
             << "   Expected number of elements: 2\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Counting the number of elements in second half of the vector
   {
      test_ = "Iterator subtraction";

      SVT subvector = sub( vec_, 4UL, 4UL );
      const size_t number( subvector.end() - subvector.begin() );

      if( number != 2UL ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid number of elements detected\n"
             << " Details:\n"
             << "   Number of elements         : " << number << "\n"
             << "   Expected number of elements: 2\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Testing read-only access via ConstIterator
   {
      test_ = "Read-only access via ConstIterator";

      SVT subvector = sub( vec_, 1UL, 5UL );
      SVT::ConstIterator it( subvector.cbegin() );

      if( it->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Unexpected iterator behavior\n"
             << " Details:\n"
             << "   Current value : " << it->value() << "\n"
             << "   Expected value: 1\n";
         throw std::runtime_error( oss.str() );
      }

      ++it;

      if( it->value() != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Unexpected iterator behavior\n"
             << " Details:\n"
             << "   Current value : " << it->value() << "\n"
             << "   Expected value: -2\n";
         throw std::runtime_error( oss.str() );
      }

      ++it;

      if( it->value() != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Unexpected iterator behavior\n"
             << " Details:\n"
             << "   Current value : " << it->value() << "\n"
             << "   Expected value: -3\n";
         throw std::runtime_error( oss.str() );
      }

      ++it;

      if( it != subvector.cend() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid iterator end\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Testing assignment via Iterator
   {
      test_ = "Assignment via Iterator";

      SVT subvector = sub( vec_, 2UL, 4UL );
      int value = 6;

      for( SVT::Iterator it=subvector.begin(); it!=subvector.end(); ++it ) {
         *it = value++;
      }

      if( subvector[0] != 0 || subvector[1] != 6 || subvector[2] != 7 || subvector[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 6 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] != 0 || vec_[1] != 1 || vec_[2] != 0 || vec_[3] != 6 ||
          vec_[4] != 7 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 1 0 6 7 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Testing addition assignment via Iterator
   {
      test_ = "Addition assignment via Iterator";

      SVT subvector = sub( vec_, 2UL, 4UL );
      int value = 2;

      for( SVT::Iterator it=subvector.begin(); it!=subvector.end(); ++it ) {
         *it += value++;
      }

      if( subvector[0] != 0 || subvector[1] != 8 || subvector[2] != 10 || subvector[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 8 10 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 1 || vec_[2] != 0 || vec_[3] != 8 ||
          vec_[4] != 10 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 1 0 8 10 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Testing subtraction assignment via Iterator
   {
      test_ = "Subtraction assignment via Iterator";

      SVT subvector = sub( vec_, 2UL, 4UL );
      int value = 2;

      for( SVT::Iterator it=subvector.begin(); it!=subvector.end(); ++it ) {
         *it -= value++;
      }

      if( subvector[0] != 0 || subvector[1] != 6 || subvector[2] != 7 || subvector[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 8 10 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] != 0 || vec_[1] != 1 || vec_[2] != 0 || vec_[3] != 6 ||
          vec_[4] != 7 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 1 0 6 7 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Testing multiplication assignment via Iterator
   {
      test_ = "Multiplication assignment via Iterator";

      SVT subvector = sub( vec_, 2UL, 4UL );
      int value = 1;

      for( SVT::Iterator it=subvector.begin(); it!=subvector.end(); ++it ) {
         *it *= value++;
      }

      if( subvector[0] != 0 || subvector[1] != 6 || subvector[2] != 14 || subvector[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 8 10 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 1 || vec_[2] != 0 || vec_[3] != 6 ||
          vec_[4] != 14 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 1 0 6 14 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Testing division assignment via Iterator
   {
      test_ = "Division assignment via Iterator";

      SVT subvector = sub( vec_, 2UL, 4UL );

      for( SVT::Iterator it=subvector.begin(); it!=subvector.end(); ++it ) {
         *it /= 2;
      }

      if( subvector[0] != 0 || subvector[1] != 3 || subvector[2] != 7 || subvector[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 8 10 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] != 0 || vec_[1] != 1 || vec_[2] != 0 || vec_[3] != 3 ||
          vec_[4] != 7 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment via iterator failed\n"
             << " Details:\n"
             << "   Result:\n" << vec_ << "\n"
             << "   Expected result:\n( 0 1 0 3 7 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the nonZeros member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the nonZeros member function of SparseSubvector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testNonZeros()
{
   test_ = "SparseSubvector::nonZeros()";

   initialize();

   // Initialization check
   SVT subvector = sub( vec_, 0UL, 4UL );

   checkSize    ( subvector, 4UL );
   checkNonZeros( subvector, 2UL );
   checkSize    ( vec_     , 8UL );
   checkNonZeros( vec_     , 4UL );

   if( subvector[0] != 0 || subvector[1] != 1 || subvector[2] != 0 || subvector[3] != -2 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Initialization failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 0 1 0 -2 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Changing the number of non-zeros via the sparse subvector
   subvector[3] = 0;

   checkSize    ( subvector, 4UL );
   checkNonZeros( subvector, 1UL );
   checkSize    ( vec_     , 8UL );
   checkNonZeros( vec_     , 3UL );

   if( subvector[0] != 0 || subvector[1] != 1 || subvector[2] != 0 || subvector[3] != 0 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 0 1 0 0 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Changing the number of non-zeros via the sparse vector
   vec_[2UL] = 5;

   checkSize    ( subvector, 4UL );
   checkNonZeros( subvector, 2UL );
   checkSize    ( vec_     , 8UL );
   checkNonZeros( vec_     , 4UL );

   if( subvector[0] != 0 || subvector[1] != 1 || subvector[2] != 5 || subvector[3] != 0 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Function call operator failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 0 1 5 0 )\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the reset member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the reset member function of SparseSubvector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testReset()
{
   test_ = "SparseSubvector::reset()";

   initialize();

   // Resetting the range [0,3]
   {
      SVT subvector = sub( vec_, 0UL, 4UL );
      subvector.reset();

      checkSize    ( subvector, 4UL );
      checkNonZeros( subvector, 0UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 2UL );

      if( subvector[0] != 0 || subvector[1] != 0 || subvector[2] != 0 || subvector[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation of range [0,3] failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Resetting the range [4,7]
   {
      SVT subvector = sub( vec_, 4UL, 4UL );
      subvector.reset();

      checkSize    ( subvector, 4UL );
      checkNonZeros( subvector, 0UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 0UL );

      if( subvector[0] != 0 || subvector[1] != 0 || subvector[2] != 0 || subvector[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation of range [4,7] failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the append member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the append member function of SparseSubvector. In case
// an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAppend()
{
   test_ = "SparseSubvector::append()";

   VT vec( 10UL );

   SVT subvector = sub( vec, 2UL, 4UL );
   subvector.reserve( 4UL );

   // Appending one non-zero element
   subvector.append( 0UL, 1 );

   checkSize    ( subvector, 4UL );
   checkCapacity( subvector, 4UL );
   checkNonZeros( subvector, 1UL );
   checkNonZeros( vec      , 1UL );

   if( subvector[0] != 1 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Initialization failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 0 0 1 0 0 0 0 0 0 0 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Appending three more non-zero elements
   subvector.append( 1UL, 2 );
   subvector.append( 2UL, 3 );
   subvector.append( 3UL, 4 );

   checkSize    ( subvector, 4UL );
   checkCapacity( subvector, 4UL );
   checkNonZeros( subvector, 4UL );
   checkNonZeros( vec      , 4UL );

   if( subvector[0] != 1 || subvector[1] != 2 || subvector[2] != 3 || subvector[3] != 4 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Append operation failed\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 0 0 1 2 3 4 0 0 0 )\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the insert member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the insert member function of SparseSubvector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testInsert()
{
   test_ = "SparseSubvector::insert()";

   initialize();

   SVT subvector = sub( vec_, 0UL, 8UL );

   // Inserting a non-zero element at the end of the subvector
   {
      SVT::Iterator pos = subvector.insert( 7UL, 9 );

      checkSize    ( subvector, 8UL );
      checkNonZeros( subvector, 5UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 5UL );

      if( pos->value() != 9 || pos->index() != 7UL ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid iterator returned\n"
             << " Details:\n"
             << "   Value: " << pos->value() << "\n"
             << "   Index: " << pos->index() << "\n"
             << "   Expected value: 9\n"
             << "   Expected index: 7\n";
         throw std::runtime_error( oss.str() );
      }

      if( subvector[0] !=  0 || subvector[1] != 1 || subvector[2] != 0 || subvector[3] != -2 ||
          subvector[4] != -3 || subvector[5] != 0 || subvector[6] != 4 || subvector[7] !=  9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 2 0 -2 -3 0 4 9 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Inserting a non-zero element at the beginning of the subvector
   {
      SVT::Iterator pos = subvector.insert( 0UL, 9 );

      checkSize    ( subvector, 8UL );
      checkNonZeros( subvector, 6UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 6UL );

      if( pos->value() != 9 || pos->index() != 0UL ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid iterator returned\n"
             << " Details:\n"
             << "   Value: " << pos->value() << "\n"
             << "   Index: " << pos->index() << "\n"
             << "   Expected value: 9\n"
             << "   Expected index: 0\n";
         throw std::runtime_error( oss.str() );
      }

      if( subvector[0] !=  9 || subvector[1] != 1 || subvector[2] != 0 || subvector[3] != -2 ||
          subvector[4] != -3 || subvector[5] != 0 || subvector[6] != 4 || subvector[7] !=  9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 9 2 0 -2 -3 0 4 9 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Inserting a non-zero element at the center of the subvector
   {
      SVT::Iterator pos = subvector.insert( 2UL, 9 );

      checkSize    ( subvector, 8UL );
      checkNonZeros( subvector, 7UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 7UL );

      if( pos->value() != 9 || pos->index() != 2UL ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid iterator returned\n"
             << " Details:\n"
             << "   Value: " << pos->value() << "\n"
             << "   Index: " << pos->index() << "\n"
             << "   Expected value: 9\n"
             << "   Expected index: 2\n";
         throw std::runtime_error( oss.str() );
      }

      if( subvector[0] !=  9 || subvector[1] != 1 || subvector[2] != 9 || subvector[3] != -2 ||
          subvector[4] != -3 || subvector[5] != 0 || subvector[6] != 4 || subvector[7] !=  9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 9 2 9 -2 -3 0 4 9 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Trying to insert an already existing element
   try {
      subvector.insert( 3UL, 9 );

      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Inserting an existing element succeeded\n"
          << " Details:\n"
          << "   Result:\n" << subvector << "\n"
          << "   Expected result:\n( 9 2 0 9 -3 0 4 9 )\n";
      throw std::runtime_error( oss.str() );
   }
   catch( std::invalid_argument& ) {}
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the erase member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the erase member function of SparseSubvector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testErase()
{
   //=====================================================================================
   // Index-based erase function
   //=====================================================================================

   {
      test_ = "SparseSubvector::erase( size_t )";

      initialize();

      SVT subvector = sub( vec_, 1UL, 6UL );

      // Erasing the non-zero element at the end of the subvector
      subvector.erase( 5UL );

      checkSize    ( subvector, 6UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 3UL );

      if( subvector[0] !=  1 || subvector[1] != 0 || subvector[2] != -2 ||
          subvector[3] != -3 || subvector[4] != 0 || subvector[5] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 1 0 -2 -3 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the non-zero element at the beginning of the subvector
      subvector.erase( 0UL );

      checkSize    ( subvector, 6UL );
      checkNonZeros( subvector, 2UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 2UL );

      if( subvector[0] !=  0 || subvector[1] != 0 || subvector[2] != -2 ||
          subvector[3] != -3 || subvector[4] != 0 || subvector[5] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 0 -2 -3 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the non-zero element at the beginning of the subvector
      subvector.erase( 2UL );

      checkSize    ( subvector, 6UL );
      checkNonZeros( subvector, 1UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 1UL );

      if( subvector[0] !=  0 || subvector[1] != 0 || subvector[2] != 0 ||
          subvector[3] != -3 || subvector[4] != 0 || subvector[5] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 0 0 -3 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to erase an already erased element
      subvector.erase( 2UL );

      checkSize    ( subvector, 6UL );
      checkNonZeros( subvector, 1UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 1UL );

      if( subvector[0] !=  0 || subvector[1] != 0 || subvector[2] != 0 ||
          subvector[3] != -3 || subvector[4] != 0 || subvector[5] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 0 0 -3 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Iterator-based erase function
   //=====================================================================================

   {
      test_ = "SparseSubvector::erase( Iterator )";

      initialize();

      SVT subvector = sub( vec_, 1UL, 6UL );

      // Erasing the non-zero element at the end of the subvector
      {
         SVT::Iterator pos = subvector.erase( subvector.find( 5UL ) );

         checkSize    ( subvector, 6UL );
         checkNonZeros( subvector, 3UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 3UL );

         if( pos != subvector.end() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] !=  1 || subvector[1] != 0 || subvector[2] != -2 ||
             subvector[3] != -3 || subvector[4] != 0 || subvector[5] !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 1 0 -2 -3 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the non-zero element at the beginning of the subvector
      {
         SVT::Iterator pos = subvector.erase( subvector.find( 0UL ) );

         checkSize    ( subvector, 6UL );
         checkNonZeros( subvector, 2UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 2UL );

         if( pos->value() != -2 || pos->index() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: -2\n"
                << "   Expected index:  2\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] !=  0 || subvector[1] != 0 || subvector[2] != -2 ||
             subvector[3] != -3 || subvector[4] != 0 || subvector[5] !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 0 0 -2 -3 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the non-zero element at the beginning of the subvector
      {
         SVT::Iterator pos = subvector.erase( subvector.find( 2UL ) );

         checkSize    ( subvector, 6UL );
         checkNonZeros( subvector, 1UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 1UL );

         if( pos->value() != -3 || pos->index() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: -3\n"
                << "   Expected index:  3\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] !=  0 || subvector[1] != 0 || subvector[2] != 0 ||
             subvector[3] != -3 || subvector[4] != 0 || subvector[5] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 0 0 0 -3 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an already erased element
      {
         SVT::Iterator pos = subvector.erase( subvector.find( 2UL ) );

         checkSize    ( subvector, 6UL );
         checkNonZeros( subvector, 1UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 1UL );

         if( pos != subvector.end() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] !=  0 || subvector[1] != 0 || subvector[2] != 0 ||
             subvector[3] != -3 || subvector[4] != 0 || subvector[5] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 0 0 0 -3 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Iterator-range-based erase function
   //=====================================================================================

   {
      test_ = "SparseSubvector::erase( Iterator, Iterator )";

      // Erasing the entire vector
      {
         initialize();

         SVT subvector = sub( vec_, 0UL, 8UL );

         SVT::Iterator pos = subvector.erase( subvector.begin(), subvector.end() );

         checkSize    ( subvector, 8UL );
         checkNonZeros( subvector, 0UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 0UL );

         if( pos != subvector.end() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] != 0 || subvector[1] != 0 || subvector[2] != 0 || subvector[3] != 0 ||
             subvector[4] != 0 || subvector[5] != 0 || subvector[6] != 0 || subvector[7] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the subvector failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 0 0 0 0 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the first half of the vector
      {
         initialize();

         SVT subvector = sub( vec_, 0UL, 8UL );

         SVT::Iterator pos = subvector.erase( subvector.begin(), subvector.find( 4UL ) );

         checkSize    ( subvector, 8UL );
         checkNonZeros( subvector, 2UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 2UL );

         if( pos->value() != -3 || pos->index() != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: -3\n"
                << "   Expected index:  4\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] !=  0 || subvector[1] != 0 || subvector[2] != 0 || subvector[3] != 0 ||
             subvector[4] != -3 || subvector[5] != 0 || subvector[6] != 4 || subvector[7] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a partial subvector failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 0 0 0 0 -3 0 4 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the second half of the vector
      {
         initialize();

         SVT subvector = sub( vec_, 0UL, 8UL );

         SVT::Iterator pos = subvector.erase( subvector.find( 4UL ), subvector.end() );

         checkSize    ( subvector, 8UL );
         checkNonZeros( subvector, 2UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 2UL );

         if( pos != subvector.end() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] != 0 || subvector[1] != 1 || subvector[2] != 0 || subvector[3] != -2 ||
             subvector[4] != 0 || subvector[5] != 0 || subvector[6] != 0 || subvector[7] !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a partial subvector failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 0 1 0 -2 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an empty range
      {
         initialize();

         SVT subvector = sub( vec_, 0UL, 8UL );

         SVT::Iterator pos = subvector.erase( subvector.find( 1UL ), subvector.find( 1UL ) );

         checkSize    ( subvector, 8UL );
         checkNonZeros( subvector, 4UL );
         checkSize    ( vec_     , 8UL );
         checkNonZeros( vec_     , 4UL );

         if( pos != subvector.find( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( subvector[0] !=  0 || subvector[1] != 1 || subvector[2] != 0 || subvector[3] != -2 ||
             subvector[4] != -3 || subvector[5] != 0 || subvector[6] != 4 || subvector[7] !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing an empty range failed\n"
                << " Details:\n"
                << "   Result:\n" << subvector << "\n"
                << "   Expected result:\n( 0 1 0 -2 -3 0 4 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the scale member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the scale member function of SparseSubvector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testScale()
{
   test_ = "SparseSubvector::scale()";

   initialize();

   // Scaling the subvector in the range [1,4]
   {
      SVT subvector = sub( vec_, 1UL, 4UL );
      subvector.scale( 3 );

      checkSize    ( subvector, 4UL );
      checkNonZeros( subvector, 3UL );
      checkSize    ( vec_     , 8UL );
      checkNonZeros( vec_     , 4UL );

      if( subvector[0] != 3 || subvector[1] != 0 || subvector[2] != -6 || subvector[3] != -9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation of range [1,4] failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 3 0 -6 -9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( vec_[0] !=  0 || vec_[1] != 3 || vec_[2] != 0 || vec_[3] != -6 ||
          vec_[4] != -9 || vec_[5] != 0 || vec_[6] != 4 || vec_[7] !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation of range [1,4] failed\n"
             << " Details:\n"
             << "   Result:\n" << subvector << "\n"
             << "   Expected result:\n( 0 3 0 -6 -9 0 4 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the find member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the find member function of SparseSubvector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testFind()
{
   test_ = "SparseSubvector::find()";

   initialize();

   SVT subvector = sub( vec_, 1UL, 5UL );

   // Searching for the first element
   {
      SVT::Iterator pos = subvector.find( 0UL );

      if( pos == subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Element could not be found\n"
             << " Details:\n"
             << "   Required index = 0\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
      else if( pos->index() != 0 || pos->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Wrong element found\n"
             << " Details:\n"
             << "   Required index = 0\n"
             << "   Found index    = " << pos->index() << "\n"
             << "   Expected value = 1\n"
             << "   Value at index = " << pos->value() << "\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Searching for the second element
   {
      SVT::Iterator pos = subvector.find( 2UL );

      if( pos == subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Element could not be found\n"
             << " Details:\n"
             << "   Required index = 2\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
      else if( pos->index() != 2 || pos->value() != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Wrong element found\n"
             << " Details:\n"
             << "   Required index = 2\n"
             << "   Found index    = " << pos->index() << "\n"
             << "   Expected value = -2\n"
             << "   Value at index = " << pos->value() << "\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Searching for a non-existing non-zero element
   {
      SVT::Iterator pos = subvector.find( 1UL );

      if( pos != subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Non-existing element could be found\n"
             << " Details:\n"
             << "   Required index = 1\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the lowerBound member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the lowerBound member function of SparseSubvector. In case
// an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testLowerBound()
{
   test_ = "SparseSubvector::lowerBound()";

   initialize();

   SVT subvector = sub( vec_, 0UL, 3UL );

   // Determining the lower bound for index 0
   {
      SVT::Iterator pos = subvector.lowerBound( 0UL );

      if( pos == subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Lower bound could not be determined\n"
             << " Details:\n"
             << "   Required index = 0\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
      else if( pos->index() != 1 || pos->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Wrong element found\n"
             << " Details:\n"
             << "   Required index = 1\n"
             << "   Found index    = " << pos->index() << "\n"
             << "   Expected value = 1\n"
             << "   Value at index = " << pos->value() << "\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Determining the lower bound for index 1
   {
      SVT::Iterator pos = subvector.lowerBound( 1UL );

      if( pos == subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Lower bound could not be determined\n"
             << " Details:\n"
             << "   Required index = 1\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
      else if( pos->index() != 1 || pos->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Wrong element found\n"
             << " Details:\n"
             << "   Required index = 1\n"
             << "   Found index    = " << pos->index() << "\n"
             << "   Expected value = 1\n"
             << "   Value at index = " << pos->value() << "\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Determining the lower bound for index 2
   {
      SVT::Iterator pos = subvector.lowerBound( 2UL );

      if( pos != subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Lower bound could not be determined\n"
             << " Details:\n"
             << "   Required index = 2\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the upperBound member function of SparseSubvector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the upperBound member function of SparseSubvector. In case
// an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testUpperBound()
{
   test_ = "SparseSubvector::upperBound()";

   initialize();

   SVT subvector = sub( vec_, 0UL, 3UL );

   // Determining the upper bound for index 0
   {
      SVT::Iterator pos = subvector.upperBound( 0UL );

      if( pos == subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Upper bound could not be determined\n"
             << " Details:\n"
             << "   Required index = 0\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
      else if( pos->index() != 1 || pos->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Wrong element found\n"
             << " Details:\n"
             << "   Required index = 1\n"
             << "   Found index    = " << pos->index() << "\n"
             << "   Expected value = 1\n"
             << "   Value at index = " << pos->value() << "\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Determining the upper bound for index 1
   {
      SVT::Iterator pos = subvector.upperBound( 1UL );

      if( pos != subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Upper bound could not be determined\n"
             << " Details:\n"
             << "   Required index = 1\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Determining the upper bound for index 2
   {
      SVT::Iterator pos = subvector.upperBound( 2UL );

      if( pos != subvector.end() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Upper bound could not be determined\n"
             << " Details:\n"
             << "   Required index = 2\n"
             << "   Current subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the isDefault function with the SparseSubvector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the isDefault function with the SparseSubvector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIsDefault()
{
   test_ = "isDefault() function";

   initialize();

   // isDefault with default vector
   {
      VT vec( 8UL );
      SVT subvector( vec, 2UL, 5UL );

      if( isDefault( subvector ) != true ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isDefault evaluation\n"
             << " Details:\n"
             << "   Subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // isDefault with non-default vector
   {
      SVT subvector( vec_, 2UL, 5UL );

      if( isDefault( subvector ) != false ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isDefault evaluation\n"
             << " Details:\n"
             << "   Subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the isnan function with the SparseSubvector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the isnan function with the SparseSubvector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIsNan()
{
   test_ = "isnan() function";

   typedef blaze::CompressedVector<float,blaze::columnVector>  VectorType;
   typedef blaze::SparseSubvector<VectorType>                  SubvectorType;

   VectorType vec( 9UL, 4UL );
   vec[2] =  1;
   vec[3] = -2;
   vec[4] = -3;
   vec[8] =  4;

   // isnan with empty 3-dimensional subvector
   {
      SubvectorType subvector = sub( vec, 5UL, 3UL );

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 0UL );

      if( isnan( subvector ) != false ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isnan evaluation\n"
             << " Details:\n"
             << "   Subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // isnan with partially filled 5-dimensional subvector
   {
      SubvectorType subvector = sub( vec, 4UL, 5UL );

      checkSize    ( subvector, 5UL );
      checkNonZeros( subvector, 2UL );

      if( isnan( subvector ) != false ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isnan evaluation\n"
             << " Details:\n"
             << "   Subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // isnan with fully filled 5-dimensional subvector
   {
      SubvectorType subvector = sub( vec, 2UL, 3UL );

      checkSize    ( subvector, 3UL );
      checkNonZeros( subvector, 3UL );

      if( isnan( subvector ) != false ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isnan evaluation\n"
             << " Details:\n"
             << "   Subvector:\n" << subvector << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the min function with the SparseSubvector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the min function used with the SparseSubvector class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testMinimum()
{
   test_ = "min() function";

   initialize();

   // Computing the minimum of the in the range [0,2]
   {
      const int minimum = min( sub( vec_, 0UL, 3UL ) );

      if( minimum != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Minimum computation for range [0,2] failed\n"
             << " Details:\n"
             << "   Result: " << minimum << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Computing the minimum of the in the range [2,4]
   {
      const int minimum = min( sub( vec_, 2UL, 3UL ) );

      if( minimum != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Minimum computation for range [2,4] failed\n"
             << " Details:\n"
             << "   Result: " << minimum << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Computing the minimum of the in the range [4,6]
   {
      const int minimum = min( sub( vec_, 4UL, 3UL ) );

      if( minimum != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Minimum computation for range [4,6] failed\n"
             << " Details:\n"
             << "   Result: " << minimum << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Computing the minimum of the in the range [6,7]
   {
      const int minimum = min( sub( vec_, 6UL, 2UL ) );

      if( minimum != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Minimum computation for range [6,7] failed\n"
             << " Details:\n"
             << "   Result: " << minimum << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the max function with the SparseSubvector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the max function used with the SparseSubvector class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testMaximum()
{
   test_ = "max() function";

   initialize();

   // Computing the maximum of the in the range [0,2]
   {
      const int maximum = max( sub( vec_, 0UL, 3UL ) );

      if( maximum != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Maximum computation for range [0,2] failed\n"
             << " Details:\n"
             << "   Result: " << maximum << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Computing the maximum of the in the range [2,4]
   {
      const int maximum = max( sub( vec_, 2UL, 3UL ) );

      if( maximum != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Maximum computation for range [2,4] failed\n"
             << " Details:\n"
             << "   Result: " << maximum << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Computing the maximum of the in the range [4,6]
   {
      const int maximum = max( sub( vec_, 4UL, 3UL ) );

      if( maximum != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Maximum computation for range [4,6] failed\n"
             << " Details:\n"
             << "   Result: " << maximum << "\n"
             << "   Expected result: 4\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Computing the maximum of the in the range [6,7]
   {
      const int maximum = max( sub( vec_, 6UL, 2UL ) );

      if( maximum != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Maximum computation for range [6,7] failed\n"
             << " Details:\n"
             << "   Result: " << maximum << "\n"
             << "   Expected result: 4\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Initialization of all member vectors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function initializes all member vectors to specific predetermined values.
*/
void ClassTest::initialize()
{
   // Initializing the compressed row vector
   vec_.reset();
   vec_[1] =  1;
   vec_[3] = -2;
   vec_[4] = -3;
   vec_[6] =  4;
}
//*************************************************************************************************

} // namespace sparsesubvector

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running SparseSubvector class test..." << std::endl;

   try
   {
      RUN_SPARSESUBVECTOR_CLASS_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during SparseSubvector class test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
