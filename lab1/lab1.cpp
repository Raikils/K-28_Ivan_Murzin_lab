#include <iostream>
#include <cmath>

using namespace std;

struct dot {
	int x;
	int y;
};

struct point {
	dot value;
	point* prev;
	point* next;
	point(dot value, point* prev = nullptr, point* next = nullptr) : value{ value }, prev{ prev }, next{ next } {}
};

class figure {
private:
	point* begin;
	point* end;
	int n;

	double AreaTriangle(dot a1, dot a2, dot a3) {
		double a, b, c, p;
		a = sqrt((a1.x - a2.x) * (a1.x - a2.x) + (a1.y - a2.y) * (a1.y - a2.y));
		b = sqrt((a2.x - a3.x) * (a2.x - a3.x) + (a2.y - a3.y) * (a2.y - a3.y));
		c = sqrt((a3.x - a1.x) * (a3.x - a1.x) + (a3.y - a1.y) * (a3.y - a1.y));
		p = (a + b + c) * 0.5;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

public:
	figure() : begin{ nullptr }, end{ nullptr }, n{ 0 } {}

	int size() {
		return n;
	}

	double perimeter() {
		if (n < 2) return 0;
		point* cur = begin;
		double p = sqrt((begin->value.x - end->value.x) * (begin->value.x - end->value.x) + (begin->value.y - end->value.y) * (begin->value.y - end->value.y));
		while (cur->next) {
			p = p + sqrt((cur->value.x - (cur->next)->value.x) * (cur->value.x - (cur->next)->value.x) + (cur->value.y - (cur->next)->value.y) * (cur->value.y - (cur->next)->value.y));
			cur = cur->next;
		}
		return p;
	}

	bool Isconvex() {
		if (n < 3) return true;
		bool p;
		point* cur = begin, *t;
		if (((cur->next)->value.x - cur->value.x) * (cur->value.y - end->value.y) - ((cur->next)->value.y - cur->value.y) * (cur->value.x - end->value.x) > 0) p = 1; else p = 0;
		t = cur;
		cur = cur->next;
		while (cur->next) {
			if (((cur->next)->value.x - cur->value.x) * (cur->value.y - t->value.y) - ((cur->next)->value.y - cur->value.y) * (cur->value.x - t->value.x) > 0)
				if (p) { t = cur; cur = cur->next; } else return false; else if (!p) { t = cur; cur = cur->next; } else return false;
		}
		return true;
	}

	double area() {
		if (n < 3) return 0;
		if (n == 3) return AreaTriangle(begin->value, (begin->next)->value, end->value);
		point* cur;
		double s = 0;
		if (Isconvex()) {
			cur = begin->next;
			while (cur->next) {
				s += AreaTriangle(begin->value, cur->value, (cur->next)->value);
				cur = cur->next;
			}
			return s;
		}
		return 0;
	}

	void CheckTriangle() {
		if (n != 3) cout << "It is not triangle" << endl;
		else
		{
			double a, b, c; 
			a = sqrt((begin->value.x - (begin->next)->value.x) * (begin->value.x - (begin->next)->value.x) + (begin->value.y - (begin->next)->value.y) * (begin->value.y - (begin->next)->value.y));
			b = sqrt(((begin->next)->value.x - end->value.x) * ((begin->next)->value.x - end->value.x) + ((begin->next)->value.y - end->value.y) * ((begin->next)->value.y - end->value.y));
			c = sqrt((end->value.x - begin->value.x) * (end->value.x - begin->value.x) + (end->value.y - begin->value.y) * (end->value.y - begin->value.y));
			if (a == b && a == c) cout << "It is equilateral triangle" << endl;
			else if (a == b || a == c || b == c) if (a * a == b * b + c * c || b * b == a * a + c * c || c * c == a * a + b * b) cout << "It is isosceles and right triangle" << endl; else cout << "It is isosceles triangle" << endl;
			else if (a * a == b * b + c * c || b * b == a * a + c * c || c * c == a * a + b * b) cout << "It is right triangle" << endl;
			else cout << "It is simple triangle" << endl;

		}
	}

	void CheckQuadrangle() {
		if (n != 4) cout << "It is not quadrangle" << endl;
		else
		{
			double AB, BC, CD, DA, AC, BD;
			AB = sqrt((begin->value.x - (begin->next)->value.x) * (begin->value.x - (begin->next)->value.x) + (begin->value.y - (begin->next)->value.y) * (begin->value.y - (begin->next)->value.y));
			BC = sqrt(((end->prev)->value.x - (begin->next)->value.x) * ((end->prev)->value.x - (begin->next)->value.x) + ((end->prev)->value.y - (begin->next)->value.y) * ((end->prev)->value.y - (begin->next)->value.y));
			CD = sqrt(((end->prev)->value.x - end->value.x) * ((end->prev)->value.x - end->value.x) + ((end->prev)->value.y - end->value.y) * ((end->prev)->value.y - end->value.y));
			DA = sqrt((begin->value.x - end->value.x) * (begin->value.x - end->value.x) + (begin->value.y - end->value.y) * (begin->value.y - end->value.y));
			AC = sqrt((begin->value.x - (end->prev)->value.x) * (begin->value.x - (end->prev)->value.x) + (begin->value.y - (end->prev)->value.y) * (begin->value.y - (end->prev)->value.y));
			BD = sqrt((end->value.x - (begin->next)->value.x) * (end->value.x - (begin->next)->value.x) + (end->value.y - (begin->next)->value.y) * (end->value.y - (begin->next)->value.y));
			if (AB == CD && BC == DA) {
				if (AB == BC) {
					if (AC == BD) {
						cout << "It is square";
					}
					else {
						cout << "It is rhombus";
					}
				}
				else
					if (AC == BD) {
						cout << "It is rectangle";
					}
					else {
						cout << "It is parallelogram";
					}
			}
			else
				if (((begin->value.x - (begin->next)->value.x) * ((end->prev)->value.y - end->value.y) == (begin->value.y - (begin->next)->value.y) * ((end->prev)->value.x - end->value.x)) || ((begin->value.x - end->value.x) * ((begin->next)->value.y - (end->prev)->value.y) == (begin->value.y - end->value.y) * ((begin->next)->value.x - (end->prev)->value.x))) {
					cout << "It is trapezoid";
				}
				else {
					cout << "It is arbitrary quadrangle";
				}
		}
	}

	void create() {
		dot k;
		cout << "Enter n" << endl;
		cin >> n;
		for (auto i = 0; i < n; i++) {
			cout << "Enter x and y" << endl;
			cin >> k.x >> k.y;
			point* new_point = new point{ {k.x,k.y} };
			if (begin == nullptr) {
				begin = end = new_point;
			}
			else {
				new_point->prev = end;
				end->next = new_point;
				end = new_point;
			}
		}
	}

	point* operator[](int index) {
		point* current = begin;
		int cur_index = 0;
		while (current) {
			if (cur_index == index) {
				return current;
			}
			current = current->next;
			cur_index++;
		}
		//throw out_of_range{ "index=" + to_string(index) + " larger than list size=" + to_string(n) };
	}
};

int main() {
	figure a;
	a.create();
	a.CheckQuadrangle();
	return 0;
}
