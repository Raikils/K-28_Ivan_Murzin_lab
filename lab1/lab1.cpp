#include <iostream>
#include <cmath>
#include <string>

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
friend class List;
private:
	point* begin;
	point* end;
	int n;
	class figure* next;
	class figure* prev;

public:
	figure() : begin{ nullptr }, end{ nullptr }, n{ 0 }, next{ nullptr }, prev{ nullptr } {}
	
	void set(int n, dot* arr) {
		clear();
		point* new_point;
		dot p;
		while (n) {
			p = *arr;
			point* new_point = new point{ {p.x,p.y} };
			if (begin == nullptr) {
				begin = end = new_point;
			}
			else {
				new_point->prev = end;
				end->next = new_point;
				end = new_point;
			}
			n--; arr++;
		}
	}
	
	void clear() {
		point* del, * cur = begin;
		while (cur) {
			del = cur;
			cur = cur->next;
			delete cur;
		}
		begin = end = nullptr;
		n = 0;
	}
	
	bool Isempty() {
		if (begin == end && begin == nullptr) return true;
		else return false;
	}
	
	void print() {
		point* cur = begin;
		cout << "{";
		while (cur) {
			cout << "(" << cur->value.x << "," << cur->value.y << ")";
			cur = cur->next;
		}
		cout << "}" << endl;
	}
	
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
		double s = 0;
		point* cur = begin;
		while (cur != end) {
			s += (cur->value.x + (cur->next)->value.x) * (cur->value.y - (cur->next)->value.y);
			cur = cur->next;
		}
		s += (cur->value.x + begin->value.x) * (cur->value.y - begin->value.y);
		s = 0.5 * fabs(s);
		return s;
	}

	bool CheckRegular() {
		if (!Isconvex()) return false;
		point* cur = begin;
		double p = sqrt((begin->value.x - end->value.x) * (begin->value.x - end->value.x) + (begin->value.y - end->value.y) * (begin->value.y - end->value.y));
		double t;
		while (cur->next) {
			t =sqrt((cur->value.x - (cur->next)->value.x) * (cur->value.x - (cur->next)->value.x) + (cur->value.y - (cur->next)->value.y) * (cur->value.y - (cur->next)->value.y));
			if (p != t) return false;
			cur = cur->next;
		}
		return true;
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
				if ((AB == BC && CD == DA) || (AB == DA && BC == CD)) cout << "It is deltoid";
				else if (((begin->value.x - (begin->next)->value.x) * ((end->prev)->value.y - end->value.y) == (begin->value.y - (begin->next)->value.y) * ((end->prev)->value.x - end->value.x)) || ((begin->value.x - end->value.x) * ((begin->next)->value.y - (end->prev)->value.y) == (begin->value.y - end->value.y) * ((begin->next)->value.x - (end->prev)->value.x))) {
					if (AB == CD || BD == DA) cout << "It is equilateral trapezoid";
					else if (AB * AB + BC * BC == AC * AC || DA * DA + AB * AB == BD * BD || BC * BC + CD * CD == BD * BD || CD * CD + DA * DA == AC * AC) cout << "It is rectangular trapezoid";
					else cout << "It is trapezoid";
				}
				else {
					cout << "It is arbitrary quadrangle";
				}
		}
		cout << endl;
	}

	void create() {
		clear();
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

	dot operator[](int index) {
		point* current = begin;
		dot o;
		int cur_index = 0;
		while (current) {
			if (cur_index == index) {
				{ o = current->value; return o; }
			}
			current = current->next;
			cur_index++;
		}
		//throw out_of_range{ "index=" + to_string(index) + " larger than list size=" + to_string(n) };
	}
};

class List {
private:
	figure* begin;
	figure* end;
	int _size;
public:
	List() : begin{ nullptr }, end{ nullptr }, _size{ 0 } {}

	void clear() {
		figure* del, * cur = begin;
		while (cur) {
			del = cur;
			cur = cur->next;
			delete cur;
		}
		begin = end = nullptr;
		_size = 0;
	}
	
	void del(figure* cur) {
		if (cur == begin) begin = cur->next;
		if (cur == end) end = cur->prev;
		if (cur->prev) (cur->prev)->next = cur->next;
		if (cur->next) (cur->next)->prev = cur->prev;
		delete cur;
		_size--;
	}
	
