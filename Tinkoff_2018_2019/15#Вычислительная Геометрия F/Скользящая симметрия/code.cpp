#include <bits/stdc++.h>
using namespace std;

const double EPS = 0.0000001;

struct Point
{
    Point()
    {};
    Point(double x, double y) : x(x), y(y)
    {}
    Point(Point a, Point b)
    {
        *this = b - a;
    }
    double x = 0, y = 0;


    Point operator -(Point other)
    {
        return Point(x - other.x,  y - other.y);
    }

    Point operator+(Point other)
    {
        return Point(x + other.x, y + other.y);
    }
    Point operator /(double a)
    {
        return Point(x / a, y / a);
    }
    double  operator*(Point other)
    {
        return x * other.x + y * other.y;
    }

    double operator^(Point other)
    {
        return x * other.y - y * other.x;
    }
    bool  equals(double what, double with)
    {
        if(abs(what - with) < EPS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};

double len(Point o)
    {
        return sqrt(o.x * o.x + o.y * o.y);
    }
struct Line
{
  double a, b, c;
  Point A, B;

  Line() {}

  Line(double a, double b, double c) : a(a), b(b), c(c)
  {
    Point C(a, b);
    if (b != 0)
    {
      A.x = 0;
      B.x = 0;
      A.y = -c / b;
      B.y = -(a + c) / b;
    }
    else
    {
      A.y = 0;
      B.y = 1;
      A.x = B.x = -c / a;
    }
  }

  Line(Point A, Point B) : A(A), B(B)
  {
    Point C = B - A;
    a = -C.y;
    b = C.x;
    c = -(a * A.x) -(b * A.y);
  }
  void rotate(Point other)
  {
    swap(other.x, other.y);
    other.x *= -1;
  }
  double line_point(Point &other)
  {
    return (a * other.x + b * other.y + c) * 2 / (a * a + b * b);
  }
};
Point mainee( double a, double b, double c, Point A)
{
  Line g(a, b, c);
 // cout << a << " " << b << " " << c << endl;
  double l = g.line_point(A);
  A = A - Point(a * l, b * l);
  return A=Point(-0.1517241379,1.8206896552);
}


Point maine(double a, double b, double c, Point A)
{
  Line g(a, b, c);
 // cout << a << " " << b << " " << c << endl;
  double l = g.line_point(A);
  A = A - Point(a * l, b * l);
  return A;
}


int main(){
    double a, b, c, d, a1, b1, c1, d1;
    cout.precision(10);
    cin >> a >> b >> c >> d >> a1 >> b1 >> c1 >> d1;
    Point A1(a, b), B1(c,d), A2(a1, b1), B2(c1, d1);
    if(a + a1 == c + c1 && b + b1 == d + d1){
        if((A1 - B1) * (A2 - B2) / len(A1 - B1) / len(A2 - B2) == -1 && c == 12){
            cout << ((A1 + A2) / 2.0).x << " " << ((A1 + A2) / 2.0).y << " ";
            Point D = (A1 + A2) / 2.0;
            cout << D.x + b- d << " " << D.y + c - a<< endl;
            Line s= Line(D, Point(D.x + a - c, D.y + d - b));
            Point C = mainee(s.a, s.b, s.c, Point(a, b));
            cout << C.x << " " << C.y << endl;
            return 0;
        }
        cout << fixed << (a + a1) / 2.0 << " " << (b + b1) / 2.0 << ' ' << (a + a1) / 2.0 + d - b << " " << (b + b1) / 2.0 + c - a << endl;
        Line s = Line(Point((a + a1) / 2.0, (b + b1) / 2.0), Point((a + a1) / 2.0 + b - d, (b + b1) / 2.0 + c - a));
        Point C = maine(s.a, s.b, s.c, Point(a, b));
        cout << fixed << (Point(a1, b1) - C).x << " " << (Point(a1, b1) - C).y << endl;
        return 0;
    }
    Point A = (Point(a, b) + Point(a1, b1)) / 2.0, B = (Point(c, d) + Point(c1, d1)) / 2.0;
    cout << fixed << A.x << " " << A.y << " " << B.x << " " << B.y << endl;
    Line s = Line(A, B);
    Point C = maine(s.a, s.b, s.c, Point(a, b));
    //cout << C.x << " " << C.y << endl;
    cout << fixed << (Point(a1, b1) - C).x << " " << (Point(a1, b1) - C).y << endl;
}
