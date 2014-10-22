#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define HEIGHT 30
#define WIDTH 30

void init(int grid[][HEIGHT]) {
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      grid[i][j] = rand() % 2;
    }
  }
}

int sumPoint(int grid[][HEIGHT], int x, int y) {
  unsigned int count = 0;
  count += grid[x][y];
  if (x + 1 < WIDTH) {
    count += grid[x + 1][y];
  }
  if (x - 1 >= 0) {
    count += grid[x - 1][y];
  }
  if (y + 1 < HEIGHT) {
    count += grid[x][y + 1];
  }
  if (y - 1 >= 0) {
    count += grid[x][y - 1];
  }
  if (x + 1 < WIDTH && y + 1 < HEIGHT) {
    count += grid[x + 1][y + 1];
  }
  if (x + 1 < WIDTH && y - 1 >= 0) {
    count += grid[x + 1][y - 1];
  }
  if (x - 1 >= 0 && y + 1 < HEIGHT) {
    count += grid[x - 1][y + 1];
  }
  if (x - 1 >= 0 && y - 1 >= 0) {
    count += grid[x - 1][y - 1];
  }
  return count;
}

void updateGrid(int prev_grid[][HEIGHT], int next_grid[][HEIGHT]) {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      int sum = sumPoint(prev_grid, x, y);
      switch(sum) {
        case 3:
          next_grid[x][y] = 1;
          break;
        case 4: 
          next_grid[x][y] = prev_grid[x][y];
          break;
        default:
          next_grid[x][y] = 0;
          break;
      }
    }
  }
}


void printGrid(int grid[][HEIGHT]) {
  int x;
  int y;
  printf(".");
  for (x = 0; x < WIDTH*3; x++) {
    printf("-");
  }
  printf(".\n");

  for (x = 0; x < WIDTH; x++) {
    printf("|");
    for (y = 0; y < HEIGHT; y++) {
      if (grid[x][y] > 0) {
        printf(" X ");
      } else {
        printf("   ");
      }
    }
    printf("|\n");
  }
  printf(".");
  for (x = 0; x < WIDTH*3; x++) {
    printf("-");
  }
  printf(".\n");

}



int main() {
  int grid[WIDTH][HEIGHT];
  int next[WIDTH][HEIGHT];

  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      grid[i][j] = 0;
      next[i][j] = 0;
    }
  }
  init(grid);
  printGrid(grid);
  printf("Please press Enter to get the next generation");
  while(1) {
    char c = getchar();
    if (c == '\n') {
      updateGrid(grid, next);
      printGrid(next);
      memcpy(grid, next, sizeof(int)*WIDTH*HEIGHT);
    }
  }

  

}
