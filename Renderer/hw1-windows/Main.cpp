#include "MeshObject.h"
#include "InstanceObject.h"
#include "MovingObject.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "Scene.h"
#include "BoxTreeObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <cmath>
#include <cstdio>
#include <ctime>
#include <queue>
#include "MetalMaterial.h"
#include "AshikhminMaterial.h"

#define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES

void project3();
void project3EC();
void project3EC2();
void project4();
void FinalProject();


void main() {
	project3();
	return;
}

void project3() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));
	// Create ground
	LambertMaterial groundMtl;
	groundMtl.SetColor(Color(0.25f, 0.25f, 0.25f));
	MeshObject ground;
	ground.MakeBox(2.0f, 0.11f, 2.0f, &groundMtl);
	scn.AddObject(ground);
	// Load dragon mesh
	MeshObject dragon;
	dragon.LoadPLY("../hw1-windows/dragon.ply", 0);
	// Create box tree
	BoxTreeObject tree;
	tree.Construct(dragon);
	// Materials
	LambertMaterial white;
	white.SetColor(Color(0.7f, 0.7f, 0.7f));
	LambertMaterial red;
	red.SetColor(Color(0.7f, 0.1f, 0.1f));
	MetalMaterial metal;
	metal.SetColor(Color(0.95f, 0.64f, 0.54f));
	const int numDragons = 4;
	Material *mtl[numDragons] = { &white,&metal,&red,&white };
	// Create dragon instances
	glm::mat4 mtx;
	for (int i = 0; i<numDragons; i++) {
		InstanceObject *inst = new InstanceObject(tree);
		mtx[3] = glm::vec4(0.0f, 0.0f, 0.3f*(float(i) / float(numDragons - 1) - 0.5f), 1.0f);
		inst->SetMatrix(mtx);
		inst->setMaterial(mtl[i]);
		scn.AddObject(*inst);
	}
	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);
	// Create camera
	Camera cam;
	cam.SetResolution(640, 480);
	cam.SetAspect(1.33f);
	cam.LookAt(glm::vec3(-0.5f, 0.25f, -0.2f), glm::vec3(0.0f, 0.15f, 0.0f), glm::vec3(0, 1.0f, 0));
	cam.SetFOV(40.0f);
	cam.SetSuperSample(10, 10);
	cam.SetJitter(true);
	cam.SetShirley(true);
	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project3.bmp");
}

void project3EC() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));
	// Materials
	const int nummtls = 4;
	AshikhminMaterial diffuse;
	AshikhminMaterial copper;
	AshikhminMaterial gold;
	AshikhminMaterial plastic;
	// Diffuse
	diffuse.SetSpecularLevel(0.0f);
	diffuse.SetDiffuseLevel(1.0f);
	diffuse.SetDiffuseColor(Color(0.7f, 0.7f, 0.7f));
	// Roughened copper
	copper.SetDiffuseLevel(0.0f);
	copper.SetSpecularLevel(1.0f);
	copper.SetSpecularColor(Color(0.9f, 0.6f, 0.5f));
	copper.SetRoughness(100.0f, 100.0f);
	// Anisotropic gold
	gold.SetDiffuseLevel(0.0f);
	gold.SetSpecularLevel(1.0f);
	gold.SetSpecularColor(Color(0.95f, 0.7f, 0.3f));
	gold.SetRoughness(1.0f, 1000.0f);
	// Red plastic
	plastic.SetDiffuseColor(Color(1.0f, 0.1f, 0.1f));
	plastic.SetDiffuseLevel(0.8f);
	plastic.SetSpecularLevel(0.2f);
	plastic.SetSpecularColor(Color(1.0f, 1.0f, 1.0f));
	plastic.SetRoughness(1000.0f, 1000.0f);

	Material* mtl[nummtls] = { &diffuse, &copper, &gold, &plastic };

	// Load dragon mesh
	MeshObject dragon;
	dragon.LoadPLY("dragon.ply", 0);
	// Create box tree
	BoxTreeObject tree;
	tree.Construct(dragon);
	// Create dragon instances
	glm::mat4 mtx;
	for (int i = 0; i<nummtls; i++) {
		InstanceObject *inst = new InstanceObject(tree);
		mtx[3] = glm::vec4(0.0f, 0.0f, -0.1f*float(i), 1.0f);
		inst->SetMatrix(mtx);
		inst->setMaterial(mtl[i]);
		scn.AddObject(*inst);
	}
	// Create ground
	LambertMaterial lambert;
	lambert.SetColor(Color(0.3f, 0.3f, 0.35f));

	MeshObject ground;
	ground.MakeBox(2.0f, 0.11f, 2.0f, &lambert);
	scn.AddObject(ground);
	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);
	// Create camera
	Camera cam;
	cam.LookAt(glm::vec3(-0.2f, 0.15f, 0.25f), glm::vec3(-0.0625f, 0.15f, 0.0f), glm::vec3(0, 1, 0));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);
	cam.SetSuperSample(10, 10);
	cam.SetJitter(true);
	cam.SetShirley(true);
	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project3EC1.bmp");
}

