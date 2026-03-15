#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//Base Class
class Shape
{
public:
    virtual ~Shape() {} //Destructor
    virtual void draw() = 0;
    virtual void area() = 0;
    virtual void perimeter() = 0;
};

//Shape Classes
class Circle : public Shape
{
private:
    float r;

public:
    Circle(float r) : r(r) {}
    
    void draw() override
    {
        cout << "Drawing a circle" << endl;
    }
    
    void area() override
    {
        float a = 3.14 * r * r;
        cout << "The area of the circle is " << a << endl;
    }

    void perimeter() override
    {
        float p = 2 * 3.14 * r;
        cout << "The perimeter of the circle is " << p << endl;
    }
};

class Rectangle : public Shape
{
private:
    float l;
    float b;

public:
    Rectangle(float l, float b) : l(l), b(b) {}
    
    void draw() override
    {
        cout << "Drawing a rectangle" << endl;
    }
    
    void area() override
    {
        float a = l * b;
        cout << "The area of the rectangle is " << a << endl;
    }

    void perimeter() override
    {
        float p = 2 * (l + b);
        cout << "The perimeter of the rectangle is " << p << endl;
    }
};

class Triangle : public Shape
{
private:
    float a;
    float b;
    float c;

public:
    Triangle(float l, float b, float c) : a(l), b(b), c(c) {}
    
    void draw() override
    {
        cout << "Drawing a triangle" << endl;
    }
    
    void area() override
    {
        float s = (a + b + c) / 2.0;
        float ar = sqrt(s * (s - a) * (s - b) * (s - c));
        cout << "The area of the triangle is " << ar << endl;
    }

    void perimeter() override
    {
        cout << "The perimeter of the triangle is " << a + b + c << endl;
    }
};

//Factory Class
class ShapeFactory
{
public:
    static Shape *drawShape(string shape, float n1 = 0, float n2 = 0, float n3 = 0)
    {
        //converting string to lowercase to handle weird inputs
        transform(shape.begin(), shape.end(), shape.begin(), ::tolower);

        if (shape == "circle")
        {
            return new Circle(n1);
        }
        else if (shape == "rectangle")
        {
            return new Rectangle(n1, n2);
        }
        else if (shape == "triangle")
        {
            //checking valid triangle or not
            if ((n1 + n2 > n3) && (n2 + n3 > n1) && (n1 + n3 > n2))
            {
                return new Triangle(n1, n2, n3);
            }
            else
            {
                cout << "Invalid sides for triangle" << endl;
                return nullptr;
            }
        }

        cout << "Wrong shape entered. Please check." << endl;
        return nullptr;
    }
};

int main()
{
    //testing circle
    Shape *s1 = ShapeFactory::drawShape("circle", 5.0);
    if (s1)
    {
        s1->draw();
        s1->area();
        s1->perimeter();
        cout << endl;
    }

    //testing rectangle with messy case
    Shape *s2 = ShapeFactory::drawShape("ReCtAnGlE", 10.0, 4.0);
    if (s2)
    {
        s2->draw();
        s2->area();
        s2->perimeter();
        cout << endl;
    }

    //testing valid triangle
    Shape *s3 = ShapeFactory::drawShape("triangle", 3.0, 4.0, 5.0);
    if (s3)
    {
        s3->draw();
        s3->area();
        s3->perimeter();
        cout << endl;
    }

    //testing invalid shape edge case
    Shape *s4 = ShapeFactory::drawShape("hexagon", 10.0);

    delete s1;
    delete s2;
    delete s3;

    return 0;
}
