
#include <stdio.h>
#include "PhysicsGeneralMethods.h"
#define M_PI 3.14159265358979323846


bool Physics::IsOverlapping(BoxCollider c1, BoxCollider c2)
{
	//printf("\nstat\n");
	XMVECTOR points1[4], points2[4];
	points1[0] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points1[1] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points1[2] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points1[3] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points2[0] = XMVectorSet(XMVectorGetX(c2.GetCenter()) + XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) + XMVectorGetY(c2.GetSize()) / 2, 0, 0);
	points2[1] = XMVectorSet(XMVectorGetX(c2.GetCenter()) + XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) - XMVectorGetY(c2.GetSize()) / 2, 0, 0);
	points2[2] = XMVectorSet(XMVectorGetX(c2.GetCenter()) - XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) - XMVectorGetY(c2.GetSize()) / 2, 0, 0);
	points2[3] = XMVectorSet(XMVectorGetX(c2.GetCenter()) - XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) + XMVectorGetY(c2.GetSize()) / 2, 0, 0);

	for (int i = 0; i < 4; i++) {
		points1[i] -= c1.GetCenter();
		points2[i] -= c2.GetCenter();
		points1[i] = XMVector2Transform(points1[i], c1.GetRotateMatrix());
		points2[i] = XMVector2Transform(points2[i], c2.GetRotateMatrix());
		points1[i] += c1.GetCenter();
		points2[i] += c2.GetCenter();
		XMVECTOR or1 = c1.GetOffset();
		XMVECTOR or2 = c2.GetOffset();
		or1 = XMVector2Transform(or1, c1.GetRotateMatrix());
		or2 = XMVector2Transform(or2, c2.GetRotateMatrix());

		points1[i] += or1;
		//printf("\nPoint1 %d:%f,%f\n", i, XMVectorGetX(points1[i]), XMVectorGetY(points1[i]));
		points2[i] += or2;
		//printf("\nPoint2 %d:%f,%f\n", i, XMVectorGetX(points2[i]), XMVectorGetY(points2[i]));
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			XMFLOAT2 p1, p2, p3, p4;
			int n, m;
			if (i < 3) {
				n = i + 1;
			}
			else {
				n = 0;
			}
			if (j < 3) {
				m = j + 1;
			}
			else {
				m = 0;
			}
			p1.x = XMVectorGetX(points1[i]);
			p1.y = XMVectorGetY(points1[i]);
			p2.x = XMVectorGetX(points1[n]);
			p2.y = XMVectorGetY(points1[n]);
			p3.x = XMVectorGetX(points2[j]);
			p3.y = XMVectorGetY(points2[j]);
			p4.x = XMVectorGetX(points2[m]);
			p4.y = XMVectorGetY(points2[m]);
			bool isIntersecting;
			XMFLOAT2 result;
			isIntersecting = IsTwoLineIntersecting(p1, p2, p3, p4, result);
			if (isIntersecting) {
				//printf("\nOrigin1:%f,%f Origin2:%f,%f Origin3:%f,%f Origin4:%f,%f Point:%f,%f", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, result.x, result.y);
				return true;
			}
		}
	}
	return false;
}

bool Physics::IsOverlapping(BoxCollider c1, CircleCollider c2)
{
	XMVECTOR points[4];
	points[0] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points[1] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points[2] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points[3] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	for (int i = 0; i < 4; i++) {
		points[i] -= c1.GetCenter();
		points[i] = XMVector2Transform(points[i], c1.GetRotateMatrix());
		points[i] += c1.GetCenter();
		XMVECTOR or1 = c1.GetOffset();
		or1 = XMVector2Transform(or1, c1.GetRotateMatrix());
		points[i] += or1;
		//printf("\nPoint%d:%f,%f\n", i, XMVectorGetX(points[i]), XMVectorGetY(points[i]));
	}
	XMVECTOR or2 = c2.GetOffset();
	or2 = XMVector2Transform(or2, c2.GetRotateMatrix());
	for (int i = 0; i < 4; i++) {
		if (i < 3) {
			float distance = PointToLineDistance(XMVectorGetX(c2.GetCenter()) + XMVectorGetX(or2), XMVectorGetY(c2.GetCenter()) + XMVectorGetY(or2), XMVectorGetX(points[i]), XMVectorGetY(points[i]), XMVectorGetX(points[i + 1]), XMVectorGetY(points[i + 1]));
			//printf("\nDistance:%f\n", distance);
			if (distance <= c2.GetRadius()) {
				return true;
			}
		}
		else {
			float distance = PointToLineDistance(XMVectorGetX(c2.GetCenter()) + XMVectorGetX(or2), XMVectorGetY(c2.GetCenter()) + XMVectorGetY(or2), XMVectorGetX(points[i]), XMVectorGetY(points[i]), XMVectorGetX(points[0]), XMVectorGetY(points[0]));
			//printf("\nDistance:%f\n", distance);
			if (distance <= c2.GetRadius()) {
				return true;
			}
		}
	}
	return false;
}

