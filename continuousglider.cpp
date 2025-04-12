// Project: Fuzzy Game of Life Glider

#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

    // Grid width and height 10 by 15, with each box 25 pixels wide and tall
    const int num_h_boxes = 10;
    const int num_w_boxes = 15;
    const double RECT_SIDE = 25;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    // Vectors to hold information about the CA and canvas initialization
    std::vector<std::vector<double>> cells;
    emp::web::Canvas canvas{width, height, "canvas"};

public:
    CAAnimator() {

        // Add canvas and buttons
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        // Resizes vector to correct dimensions and sets all cell values to 0
        cells.resize(num_w_boxes, std::vector<double>(num_h_boxes, 0.0));

        // Start with a continuous glider
        cells[1][0] = 1.0;
        cells[2][1] = 1.0;
        cells[0][2] = 1.0;
        cells[1][2] = 1.0;
        cells[2][2] = 1.0;
    }

    void DoFrame() override {
        canvas.Clear();

        // Create a new grid to hold the updated states of the cells
        std::vector<std::vector<double>> new_cells = cells;

        // Iterates over all cells
        for (int x = 0; x < num_w_boxes; ++x) {
            for (int y = 0; y < num_h_boxes; ++y) {
                int active_neighbors = 0;

                // Count active neighbors as in classic Game of Life
                // including toroidal wrapping
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = (x + dx + num_w_boxes) % num_w_boxes;
                        int ny = (y + dy + num_h_boxes) % num_h_boxes;
                        if (cells[nx][ny] > 0.5) ++active_neighbors;
                    }
                }

                // Fuzzy Game of Life logic
                double current = cells[x][y];

                if (current > 0.5) {
                    // Cell is "alive" — stays active with 2 or 3 neighbors
                    if (active_neighbors == 2 || active_neighbors == 3) {
                        new_cells[x][y] = std::min(current + 0.1, 1.0);  // reinforce
                    } else {
                        new_cells[x][y] *= 0.9;  // decay
                    }
                } else {
                    // Dead cell becomes alive if it has exactly 3 live neighbors
                    if (active_neighbors == 3) {
                        new_cells[x][y] = 1.0;
                    } else {
                        new_cells[x][y] *= 0.95;  // decay more slowly
                    }
                }

                // Clamp to [0, 1]
                if (new_cells[x][y] < 0.01) new_cells[x][y] = 0.0;

                // Draw
                double hue = 240.0 * (1.0 - new_cells[x][y]);
                canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorHSV(hue, 1.0, new_cells[x][y]));
            }
        }

        cells = new_cells;
    }
};

CAAnimator animator;

int main() {
    animator.Step();
    animator.DoFrame();
}