void project3EC2() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));
	LambertMaterial lambert;
	lambert.SetColor(Color(0.3f, 0.3f, 0.35f));

	MeshObject ground;
	ground.MakeBox(2.0f, 0.11f, 2.0f, &lambert);
	scn.AddObject(ground);
	AshikhminMaterial gold;
	gold.SetDiffuseLevel(0.0f);
	gold.SetSpecularLevel(1.0f);
	gold.SetSpecularColor(Color(0.95f, 0.7f, 0.3f));
	gold.SetRoughness(1.0f, 1000.0f);
	Material* mtl = &gold;
	MeshObject dragon;
	dragon.LoadPLY("dragon.ply", 0);
	// Create box tree
	BoxTreeObject tree;
	tree.Construct(dragon);
	MovingObject* move = new MovingObject(tree);
	//InstanceObject* move = new InstanceObject(tree);
	move->setMaterial(mtl);
	mat4x4 init(1.0);
	init[3][0] = -0.125f;
	init[3][1] = 0.01f;
	mat4x4 fin(1.0);
	fin[3][0] = 0.125f;
	fin[3][1] = 0.01f;
	move->SetInitialFinalMatrix(init, fin);
	scn.AddObject(*move);
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);
	Camera cam;
	cam.SetResolution(800, 600);
	cam.SetAspect(1.33f);
	cam.LookAt(glm::vec3(-0.125f, 0.25f, -0.35f), glm::vec3(0.0f, 0.15f, 0.0f), glm::vec3(0, 1, 0));
	cam.SetFOV(40.0f);
	cam.SetSuperSample(10, 10);
	cam.SetJitter(true);
	cam.SetShirley(true);
	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project3EC2.bmp");
}

void project4() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));
	// Materials
	const int nummtls = 4;
	AshikhminMaterial diffuse;
	AshikhminMaterial copper;
	AshikhminMaterial gold;
	AshikhminMaterial plastic;
	// Diffuse
	diffuse.SetSpecularLevel(0.0f);
	diffuse.SetDiffuseLevel(1.0f);
	diffuse.SetDiffuseColor(Color(0.7f, 0.7f, 0.7f));
	// Roughened copper
	copper.SetDiffuseLevel(0.0f);
	copper.SetSpecularLevel(1.0f);
	copper.SetSpecularColor(Color(0.9f, 0.6f, 0.5f));
	copper.SetRoughness(100.0f, 100.0f);
	// Anisotropic gold
	gold.SetDiffuseLevel(0.0f);
	gold.SetSpecularLevel(1.0f);
	gold.SetSpecularColor(Color(0.95f, 0.7f, 0.3f));
	gold.SetRoughness(1.0f, 1000.0f);
	// Red plastic
	plastic.SetDiffuseColor(Color(1.0f, 0.1f, 0.1f));
	plastic.SetDiffuseLevel(0.8f);
	plastic.SetSpecularLevel(0.2f);
	plastic.SetSpecularColor(Color(1.0f, 1.0f, 1.0f));
	plastic.SetRoughness(1000.0f, 1000.0f);

	Material* mtl[nummtls] = { &diffuse, &copper, &gold, &plastic };

	// Load dragon mesh
	MeshObject dragon;
	dragon.LoadPLY("dragon.ply", 0);
	// Create box tree
	BoxTreeObject tree;
	tree.Construct(dragon);
	// Create dragon instances
	glm::mat4 mtx;
	for (int i = 0; i<nummtls; i++) {
		InstanceObject *inst = new InstanceObject(tree);
		mtx[3] = glm::vec4(0.0f, 0.0f, -0.1f*float(i), 1.0f);
		inst->SetMatrix(mtx);
		inst->setMaterial(mtl[i]);
		scn.AddObject(*inst);
	}
	// Create ground
	LambertMaterial lambert;
	lambert.SetColor(Color(0.3f, 0.3f, 0.35f));

	MeshObject ground;
	ground.MakeBox(2.0f, 0.11f, 2.0f, &lambert);
	scn.AddObject(ground);
	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);
	// Create camera
	Camera cam;
	cam.LookAt(glm::vec3(-0.5f, 0.25f, -0.2f), glm::vec3(0.0f, 0.15f, -0.15f), glm::vec3(0, 1, 0));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);
	cam.SetSuperSample(10, 10);
	cam.SetJitter(true);
	cam.SetShirley(true);
	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project4.bmp");
}

