#include "BoxTreeNode.h"
#include "algorithm"
#include "iostream"
#include "glm/ext.hpp"


BoxTreeNode::BoxTreeNode() {
	BoxMin = glm::vec3(100000.0, 100000.0, 100000.0);
	BoxMax = glm::vec3(-100000.0, -100000.0, -100000.0);
	Child1 = NULL;
	Child2 = NULL;
	Tri = new Triangle[MaxTrianglesPerBox];
	numTris = 0;
}
BoxTreeNode::~BoxTreeNode() {
	delete Child1;
	delete Child2;
	Child1 = NULL;
	Child2 = NULL;
}
bool BoxTreeNode::Intersect(const Ray &ray, Intersection &hit) {
	bool success = false;
	if (Child1 == NULL) {
		for (int i = 0; i < numTris; i++) {
			if (Tri[i].Intersect(ray, hit)) {
				success = true;
			}
		}
		return success;
	}
	double t;
	double tx1 = (BoxMin[0] - ray.Origin[0]) / ray.Direction[0]; double tx2 = (BoxMax[0] - ray.Origin[0]) / ray.Direction[0];
	double ty1 = (BoxMin[1] - ray.Origin[1]) / ray.Direction[1]; double ty2 = (BoxMax[1] - ray.Origin[1]) / ray.Direction[1];
	double tz1 = (BoxMin[2] - ray.Origin[2]) / ray.Direction[2]; double tz2 = (BoxMax[2] - ray.Origin[2]) / ray.Direction[2];
	double tmin = std::max(std::min(tx1, tx2), std::max(std::min(ty1, ty2), std::min(tz1, tz2)));
	double tmax = std::min(std::max(tx1, tx2), std::min(std::max(ty1, ty2), std::max(tz1, tz2)));
	if (tmax < 0) {
		return false;
	}
	if (tmax < tmin) return false;
	if (tmin < 0) t = 0;
	else if (tmin <= tmax) t = tmin;
	if (t >= hit.HitDistance) return false;

	double tChild1, tChild2;

	double tChild1x1 = (Child1->BoxMin[0] - ray.Origin[0]) / ray.Direction[0]; double tChild1x2 = (Child1->BoxMax[0] - ray.Origin[0]) / ray.Direction[0];
	double tChild1y1 = (Child1->BoxMin[1] - ray.Origin[1]) / ray.Direction[1]; double tChild1y2 = (Child1->BoxMax[1] - ray.Origin[1]) / ray.Direction[1];
	double tChild1z1 = (Child1->BoxMin[2] - ray.Origin[2]) / ray.Direction[2]; double tChild1z2 = (Child1->BoxMax[2] - ray.Origin[2]) / ray.Direction[2];
	double tChild1min = std::max(std::min(tChild1x1, tChild1x2), std::max(std::min(tChild1y1, tChild1y2), std::min(tChild1z1, tChild1z2)));
	double tChild1max = std::min(std::max(tChild1x1, tChild1x2), std::min(std::max(tChild1y1, tChild1y2), std::max(tChild1z1, tChild1z2)));
	if (tChild1min < 0) tChild1 = tChild1max;
	else if (tChild1min <= tChild1max) tChild1 = tChild1min;
	if (tChild1max < 0) {
		tChild1 = 0;
	}

	double tChild2x1 = (Child2->BoxMin[0] - ray.Origin[0]) / ray.Direction[0]; double tChild2x2 = (Child2->BoxMax[0] - ray.Origin[0]) / ray.Direction[0];
	double tChild2y1 = (Child2->BoxMin[1] - ray.Origin[1]) / ray.Direction[1]; double tChild2y2 = (Child2->BoxMax[1] - ray.Origin[1]) / ray.Direction[1];
	double tChild2z1 = (Child2->BoxMin[2] - ray.Origin[2]) / ray.Direction[2]; double tChild2z2 = (Child2->BoxMax[2] - ray.Origin[2]) / ray.Direction[2];
	double tChild2min = std::max(std::min(tChild2x1, tChild2x2), std::max(std::min(tChild2y1, tChild2y2), std::min(tChild2z1, tChild2z2)));
	double tChild2max = std::min(std::max(tChild2x1, tChild2x2), std::min(std::max(tChild2y1, tChild2y2), std::max(tChild2z1, tChild2z2)));
	if (tChild2min < 0) tChild2 = tChild2max;
	else if (tChild2min <= tChild2max) tChild2 = tChild2min;
	if (tChild2max < 0) {
		tChild2 = 0;
	}
	if (tChild1 == 0 && tChild2 == 0) return false;
	if (tChild2 == 0) {
		success = Child1->Intersect(ray, hit);
		return success;
	}
	else if (tChild1 == 0) {
		success = Child2->Intersect(ray, hit);
		return success;
	}
	else if (tChild1 < tChild2) {
		success = Child1->Intersect(ray, hit);
		if (!success) {
			success = Child2->Intersect(ray, hit);
		}
		else {
			bool trash = Child2->Intersect(ray, hit);
		}
		return success;
	}
	else if (tChild1 >= tChild2) {
		success = Child2->Intersect(ray, hit);
		if (!success) {
			success = Child1->Intersect(ray, hit);
		}
		else {
			bool trash = Child1->Intersect(ray, hit);
		}
		return success;
	}
	return false;
}

