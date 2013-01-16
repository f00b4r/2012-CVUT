//============================================================================
// Name        : ShapeFactory.cpp
// Author      : Vikturek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

#define DRAWING_FILE "Drawing.txt"

class Shape {
public:
    virtual void draw() = 0;
    virtual void load(ifstream &file) = 0;
    virtual Shape* create() = 0;

    virtual ~Shape() {
    }
};

class ShapeFactory {
public:
    typedef Shape*(*shapeCallback)(void);
    map<int, shapeCallback> factories;
    static ShapeFactory* instance;

private:

    ShapeFactory() {
    }
public:

    void reg(int id, shapeCallback cb) {
        cout << "Register new type of shape: " << id << endl;
        factories[id] = cb;
    }

    Shape* create(int id) {
        return factories[id]();
    }

    static ShapeFactory* getInstance() {
        if (instance == NULL) {
            instance = new ShapeFactory();
        }

        return instance;
    }
};

ShapeFactory* ShapeFactory::instance = NULL;

Shape* createSquareCircle() {
    return new ShapeCircle();
}

class ShapeCircle : public Shape {
private:
    double x, y, r;
    bool registered;

private:

    void reg() {
        if (!registered) {
            ShapeFactory::getInstance()->reg(1, createSquareCircle());
        }
        registered = true;
    }
public:

    ShapeCircle() {
        x = 0;
        y = 0;
        r = 0;
        reg();
    }

    ShapeCircle(double _x, double _y, double _r) {
        reg();
        x = _x;
        y = _y;
        r = _r;
    }

    virtual void draw() {
        cout << "Cycle: " << x << " " << y << " " << r << endl;
    }

    virtual Shape* create() {
        return new ShapeCircle();
    }

    virtual void load(ifstream &file) {
        file >> x;
        file >> y;
        file >> r;
    }

    virtual ~ShapeCircle() {
    }
};

Shape* createSquareCallback() {
    return new ShapeSquare();
}

class ShapeSquare : public Shape {
private:
    double x, y, a;
    bool registered;

private:

    void reg() {
        if (!registered) {
            ShapeFactory::getInstance()->reg(2, createSquareCallback());
        }
        registered = true;
    }
public:

    ShapeSquare() {
        reg();
        x = 0;
        y = 0;
        a = 0;
    }

    ShapeSquare(double _x, double _y, double _a) {
        reg();
        x = _x;
        y = _y;
        a = _a;
    }

    virtual void draw() {
        cout << "Square: " << x << " " << y << " " << a << endl;
    }

    virtual Shape* create() {
        return new ShapeSquare();
    }

    virtual void load(ifstream &file) {
        file >> x;
        file >> y;
        file >> a;
    }

    virtual ~ShapeSquare() {
    }
};

class Drawing {
public:
    typedef vector<Shape *> Shapes;
private:
    Shapes shapes;
public:

    void addShape(Shape *shape) {
        shapes.push_back(shape);
    }

    void draw() {
        for (Shapes::iterator i = shapes.begin(); i != shapes.end(); ++i) {
            (*i)->draw();
        }
    }

    void load(const char *fileName) {
        ifstream file;
        file.open(fileName);
        if (!file.is_open()) {
            cout << endl << "Nemohu otevrit prikazovy soubor: " << fileName << endl;
            return;
        } else {
            string line;
            getline(file, line);
            if (file.fail()) {
                cout << endl << "Parsovani souboru se nepodarilo." << endl;
                return;
            }

            stringstream ss;
            ss.clear();
            ss.str(line);

            Shape* shape;
            int id;
            ss >> id;
            shape = ShapeFactory::getInstance()->create(id);
            shape->load(file);
            shapes.push_back(shape);
        }
    }
};

int main() {
    Drawing drawing;

    drawing.addShape(new ShapeCircle(1, 1, 2));
    drawing.addShape(new ShapeSquare(2, 2, 4));
    drawing.draw();
    // prints:	Circle: 1 1 2
    //		Square: 2 2 4
    drawing.load(DRAWING_FILE);
    drawing.draw();
    // prints:	Circle: 1 1 2
    // 		Square: 2 2 4
    //		Circle: 1 1 3
    //		Square: 3 3 4

    return 0;
}

