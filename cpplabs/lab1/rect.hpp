
class Rect
{
    int left;
    int right;
    int top;
    int bottom;

public:
    Rect();
    Rect(int p1, int p2, int p3, int p4);
    ~Rect();
    Rect(const Rect &other);
    int get_left();
    int get_right();
    int get_top();
    int get_bottom();
    void set_all(int left, int right, int top, int bottom);
    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);
    void move(int x, int y = 0);
    int get_width();
    int get_height();
    int get_square();
    void set_width(int w);
    void set_height(int h);
};
Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);