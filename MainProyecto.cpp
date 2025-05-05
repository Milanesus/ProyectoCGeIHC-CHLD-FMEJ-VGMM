//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
//Animacion
bool puertaAbierta = false;  // Controla si la puerta está abierta o cerrada
float alguloPuerta = 0.0f;  // Ángulo actual de la puerta
float velocidadPuerta = 2.0f; // Velocidad de apertura/cierre

//Texturas
//Texture brickTexture;

//Modelos
Model Piso_M;
//Puertas
Model Rejas_M;
Model PuertaN_1;
Model PuertaN_2;
Model PuertaR_1;
Model PuertaR_2;
Model PuertaV_1;
Model PuertaV_2;
Model MaquinaMoneda_M;
Model Moneda_M;
Model banca_M;
Model bocina;
Model bote_b;
//Poste de luz
Model poste;
Model farola;
//Lanzamiento de hacha
Model hacha_M;
Model cabina;
Model diana;
//Puesto de bebidas
Model puesto_bebidas;
Model botellas;
Model aguas;
Model latas;
Model vasos;
Model tarro;
//Puesto de tacos
Model puesto_tacos;
Model tabla;
Model salsa_verde;
Model salsa_roja;
Model tacos2;
Model comal;
Model platos;
Model servilletas;
Model cuchillo;
Model trompo;
//Mesa de dados
Model Base_M;
Model Borde_M;
Model Tablero_M;
Model Dado_M;
//Línea de boliche
Model PistaBoliche_M;
Model CanaletaBoliche_M;
Model Bolo_M;
Model BolaBoliche_M;
//Línea de boliche
Model MesaTopo_M;
Model LetreroTopo_M;
Model HoyoTopo_M;
Model MesaMazoTopo_M;
Model MazoTopo_M;
//Puesto de pizzas
Model PuestoPizzas_M;
Model PizzaLimon_M;
Model PizzaPeperoni_M;
Model PizzaQueso_M;
Model PizzaHawaiana_M;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);//[0]

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);//[1]

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);//[2]

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);//[3]

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	/*
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	*/
	//Modelos 
	Piso_M = Model();
	Piso_M.LoadModel("Models/Piso_obj.obj");
	//Puertas
	Rejas_M = Model();
	Rejas_M.LoadModel("Models/Puertas/rejas_arcos.obj");
	PuertaN_1 = Model();
	PuertaN_1.LoadModel("Models/Puertas/puerta1_n.obj");
	PuertaN_2 = Model();
	PuertaN_2.LoadModel("Models/Puertas/puerta2_n.obj");
	PuertaR_1 = Model();
	PuertaR_1.LoadModel("Models/Puertas/puerta1_r.obj");
	PuertaR_2 = Model();
	PuertaR_2.LoadModel("Models/Puertas/puerta2_r.obj");
	PuertaV_1 = Model();
	PuertaV_1.LoadModel("Models/Puertas/puerta1_v.obj");
	PuertaV_2 = Model();
	PuertaV_2.LoadModel("Models/Puertas/puerta2_v.obj");
	MaquinaMoneda_M = Model();
	MaquinaMoneda_M.LoadModel("Models/MaquinaMoneda_obj.obj");
	Moneda_M = Model();
	Moneda_M.LoadModel("Models/Moneda_obj.obj");
	banca_M = Model();
	banca_M.LoadModel("Models/banca.obj");
	bocina = Model();
	bocina.LoadModel("Models/bocina.obj");
	bote_b = Model();
	bote_b.LoadModel("Models/bote_b.obj");
	//Poste de luz
	poste = Model();
	poste.LoadModel("Models/poste.obj");
	farola = Model();
	farola.LoadModel("Models/lampara.obj");
	//Lanzamiento de hacha
	hacha_M = Model();
	hacha_M.LoadModel("Models/hacha.obj");
	cabina = Model();
	cabina.LoadModel("Models/cabina_hacha.obj");
	diana = Model();
	diana.LoadModel("Models/diana_hacha.obj");
	//Puesto de bebidas
	puesto_bebidas = Model();
	puesto_bebidas.LoadModel("Models/P_bebidas/bebidas_p.obj");
	botellas = Model();
	botellas.LoadModel("Models/P_bebidas/botellas.obj");
	aguas = Model();
	aguas.LoadModel("Models/P_bebidas/aguas.obj");
	latas = Model();
	latas.LoadModel("Models/P_bebidas/latas.obj");
	vasos = Model();
	vasos.LoadModel("Models/P_bebidas/vaso.obj");
	tarro = Model();
	tarro.LoadModel("Models/P_bebidas/tarro.obj");
	//Puesto de tacos
	puesto_tacos = Model();
	puesto_tacos.LoadModel("Models/P_tacos/tacos_p.obj");
	tabla = Model();
	tabla.LoadModel("Models/P_tacos/tabla.obj");
	salsa_verde = Model();
	salsa_verde.LoadModel("Models/P_tacos/salsa_v.obj");
	salsa_roja = Model();
	salsa_roja.LoadModel("Models/P_tacos/salsa_r.obj");
	tacos2 = Model();
	tacos2.LoadModel("Models/P_tacos/tacos2.obj");
	comal = Model();
	comal.LoadModel("Models/P_tacos/comal.obj");
	platos = Model();
	platos.LoadModel("Models/P_tacos/platos.obj");
	servilletas = Model();
	servilletas.LoadModel("Models/P_tacos/servilletas.obj");
	cuchillo = Model();
	cuchillo.LoadModel("Models/P_tacos/cuchillo.obj");
	trompo = Model();
	trompo.LoadModel("Models/P_tacos/trompo.obj");
	//Mesa de dados
	Base_M = Model();
	Base_M.LoadModel("Models/Base_obj.obj");
	Borde_M = Model();
	Borde_M.LoadModel("Models/BordeMesaDados_obj.obj");
	Tablero_M = Model();
	Tablero_M.LoadModel("Models/TableroMesaDados_obj.obj");
	Dado_M = Model();
	Dado_M.LoadModel("Models/Dado_HoradeAventura_obj.obj");
	//Línea de boliche
	PistaBoliche_M = Model();
	PistaBoliche_M.LoadModel("Models/PistaBoliche_obj.obj");
	CanaletaBoliche_M = Model();
	CanaletaBoliche_M.LoadModel("Models/CanaletaBoliche_obj.obj");
	Bolo_M = Model();
	Bolo_M.LoadModel("Models/Bolo_obj.obj");
	BolaBoliche_M = Model();
	BolaBoliche_M.LoadModel("Models/BolaBoliche_obj.obj");
	//Golpea al topo
	MesaTopo_M = Model();
	MesaTopo_M.LoadModel("Models/MesaTopo_obj.obj");
	LetreroTopo_M = Model();
	LetreroTopo_M.LoadModel("Models/LetreroTopo_obj.obj");
	HoyoTopo_M = Model();
	HoyoTopo_M.LoadModel("Models/HoyoTopo_obj.obj");
	MesaMazoTopo_M = Model();
	MesaMazoTopo_M.LoadModel("Models/MesaMazoTopo_obj.obj");
	MazoTopo_M = Model();
	MazoTopo_M.LoadModel("Models/MazoTopo_obj.obj");
	//Puesto de Pizzas
	PuestoPizzas_M = Model();
	PuestoPizzas_M.LoadModel("Models/PuestoPizzas_obj.obj");
	PizzaLimon_M = Model();
	PizzaLimon_M.LoadModel("Models/PizzaLimon_obj.obj");
	PizzaPeperoni_M = Model();
	PizzaPeperoni_M.LoadModel("Models/PizzaPeperoni_obj.obj");
	PizzaQueso_M = Model();
	PizzaQueso_M.LoadModel("Models/PizzaQueso_obj.obj");
	PizzaHawaiana_M = Model();
	PizzaHawaiana_M.LoadModel("Models/PizzaHawaiana_obj.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, -1.0f, 0.0f);

	//==================POINTLIGHTS==================

	//Contador de luces puntuales
	unsigned int pointLightCount = 0;

	//Luz puntual de la Lampara en el centro de la feria
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		//Intensidad ambiental y tonalidad
		1.0f, 8.0f,
		//Posición x, y, z
		0.0f, 10.0f, 0.0f,
		//No poner en 0.0f, 0.0f, 0.0f en la linea de abajo
		1.0f, 0.2f, 0.1f);
	pointLightCount++;

	//Luz puntual de la Lampara 2
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
		//Intensidad ambiental y tonalidad
		1.0f, 8.0f,
		//Posición x, y, z
		-34.0f, 10.0f, -25.0f,
		//No poner en 0.0f, 0.0f, 0.0f en la linea de abajo
		1.0f, 0.2f, 0.1f);
	pointLightCount++;

	//Luz puntual de la Lampara 3
	pointLights[2] = PointLight(0.0f, 0.0f, 1.0f,
		//Intensidad ambiental y tonalidad
		1.0f, 8.0f,
		//Posición x, y, z
		34.0f, 10.0f, -25.0f,
		//No poner en 0.0f, 0.0f, 0.0f en la linea de abajo
		1.0f, 0.2f, 0.1f);
	pointLightCount++;

	//==================SPOTLIGHTS==================

	//Contador de luces spot
	unsigned int spotLightCount = 0;

	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		//Intensidad ambiental y tonalidad
		0.0f, 0.0f,
		//Posición x, y, z
		0.0f, 0.0f, 0.0f,
		//Dirección de la luz
		0.0f, -1.0f, 0.0f,
		//No poner en 0.0f, 0.0f, 0.0f en la linea de abajo
		1.0f, 0.0f, 0.0f,
		//Ángulo de apertura
		5.0f);
	spotLightCount++;


	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);

		//Pasar luces al shader
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		glm::mat4 model(1.0);
		glm::mat4 modelauxlamp(1.0);
		glm::mat4 modelauxbebidas(1.0);
		glm::mat4 modelauxPizzas(1.0);
		glm::mat4 modelauxDados(1.0);
		glm::mat4 modelauxBoliche(1.0);
		glm::mat4 modelauxTopo(1.0);
		glm::mat4 modelauxPuertas(1.0);
		glm::mat4 modelauxTacos(1.0);

		//Piso de la Feria
		model = glm::mat4(1.0);
		//model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Piso_M.RenderModel();
		//Rejas
		model = glm::mat4(1.0);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rejas_M.RenderModel();

		//Puertas
		puertaAbierta = mainWindow.getarticulacion1();
		if (puertaAbierta == 1)
		{
			alguloPuerta += velocidadPuerta * deltaTime;
			if (alguloPuerta > 90.0f)
			{
				alguloPuerta = 90.0f;
			}
		}
		else
		{
			alguloPuerta -= velocidadPuerta * deltaTime;
			if (alguloPuerta < 0.0f)
			{
				alguloPuerta = 0.0f;
			}
		}
		modelauxPuertas = model;
		model = glm::translate(model, glm::vec3(-10.0f, 8.49f, 50.842f));
		model = glm::rotate(model, alguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaN_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(10.0f, 8.49f, 50.842f));
		model = glm::rotate(model, alguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaN_2.RenderModel();

		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(-30.161f, 7.5f, -42.403f));
		model = glm::rotate(model, alguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaR_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(-44.141f, 7.5f, -27.561f));
		model = glm::rotate(model, alguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaR_2.RenderModel();

		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(42.612f, 13.861f, -28.45f));
		model = glm::rotate(model, alguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaV_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(27.255f, 13.861f, -43.279f));
		model = glm::rotate(model, alguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaV_2.RenderModel();

		//Máquinas para introducir moneda
		//Máquina para lanzamiento de dados
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -0.03f, -32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MaquinaMoneda_M.RenderModel();

		//Máquina para línea de boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.5f, -0.03f, -32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MaquinaMoneda_M.RenderModel();

		//Máquina para jaula de bateo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, -0.03f, -3.5f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MaquinaMoneda_M.RenderModel();

		//Máquina para lanzamiento de hacha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(37.0f, -0.03f, -3.5f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MaquinaMoneda_M.RenderModel();

		//Máquina para dardos y globos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.5f, -0.03f, 32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MaquinaMoneda_M.RenderModel();

		//Máquina para golpea al topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(21.0f, -0.03f, 32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MaquinaMoneda_M.RenderModel();

		//Bancas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.5f, 1.2, 17.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banca_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.5f, 1.2f, 17.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banca_M.RenderModel();

		//Bocinas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, 1.5f, -40.0));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bocina.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.5f, -40.0));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bocina.RenderModel();

		//Botes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, 0.9f, 0.0));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bote_b.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 0.9f, 0.0));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bote_b.RenderModel();

		//Postes de luz
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-34.0f, 5.0f, -25.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(34.0f, 5.0f, -25.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		farola.RenderModel();

		//====== ATRACCIONES ======
		//Lanzamiento de hacha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 3.2f, -3.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		cabina.RenderModel();
		//diana
		model = glm::translate(model, glm::vec3(15.0f, 5.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		diana.RenderModel();
		//Hacha
		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, -5.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		hacha_M.RenderModel();

		//Mesa de dados
		//Base de la mesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, 2.0f, -32.0f));
		modelauxDados = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Base_M.RenderModel();

		//Borde de la mesa
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(0.0f, 1.51f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Borde_M.RenderModel();

		//Tablero de la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(0.0f, 1.15f, 0.0f));
		modelauxDados = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tablero_M.RenderModel();

		//Monedas decorativas para la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.08f, -0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Moneda_M.RenderModel();

		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.08f, 0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Moneda_M.RenderModel();

		//Dados para la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.11f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Dado_M.RenderModel();

		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.11f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Dado_M.RenderModel();

		//Línea de Boliche
		//Pista de boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 0.0f, -32.0f));
		modelauxBoliche = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PistaBoliche_M.RenderModel();

		//Canaleta izqueirda de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-2.8f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CanaletaBoliche_M.RenderModel();

		//Canaleta derecha de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(2.8f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CanaletaBoliche_M.RenderModel();

		//Bola de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		BolaBoliche_M.RenderModel();

		//Bolos
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();
		
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.35f, 0.6f, -5.6f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.35f, 0.6f, -5.6f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.7f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.7f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-1.05f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.35f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.35f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(1.05f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Bolo_M.RenderModel();

		//Golpea al topo
		//Mesa de golpear al topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 1.4f, 32.0f));
		modelauxTopo = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MesaTopo_M.RenderModel();

		//Letrero golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.3f, -1.75f));
		model = glm::scale(model, glm::vec3(0.3f, 0.37f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LetreroTopo_M.RenderModel();

		//Hoyos
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();
		
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		HoyoTopo_M.RenderModel();

		//Mesa para mazo de golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(2.93f, 1.43f, 0.0f));
		modelauxTopo = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MesaMazoTopo_M.RenderModel();

		//Mazo de golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 0.24f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		MazoTopo_M.RenderModel();


		/*
		//Moneda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 2.74f, -31.5f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Moneda_M.RenderModel();
		*/

		//====== PUESTOS ======
		//Puesto de bebidas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.5f, 3.25f, 10.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_bebidas.RenderModel();
		//Aguas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aguas.RenderModel();
		//Botellas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		botellas.RenderModel();
		//Latas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		latas.RenderModel();
		//Vasos
		modelauxbebidas = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//1
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//2
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//3
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//4
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//5
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//6
		vasos.RenderModel();
		model = modelauxbebidas;
		model = glm::translate(model, glm::vec3(2.0f,0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//7
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//8
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//9
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//10
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//11
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//12
		vasos.RenderModel();
		//Tarro
		model = modelauxbebidas;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tarro.RenderModel();

		//Puesto de Pizzas
		//Puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.5f, 3.0f, 10.0f));
		modelauxPizzas = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PuestoPizzas_M.RenderModel();

		//Pizzas
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PizzaLimon_M.RenderModel();
		
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PizzaPeperoni_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PizzaQueso_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PizzaHawaiana_M.RenderModel();

		//Platos
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(0.4f, 0.71f, 0.8f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		platos.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-8.95f, 0.71f, 0.8f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		platos.RenderModel();

		//Servilletas
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(0.0f, -0.23f, 0.82f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		servilletas.RenderModel();

		//Puesto de tacos
		//Puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, 3.25f, -10.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_tacos.RenderModel();
		//Tacos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tacos2.RenderModel();
		//Comal
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		comal.RenderModel();
		//Platos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		platos.RenderModel();
		//salsas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		salsa_roja.RenderModel();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		salsa_verde.RenderModel();
		//tabla
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tabla.RenderModel();
		//Trompo
		modelauxTacos = model;
		model = glm::translate(model, glm::vec3(-6.805f, 1.893f, -1.72f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		trompo.RenderModel();
		//Cuchillo
		model = modelauxTacos;
		model = glm::translate(model, glm::vec3(6.572f, -0.333f, -3.446f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuchillo.RenderModel();
		//Servilletas
		model = modelauxTacos;
		model = glm::translate(model, glm::vec3(7.484f, 4.911f, 3.573f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		servilletas.RenderModel();



		//blending: transparencia o traslucidez
		/*
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);
		*/

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
