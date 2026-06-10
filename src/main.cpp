#include <vector>
#include <iostream>

class Canvas {
public:
    Canvas(size_t w, size_t h) : width(w), height(h), grid(h, std::vector<bool>(w, false)) {}
    
    void set(size_t x, size_t y) {
        if (x < width && y < height)
            grid[y][x] = true;
    }

    void print() const {
        for (const auto& row : grid) {
            for (bool c : row) {
                std::cout << (c ? "\xE2\x96\x88" : " ");
            }
            std::cout << std::endl;
        }
    }

    size_t getWidth() const {
        return width;
    }

    size_t getHeight() const {
        return height;
    }

private:
    std::vector<std::vector<bool>> grid;
    size_t width, height;
};

class Painter {
protected:
    Canvas& canvas; /* Kompozycja */
public:
    Painter(Canvas& c) : canvas(c) {}
    virtual void paint() = 0;
};



class VerticalLinePainter : public Painter {
private:
    int x;

public:
    VerticalLinePainter(Canvas& c, int x)
        : Painter(c), x(x) {}

    void paint() override {
        if (x < 0) return;

        for (size_t y = 0; y < canvas.getHeight(); ++y) {
            canvas.set(x, y);
        }
    }
};

class HorizontalLinePainter : public Painter {
private:
    int y;

public:
    HorizontalLinePainter(Canvas& c, int y)
        : Painter(c), y(y) {}

    void paint() override {
        if (y < 0) return;

        for (size_t x = 0; x < canvas.getWidth(); ++x) {
            canvas.set(x, y);
        }
    }
};

class RectanglePainter : public Painter {
public:
    RectanglePainter(Canvas& c)
        : Painter(c) {}

    void paint() override {
        size_t w = canvas.getWidth();
        size_t h = canvas.getHeight();

        if (w == 0 || h == 0)
            return;

        for (size_t x = 0; x < w; ++x) {
            canvas.set(x, 0);
            canvas.set(x, h - 1);
        }

        for (size_t y = 0; y < h; ++y) {
            canvas.set(0, y);
            canvas.set(w - 1, y);
        }
    }
};



int main() {
    Canvas canvas(20, 10);

    RectanglePainter rect(canvas);
    VerticalLinePainter vline(canvas, 10);
    HorizontalLinePainter hline(canvas, 5);

    rect.paint();
    vline.paint();
    hline.paint();

    canvas.print();

    return 0;
}