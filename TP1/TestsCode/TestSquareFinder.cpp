#include "stdafx.h"
#include "CppUnitTest.h"
#include "SquareFinder.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestsCode
{
	TEST_CLASS(SquareFinderTests)
	{
	public:

		TEST_METHOD(addDot_DotsArrayWithManyDots_OneMoreDotInDotsArray)
		{
			SquareFinder squareFinder;
			for (int i = 0; i < 5; i++)
			{
				Dot aDot(i, i + 1);
				squareFinder.addDot(aDot);
			}

			Dot aDot(1, 2);

			squareFinder.addDot(aDot);

			Assert::AreEqual(6u, squareFinder.getNbDots());
		}

		TEST_METHOD(loadDotsFromMemory_4Dots_4DotsArray)
		{
			std::stringstream content("(53,-115);(134, -115);(53, -34);(134, -34);");
			SquareFinder squareFinder;

			squareFinder.loadDotsFromMemory(content);

			Assert::AreEqual(4u, squareFinder.getNbDots());
		}

		TEST_METHOD(findSquaresBruteForce_4DotsArrayOneSquare_OneSquareFound)
		{
			std::stringstream content("(53,-115);(134, -115);(53, -34);(134, -34);");
			SquareFinder squareFinder;

			squareFinder.loadDotsFromMemory(content);

			squareFinder.findSquaresBruteForce();

			Assert::AreEqual(1u, squareFinder.getNbSquares());
		}




		// Test 1
		TEST_METHOD(loadDatafromMemory_AreDatasIntact)
		{
			//Act

			std::stringstream content("(1,1);(2,2);(3,3);(4,4);(5,5);(6,6);(7,7);(8,8);(9,9);(10,10);");
			SquareFinder squareFinder;

			//Arrange

			squareFinder.loadDotsFromMemory(content);

			//Assert

			Assert::AreEqual(10, static_cast<int>(squareFinder.getNbDots()));

			for (int i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i + 1, squareFinder.getDot(i).getX());
				Assert::AreEqual(i + 1, squareFinder.getDot(i).getY());
			}
		}

		// Test 2
		TEST_METHOD(loadDotsFromMemory_Empty_Exception)
		{
			//Act

			std::stringstream content("");

			//Arrange

			SquareFinder squareFinder;


			//Assert

			Assert::ExpectException<std::runtime_error>([&]()
				{
					squareFinder.loadDotsFromMemory(content);
				}
			);
		}

		//Test 3
		TEST_METHOD(loadDotsFromMemory_InvalidInts_Ignored)
		{
			//Act

			std::stringstream content("(1,2);(a,3);(4,b);(5,6);(7.7,8);");

			//Arrange
			SquareFinder squareFinder;
			squareFinder.loadDotsFromMemory(content);

			//Assert

			Assert::AreEqual(3, static_cast<int>(squareFinder.getNbDots()));
		}

		//Test 4
		TEST_METHOD(loadDotsFromMemory_AllInvalid_Exception)
		{

			//Act

			std::stringstream content("(a,b);(x,y);(p,f);");

			//Arrange

			SquareFinder squareFinder;

			//Assert

			Assert::ExpectException<std::runtime_error>([&]() {squareFinder.loadDotsFromMemory(content);});
		}

		//Test 5
		TEST_METHOD(loadDotsFromMemory_UwantedFormat_Ignored)
		{

			//Act

			std::stringstream content("(1,2);(3 4);(5,6");


			//Arrange

			SquareFinder squareFinder;
			squareFinder.loadDotsFromMemory(content);

			//Assert

			Assert::AreEqual(1, static_cast<int>(squareFinder.getNbDots()));

		}

		// ******* TESTS ADDDOT *******  //

		//Test 6
		TEST_METHOD(AddDot_SingleDot_StoredCorrectly)
		{

			//Act

			SquareFinder dotFinder;

			//Arrange

			dotFinder.addDot(Dot(3, 4));

			//Assert

			Assert::AreEqual(1, static_cast<int>(dotFinder.getNbDots()));
			Assert::AreEqual(3, dotFinder.getDot(0).getX());
			Assert::AreEqual(4, dotFinder.getDot(0).getY());
		}

		//Test 7
		TEST_METHOD(AddDot_MultipleDots_StoredInOrder)
		{

			//Act

			SquareFinder dotFinder;

			//Arrange

			dotFinder.addDot(Dot(1, 1));
			dotFinder.addDot(Dot(2, 2));
			dotFinder.addDot(Dot(3, 3));

			//Assert

			Assert::AreEqual(3, static_cast<int>(dotFinder.getNbDots()));
			Assert::AreEqual(2, dotFinder.getDot(1).getX());
			Assert::AreEqual(2, dotFinder.getDot(1).getY());
		}

		//Test 8
		TEST_METHOD(AddDot_DuplicateDots_Accepted)
		{
			//Act

			SquareFinder dotFinder;

			//Arrange

			dotFinder.addDot(Dot(5, 5));
			dotFinder.addDot(Dot(5, 5));

			//Assert

			Assert::AreEqual(2, static_cast<int>(dotFinder.getNbDots()));
			Assert::AreEqual(5, dotFinder.getDot(0).getX());
			Assert::AreEqual(5, dotFinder.getDot(1).getY());
		}

		//Test 9
		TEST_METHOD(AddDot_InitialEmptyArray_AddsOneDot)
		{
			//Act
			SquareFinder dotFinder;


			//Arrange

			dotFinder.addDot(Dot(0, 0));


			//Assert

			Assert::AreEqual(1, static_cast<int>(dotFinder.getNbDots()));
			Assert::AreEqual(0, dotFinder.getDot(0).getX());
			Assert::AreEqual(0, dotFinder.getDot(0).getY());
		}


		// ******* TESTS FindSquareBruteForce *******  //

		//Test 10
		TEST_METHOD(FindSquaresBruteForce_NoSquare_Found)
		{
			//Act

			SquareFinder squareFinder;
			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(1, 2));
			squareFinder.addDot(Dot(3, 1));
			squareFinder.addDot(Dot(2, 4));

			//Arrange


			squareFinder.findSquaresBruteForce();

			//Assert

			Assert::AreEqual(0, static_cast<int>(squareFinder.getNbSquares()));
		}

		//Test 11
		TEST_METHOD(FindSquaresBruteForce_TwoValidSquares_Found)
		{

			//Act
			SquareFinder squareFinder;

			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(0, 1));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(1, 1));

			squareFinder.addDot(Dot(3, 3));
			squareFinder.addDot(Dot(3, 4));
			squareFinder.addDot(Dot(4, 3));
			squareFinder.addDot(Dot(4, 4));

			//Arrange

			squareFinder.findSquaresBruteForce();

			//Assert

			Assert::AreEqual(2, static_cast<int>(squareFinder.getNbSquares()));
		}

		//Test 12
		TEST_METHOD(FindSquaresBruteForce_LessThanFourDots_Throws)
		{

			//Act

			SquareFinder squareFinder;

			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(1, 1));


			//Assert


			Assert::ExpectException<std::runtime_error>([&]()
				{
					squareFinder.findSquaresBruteForce();
				});
		}

		//Test 13
		TEST_METHOD(FindSquaresBruteForce_AllDotsIdentical_NoSquare)
		{

			//Act

			SquareFinder squareFinder;

			for (int i = 0; i < 4; ++i)
			{
				squareFinder.addDot(Dot(2, 2));

			}

			//Arrange

			squareFinder.findSquaresBruteForce();


			//Assert

			Assert::AreEqual(0, static_cast<int>(squareFinder.getNbSquares()));
		}

		//Test 14
		TEST_METHOD(FindSquaresBruteForce_LinearDots_NoSquare)
		{

			//Act

			SquareFinder squareFinder;

			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(2, 0));
			squareFinder.addDot(Dot(3, 0));

			//Arrange

			squareFinder.findSquaresBruteForce();


			//Assert

			Assert::AreEqual(0, static_cast<int>(squareFinder.getNbSquares()));
		}

		//Test 15
		TEST_METHOD(FindSquaresBruteForce_NonAlignedDots_NoSquare)
		{
			//Act

			SquareFinder squareFinder;

			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(2, 0));
			squareFinder.addDot(Dot(1, 1));
			squareFinder.addDot(Dot(2, 2));

			//Arrange

			squareFinder.findSquaresBruteForce();


			//Assert


			Assert::AreEqual(0, static_cast<int>(squareFinder.getNbSquares()));
		}

		//Test 16
		TEST_METHOD(FindSquaresBruteForce_OddNumberOfDots_OneSquare_UsingIsSquareInList)
		{
			//Act

			SquareFinder squareFinder;

			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(0, 1));
			squareFinder.addDot(Dot(1, 1));
			squareFinder.addDot(Dot(7, 3));

			//Arrange

			squareFinder.findSquaresBruteForce();

			Square expectedSquare;
			expectedSquare.dots[0] = Dot(0, 0);
			expectedSquare.dots[1] = Dot(1, 0);
			expectedSquare.dots[2] = Dot(0, 1);
			expectedSquare.dots[3] = Dot(1, 1);

			const Square* constSquares = squareFinder.getSquares();
			Square* squares = const_cast<Square*>(constSquares);    // Puisque la fonction prend en paramétre un pointeur j'ai du caster le carré.

			//Assert

			Assert::IsTrue(squareFinder.isSquareInList(expectedSquare, squares, squareFinder.getNbSquares()), L"Expected square not found in list.");
		}

		// ******* TESTS FindSquareOptimized *******  //

		//Test 17
		TEST_METHOD(FindSquaresOptimized_TwoDistinctSquares_Found)
		{
			//Act

			SquareFinder squareFinder;

			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(0, 1));
			squareFinder.addDot(Dot(1, 1));

			squareFinder.addDot(Dot(2, 0));
			squareFinder.addDot(Dot(2, 1));
			squareFinder.addDot(Dot(3, 0));
			squareFinder.addDot(Dot(3, 1));

			//Arrange

			squareFinder.findSquaresOptimized();


			//Assert

			Assert::AreEqual(3, static_cast<int>(squareFinder.getNbSquares()));
		}

		//Test 18
		TEST_METHOD(FindSquaresOptimized_LessThanFourDots_Throws)
		{
			//Act

			SquareFinder squareFinder;
			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(0, 1));

			//Arrange

			auto action = [&]() { squareFinder.findSquaresOptimized(); };

			//Assert

			Assert::ExpectException<std::runtime_error>(action);
		}

		// Test 19
		TEST_METHOD(FindSquaresOptimized_OddNumberOfDots_NoSquare)
		{
			//Act

			SquareFinder squareFinder;

			for (int i = 0; i < 13; ++i)
			{
				squareFinder.addDot(Dot(i, i * i));
			}

			//Arrange

			squareFinder.findSquaresOptimized();

			//Assert

			Assert::AreEqual(0, static_cast<int>(squareFinder.getNbSquares()));
		}

		//Test20
		TEST_METHOD(FindSquaresOptimized_UnorderedPoints_StillDetectsSquare)
		{
			//Act

			SquareFinder squareFinder;
			squareFinder.addDot(Dot(1, 1));
			squareFinder.addDot(Dot(0, 1));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(0, 0));

			//Arrange

			squareFinder.findSquaresOptimized();

			//Assert

			Assert::AreEqual(1, static_cast<int>(squareFinder.getNbSquares()));
		}

		TEST_METHOD(FindSquaresOptimized_TwoDistinctSquares_FoundUslessDots)
		{
			//Act

			SquareFinder squareFinder;

			squareFinder.addDot(Dot(0, 0));
			squareFinder.addDot(Dot(1, 0));
			squareFinder.addDot(Dot(0, 1));
			squareFinder.addDot(Dot(1, 1));

			squareFinder.addDot(Dot(3, 0));
			squareFinder.addDot(Dot(3, 1));
			squareFinder.addDot(Dot(4, 0));
			squareFinder.addDot(Dot(4, 1));

			//Arrange

			squareFinder.findSquaresOptimized();

			//Assert

			Assert::AreEqual(2, static_cast<int>(squareFinder.getNbSquares()));
		}


	};
}