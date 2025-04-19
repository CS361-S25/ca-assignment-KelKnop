/* Kellen Knop
   April 16, 2025
*/
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

    const int num_h_boxes = 10;
    const int num_w_boxes = 15;
    const double RECT_SIDE = 25;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    std::vector<std::vector<double>> cells;
    emp::web::Canvas canvas{width, height, "canvas"};

public:
    CAAnimator() {
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        cells.resize(num_w_boxes, std::vector<double>(num_h_boxes, 0.0));

        // Seed: continuous glider pattern
        cells[1][0] = 1.0;
        cells[2][1] = 1.0;
        cells[0][2] = 1.0;
        cells[1][2] = 1.0;
        cells[2][2] = 1.0;
    }

    void DoFrame() override {
        canvas.Clear();
        std::vector<std::vector<double>> new_cells = cells;

        for (int x = 0; x < num_w_boxes; ++x) {
            for (int y = 0; y < num_h_boxes; ++y) {
                int active_neighbors = CountActiveNeighbors(x, y);
                UpdateCellState(x, y, active_neighbors, new_cells);
                DrawCell(x, y, new_cells[x][y]);
            }
        }

        cells = new_cells;
    }

private:
    int CountActiveNeighbors(int x, int y) {
        int count = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int nx = (x + dx + num_w_boxes) % num_w_boxes;
                int ny = (y + dy + num_h_boxes) % num_h_boxes;
                if (cells[nx][ny] > 0.5) ++count;
            }
        }
        return count;
    }

    void UpdateCellState(int x, int y, int neighbors, std::vector<std::vector<double>>& new_cells) {
        double current = cells[x][y];

        if (current > 0.5) {
            // Alive
            if (neighbors == 2 || neighbors == 3) {
                new_cells[x][y] = std::min(current + 0.1, 1.0); // Reinforce
            } else {
                new_cells[x][y] *= 0.5; // Decay
            }
        } else {
            // Dead
            if (neighbors == 3) {
                new_cells[x][y] = 1.0;
            } else {
                new_cells[x][y] *= 0.96;
            }
        }

        // Clamp very small values to zero
        if (new_cells[x][y] < 0.01) new_cells[x][y] = 0.0;
    }

    void DrawCell(int x, int y, double state) {
        double hue = 240.0 * (1.0 - state); // Red to blue
        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorHSV(hue, 1.0, state));
    }
};

CAAnimator animator;

int main() {
    animator.Step();
    animator.DoFrame();
}
