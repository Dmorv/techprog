#include <iostream>
#include <cmath>
#include <vector>

const double PI = acos(-1.0);

// Базовый класс Точка
class Point {
public:
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual ~Point() {}
};

// Реализация точки
class BasicPoint : public Point {
private:
    double x, y;
public:
    BasicPoint(double x = 0, double y = 0) : x(x), y(y) {}

    double getX() const override { return x; }
    double getY() const override { return y; }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void setCoordinates(double newX, double newY) {
        x = newX;
        y = newY;
    }
};

// Базовый класс для всех фигур
class Shape {
public:
    virtual void draw() const = 0;
    virtual void erase() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    virtual ~Shape() {}
};

// Класс Линия
class Line : public Shape {
private:
    BasicPoint start, end;
public:
    Line(double x1, double y1, double x2, double y2) 
        : start(x1, y1), end(x2, y2) {}

    void draw() const override {
        std::cout << "Рисуется линия: (" << start.getX() << "," << start.getY() 
                  << ") -> (" << end.getX() << "," << end.getY() << ")\n";
    }

    void erase() const override {
        std::cout << "Стирается линия\n";
    }

    void move(double dx, double dy) override {
        start.move(dx, dy);
        end.move(dx, dy);
    }

    void rotate(double angle) override {
        double rad = angle * PI / 180.0;
        double midX = (start.getX() + end.getX()) / 2;
        double midY = (start.getY() + end.getY()) / 2;

        rotatePoint(start, midX, midY, rad);
        rotatePoint(end, midX, midY, rad);
    }

private:
    void rotatePoint(BasicPoint& p, double centerX, double centerY, double angle) {
        double x = p.getX() - centerX;
        double y = p.getY() - centerY;
        double newX = x * cos(angle) - y * sin(angle) + centerX;
        double newY = x * sin(angle) + y * cos(angle) + centerY;
        p.setCoordinates(newX, newY);
    }
};

// Класс Прямоугольник
class Rectangle : public Shape {
protected:
    BasicPoint topLeft;
    double width, height;
public:
    Rectangle(double x, double y, double w, double h) 
        : topLeft(x, y), width(w), height(h) {}

    void draw() const override {
        std::cout << "Рисуется прямоугольник: (" << topLeft.getX() << "," << topLeft.getY()
                  << "), w=" << width << ", h=" << height << "\n";
    }

    void erase() const override {
        std::cout << "Стирается прямоугольник\n";
    }

    void move(double dx, double dy) override {
        topLeft.move(dx, dy);
    }

    void rotate(double angle) override {
        double rad = angle * PI / 180.0;
        double centerX = topLeft.getX() + width/2;
        double centerY = topLeft.getY() + height/2;

        std::vector<BasicPoint> corners = {
            BasicPoint(topLeft.getX(), topLeft.getY()),
            BasicPoint(topLeft.getX() + width, topLeft.getY()),
            BasicPoint(topLeft.getX() + width, topLeft.getY() + height),
            BasicPoint(topLeft.getX(), topLeft.getY() + height)
        };

        for (auto& corner : corners) {
            double x = corner.getX() - centerX;
            double y = corner.getY() - centerY;
            double newX = x * cos(rad) - y * sin(rad) + centerX;
            double newY = x * sin(rad) + y * cos(rad) + centerY;
            corner.setCoordinates(newX, newY);
        }

        // Обновляем topLeft и размеры
        double minX = corners[0].getX(), maxX = corners[0].getX();
        double minY = corners[0].getY(), maxY = corners[0].getY();
        
        for (const auto& corner : corners) {
            if (corner.getX() < minX) minX = corner.getX();
            if (corner.getX() > maxX) maxX = corner.getX();
            if (corner.getY() < minY) minY = corner.getY();
            if (corner.getY() > maxY) maxY = corner.getY();
        }
        
        topLeft.setCoordinates(minX, minY);
        width = maxX - minX;
        height = maxY - minY;
    }
};

// Класс Квадрат
class Square : public Rectangle {
public:
    Square(double x, double y, double size) : Rectangle(x, y, size, size) {}

    void draw() const override {
        std::cout << "Рисуется квадрат: (" << topLeft.getX() << "," << topLeft.getY()
                  << "), сторона=" << width << "\n";
    }

    void erase() const override {
        std::cout << "Стирается квадрат\n";
    }
};

// Класс Параллелограмм
class Parallelogram : public Shape {
protected:
    BasicPoint basePoint;
    double base, height, skew;
public:
    Parallelogram(double x, double y, double b, double h, double s) 
        : basePoint(x, y), base(b), height(h), skew(s) {}

    void draw() const override {
        std::cout << "Рисуется параллелограмм: (" << basePoint.getX() << "," << basePoint.getY()
                  << "), основание=" << base << ", высота=" << height 
                  << ", скос=" << skew << "\n";
    }

    void erase() const override {
        std::cout << "Стирается параллелограмм\n";
    }

    void move(double dx, double dy) override {
        basePoint.move(dx, dy);
    }

    void rotate(double angle) override {
        double rad = angle * PI / 180.0;
        double centerX = basePoint.getX() + base/2 + skew/2;
        double centerY = basePoint.getY() + height/2;

        std::vector<BasicPoint> corners = getCorners();
        
        for (auto& corner : corners) {
            double x = corner.getX() - centerX;
            double y = corner.getY() - centerY;
            double newX = x * cos(rad) - y * sin(rad) + centerX;
            double newY = x * sin(rad) + y * cos(rad) + centerY;
            corner.setCoordinates(newX, newY);
        }

        // Обновляем basePoint и параметры
        double minX = corners[0].getX();
        basePoint.setCoordinates(minX, corners[0].getY());
    }

protected:
    std::vector<BasicPoint> getCorners() const {
        return {
            BasicPoint(basePoint.getX(), basePoint.getY()),
            BasicPoint(basePoint.getX() + base, basePoint.getY()),
            BasicPoint(basePoint.getX() + skew, basePoint.getY() + height),
            BasicPoint(basePoint.getX() + base + skew, basePoint.getY() + height)
        };
    }
};

// Класс Ромб
class Rhombus : public Parallelogram {
public:
    Rhombus(double x, double y, double d1, double d2) 
        : Parallelogram(x, y, d1, d2, 0) {}

    void draw() const override {
        std::cout << "Рисуется ромб: (" << basePoint.getX() << "," << basePoint.getY()
                  << "), диагонали=" << base << " и " << height << "\n";
    }

    void erase() const override {
        std::cout << "Стирается ромб\n";
    }
};

// Функция для демонстрации работы с фигурой
void demonstrateShape(Shape* shape) {
    shape->draw();
    shape->move(2, 3);
    shape->rotate(30);
    shape->draw();
    shape->erase();
    std::cout << "----------------\n";
}

int main() {
    // Создаем фигуры
    Line line(0, 0, 5, 5);
    Rectangle rectangle(1, 1, 4, 2);
    Square square(2, 2, 3);
    Parallelogram parallelogram(0, 0, 5, 3, 2);
    Rhombus rhombus(1, 1, 4, 6);

    // Демонстрируем работу с каждой фигурой
    demonstrateShape(&line);
    demonstrateShape(&rectangle);
    demonstrateShape(&square);
    demonstrateShape(&parallelogram);
    demonstrateShape(&rhombus);

    return 0;
}