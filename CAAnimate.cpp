// Project: Game of Life Glider
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

// grid width and height
const int num_h_boxes = 10;
const int num_w_boxes = 15;
const double RECT_SIDE = 25;
const double width{num_w_boxes * RECT_SIDE};
const double height{num_h_boxes * RECT_SIDE};


//some vectors to hold information about the CA
std::vector<std::vector<int> > cells;
        

// where we'll draw
emp::web::Canvas canvas{width, height, "canvas"};

public:

    CAAnimator() {
        // shove canvas into the div
        // along with some control buttons
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        //fill the vectors with 0 to start
        cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));

        //showing how to set a cell to 'alive'
        cells[1][0] = 1;
        cells[2][1] = 1;
        cells[0][2] = 1;
        cells[1][2] = 1;
        cells[2][2] = 1;
    }

    void DoFrame() override {
    canvas.Clear();

    // Create a new grid to hold the updated states of the cells
    std::vector<std::vector<int>> new_cells = cells;

    // Loop over all cells to apply the rules of the Game of Life
    for (int x = 0; x < num_w_boxes; x++) {
        for (int y = 0; y < num_h_boxes; y++) {

            // Count live neighbors (including toroidal wrapping)
            int live_neighbors = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue; // Skip the current cell
                    int nx = (x + dx + num_w_boxes) % num_w_boxes; // Wrap x-coordinate
                    int ny = (y + dy + num_h_boxes) % num_h_boxes; // Wrap y-coordinate

                    live_neighbors += cells[nx][ny];  // Add the state of the neighbor
                }
            }

            // Apply the Game of Life rules to decide the new state of the cell
            if (cells[x][y] == 1) {
                // Cell stays alive if it has 2 or 3 live neighbors
                new_cells[x][y] = (live_neighbors == 2 || live_neighbors == 3) ? 1 : 0;
            } else {
                // Cell becomes alive if it has exactly 3 live neighbors
                new_cells[x][y] = (live_neighbors == 3) ? 1 : 0;
            }

            // Draw the current cell: alive cells are black, dead cells are white
            if (new_cells[x][y] == 1) {
                canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
            } else {
                canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
            }
        }
    }

    // Update the cells grid with the new state
    cells = new_cells;
}



};

CAAnimator animator;

int main() {
    //Have animator call DoFrame once to start
    animator.Step();
    animator.DoFrame();
}