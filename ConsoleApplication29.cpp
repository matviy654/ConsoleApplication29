#include <iostream>
#include <cmath>
#include <vector>

class Equation {
public:
    virtual void findRoots() const = 0;
    virtual ~Equation() = default;    
};

class LinearEquation : public Equation {
    double a, b;
public:
    LinearEquation(double a, double b) : a(a), b(b) {}
    void findRoots() const override {
        if (a != 0)
            std::cout << "Root: x = " << -b / a << std::endl;
        else if (b == 0)
            std::cout << "Infinite solutions." << std::endl;
        else
            std::cout << "No solutions." << std::endl;
    }
};

class QuadraticEquation : public Equation {
    double a, b, c;
public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}
    void findRoots() const override {
        if (a == 0) {
            LinearEquation linear(b, c);
            linear.findRoots();
            return;
        }
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            std::cout << "Roots: x1 = " << (-b + std::sqrt(discriminant)) / (2 * a)
                << ", x2 = " << (-b - std::sqrt(discriminant)) / (2 * a) << std::endl;
        }
        else if (discriminant == 0) {
            std::cout << "One root: x = " << -b / (2 * a) << std::endl;
        }
        else {
            std::cout << "No real roots." << std::endl;
        }
    }
};

int main() {
    std::vector<Equation*> equations;
    equations.push_back(new LinearEquation(2, -4)); 
    equations.push_back(new QuadraticEquation(1, -3, 2)); 

    for (const auto& eq : equations) {
        eq->findRoots();
    }

    for (auto eq : equations) {
        delete eq;
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual void Show() const = 0;     // Віртуальний метод для показу
    virtual void Save(std::ofstream& file) const = 0; // Збереження в файл
    virtual void Load(std::ifstream& file) = 0;       // Завантаження з файлу
    virtual ~Shape() = default;       // Віртуальний деструктор
};

class Square : public Shape {
    int x, y, side;
public:
    Square(int x = 0, int y = 0, int side = 0) : x(x), y(y), side(side) {}
    void Show() const override {
        std::cout << "Square: (" << x << ", " << y << "), side = " << side << std::endl;
    }
    void Save(std::ofstream& file) const override {
        file << "Square " << x << " " << y << " " << side << "\n";
    }
    void Load(std::ifstream& file) override {
        file >> x >> y >> side;
    }
};

class Rectangle : public Shape {
    int x, y, width, height;
public:
    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height) {}
    void Show() const override {
        std::cout << "Rectangle: (" << x << ", " << y << "), width = " << width << ", height = " << height << std::endl;
    }
    void Save(std::ofstream& file) const override {
        file << "Rectangle " << x << " " << y << " " << width << " " << height << "\n";
    }
    void Load(std::ifstream& file) override {
        file >> x >> y >> width >> height;
    }
};

class Circle : public Shape {
    int x, y, radius;
public:
    Circle(int x = 0, int y = 0, int radius = 0) : x(x), y(y), radius(radius) {}
    void Show() const override {
        std::cout << "Circle: center = (" << x << ", " << y << "), radius = " << radius << std::endl;
    }
    void Save(std::ofstream& file) const override {
        file << "Circle " << x << " " << y << " " << radius << "\n";
    }
    void Load(std::ifstream& file) override {
        file >> x >> y >> radius;
    }
};

class Ellipse : public Shape {
    int x, y, width, height;
public:
    Ellipse(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height) {}
    void Show() const override {
        std::cout << "Ellipse: top-left = (" << x << ", " << y << "), width = " << width << ", height = " << height << std::endl;
    }
    void Save(std::ofstream& file) const override {
        file << "Ellipse " << x << " " << y << " " << width << " " << height << "\n";
    }
    void Load(std::ifstream& file) override {
        file >> x >> y >> width >> height;
    }
};

int main() {
    std::vector<std::shared_ptr<Shape>> shapes = {
        std::make_shared<Square>(0, 0, 10),
        std::make_shared<Rectangle>(1, 1, 20, 10),
        std::make_shared<Circle>(5, 5, 7),
        std::make_shared<Ellipse>(2, 2, 10, 6)
    };

    std::ofstream outFile("shapes.txt");
    for (const auto& shape : shapes) {
        shape->Save(outFile);
    }
    outFile.close();

    std::vector<std::shared_ptr<Shape>> loadedShapes;
    std::ifstream inFile("shapes.txt");
    std::string shapeType;
    while (inFile >> shapeType) {
        if (shapeType == "Square") {
            auto shape = std::make_shared<Square>();
            shape->Load(inFile);
            loadedShapes.push_back(shape);
        }
        else if (shapeType == "Rectangle") {
            auto shape = std::make_shared<Rectangle>();
            shape->Load(inFile);
            loadedShapes.push_back(shape);
        }
        else if (shapeType == "Circle") {
            auto shape = std::make_shared<Circle>();
            shape->Load(inFile);
            loadedShapes.push_back(shape);
        }
        else if (shapeType == "Ellipse") {
            auto shape = std::make_shared<Ellipse>();
            shape->Load(inFile);
            loadedShapes.push_back(shape);
        }
    }
    inFile.close();

    for (const auto& shape : loadedShapes) {
        shape->Show();
    }

    return 0;
}