	void replece_prev(figure* cur1, figure* cur2) {
		if (cur2 == begin) begin = cur2->next;
		if (cur2 == end) end = cur2->prev;
		if (cur2->prev) (cur2->prev)->next = cur2->next;
		if (cur2->next) (cur2->next)->prev = cur2->prev;
		if (cur1 == begin) begin = cur2;
		cur2->prev = cur1->prev;
		cur2->next = cur1;
		if (cur1->prev) (cur1->prev)->next = cur2;
		cur1->prev = cur2;
	}

	void replece_next(figure* cur1, figure* cur2) {
		if (cur2 == begin) begin = cur2->next;
		if (cur2 == end) end = cur2->prev;
		if (cur2->prev) (cur2->prev)->next = cur2->next;
		if (cur2->next) (cur2->next)->prev = cur2->prev;
		if (cur1 == end) cur2 = end;
		cur2->prev = cur1;
		cur2->next = cur1->next;
		if (cur1->next) (cur1->next)->prev = cur2;
		cur1->next = cur2;
	}
	
	figure* get_begin() {
		return begin;
	}
	
	figure* get_end() {
		return end;
	}

	figure* Next(figure* cur) {
		return cur->next;
	}

	figure* Prev(figure* cur) {
		return cur->prev;
	}
	
	void set(int ind, figure s) {
		if (ind < _size) {
			figure* cur = begin;
			while (ind) { cur = cur->next; ind--; }
			cur->begin = s.begin;
			cur->end = s.end;
			cur->n = s.n;
		}
	}
	
	int size() {
		return _size;
	}
	
	figure operator[](int index) {
		figure* current = begin;
		figure x;
		int cur_index = 0;
		while (current) {
			if (cur_index == index) {
				{ x = *current; return x; }
			}
			current = current->next;
			cur_index++;
		}
		//throw out_of_range{ "index=" + to_string(index) + " larger than list size=" + to_string(n) };
	}

	void print() {
		figure* cur = begin;
		while (cur) {
			cur->print();
			cur = cur->next;
		}
	}

	void append(figure x) {
		figure* new_figure = new figure;
		new_figure->begin = x.begin;
		new_figure->end = x.end;
		new_figure->n = x.n;
		if (begin == nullptr) {
			begin = end = new_figure;
		}
		else {
			new_figure->prev = end;
			end->next = new_figure;
			end = new_figure;
		}
		_size++;
	}

	void swap(int f1, int f2) {
		if (f1 >= _size || f2 >= _size) cout << "Incorect input" << endl;
		else if (f1!=f2)
		{
			figure* cur1 = begin, * cur2 = begin, * t1, * t2;
			int i1 = 0, i2 = 0;
			while (i1 < f1) {
				cur1 = cur1->next;
				i1++;
			}
			while (i2 < f2) {
				cur2 = cur2->next;
				i2++;
			}
			if (cur1 == begin && cur2 == end) { begin = cur2; end = cur1; }
			else if (cur2 == begin && cur1 == end) { begin = cur1; end = cur2; }
			else if (cur1 == begin) begin = cur2;
			else if (cur1 == end) end = cur2;
			else if (cur2 == begin) begin = cur1;
			else if (cur2 == end) end = cur1;
			if (fabs(f1 - f2) != 1)
			{
				if (cur1->prev) (cur1->prev)->next = cur2;
				if (cur2->prev) (cur2->prev)->next = cur1;
				if (cur1->next) (cur1->next)->prev = cur2;
				if (cur2->next) (cur2->next)->prev = cur1;
				t1 = cur2->prev; t2 = cur2->next;
				cur2->prev = cur1->prev;
				cur2->next = cur1->next;
				cur1->prev = t1;
				cur1->next = t2;
			}
			else
			{
				if (f2 > f1) {
					if (cur1->prev) (cur1->prev)->next = cur2;
					if (cur2->next) (cur2->next)->prev = cur1;
					cur1->next = cur2->next;
					cur2->prev = cur1->prev;
					cur1->prev = cur2;
					cur2->next = cur1;
				}
				else {
					if (cur2->prev) (cur2->prev)->next = cur1;
					if (cur1->next) (cur1->next)->prev = cur2;
					cur2->next = cur1->next;
					cur1->prev = cur2->prev;
					cur2->prev = cur1;
					cur1->next = cur2;
				}
			}
		}
	}
};

void insert_sort(List& list, bool growth, int num_keys, int(*key)(figure, figure), ...);
void merge_sort(List& list, bool growth, int num_keys, int(*key)(figure, figure), ...);
void quick_sort(List& list, bool growth, int num_keys, int(*key)(figure, figure), ...);
void merge1(List& list, int l, int r, bool growth, int num_keys, int(**key)(figure, figure), ...);
int comparison(figure a, figure b, int num_keys, int(**key)(figure, figure));
void merge2(List& list, int l, int m, int r, bool growth, int num_keys, int(**key)(figure, figure), ...);
void quick(List& list, figure* l, figure* r, bool growth, int num_keys, int(**key)(figure, figure), ...);
int key1(figure a, figure b);
int key2(figure a, figure b);

