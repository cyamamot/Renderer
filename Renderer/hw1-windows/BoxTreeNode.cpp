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
void BoxTreeNode::Construct(int count, Triangle **tri) {

	//std::cout << count << std::endl;
	//std::cout << "vertices in node : ";

	for (unsigned int i = 0; i < count; i++) {

		//std::cout << (*tri)[i].index << ", ";

		/*double x = (*tri)[i].center[0];
		double y = (*tri)[i].center[1];
		double z = (*tri)[i].center[2];
		if (x < BoxMin[0]) BoxMin[0] = x;
		if (x > BoxMax[0]) BoxMax[0] = x;
		if (y < BoxMin[1]) BoxMin[1] = y;
		if (y > BoxMax[1]) BoxMax[1] = y;
		if (z < BoxMin[2]) BoxMin[2] = z;
		if (z > BoxMax[2]) BoxMax[2] = z;*/

		//std::cout << glm::to_string((*tri)[i].GetVtx(0)->Position) << std::endl;

		Vertex xm = *((*tri)[i].GetVtx(0));
		Vertex ym = *((*tri)[i].GetVtx(1));
		Vertex zm = *((*tri)[i].GetVtx(2));
		double x = std::max(xm.Position[0], std::max(ym.Position[0], zm.Position[0]));
		double y = std::max(xm.Position[1], std::max(ym.Position[1], zm.Position[1]));
		double z = std::max(xm.Position[2], std::max(ym.Position[2], zm.Position[2]));
		double xn = std::min(xm.Position[0], std::min(ym.Position[0], zm.Position[0]));
		double yn = std::min(xm.Position[1], std::min(ym.Position[1], zm.Position[1]));
		double zn = std::min(xm.Position[2], std::min(ym.Position[2], zm.Position[2]));

		if (xn < BoxMin[0]) BoxMin[0] = xn;
		if (x > BoxMax[0]) BoxMax[0] = x;
		if (yn < BoxMin[1]) BoxMin[1] = yn;
		if (y > BoxMax[1]) BoxMax[1] = y;
		if (zn < BoxMin[2]) BoxMin[2] = zn;
		if (z > BoxMax[2]) BoxMax[2] = z;

	}
	if (count <= MaxTrianglesPerBox) {
		for (int i = 0; i < count; i++) {
			Tri[i] = (*tri)[i];
		}
		numTris = count;
		return;
	}
	double lengthX = BoxMax[0] - BoxMin[0];
	double lengthY = BoxMax[1] - BoxMin[1];
	double lengthZ = BoxMax[2] - BoxMin[2];
	Triangle *tri1 = new Triangle[count]; 
	Triangle *tri2 = new Triangle[count];
	int count1 = 0, count2 = 0;
	if (std::max(lengthX, std::max(lengthY, lengthZ)) == lengthX) {
		double mid = (lengthX / 2.0) + BoxMin[0];
		for (int i = 0; i < count; i++) {
			glm::vec3 triCenter = (*tri)[i].center;
			if (triCenter[0] >= mid) {
				tri2[count2] = (*tri)[i];
				count2 = count2 + 1;
			}
			else {
				tri1[count1] = (*tri)[i];
				count1 = count1 + 1;
			}
		}
		if (count1 == 0) {
			count2 = count2 - 1;
			tri1[0] = tri2[count2];
			count1 = 1;
		}
		else if (count2 == 0) {
			count1 = count1 - 1;
			tri2[0] = tri1[count1];
			count2 = 1;
		}
		Child1 = new BoxTreeNode;
		Child2 = new BoxTreeNode;
		Child1->Construct(count1, &tri1);
		Child2->Construct(count2, &tri2);
		delete[]tri1;
		delete[]tri2;
	}
	else if (std::max(lengthX, std::max(lengthY, lengthZ)) == lengthY) {
		double mid = (lengthY / 2.0) + BoxMin[1];
		for (int i = 0; i < count; i++) {
			glm::vec3 triCenter = (*tri)[i].center;
			if (triCenter[1] >= mid) {
				tri2[count2] = (*tri)[i];
				count2++;
			}
			else {
				tri1[count1] = (*tri)[i];
				count1++;
			}
		}
		if (count1 == 0) {
			count2 = count2 - 1;
			tri1[count1] = tri2[count2];
			count1 = count1 + 1;
		}
		else if (count2 == 0) {
			count1 = count1 - 1;
			tri2[count2] = tri1[count1];
			count2 = count2 + 1;
		}
		Child1 = new BoxTreeNode;
		Child2 = new BoxTreeNode;
		Child1->Construct(count1, &tri1);
		Child2->Construct(count2, &tri2);
		delete[]tri1;
		delete[]tri2;
	}
	else if (std::max(lengthX, std::max(lengthY, lengthZ)) == lengthZ) {
		double mid = (lengthZ / 2.0) + BoxMin[2];
		for (int i = 0; i < count; i++) {
			glm::vec3 triCenter = (*tri)[i].center;
			if (triCenter[2] >= mid) {
				tri2[count2] = (*tri)[i];
				count2++;
			}
			else {
				tri1[count1] = (*tri)[i];
				count1++;
			}
		}
		if (count1 == 0) {
			count2 = count2 - 1;
			tri1[count1] = tri2[count2];
			count1 = count1 + 1;
		}
		else if (count2 == 0) {
			count1 = count1 - 1;
			tri2[count2] = tri1[count1];
			count2 = count2 + 1;
		}
		Child1 = new BoxTreeNode;
		Child2 = new BoxTreeNode;
		Child1->Construct(count1, &tri1);
		Child2->Construct(count2, &tri2);
		delete[]tri1;
		delete[]tri2;
	}
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

