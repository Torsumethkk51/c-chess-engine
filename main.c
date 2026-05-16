#include <stdio.h>
#include <stdint.h>

uint64_t board = 0ULL;

uint64_t notAFile = 0xFEFEFEFEFEFEFEFE;
uint64_t notHFile = 0x7F7F7F7F7F7F7F7F;

uint64_t notABFile = 0xFCFCFCFCFCFCFCFC;
uint64_t notGHFile = 0x3F3F3F3F3F3F3F3F;

// White pieces
uint64_t whitePawns = 0ULL;
uint64_t whiteBishops = 0ULL;
uint64_t whiteKnights = 0ULL;
uint64_t whiteRooks = 0ULL;
uint64_t whiteQueen = 0ULL;
uint64_t whiteKing = 0ULL;

uint64_t whitePieces = 0ULL;

// Black pieces
uint64_t blackPawns = 0ULL;
uint64_t blackBishops = 0ULL;
uint64_t blackKnights = 0ULL;
uint64_t blackRooks = 0ULL;
uint64_t blackQueen = 0ULL;
uint64_t blackKing = 0ULL;

uint64_t blackPieces = 0ULL;

void printBinary(uint64_t n) {
  for (int i = 63; i >= 0; i--) {
    printf("%lu", (n >> i) & 1);
    if (i % 8 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

void printBoard() {
  for (int y = 7; y >= 0; y--) {
    for (int x = 0; x <= 7; x++) {
      int bit = (8 * y) + x;

      if (x == 0) {
        printf(" %d ", y + 1);
      }

      if ((whitePawns >> bit) & 1) printf(" P ");
      else if ((whiteBishops >> bit) & 1) printf(" B ");
      else if ((whiteKnights >> bit) & 1) printf(" N ");
      else if ((whiteRooks >> bit) & 1) printf(" R ");
      else if ((whiteQueen >> bit) & 1) printf(" Q ");
      else if ((whiteKing >> bit) & 1) printf(" K ");

      else if ((blackPawns >> bit) & 1) printf(" p ");
      else if ((blackKnights >> bit) & 1) printf(" n ");
      else if ((blackBishops >> bit) & 1) printf(" b ");
      else if ((blackRooks >> bit) & 1) printf(" r ");
      else if ((blackQueen >> bit) & 1) printf(" q ");
      else if ((blackKing >> bit) & 1) printf(" k ");

      else printf(" . ");
    }
    printf("\n\n");
  }
  printf("    a  b  c  d  e  f  g  h \n");
}

uint64_t knightMoves(uint64_t knights) {
  uint64_t moves = 0ULL;

  // Move up 2 left/right 1
  moves |= ((knights << 15) & notHFile) | ((knights << 17) & notAFile);
 
  // Move down 2 left/right 1
  moves |= ((knights >> 15) & notAFile) | ((knights >> 17) & notHFile);

  // Move left 2 up/down 1
  moves |= ((knights << 6) & notGHFile) | ((knights >> 10) & notGHFile);

  // Move right 2 up/down 1
  moves |= ((knights << 10) & notABFile) | ((knights >> 6) & notABFile);

  // Remove bit that has piece already
  moves &= ~whitePieces;

  return moves;
}

uint64_t whitePawnMoves(uint64_t pawns) {
  uint64_t moves = 0ULL;

  // Normal move logic
  uint64_t singleStep = (pawns << 8);

  singleStep &= ~board;

  moves |= singleStep;

  uint64_t doubleStep = singleStep & 0x0000000000FF0000ULL;

  doubleStep = (doubleStep << 8);

  doubleStep &= ~board;

  moves |= doubleStep;

  // Kill move logic

  // Left 1 top 1
  moves |= ((pawns << 7) & blackPieces) & notHFile;

  // Right 1 top 1
  moves |= ((pawns << 9) & blackPieces) & notAFile;

  return moves;
}

uint64_t blackPawnMoves(uint64_t pawns) {
  uint64_t moves = 0ULL;

  // Normal move logic
  uint64_t singleStep = (pawns >> 8);

  singleStep &= ~board;

  moves |= singleStep;

  uint64_t doubleStep = singleStep & 0x0000FF0000000000ULL;

  doubleStep = doubleStep >> 8;

  doubleStep &= ~board;

  moves |= doubleStep;

  // Kill move logic

  // Left 1 down 1
  moves |= ((pawns >> 9) & whitePieces) & notHFile;

  // Right 1 down 1
  moves |= ((pawns >> 7) & whitePieces) & notAFile;

  return moves;
}

int main() {
  // Setup white pieces position

  // White setup

  whitePawns |= (1ULL << 8);
  whitePawns |= (1ULL << 9);
  whitePawns |= (1ULL << 10);
  whitePawns |= (1ULL << 11);
  whitePawns |= (1ULL << 12);
  whitePawns |= (1ULL << 13);
  whitePawns |= (1ULL << 14);
  whitePawns |= (1ULL << 15);

  whiteBishops |= (1ULL << 2);
  whiteBishops |= (1ULL << 5);

  whiteKnights |= (1ULL << 1);
  whiteKnights |= (1ULL << 6);

  whiteRooks |= 1ULL;
  whiteRooks |= (1ULL << 7);

  whiteQueen |= (1ULL << 3);

  whiteKing |= (1ULL << 4);

  whitePieces = whitePawns | whiteBishops | whiteKnights | whiteRooks | whiteQueen | whiteKing;

  // Black setup

  blackPawns |= (1ULL << 48);
  blackPawns |= (1ULL << 49);
  blackPawns |= (1ULL << 50);
  blackPawns |= (1ULL << 51);
  blackPawns |= (1ULL << 52);
  blackPawns |= (1ULL << 53);
  blackPawns |= (1ULL << 54);
  blackPawns |= (1ULL << 55);

  blackBishops |= (1ULL << 58);
  blackBishops |= (1ULL << 61);

  blackKnights |= (1ULL << 57);
  blackKnights |= (1ULL << 62);
  
  blackRooks |= (1ULL << 56);
  blackRooks |= (1ULL << 63);

  blackQueen |= (1ULL << 59);

  blackKing |= (1ULL << 60);

  blackPieces |= blackPawns | blackBishops | blackKnights | blackRooks | blackQueen | blackKing;


  // Bind every pieces
  board |= whitePawns | whiteBishops | whiteKnights | whiteRooks | whiteQueen | whiteKing | 
           blackPawns | blackBishops | blackKnights | blackRooks | blackQueen | blackKing ;

  printBinary(whitePawnMoves(whitePawns));

  printBinary(blackPawnMoves(blackPawns));

  printBoard();
  
  return 0;
}