int main() {
	return 0;
}

void insert_sort(List& list, bool growth, int num_keys, int(*key)(figure, figure), ...)
{
	int i=1, p, j;
	int(**k)(figure, figure) = &key;
	while (i<list.size()) {
		p = comparison(list[i - 1], list[i], num_keys, k);
		j = i;
		if (!growth) p *= -1;
		while (p == 1 && j) {
			list.swap(j - 1, j);
			j--;
			if (j>0) p = comparison(list[j - 1], list[j], num_keys, k);
			if (!growth) p *= -1;
		}
		i++;
	}
}

int comparison(figure a, figure b, int num_keys, int(**key)(figure, figure))
{
	int(**k)(figure, figure) = key;
	int p;
	while (num_keys) {
		p = (*k)(a, b);
		if (p == 1) return 1;
		else if (p == -1) return -1;
		k++; num_keys--;
	}
	return 0;
}

int key1(figure a, figure b)
{
	if (a.Isempty() && b.Isempty()) return 0;
	if (a.Isempty()) return -1;
	if (b.Isempty()) return 1;
	if (a[0].x > b[0].x) return 1;
	if (a[0].x == b[0].x) return 0;
	return -1;
}

int key2(figure a, figure b)
{
	return 0;
}

void merge_sort(List& list, bool growth, int num_keys, int(*key)(figure, figure), ...)
{
	int(**k)(figure, figure) = &key;
	merge1(list, 0, list.size() - 1, growth, num_keys, k);
}

void merge1(List& list, int l, int r, bool growth, int num_keys, int(**key)(figure, figure), ...)
{
	if (l < r) {
		int m = l + (r - l) / 2;
		merge1(list, l, m, growth, num_keys, key);
		merge1(list, m + 1, r, growth, num_keys, key);
		merge2(list, l, m, r, growth, num_keys, key);
	}
}

void merge2(List& list, int l, int m, int r, bool growth, int num_keys, int(**key)(figure, figure), ...)
{
	int(**ky)(figure, figure) = key;
	int i, j, k, p;
	int n1 = m - l + 1;
	int n2 = r - m;
	List L, R;
	for (i = 0; i < n1; i++)
	    L.append(list[l + i]);
	for (j = 0; j < n2; j++)
		R.append(list[m + 1 + j]);
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		p = comparison(L[i], R[i], num_keys, ky);
		if ((p < 1 && growth) || (p == 1 && !growth)) {
			list.set(k, L[i]);
			i++;
		}
		else {
			list.set(k, R[j]);
			j++;
		}
		k++;
	}
	while (i < n1) {
		list.set(k, L[i]);
		i++;
		k++;
	}
	while (j < n2) {
		list.set(k, R[j]);
		j++;
		k++;
	}
}

void quick_sort(List& list, bool growth, int num_keys, int(*key)(figure, figure), ...)
{
	int(**k)(figure, figure) = &key;
	quick(list, list.get_begin(), list.get_end(), growth, num_keys, k);
}

void quick(List& list, figure* l, figure* r, bool growth, int num_keys, int(**key)(figure, figure), ...)
{
	bool q = true;
	int p;
	figure* cur = l;
	figure* t, * l1 = l;
	while (cur != r) {
		p = comparison(*l, *cur, num_keys, key);
		if ((p == 1 && growth) || (p == -1 && !growth)) {
			t = list.Next(cur);
			if (q) { l1 = cur; q = false; }
			list.replece_prev(l, cur);
			cur = t;
		}
		else cur = list.Next(cur);
	}
	if (l != r) {
		p = comparison(*l, *cur, num_keys, key);
		if ((p == 1 && growth) || (p == -1 && !growth)) {
			if (q) { l1 = cur; q = false; }
			r = list.Prev(cur);
			list.replece_prev(l, cur);
		}
	}
	if (l != l1) if (list.Prev(l) != nullptr) if (list.Prev(list.Prev(l)) != nullptr) quick(list, l1, list.Prev(l), growth, num_keys, key);
	if (l != r) if (list.Next(l) != nullptr) if (list.Next(list.Next(l)) != nullptr) quick(list, list.Next(l), r, growth, num_keys, key);
}