void FinalProject() {
	MetalMaterial metal;
	metal.SetColor(Color(0.0f, 0.5f, 0.0f));
	AshikhminMaterial gold;
	gold.SetDiffuseLevel(0.0f);
	gold.SetSpecularLevel(1.0f);
	gold.SetSpecularColor(Color(0.95f, 0.7f, 0.3f));
	gold.SetRoughness(1.0f, 1000.0f);
	AshikhminMaterial onyx;
	onyx.SetDiffuseLevel(0.0f);
	onyx.SetSpecularLevel(1.0f);
	onyx.SetSpecularColor(Color(0.25f, 0.25f, 0.25f));
	onyx.SetRoughness(1000.0f, 1000.0f);
	Material* mtl[3] = { &metal, &gold, &onyx };
	//first path
	std::queue<mat4x4> path;
	mat4x4 init(1.0);
	init[3] = { -7.0, 0.7, 0.0, 1.0 };
	mat4x4 fin(1.0);
	fin[3] = { 7.5, 0.7, -3.0, 0.8 };
	for (int i = 0; i < 3; i++) {
		path.push(init);
	}
	for (float i = 0.0f; i <= 1.0f; i += 1.0f) {
		path.push(glm::interpolate(init, fin, i));
	}
	//second path
	init = mat4x4(1.0);
	init[3] = { 7.5, 0.7, -3.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { 2.0, 0.7, -6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.75) {
		if (i > 1.0f) i = 1.0f;
		path.push(glm::interpolate(init, fin, i));
	}
	//third path
	init = mat4x4(1.0);
	init[3] = { 2.0, 0.7, -6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -7.5, 0.7, 5.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.3f) {
		path.push(glm::interpolate(init, fin, i));
	}
	//fourth path
	init = mat4x4(1.0);
	init[3] = { -7.5, 0.7, 5.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -5.5, 0.7, 6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.55) {
		path.push(glm::interpolate(init, fin, i));
	}
	//fifth path
	init = mat4x4(1.0);
	init[3] = { -6.0, 0.7, 6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -1.0, 0.7, -6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.225) {
		path.push(glm::interpolate(init, fin, i));
	}
	//sixth path
	init = mat4x4(1.0);
	init[3] = { -1.0, 0.7, -6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { 3.0, 0.7, 6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.175) {
		path.push(glm::interpolate(init, fin, i));
	}
	//seventh path
	init = mat4x4(1.0);
	init[3] = { 3.0, 0.7, 6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { 7.5, 0.7, 3.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.225) {
		path.push(glm::interpolate(init, fin, i));
	}
	//eighth path
	init = mat4x4(1.0);
	init[3] = { 7.5, 0.7, 3.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -6.75, 0.7, -6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.1075) {
		path.push(glm::interpolate(init, fin, i));
	}
	//ninth path
	init = mat4x4(1.0);
	init[3] = { -6.75, 0.7, -6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -7.5, 0.7, -5.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.875) {
		path.push(glm::interpolate(init, fin, i));
	}
	//tenth path
	init = mat4x4(1.0);
	init[3] = { -7.5, 0.7, -5.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { 0.0, 0.7, 6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.12) {
		path.push(glm::interpolate(init, fin, i));
	}
	//eleventh path
	init = mat4x4(1.0);
	init[3] = { 0.0, 0.7, 6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { 7.5, 0.7, 0.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.1075) {
		path.push(glm::interpolate(init, fin, i));
	}
	//twelfth path
	init = mat4x4(1.0);
	init[3] = { 7.5, 0.7, 0.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { 2.375, 0.7, -6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.1075) {
		path.push(glm::interpolate(init, fin, i));
	}
	//thirteenth path
	init = mat4x4(1.0);
	init[3] = { 2.375, 0.7, -6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -1.75, 0.7, 6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.075) {
		path.push(glm::interpolate(init, fin, i));
	}
	//fourteenth path
	init = mat4x4(1.0);
	init[3] = { -1.75, 0.7, 6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -7.5, 0.7, 0.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.06) {
		path.push(glm::interpolate(init, fin, i));
	}
	//fifteenth path
	init = mat4x4(1.0);
	init[3] = { -7.5, 0.7, 0.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { -1.0, 0.7, -6.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.03) {
		path.push(glm::interpolate(init, fin, i));
	}
	init = mat4x4(1.0);
	init[3] = { -1.0, 0.7, -6.0, 1.0 };
	fin = mat4x4(1.0);
	fin[3] = { 5.0, 0.7, 0.0, 1.0 };
	for (float i = 0.0; i <= 1.0f; i += 0.015) {
		path.push(glm::interpolate(init, fin, pow(i, 1.0f / 1.5f)));
	}
	//eighth path
	/*init = mat4x4(1.0);
	init[3] = { 7.5, 0.7, 3.0, 1.0 };
	fin = mat4x4(1.0);
	//fin[3] = { 2.75, 0.5, 0.5, 1.0 };
	fin[3] = { -2.0, 0.7, -2.0, 1.0 };
	float temp = 0.0f;
	for (float i = 0.0; i < 1.0f; i += 0.01) {
		temp = pow(i, 1.0f / 1.35f);
		path.push(glm::interpolate(init, fin, temp));
	}*/


	int x = 0;
	while (!path.empty()) {
		std::cout << x << " : " << path.size() << std::endl;

		Scene scn;
		scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));

		MeshObject table;
		table.MakeBox(15.0f, 0.5f, 12.0f, mtl[0]);
		scn.AddObject(table);
		MeshObject ball;
		ball.MakeBox(1.0, 1.0, 1.0);
		MovingObject* movingBall = new MovingObject(ball);
		mat4x4 init = path.front();
		path.pop();
		mat4x4 fin = path.front();
		if (path.empty()) continue;
		movingBall->setMaterial(mtl[1]);
		movingBall->SetInitialFinalMatrix(init, fin);
		scn.AddObject(*movingBall);

		DirectLight sunlgt;
		sunlgt.SetBaseColor(Color(1.5f, 1.5f, 0.5f));
		sunlgt.SetIntensity(1.0f);
		sunlgt.SetDirection(glm::vec3(0.0f, 5.0f, 0.0f));
		scn.AddLight(sunlgt);

		Camera cam;
		cam.LookAt(glm::vec3(0.0f, 15.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));
		cam.SetFOV(40.0f);
		cam.SetAspect(1.33f);
		cam.SetResolution(400, 300);
		cam.SetSuperSample(5, 5);
		cam.SetJitter(true);
		cam.SetShirley(true);
		cam.Render(scn);
		std::string filename = "FinalImages/FinalProject" + std::to_string(x) + ".bmp";
		cam.SaveBitmap(filename.c_str());
		x++;
	}
}


////////////////////////////////////////////////////////////////////////////////