bool Physics::IsOverlapping(CircleCollider c1, CircleCollider c2)
{
	XMVECTOR or1 = c1.GetOffset();
	XMVECTOR or2 = c2.GetOffset();
	or1 = XMVector2Transform(or1, c1.GetRotateMatrix());
	or2 = XMVector2Transform(or2, c2.GetRotateMatrix());
	float distance = PointToPointDistance(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(or1), XMVectorGetY(c1.GetCenter()) + XMVectorGetY(or1), XMVectorGetX(c2.GetCenter()) + XMVectorGetX(or2), XMVectorGetY(c2.GetCenter()) + XMVectorGetY(or2));

	if (distance <= c1.GetRadius() + c2.GetRadius()) {
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(BoxCollider c1, BoxCollider c2, XMVECTOR& result)
{
	XMVECTOR points1[4], points2[4];
	points1[0] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points1[1] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points1[2] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points1[3] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points2[0] = XMVectorSet(XMVectorGetX(c2.GetCenter()) + XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) + XMVectorGetY(c2.GetSize()) / 2, 0, 0);
	points2[1] = XMVectorSet(XMVectorGetX(c2.GetCenter()) + XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) - XMVectorGetY(c2.GetSize()) / 2, 0, 0);
	points2[2] = XMVectorSet(XMVectorGetX(c2.GetCenter()) - XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) - XMVectorGetY(c2.GetSize()) / 2, 0, 0);
	points2[3] = XMVectorSet(XMVectorGetX(c2.GetCenter()) - XMVectorGetX(c2.GetSize()) / 2, XMVectorGetY(c2.GetCenter()) + XMVectorGetY(c2.GetSize()) / 2, 0, 0);

	for (int i = 0; i < 4; i++) {
		points1[i] -= c1.GetCenter();
		points2[i] -= c2.GetCenter();
		points1[i] = XMVector2Transform(points1[i], c1.GetRotateMatrix());
		points2[i] = XMVector2Transform(points2[i], c2.GetRotateMatrix());
		points1[i] += c1.GetCenter();
		points2[i] += c2.GetCenter();
		XMVECTOR or1 = c1.GetOffset();
		XMVECTOR or2 = c2.GetOffset();
		or1 = XMVector2Transform(or1, c1.GetRotateMatrix());
		or2 = XMVector2Transform(or2, c2.GetRotateMatrix());

		points1[i] += or1;
		points2[i] += or2;
	}
	vector<XMFLOAT2> ress;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			XMFLOAT2 p1, p2, p3, p4;
			int n, m;
			if (i < 3) {
				n = i + 1;
			}
			else {
				n = 0;
			}
			if (j < 3) {
				m = j + 1;
			}
			else {
				m = 0;
			}
			p1.x = XMVectorGetX(points1[i]);
			p1.y = XMVectorGetY(points1[i]);
			p2.x = XMVectorGetX(points1[n]);
			p2.y = XMVectorGetY(points1[n]);
			p3.x = XMVectorGetX(points2[j]);
			p3.y = XMVectorGetY(points2[j]);
			p4.x = XMVectorGetX(points2[m]);
			p4.y = XMVectorGetY(points2[m]);
			bool isIntersecting;
			XMFLOAT2 r;
			isIntersecting = IsTwoLineIntersecting(p1, p2, p3, p4, r);
			if (isIntersecting) {
				flag = true;
				ress.push_back(r);
			}
		}
	}
	if (flag) {
		XMFLOAT2 r;
		r.x = 0;
		r.y = 0;
		for (int i = 0; i < ress.size(); i++) {
			r.x += ress[i].x;
			r.y += ress[i].y;
		}
		r.x /= ress.size();
		r.y /= ress.size();
		result = XMVectorSet(r.x, r.y, 0, 0);
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(BoxCollider c1, CircleCollider c2, XMVECTOR& result)
{
	XMVECTOR points[4];
	points[0] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points[1] = XMVectorSet(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points[2] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) - XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	points[3] = XMVectorSet(XMVectorGetX(c1.GetCenter()) - XMVectorGetX(c1.GetSize()) / 2, XMVectorGetY(c1.GetCenter()) + XMVectorGetY(c1.GetSize()) / 2, 0, 0);
	for (int i = 0; i < 4; i++) {
		points[i] -= c1.GetCenter();
		points[i] = XMVector2Transform(points[i], c1.GetRotateMatrix());
		points[i] += c1.GetCenter();
		XMVECTOR or1 = c1.GetOffset();
		or1 = XMVector2Transform(or1, c1.GetRotateMatrix());
		points[i] += or1;
		//printf("\nPoint%d:%f,%f\n", i, XMVectorGetX(points[i]), XMVectorGetY(points[i]));
	}
	XMVECTOR or2 = c2.GetOffset();
	or2 = XMVector2Transform(or2, c2.GetRotateMatrix());
	//printf("\nPoint:%f,%f\n", XMVectorGetX(c2.GetCenter()), XMVectorGetY(c2.GetCenter()));

	vector<XMFLOAT2> ress;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		if (i < 3) {
			XMFLOAT2 r1, r2;
			int temp = IsLineCircleIntersecting(XMFLOAT2(XMVectorGetX(c2.GetCenter()), XMVectorGetY(c2.GetCenter())), c2.GetRadius(), XMFLOAT2(XMVectorGetX(points[i]), XMVectorGetY(points[i])), XMFLOAT2(XMVectorGetX(points[i + 1]), XMVectorGetY(points[i + 1])), r1, r2);
			if (temp == 1) {
				ress.push_back(r1);
				flag = true;
			}
			else if (temp == 2) {
				ress.push_back(r1);
				ress.push_back(r2);
				flag = true;
			}
		}
		else {
			XMFLOAT2 r1, r2;
			int temp = IsLineCircleIntersecting(XMFLOAT2(XMVectorGetX(c2.GetCenter()), XMVectorGetY(c2.GetCenter())), c2.GetRadius(), XMFLOAT2(XMVectorGetX(points[i]), XMVectorGetY(points[i])), XMFLOAT2(XMVectorGetX(points[0]), XMVectorGetY(points[0])), r1, r2);
			if (temp == 1) {
				ress.push_back(r1);
				flag = true;
			}
			else if (temp == 2) {

				ress.push_back(r1);
				ress.push_back(r2);
				flag = true;
			}
		}
	}
	if (flag) {
		XMFLOAT2 r;
		r.x = 0;
		r.y = 0;
		for (int i = 0; i < ress.size(); i++) {
			r.x += ress[i].x;
			r.y += ress[i].y;
			//printf("\nPoint:%f,%f\n", ress[i].x, ress[i].y);
		}
		r.x /= ress.size();
		r.y /= ress.size();
		result = XMVectorSet(r.x, r.y, 0, 0);

		//printf("\nPoint:%f,%f\n", XMVectorGetX(result), XMVectorGetY(result));
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(CircleCollider c1, CircleCollider c2, XMVECTOR& result)
{
	XMVECTOR or1 = c1.GetOffset();
	XMVECTOR or2 = c2.GetOffset();
	or1 = XMVector2Transform(or1, c1.GetRotateMatrix());
	or2 = XMVector2Transform(or2, c2.GetRotateMatrix());
	float distance = PointToPointDistance(XMVectorGetX(c1.GetCenter()) + XMVectorGetX(or1), XMVectorGetY(c1.GetCenter()) + XMVectorGetY(or1), XMVectorGetX(c2.GetCenter()) + XMVectorGetX(or2), XMVectorGetY(c2.GetCenter()) + XMVectorGetY(or2));

	if (distance <= c1.GetRadius() + c2.GetRadius()) {
		float r1 = c1.GetRadius() / (c1.GetRadius() + c2.GetRadius());
		float r2 = c2.GetRadius() / (c1.GetRadius() + c2.GetRadius());
		result = r2 * (c1.GetCenter() + or1) + r1 * (c2.GetCenter() + or2);
		//printf("\nPoint:%f,%f\n", XMVectorGetX(result), XMVectorGetY(result));
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsTwoLineIntersecting(XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2 point3, XMFLOAT2 point4)
{
	bool isPerp1 = false, isPerp2 = false;
	double k1, b1, k2, b2;
	if (point2.x != point1.x) {
		k1 = (point2.y - point1.y) / (point2.x - point1.x);
		b1 = point1.y - k1 * point1.x;
	}
	else {
		isPerp1 = true;
	}
	if (point4.x != point3.x) {
		k2 = (point4.y - point3.y) / (point4.x - point3.x);
		b2 = point3.y - k2 * point3.x;
	}
	else {
		isPerp2 = true;
	}
	if (!isPerp1 && !isPerp2) {
		if (k1 == k2) {
			if (b1 == b2) {
				if (IsMiddleValuesOverlapping(point1.x, point2.x, point3.x, point4.x)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		float px = (b2 - b1) / (k1 - k2);
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			return true;
		}
		else {
			return false;
		}
		return true;
	}
	else if (isPerp1 && isPerp2) {
		if (point1.x == point3.x) {
			if (IsMiddleValuesOverlapping(point1.y, point2.y, point3.y, point4.y)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (isPerp1 && !isPerp2) {
		float px = point1.x;
		float py = k2 * px + b2;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (!isPerp1 && isPerp2) {
		float px = point3.x;
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool Physics::IsTwoLineIntersecting(XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2 point3, XMFLOAT2 point4, XMFLOAT2& result)
{
	bool isPerp1 = false, isPerp2 = false;
	double k1, b1, k2, b2;
	if (point2.x != point1.x) {
		k1 = (point2.y - point1.y) / (point2.x - point1.x);
		b1 = point1.y - k1 * point1.x;
	}
	else {
		isPerp1 = true;
	}
	if (point4.x != point3.x) {
		k2 = (point4.y - point3.y) / (point4.x - point3.x);
		b2 = point3.y - k2 * point3.x;
	}
	else {
		isPerp2 = true;
	}
	if (!isPerp1 && !isPerp2) {
		if (k1 == k2) {
			if (b1 == b2) {
				if (IsMiddleValuesOverlapping(point1.x, point2.x, point3.x, point4.x)) {
					result = GetMiddlePointOfTwoMiddlePoints(point1, point2, point3, point4);
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		float px = (b2 - b1) / (k1 - k2);
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
		return true;
	}
	else if (isPerp1 && isPerp2) {
		if (point1.x == point3.x) {
			if (IsMiddleValuesOverlapping(point1.y, point2.y, point3.y, point4.y)) {
				result = GetMiddlePointOfTwoMiddlePoints(point1, point2, point3, point4);
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (isPerp1 && !isPerp2) {
		float px = point1.x;
		float py = k2 * px + b2;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	else if (!isPerp1 && isPerp2) {
		float px = point3.x;
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool Physics::IsRayLineIntersecting(Ray ray, XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2& result)
{
	bool isPerp1 = false, isPerp2 = false;
	double k1, b1, k2, b2;
	XMFLOAT2 point3 = XMFLOAT2(XMVectorGetX(ray.point), XMVectorGetY(ray.point));
	XMFLOAT2 point4 = XMFLOAT2(XMVectorGetX(ray.point) + XMVectorGetX(ray.direction), XMVectorGetY(ray.point) + XMVectorGetY(ray.direction));
	if (point2.x != point1.x) {
		k1 = (point2.y - point1.y) / (point2.x - point1.x);
		b1 = point1.y - k1 * point1.x;
	}
	else {
		isPerp1 = true;
	}
	if (point4.x != point3.x) {
		k2 = (point4.y - point3.y) / (point4.x - point3.x);
		b2 = point3.y - k2 * point3.x;
	}
	else {
		isPerp2 = true;
	}
	if (!isPerp1 && !isPerp2) {
		if (k1 == k2) {
			if (b1 == b2) {
				if (IsMiddleValuesOverlapping(point1.x, point2.x, point3.x, point4.x)) {
					result = GetMiddlePointOfTwoMiddlePoints(point1, point2, point3, point4);
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		float px = (b2 - b1) / (k1 - k2);
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsInDirectionOfTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsInDirectionOfTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
		return true;
	}
	else if (isPerp1 && isPerp2) {
		if (point1.x == point3.x) {
			if (point4.y - point3.y > 0) {
				if (point1.y > point3.y && point2.y > point3.y) {
					if (point1.y > point2.y) {
						result = point2;
					}
					else {
						result = point1;
					}
					return true;
				}
				else if (point1.y > point3.y) {
					result = point1;
					return true;
				}
				else if (point2.y > point3.y) {
					result = point2;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (point1.y < point3.y && point2.y < point3.y) {
					if (point1.y < point2.y) {
						result = point2;
					}
					else {
						result = point1;
					}
					return true;
				}
				else if (point1.y < point3.y) {
					result = point1;
					return true;
				}
				else if (point2.y < point3.y) {
					result = point2;
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else if (isPerp1 && !isPerp2) {
		float px = point1.x;
		float py = k2 * px + b2;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsInDirectionOfTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsInDirectionOfTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	else if (!isPerp1 && isPerp2) {
		float px = point3.x;
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsInDirectionOfTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsInDirectionOfTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

int Physics::IsLineCircleIntersecting(XMFLOAT2 point, float radius, XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2& result1, XMFLOAT2& result2)
{
	if (PointToLineDistance(point.x, point.y, point1.x, point1.y, point2.x, point2.y) > radius) {
		return 0;
	}
	float a, b, c, n, u1, u2;
	a = (point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y);
	b = 2 * ((point2.x - point1.x) * (point1.x - point.x) + (point2.y - point1.y) * (point1.y - point.y));
	c = point.x * point.x + point.y * point.y + point1.x * point1.x + point1.y * point1.y - 2 * (point.x * point1.x + point.y * point1.y) - radius * radius;
	n = b * b - 4 * a * c;
	if (n < 0) {
		return 0;
	}
	else if (n == 0) {
		u1 = (-b + sqrtf(n)) / (2 * a);
		if (u1 > 0 && u1 < 1) {

			result1.x = point1.x + u1 * (point2.x - point1.x);
			result1.y = point1.y + u1 * (point2.y - point1.y);
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		u1 = (-b + sqrtf(n)) / (2 * a);
		u2 = (-b - sqrtf(n)) / (2 * a);

		if (u1 > 0 && u1 < 1 && u2 >0 && u2 < 1) {
			result1.x = point1.x + u1 * (point2.x - point1.x);
			result1.y = point1.y + u1 * (point2.y - point1.y);
			//printf("\nPoint:%f,%f\n", result1.x, result1.y);


			result2.x = point1.x + u2 * (point2.x - point1.x);
			result2.y = point1.y + u2 * (point2.y - point1.y);
			//printf("\nPoint:%f,%f\n", result2.x, result2.y);


			return 2;
		}
		else if (u1 > 0 && u1 < 1) {
			result1.x = point1.x + u1 * (point2.x - point1.x);
			result1.y = point1.y + u1 * (point2.y - point1.y);
			return 1;
		}
		else if (u2 > 0 && u2 < 1) {
			result1.x = point1.x + u2 * (point2.x - point1.x);
			result1.y = point1.y + u2 * (point2.y - point1.y);
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

bool Physics::IsRayCircleIntersecting(XMFLOAT2 point, float radius, Ray ray, XMFLOAT2& result)
{
	XMFLOAT2 point1, point2;
	point1.x = XMVectorGetX(ray.point);
	point1.y = XMVectorGetY(ray.point);
	point2.x = XMVectorGetX(ray.point) + XMVectorGetX(ray.direction);
	point2.y = XMVectorGetY(ray.point) + XMVectorGetY(ray.direction);
	if (PointToInfinityLineDistance(point.x, point.y, point1.x, point1.y, point2.x, point2.y) > radius) {
		return false;
	}
	float a, b, c, n, u1, u2;
	a = (point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y);
	b = 2 * ((point2.x - point1.x) * (point1.x - point.x) + (point2.y - point1.y) * (point1.y - point.y));
	c = point.x * point.x + point.y * point.y + point1.x * point1.x + point1.y * point1.y - 2 * (point.x * point1.x + point.y * point1.y) - radius * radius;
	n = b * b - 4 * a * c;
	if (n < 0) {
		return false;
	}
	else if (n == 0) {
		XMFLOAT2 temp;
		u1 = (-b + sqrtf(n)) / (2 * a);
		temp.x = point1.x + u1 * (point2.x - point1.x);
		temp.y = point1.y + u1 * (point2.y - point1.y);
		if (IsInDirectionOfTwoValues(temp.x, point1.x, point2.x) && IsInDirectionOfTwoValues(temp.y, point1.y, point2.y)) {
			result = temp;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		u1 = (-b + sqrtf(n)) / (2 * a);
		u2 = (-b - sqrtf(n)) / (2 * a);
		XMFLOAT2 temp1, temp2;
		temp1.x = point1.x + u1 * (point2.x - point1.x);
		temp1.y = point1.y + u1 * (point2.y - point1.y);

		temp2.x = point1.x + u2 * (point2.x - point1.x);
		temp2.y = point1.y + u2 * (point2.y - point1.y);
		bool isT1, isT2;
		isT1 = IsInDirectionOfTwoValues(temp1.x, point1.x, point2.x) && IsInDirectionOfTwoValues(temp1.y, point1.y, point2.y);
		isT2 = IsInDirectionOfTwoValues(temp2.x, point1.x, point2.x) && IsInDirectionOfTwoValues(temp2.y, point1.y, point2.y);
		if (isT1 && isT2) {
			float d1, d2;
			d1 = PointToPointDistance(temp1.x, temp1.y, point1.x, point1.y);
			d2 = PointToPointDistance(temp2.x, temp2.y, point1.x, point1.y);

			if (d1 < d2) {
				result = temp1;
				return true;
			}
			else {
				result = temp2;
				return true;
			}
		}
		else if (isT1) {
			result = temp1;
			return true;
		}
		else if (isT2) {
			result = temp2;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

XMFLOAT2 Physics::GetMiddlePointOfTwoMiddlePoints(XMFLOAT2 point1, XMFLOAT2 point2, XMFLOAT2 point3, XMFLOAT2 point4)
{
	float x[4], y[4];
	x[0] = point1.x;
	x[1] = point2.x;
	x[2] = point3.x;
	x[3] = point4.x;
	y[0] = point1.y;
	y[1] = point2.y;
	y[2] = point3.y;
	y[3] = point4.y;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (x[i] > x[j]) {
				float temp;
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
			if (y[i] > y[j]) {
				float temp;
				temp = y[i];
				y[i] = y[j];
				y[j] = temp;
			}
		}
	}
	XMFLOAT2 point;
	point.x = (x[1] + x[2]) / 2;
	point.y = (y[1] + y[2]) / 2;
	return point;
}

float Physics::PointToPointDistance(float x1, float y1, float x2, float y2)
{
	return sqrtf(powf((x2 - x1), 2) + powf((y2 - y1), 2));
}

float Physics::PointToLineDistance(float x, float y, float x1, float y1, float x2, float y2)
{

	/*float cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
	if (cross <= 0) {
		return sqrtf((x - x1) * (x - x1) + (y - y1) * (y - y1));
	}

	float d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	if (cross >= d2) {
		return sqrtf((x - x2) * (x - x2) + (y - y2) * (y - y2));
	}

	float r = cross / d2;
	float px = x1 + (x2 - x1) * r;
	float py = y1 + (y2 - y1) * r;
	return sqrtf((x - px) * (x - px) + (py - y1) * (py - y1));*/
	float a, b, c;
	a = PointToPointDistance(x2, y2, x, y);
	if (a <= 0.00001f) {
		return 0.0f;
	}

	b = PointToPointDistance(x1, y1, x, y);
	if (b <= 0.00001f) {
		return 0.0f;
	}

	c = PointToPointDistance(x1, y1, x2, y2);
	if (c <= 0.00001f) {
		return a;
	}

	if (a * a >= b * b + c * c) {
		return b;
	}
	if (b * b >= a * a + c * c) {
		return a;
	}

	float l = (a + b + c) / 2;
	float s = sqrt(l * (l - a) * (l - b) * (l - c));
	return 2 * s / c;
}

float Physics::PointToInfinityLineDistance(float x, float y, float x1, float y1, float x2, float y2)
{
	float a, b, c;
	a = PointToPointDistance(x2, y2, x, y);
	if (a <= 0.00001f) {
		return 0.0f;
	}

	b = PointToPointDistance(x1, y1, x, y);
	if (b <= 0.00001f) {
		return 0.0f;
	}

	c = PointToPointDistance(x1, y1, x2, y2);
	if (c <= 0.00001f) {
		return a;
	}

	float l = (a + b + c) / 2;
	float s = sqrt(l * (l - a) * (l - b) * (l - c));
	return 2 * s / c;
}

bool Physics::IsMiddleValuesOverlapping(float v1, float v2, float v3, float v4)
{
	if (v1 < v3 && v1 < v4 && v2 < v3 && v2 < v4) {
		return false;
	}
	if (v3 < v1 && v3 < v2 && v4 < v1 && v4 < v2) {
		return false;
	}
	return true;
}

bool Physics::IsBetweenTwoValues(float v, float v1, float v2)
{
	if (v1 < v2) {
		if (v >= v1 && v <= v2) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (v >= v2 && v <= v1) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Physics::IsInDirectionOfTwoValues(float v, float v1, float v2)
{
	if (v1 > v2) {
		if (v >= v1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (v <= v1) {
			return true;
		}
		else {
			return false;
		}
	}
}

float Physics::AngleBetweenThreePoint(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float la, lb, lc;
	la = PointToPointDistance(x1, y1, x2, y2);
	lb = PointToPointDistance(x2, y2, x3, y3);
	lc = PointToPointDistance(x1, y1, x3, y3);
	float cos = (la * la + lb * lb - lc * lc) / (2 * la * lb);
	float angle = acosf(cos);
	return angle;
}

bool Physics::IsThreePointUnclockwise(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float ans = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
	if (ans > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Physics::RaycastCollider(Ray ray, BoxCollider targetCollider, HitInfo& result)
{
	XMVECTOR points[4];
	points[0] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) + XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) + XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	points[1] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) + XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) - XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	points[2] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) - XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) - XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	points[3] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) - XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) + XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	for (int i = 0; i < 4; i++) {
		points[i] -= targetCollider.GetCenter();
		points[i] = XMVector2Transform(points[i], targetCollider.GetRotateMatrix());
		points[i] += targetCollider.GetCenter();
		XMVECTOR or1 = targetCollider.GetOffset();
		or1 = XMVector2Transform(or1, targetCollider.GetRotateMatrix());
		points[i] += or1;
	}
	vector<XMFLOAT2> ress;
	bool isHitted = false;
	for (int i = 0; i < 4; i++) {
		XMFLOAT2 r;
		if (i < 3) {
			if (IsRayLineIntersecting(ray, XMFLOAT2(XMVectorGetX(points[i]), XMVectorGetY(points[i])), XMFLOAT2(XMVectorGetX(points[i + 1]), XMVectorGetY(points[i + 1])), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
		else {
			if (IsRayLineIntersecting(ray, XMFLOAT2(XMVectorGetX(points[i]), XMVectorGetY(points[i])), XMFLOAT2(XMVectorGetX(points[0]), XMVectorGetY(points[0])), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
	}
	if (isHitted) {
		result.hitCollider = targetCollider;
		int minIndex = 0;
		float minDis = PointToPointDistance(ress[0].x, ress[0].y, XMVectorGetX(ray.point), XMVectorGetY(ray.point));
		for (int i = 0; i < ress.size(); i++) {
			float dis = PointToPointDistance(ress[i].x, ress[i].y, XMVectorGetX(ray.point), XMVectorGetY(ray.point));
			if (dis < minDis) {
				minDis = dis;
				minIndex = i;
			}
		}
		XMVECTOR re;
		re = XMVectorSet(ress[minIndex].x, ress[minIndex].y, 0, 0);
		result.hitPoint = re;
		return true;
	}
	else {
		return false;
	}
}

bool Physics::RaycastCollider(Ray ray, CircleCollider targetCollider, HitInfo& result)
{
	XMFLOAT2 point;
	XMVECTOR or= targetCollider.GetOffset();
	or = XMVector2Transform(or, targetCollider.GetRotateMatrix());
	point.x = XMVectorGetX(targetCollider.GetCenter()) + XMVectorGetX(or);
	point.y = XMVectorGetY(targetCollider.GetCenter()) + XMVectorGetY(or);

	XMFLOAT2 r;
	if (IsRayCircleIntersecting(point, targetCollider.GetRadius(), ray, r)) {
		result.hitCollider = targetCollider;
		result.hitPoint = XMVectorSet(r.x, r.y, 0, 0);
		return true;
	}
	else {
		return false;
	}
}

bool Physics::LinecastCollider(Line line, BoxCollider targetCollider, HitInfo& result)
{
	XMVECTOR points[4];
	points[0] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) + XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) + XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	points[1] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) + XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) - XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	points[2] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) - XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) - XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	points[3] = XMVectorSet(XMVectorGetX(targetCollider.GetCenter()) - XMVectorGetX(targetCollider.GetSize()) / 2, XMVectorGetY(targetCollider.GetCenter()) + XMVectorGetY(targetCollider.GetSize()) / 2, 0, 0);
	for (int i = 0; i < 4; i++) {
		points[i] -= targetCollider.GetCenter();
		points[i] = XMVector2Transform(points[i], targetCollider.GetRotateMatrix());
		points[i] += targetCollider.GetCenter();
		XMVECTOR or1 = targetCollider.GetOffset();
		or1 = XMVector2Transform(or1, targetCollider.GetRotateMatrix());
		points[i] += or1;
	}
	vector<XMFLOAT2> ress;
	bool isHitted = false;
	for (int i = 0; i < 4; i++) {
		XMFLOAT2 r;
		if (i < 3) {
			if (IsTwoLineIntersecting(XMFLOAT2(XMVectorGetX(line.startPoint), XMVectorGetY(line.startPoint)), XMFLOAT2(XMVectorGetX(line.endPoint), XMVectorGetY(line.endPoint)), XMFLOAT2(XMVectorGetX(points[i]), XMVectorGetY(points[i])), XMFLOAT2(XMVectorGetX(points[i + 1]), XMVectorGetY(points[i + 1])), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
		else {
			if (IsTwoLineIntersecting(XMFLOAT2(XMVectorGetX(line.startPoint), XMVectorGetY(line.startPoint)), XMFLOAT2(XMVectorGetX(line.endPoint), XMVectorGetY(line.endPoint)), XMFLOAT2(XMVectorGetX(points[i]), XMVectorGetY(points[i])), XMFLOAT2(XMVectorGetX(points[0]), XMVectorGetY(points[0])), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
	}
	if (isHitted) {
		result.hitCollider = targetCollider;
		int minIndex = 0;
		float minDis = PointToPointDistance(ress[0].x, ress[0].y, XMVectorGetX(line.startPoint), XMVectorGetY(line.startPoint));
		for (int i = 0; i < ress.size(); i++) {
			float dis = PointToPointDistance(ress[i].x, ress[i].y, XMVectorGetX(line.startPoint), XMVectorGetY(line.startPoint));
			if (dis < minDis) {
				minDis = dis;
				minIndex = i;
			}
		}
		XMVECTOR re;
		re = XMVectorSet(ress[minIndex].x, ress[minIndex].y, 0, 0);
		result.hitPoint = re;
		return true;
	}
	else {
		return false;
	}
}

bool Physics::LinecastCollider(Line line, CircleCollider targetCollider, HitInfo& result)
{
	XMFLOAT2 point, point1, point2;
	XMVECTOR or = targetCollider.GetOffset();
	or = XMVector2Transform(or , targetCollider.GetRotateMatrix());
	point.x = XMVectorGetX(targetCollider.GetCenter()) + XMVectorGetX(or);
	point.y = XMVectorGetY(targetCollider.GetCenter()) + XMVectorGetY(or);

	point1.x = XMVectorGetX(line.startPoint);
	point1.y = XMVectorGetY(line.startPoint);

	point2.x = XMVectorGetX(line.endPoint);
	point2.y = XMVectorGetY(line.endPoint);

	XMFLOAT2 r1, r2;
	int isIntersecting = IsLineCircleIntersecting(point, targetCollider.GetRadius(), point1, point2, r1, r2);
	if (isIntersecting == 0) {
		return false;
	}
	else if (isIntersecting == 1) {
		result.hitCollider = targetCollider;
		result.hitPoint = XMVectorSet(r1.x, r1.y, 0, 0);
		return true;
	}
	else {
		if (PointToPointDistance(r1.x, r1.y, point1.x, point1.y) > PointToPointDistance(r2.x, r2.y, point1.x, point1.y)) {
			result.hitCollider = targetCollider;
			result.hitPoint = XMVectorSet(r1.x, r1.y, 0, 0);
			return true;
		}
		else {
			result.hitCollider = targetCollider;
			result.hitPoint = XMVectorSet(r2.x, r2.y, 0, 0);
			return true;
		}
	}
	
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, BoxCollider* targetCollider, XMVECTOR hitpoint)
{
	XMVECTOR or1 = thisCollider->GetOffset();
	or1 = XMVector2Transform(or1, thisCollider->GetRotateMatrix());

	Ray ray;
	ray.point = (thisCollider->GetCenter() + or1);
	ray.direction = ray.point - hitpoint;

	/*Ray ray2;
	ray2.point = hitpoint;
	ray2.direction = ray2.point - (targetCollider->GetCenter() + or1);*/


	HitInfo hit1;//hit2;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	//bool t2 = RaycastCollider(ray, *targetCollider, hit2);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}
	/*if (!t2) {
		hit2.hitPoint = hitpoint;
	}*/
	XMVECTOR delta = hit1.hitPoint - hitpoint;
	//float dis = sqrtf(XMVectorGetX(delta) * XMVectorGetX(delta) + XMVectorGetY(delta) * XMVectorGetY(delta));
	//if (dis > PointToPointDistance(XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter()), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter()))) {
	//	//printf("%f\n", dis);
	//	return;
	//}
	//printf("delta: %f,%f\n", XMVectorGetX(hitpoint), XMVectorGetY(hitpoint));
	//printf("delta: %f,%f\n", XMVectorGetX(ray.point), XMVectorGetY(ray.point));
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	//printf("hit1: %f,%f\n", XMVectorGetX(hit1.hitPoint), XMVectorGetY(hit1.hitPoint));
	//printf("hit2: %f,%f\n", XMVectorGetX(hit2.hitPoint), XMVectorGetY(hit2.hitPoint));
	float f = targetRb->mass * powf(XMVectorGetZ(targetRb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter())));
	XMVECTOR force = XMVector2Normalize(thisCollider->GetCenter() - hitpoint) * f;
	float f2 = rb->mass * powf(XMVectorGetZ(rb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter())));
	XMVECTOR force2 = XMVector2Normalize(targetCollider->GetCenter() - hitpoint) * f;
	force = XMVectorSetZ(force, 0);
	force2 = XMVectorSetZ(force2, 0);
	//printf("force: %f, %f, %f ,%f\n", f, XMVectorGetX(force), XMVectorGetY(force), XMVectorGetZ(force));
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, BoxCollider* targetCollider, XMVECTOR hitpoint)
{
	XMVECTOR or1 = thisCollider->GetOffset();
	or1 = XMVector2Transform(or1, thisCollider->GetRotateMatrix());

	Ray ray;
	ray.point = (thisCollider->GetCenter() + or1);
	ray.direction = ray.point - hitpoint;

	HitInfo hit1;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}


	XMVECTOR delta = hit1.hitPoint - hitpoint;

	//printf("delta: %f,%f\n", XMVectorGetX(hitpoint), XMVectorGetY(hitpoint));
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	float f = targetRb->mass * powf(XMVectorGetZ(targetRb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter())));
	XMVECTOR force = XMVector2Normalize(thisCollider->GetCenter() - hitpoint) * f;
	float f2 = rb->mass * powf(XMVectorGetZ(rb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter())));
	XMVECTOR force2 = XMVector2Normalize(targetCollider->GetCenter() - hitpoint) * f;
	force = XMVectorSetZ(force, 0);
	force2 = XMVectorSetZ(force2, 0);
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, CircleCollider* targetCollider, XMVECTOR hitpoint)
{
	XMVECTOR or1 = thisCollider->GetOffset();
	or1 = XMVector2Transform(or1, thisCollider->GetRotateMatrix());

	Ray ray;
	ray.point = (thisCollider->GetCenter() + or1);
	ray.direction = ray.point - hitpoint;

	HitInfo hit1;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}
	XMVECTOR delta = hit1.hitPoint - hitpoint;
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	float f = targetRb->mass * powf(XMVectorGetZ(targetRb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter())));
	XMVECTOR force = XMVector2Normalize(thisCollider->GetCenter() - hitpoint) * f;
	float f2 = rb->mass * powf(XMVectorGetZ(rb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter())));
	XMVECTOR force2 = XMVector2Normalize(targetCollider->GetCenter() - hitpoint) * f;
	force = XMVectorSetZ(force, 0);
	force2 = XMVectorSetZ(force2, 0);
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, CircleCollider* targetCollider, XMVECTOR hitpoint)
{
	XMVECTOR or1 = thisCollider->GetOffset();
	or1 = XMVector2Transform(or1, thisCollider->GetRotateMatrix());

	Ray ray;
	ray.point = (thisCollider->GetCenter() + or1);
	ray.direction = ray.point - hitpoint;

	HitInfo hit1;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}
	XMVECTOR delta = hit1.hitPoint - hitpoint;
	//printf("delta: %f,%f\n", XMVectorGetX(hitpoint), XMVectorGetY(hitpoint));
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->SetCenter(thisCollider->GetCenter() - delta);
		targetCollider->SetCenter(targetCollider->GetCenter() + delta);
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	float f = targetRb->mass * powf(XMVectorGetZ(targetRb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter())));
	XMVECTOR force = XMVector2Normalize(thisCollider->GetCenter() - hitpoint) * f;
	float f2 = rb->mass * powf(XMVectorGetZ(rb->angularVelocity) * M_PI / 180, 2) * (PointToPointDistance(XMVectorGetX(hitpoint), XMVectorGetY(hitpoint), XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter())));
	XMVECTOR force2 = XMVector2Normalize(targetCollider->GetCenter() - hitpoint) * f;
	force = XMVectorSetZ(force, 0);
	force2 = XMVectorSetZ(force2, 0);
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

