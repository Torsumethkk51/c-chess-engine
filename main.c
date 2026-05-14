#include <stdio.h>
#include <stdint.h>

void printBinary(uint64_t n) {
  for (int i = 63; i >= 0; i--) {
    printf("%lu", (n >> i) & 1);
    if (i % 8 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

void printBoard(
  uint64_t whitePawns, uint64_t whiteBishops, uint64_t whiteKnights, uint64_t whiteRooks, uint64_t whiteQueen, uint64_t whiteKing,
  uint64_t blackPawns, uint64_t blackBishops, uint64_t blackKnights, uint64_t blackRooks, uint64_t blackQueen, uint64_t blackKing
) {

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

int main() {
  uint64_t board = 0ULL;

  // White pieces
  uint64_t whitePawns = 0ULL;
  uint64_t whiteBishops = 0ULL;
  uint64_t whiteKnights = 0ULL;
  uint64_t whiteRooks = 0ULL;
  uint64_t whiteQueen = 0ULL;
  uint64_t whiteKing = 0ULL;

  // Black pieces
  uint64_t blackPawns = 0ULL;
  uint64_t blackBishops = 0ULL;
  uint64_t blackKnights = 0ULL;
  uint64_t blackRooks = 0ULL;
  uint64_t blackQueen = 0ULL;
  uint64_t blackKing = 0ULL;


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


  // Bind every pieces
  board |= whitePawns | whiteBishops | whiteKnights | whiteRooks | whiteQueen | whiteKing | 
           blackPawns | blackBishops | blackKnights | blackRooks | blackQueen | blackKing ;

  printBinary(board);

  printBoard(
    whitePawns, whiteBishops, whiteKnights, whiteRooks, whiteQueen, whiteKing,
    blackPawns, blackBishops, blackKnights, blackRooks, blackQueen, blackKing
  );
  
  return 0;
}