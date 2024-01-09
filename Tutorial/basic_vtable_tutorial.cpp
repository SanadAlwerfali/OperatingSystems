#include <iostream>

class Shape {
public:
    virtual void draw() const {
        std::cout << "Drawing a shape.\n";
    }
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle.\n";
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a square.\n";
    }
};

int main() {
    Shape* shapes[] = { new Circle(), new Square() };

    for (int i = 0; i < 2; ++i) {
        shapes[i]->draw();
    }

    for (int i = 0; i < 2; ++i) {
        delete shapes[i];
    }

    return 0;
}
