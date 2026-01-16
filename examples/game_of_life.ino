/*
 * Example: Game of Life
 * 
 * Conway's Game of Life animated on the LED matrix
 */

#include "config.h"
#include "display_manager.h"

DisplayManager display;

// Game state grid
uint8_t grid[MATRIX_HEIGHT][MATRIX_WIDTH];
uint8_t newGrid[MATRIX_HEIGHT][MATRIX_WIDTH];

void initializeGrid() {
  // Random initialization
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      grid[y][x] = random(2);
    }
  }
}

int countNeighbors(int x, int y) {
  int count = 0;
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      if (dx == 0 && dy == 0) continue;
      
      int nx = (x + dx + MATRIX_WIDTH) % MATRIX_WIDTH;
      int ny = (y + dy + MATRIX_HEIGHT) % MATRIX_HEIGHT;
      
      if (grid[ny][nx]) count++;
    }
  }
  return count;
}

void updateGame() {
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      int neighbors = countNeighbors(x, y);
      
      if (grid[y][x]) {
        // Cell is alive
        newGrid[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
      } else {
        // Cell is dead
        newGrid[y][x] = (neighbors == 3) ? 1 : 0;
      }
    }
  }
  
  // Copy new grid to current grid
  memcpy(grid, newGrid, sizeof(grid));
}

void displayGame() {
  display.clear();
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      if (grid[y][x]) {
        // Alive cell
        uint32_t color = getRainbowColor((x + y) % 7);
        display.setPixel(x, y, color);
      }
    }
  }
  display.update();
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("=== Game of Life ===");
  
  display.begin();
  display.setBrightness(200);
  display.clear();
  
  initializeGrid();
  Serial.println("Game started!");
}

void loop() {
  displayGame();
  updateGame();
  delay(500);  // Generation interval
}
