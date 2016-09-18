/////////////////////////////////////////////////////////////////////////////////////
//! @file tpawnmove.cc
//! @author Omar A Serrano
//! @date 2016-09-18
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <utility>

//
// zoor
//
#include "pawnmove.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace zoor {

TEST(PawnMoveTest, ConstructorShouldThrowIfRowIsNotValid)
{
}

TEST(PawnMoveTest, ConstructorShouldThrowIfColumIsNotValid)
{
}

TEST(PawnMoveTest, ConstructorShouldThrowIfThePieceIsNotAPawn)
{
}

TEST(PawnMoveTest, TypeShouldReturnAPawn)
{
}

TEST(PawnMoveTest, CanMoveShouldReturnFalseIfMovesAreNotValid)
{
}

TEST(PawnMoveTest, CanMoveShouldReturnTrueIfMovesAreValid)
{
}

TEST(PawnMoveTest, MoveShouldReturnAForwardPieceMove)
{
}

TEST(PawnMoveTest, MoveShouldReturnATwoSquareForwardPieceMove)
{
}

TEST(PawnMoveTest, MoveShouldReturnAnAttackMove)
{
}

TEST(PawnMoveTest, MoveShouldReturnMultipleMovesOnPromotion)
{
}

TEST(PawnMoveTest, MoveShouldReturnAListOfMovesOnPromotion)
{
}

TEST(PawnMoveTest, MoveShouldReturnAnEnPassantMove)
{
}

TEST(PawnMoveTest, MovesShouldReturnACorrectListOfValidMoves)
{
}

} // namespace zoor
