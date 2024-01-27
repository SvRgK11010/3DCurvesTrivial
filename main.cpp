#include "objects.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <variant>

using namespace std;

int main() {
	using namespace obj;

	const int MAX_NUM = 20; //
	int rand_num = 0;
	double rand_radius = 0;
	vector<shared_ptr<Object>> obj;
	obj.reserve(MAX_NUM);
	int first = 1; //����������� ��������, 1 - ����, 2 - �����, 3 - �������
	int last = 3; //

	for (int i = 0; i < MAX_NUM; i++) {
		rand_num = first + rand() % last;
		rand_radius = first + rand() % MAX_NUM;
		if (rand_num == 1) {
			obj.emplace_back(make_shared<Circle>(Circle().SetRadius(rand_radius)));
			continue;
		}
		else if (rand_num == 2) {
			obj.emplace_back(make_shared<Ellipse>(Ellipse().SetRadiuses(rand_radius, rand_radius + rand_num)));
			continue;
		}
		else if (rand_num == 3) {
			obj.emplace_back(make_shared<Helix>(Helix().SetRadius(rand_radius).SetStep(rand_radius + rand_num)));
			continue;
		}
	}
	double t = M_PI / 4;
	for (auto& o : obj) {
		cout << "Type: " << o->GetType() << endl;
		cout << "Point: " << "x = " << o->GetPoint(t).x << ", "
			<< "y = " << o->GetPoint(t).y << ", "
			<< "z = " << o->GetPoint(t).z << endl;
		cout << "Derivative of the point: " << "x = " << o->Getderivative(t).x << ", "
			<< "y = " << o->Getderivative(t).y << ", "
			<< "z = " << o->Getderivative(t).z << endl;
	}
	vector<shared_ptr<Circle>> circles;
	circles.reserve(MAX_NUM);
	for (auto& o : obj) {
		if (o->GetType() == "Circle") {
			auto circle = dynamic_pointer_cast<Circle>(o);
			circles.push_back(move(circle));
		}
	}

	sort(circles.begin(), circles.end(), [](auto& lhs, auto& rhs) {return lhs->GetRadius() < rhs->GetRadius(); });

	
	double sum = 0.0;
	for (auto& c : circles) {
		sum += c->GetRadius();
	}
	cout << "Cumulative sum of circle radii: " << sum << endl;
}