void BoxTreeNode::Construct(int count, std::vector<Triangle>& tri) {
	if (count <= MaxTrianglesPerBox) {
		for (int i = 0; i < count; i++) {
			Tri[i] = (tri)[i];
		}
		numTris = count;

		return;
	}
	ScaleBox(count, tri);
	double lengthX = BoxMax[0] - BoxMin[0];
	double lengthY = BoxMax[1] - BoxMin[1];
	double lengthZ = BoxMax[2] - BoxMin[2];
	//choosed how to divide current box into children based on longest axis
	if (std::max(lengthX, std::max(lengthY, lengthZ)) == lengthX) {
		DivideAlongX(count, lengthX, tri);
	}
	else if (std::max(lengthX, std::max(lengthY, lengthZ)) == lengthY) {
		DivideAlongY(count, lengthY, tri);
	}
	else if (std::max(lengthX, std::max(lengthY, lengthZ)) == lengthZ) {
		DivideAlongZ(count, lengthZ, tri);
	}
}

void BoxTreeNode::ScaleBox(int count, std::vector<Triangle>& tri) {
	for (unsigned int i = 0; i < count; i++) {
		Vertex xm = *((tri)[i].GetVtx(0));
		Vertex ym = *((tri)[i].GetVtx(1));
		Vertex zm = *((tri)[i].GetVtx(2));
		//finds max and min x,y,z among all triangles
		float x = std::max(xm.Position[0], std::max(ym.Position[0], zm.Position[0]));
		float y = std::max(xm.Position[1], std::max(ym.Position[1], zm.Position[1]));
		float z = std::max(xm.Position[2], std::max(ym.Position[2], zm.Position[2]));
		float xn = std::min(xm.Position[0], std::min(ym.Position[0], zm.Position[0]));
		float yn = std::min(xm.Position[1], std::min(ym.Position[1], zm.Position[1]));
		float zn = std::min(xm.Position[2], std::min(ym.Position[2], zm.Position[2]));
		//assignes bounds of box to farthest distance triangle in x,y,z
		if (xn < BoxMin[0]) BoxMin[0] = xn;
		if (x > BoxMax[0]) BoxMax[0] = x;
		if (yn < BoxMin[1]) BoxMin[1] = yn;
		if (y > BoxMax[1]) BoxMax[1] = y;
		if (zn < BoxMin[2]) BoxMin[2] = zn;
		if (z > BoxMax[2]) BoxMax[2] = z;
	}
}

void BoxTreeNode::DivideAlongX(const int count, double lengthX, std::vector<Triangle>& tri) {
	int count1 = 0, count2 = 0;
	//Triangle* tri1 = new Triangle[count];
	//Triangle* tri2 = new Triangle[count];
	std::vector<Triangle> tri1;
	std::vector<Triangle> tri2;
	double mid = (lengthX / 2.0) + BoxMin[0];
	for (int i = 0; i < count; i++) {
		glm::vec3 triCenter = (tri)[i].center;
		if (triCenter[0] >= mid) {
			tri2.push_back((tri)[i]);
			count2 = count2 + 1;
		}
		else {
			tri1.push_back((tri)[i]);
			count1 = count1 + 1;
		}
	}
	//if one child is empty, assign one triangle to empty child
	if (count1 == 0) {
		count2 = count2 - 1;
		tri1.push_back(tri2[count2]);
		count1 = 1;
	}
	else if (count2 == 0) {
		count1 = count1 - 1;
		tri2.push_back(tri1[count1]);
		count2 = 1;
	}
	Child1 = new BoxTreeNode;
	Child2 = new BoxTreeNode;
	Child1->Construct(count1, tri1);
	//delete[]tri1;
	Child2->Construct(count2, tri2);
	//delete[]tri2;
}

void BoxTreeNode::DivideAlongY(const int count, double lengthY, std::vector<Triangle>& tri) {
	int count1 = 0, count2 = 0;
	std::vector<Triangle> tri1;
	std::vector<Triangle> tri2;
	double mid = (lengthY / 2.0) + BoxMin[1];
	for (int i = 0; i < count; i++) {
		glm::vec3 triCenter = (tri)[i].center;
		if (triCenter[1] >= mid) {
			tri2.push_back((tri)[i]);
			count2++;
		}
		else {
			tri1.push_back((tri)[i]);
			count1++;
		}
	}
	//if one child is empty, assign one triangle to empty child
	if (count1 == 0) {
		count2 = count2 - 1;
		tri1.push_back(tri2[count2]);
		count1 = count1 + 1;
	}
	else if (count2 == 0) {
		count1 = count1 - 1;
		tri2.push_back(tri1[count1]);
		count2 = count2 + 1;
	}
	Child1 = new BoxTreeNode;
	Child2 = new BoxTreeNode;
	Child1->Construct(count1, tri1);
	//delete[]tri1;
	Child2->Construct(count2, tri2);
	//delete[]tri2;
}

void BoxTreeNode::DivideAlongZ(const int count, double lengthZ, std::vector<Triangle>& tri) {
	int count1 = 0, count2 = 0;
	std::vector<Triangle> tri1;
	std::vector<Triangle> tri2;
	double mid = (lengthZ / 2.0) + BoxMin[2];
	for (int i = 0; i < count; i++) {
		glm::vec3 triCenter = (tri)[i].center;
		if (triCenter[2] >= mid) {
			tri2.push_back((tri)[i]);
			count2++;
		}
		else {
			tri1.push_back((tri)[i]);
			count1++;
		}
	}
	//if one child is empty, assign one triangle to empty child
	if (count1 == 0) {
		count2 = count2 - 1;
		tri1.push_back(tri2[count2]);
		count1 = count1 + 1;
	}
	else if (count2 == 0) {
		count1 = count1 - 1;
		tri2.push_back(tri1[count1]);
		count2 = count2 + 1;
	}
	Child1 = new BoxTreeNode;
	Child2 = new BoxTreeNode;
	Child1->Construct(count1, tri1);
	//delete[]tri1;
	Child2->Construct(count2, tri2);
	//delete[]tri2;
}