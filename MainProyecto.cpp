//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

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
float anguloPuerta = 0.0f;  // Ángulo actual de la puerta
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
//Golpea al topo
Model MesaTopo_M;
Model LetreroTopo_M;
Model HoyoTopo_M;
Model MesaMazoTopo_M;
Model MazoTopo_M;
Model TopoDGP_M;
Model TopoHDA_M;
Model TopoBluey_M;
//Puesto de pizzas
Model PuestoPizzas_M;
Model PizzaLimon_M;
Model PizzaPeperoni_M;
Model PizzaQueso_M;
Model PizzaHawaiana_M;
//BMO
Model CuerpoBMO_M;
Model BotonesBMO_M;
Model LetrasBMO_M;
Model PiernasBMO_M;
Model BrazoIzquierdoBMO_M;
Model BrazoDerechoBMO_M;
//Gunter
Model CuerpoGunter_M;
Model OjosGunter_M;
Model PicoGunter_M;
Model AletasGunter_M;
Model PatasGunter_M;
//Limonagrio
Model CuerpoLimonagrio_M;
Model PiernasLimonagrio_M;
Model ManosLimonagrio_M;
Model CabezaLimonagrio_M;
Model CaraLimonagrio_M;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;

bool bandera = false;


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


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
	mainWindow = Window(1600, 900);
	mainWindow.Initialise();

	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

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
	TopoDGP_M = Model();
	TopoDGP_M.LoadModel("Models/TopoDonGatoysuPandilla_obj.obj");
	TopoHDA_M = Model();
	TopoHDA_M.LoadModel("Models/TopoHoradeAventura_obj.obj");
	TopoBluey_M = Model();
	TopoBluey_M.LoadModel("Models/TopoBluey_obj.obj");
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
	//BMO
	CuerpoBMO_M = Model();
	CuerpoBMO_M.LoadModel("Models/BMO/CuerpoBMO_obj.obj");
	BotonesBMO_M = Model();
	BotonesBMO_M.LoadModel("Models/BMO/BotonesBMO_obj.obj");
	LetrasBMO_M = Model();
	LetrasBMO_M.LoadModel("Models/BMO/LetrasBMO_obj.obj");
	PiernasBMO_M = Model();
	PiernasBMO_M.LoadModel("Models/BMO/PiernasBMO_obj.obj");
	BrazoIzquierdoBMO_M = Model();
	BrazoIzquierdoBMO_M.LoadModel("Models/BMO/BrazoIzquierdoBMO_obj.obj");
	BrazoDerechoBMO_M = Model();
	BrazoDerechoBMO_M.LoadModel("Models/BMO/BrazoDerechoBMO_obj.obj");
	//Gunter
	CuerpoGunter_M = Model();
	CuerpoGunter_M.LoadModel("Models/Gunter/CuerpoGunter_obj.obj");
	OjosGunter_M = Model();
	OjosGunter_M.LoadModel("Models/Gunter/OjosGunter_obj.obj");
	PicoGunter_M = Model();
	PicoGunter_M.LoadModel("Models/Gunter/PicoGunter_obj.obj");
	AletasGunter_M = Model();
	AletasGunter_M.LoadModel("Models/Gunter/AletasGunter_obj.obj");
	PatasGunter_M = Model();
	PatasGunter_M.LoadModel("Models/Gunter/PatasGunter_obj.obj");
	//Limonagrio
	CuerpoLimonagrio_M = Model();
	CuerpoLimonagrio_M.LoadModel("Models/Limonagrio/CuerpoLimonagrio_obj.obj");
	PiernasLimonagrio_M = Model();
	PiernasLimonagrio_M.LoadModel("Models/Limonagrio/PiernasLimonagrio_obj.obj");
	ManosLimonagrio_M = Model();
	ManosLimonagrio_M.LoadModel("Models/Limonagrio/ManosLimonagrio_obj.obj");
	CabezaLimonagrio_M = Model();
	CabezaLimonagrio_M.LoadModel("Models/Limonagrio/CabezaLimonagrio_obj.obj");
	CaraLimonagrio_M = Model();
	CaraLimonagrio_M.LoadModel("Models/Limonagrio/CaraLimonagrio_obj.obj");


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
		0.4f, 0.4f,
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
		bandera = mainWindow.getarticulacion2();
		if (bandera == 1.0f)
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		else
			shaderList[0].SetPointLights(pointLights, pointLightCount - 3);

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
		glm::mat4 modelauxBMO(1.0);
		glm::mat4 modelauxGunter(1.0);
		glm::mat4 modelauxLimonagrio(1.0);

		//Piso de la Feria
		model = glm::mat4(1.0);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Piso_M.RenderModel();

		//Rejas
		model = glm::mat4(1.0);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rejas_M.RenderModel();

		//Puertas
		puertaAbierta = mainWindow.getarticulacion1();
		if (puertaAbierta == 1)
		{
			anguloPuerta += velocidadPuerta * deltaTime;
			if (anguloPuerta > 90.0f)
			{
				anguloPuerta = 90.0f;
			}
		}
		else
		{
			anguloPuerta -= velocidadPuerta * deltaTime;
			if (anguloPuerta < 0.0f)
			{
				anguloPuerta = 0.0f;
			}
		}
		modelauxPuertas = model;
		model = glm::translate(model, glm::vec3(-10.0f, 8.49f, 50.842f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaN_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(10.0f, 8.49f, 50.842f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaN_2.RenderModel();

		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(-30.161f, 7.5f, -42.403f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaR_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(-44.141f, 7.5f, -27.561f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaR_2.RenderModel();

		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(42.612f, 13.861f, -28.45f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaV_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(27.255f, 13.861f, -43.279f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaV_2.RenderModel();

		//Máquinas para introducir moneda
		//Máquina para lanzamiento de dados
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -0.03f, -32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para línea de boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.5f, -0.03f, -32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para jaula de bateo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, -0.03f, -3.5f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para lanzamiento de hacha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(37.0f, -0.03f, -3.5f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para dardos y globos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.5f, -0.03f, 32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para golpea al topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(21.0f, -0.03f, 32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Bancas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.5f, 1.2, 17.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		banca_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.5f, 1.2f, 17.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		banca_M.RenderModel();

		//Bocinas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, 1.5f, -40.0));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		bocina.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.5f, -40.0));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		bocina.RenderModel();

		//Botes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, 0.9f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		bote_b.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 0.9f, 0.0));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bote_b.RenderModel();

		//Postes de luz
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-34.0f, 5.0f, -25.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(34.0f, 5.0f, -25.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		farola.RenderModel();

		//====== ATRACCIONES ======
		//Lanzamiento de hacha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 3.2f, -3.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cabina.RenderModel();
		//diana
		model = glm::translate(model, glm::vec3(15.0f, 5.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		diana.RenderModel();
		//Hacha
		model = glm::translate(model, glm::vec3(-3.0f, -5.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		hacha_M.RenderModel();

		//Mesa de dados
		//Base de la mesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, 2.0f, -32.0f));
		modelauxDados = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Base_M.RenderModel();

		//Borde de la mesa
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(0.0f, 1.51f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Borde_M.RenderModel();

		//Tablero de la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(0.0f, 1.15f, 0.0f));
		modelauxDados = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tablero_M.RenderModel();

		//Monedas decorativas para la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.08f, -0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Moneda_M.RenderModel();

		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.08f, 0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Moneda_M.RenderModel();

		//Dados para la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.11f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dado_M.RenderModel();

		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.11f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dado_M.RenderModel();

		//Línea de Boliche
		//Pista de boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 0.0f, -32.0f));
		modelauxBoliche = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PistaBoliche_M.RenderModel();

		//Canaleta izqueirda de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-2.8f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CanaletaBoliche_M.RenderModel();

		//Canaleta derecha de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(2.8f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CanaletaBoliche_M.RenderModel();

		//Bola de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BolaBoliche_M.RenderModel();

		//Bolos
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.35f, 0.6f, -5.6f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.35f, 0.6f, -5.6f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.7f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.7f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-1.05f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.35f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.35f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(1.05f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		//Golpea al topo
		//Mesa de golpear al topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 1.4f, 32.0f));
		modelauxTopo = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MesaTopo_M.RenderModel();

		//Letrero golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.3f, -1.75f));
		model = glm::scale(model, glm::vec3(0.3f, 0.37f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		LetreroTopo_M.RenderModel();

		//Hoyos
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		//Aleatorizar topos
		double tiempotopos = 0.0;
		int numeroAleatorio = 1;

		srand(static_cast<unsigned int>(time(0)));
		double currentTime = glfwGetTime();
		if (currentTime - tiempotopos >= 0.9) {
			numeroAleatorio = (rand() % 3) + 1;
			tiempotopos = currentTime;
		}

		//Topo 1
		model = modelauxTopo;
		if (numeroAleatorio == 2) {
			model = glm::translate(model, glm::vec3(-1.35f, 1.65f, -1.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(-1.35f, -1.65f, -1.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoHDA_M.RenderModel();

		//Topo 2
		model = modelauxTopo;
		if (numeroAleatorio == 1) {
			model = glm::translate(model, glm::vec3(0.0f, 1.65f, -1.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(0.0f, -1.65f, -1.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoBluey_M.RenderModel();

		//Topo 3
		model = modelauxTopo;
		if (numeroAleatorio == 3) {
			model = glm::translate(model, glm::vec3(1.35f, 1.65f, -1.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(1.35f, -1.65f, -1.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoDGP_M.RenderModel();

		//Topo 4
		model = modelauxTopo;
		if (numeroAleatorio == 3) {
			model = glm::translate(model, glm::vec3(-1.35f, 1.65f, 0.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(-1.35f, -1.65f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoBluey_M.RenderModel();

		//Topo 5
		model = modelauxTopo;
		if (numeroAleatorio == 2) {
			model = glm::translate(model, glm::vec3(0.0f, 1.65f, 0.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(0.0f, -1.65f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoDGP_M.RenderModel();

		//Topo 6
		model = modelauxTopo;
		if (numeroAleatorio == 1) {
			model = glm::translate(model, glm::vec3(1.35f, 1.65f, 0.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(1.35f, -1.65f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoHDA_M.RenderModel();

		//Topo 7
		model = modelauxTopo;
		if (numeroAleatorio == 1) {
			model = glm::translate(model, glm::vec3(-1.35f, 1.65f, 1.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(-1.35f, -1.65f, 1.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoDGP_M.RenderModel();

		//Topo 8
		model = modelauxTopo;
		if (numeroAleatorio == 3) {
			model = glm::translate(model, glm::vec3(0.0f, 1.65f, 1.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(0.0f, -1.65f, 1.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoHDA_M.RenderModel();

		//Topo 9
		model = modelauxTopo;
		if (numeroAleatorio == 2) {
			model = glm::translate(model, glm::vec3(1.35f, 1.65f, 1.0f));
		}
		else {
			model = glm::translate(model, glm::vec3(1.35f, -1.65f, 1.0f));
		}
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoBluey_M.RenderModel();

		//Mesa para mazo de golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(2.93f, 1.43f, 0.0f));
		modelauxTopo = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MesaMazoTopo_M.RenderModel();

		//Mazo de golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 0.24f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MazoTopo_M.RenderModel();


		/*
		//Moneda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 2.74f, -31.5f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Moneda_M.RenderModel();
		*/

		//====== PUESTOS ======
		//Puesto de bebidas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.5f, 3.25f, 10.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puesto_bebidas.RenderModel();
		//Aguas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		aguas.RenderModel();
		//Botellas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		botellas.RenderModel();
		//Latas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		latas.RenderModel();
		//Vasos
		modelauxbebidas = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//1
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//2
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//3
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//4
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//5
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//6
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = modelauxbebidas;
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//7
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//8
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//9
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//10
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//11
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//12
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		//Tarro
		model = modelauxbebidas;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();

		//Puesto de Pizzas
		//Puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.5f, 3.0f, 10.0f));
		modelauxPizzas = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoPizzas_M.RenderModel();

		//Pizzas
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaLimon_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaPeperoni_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaQueso_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaHawaiana_M.RenderModel();

		//Platos
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(0.4f, 0.71f, 0.8f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		platos.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-8.95f, 0.71f, 0.8f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		platos.RenderModel();

		//Servilletas
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(0.0f, -0.23f, 0.82f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		servilletas.RenderModel();

		//Puesto de tacos
		//Puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, 3.25f, -10.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puesto_tacos.RenderModel();
		//Tacos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tacos2.RenderModel();
		//Comal
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		comal.RenderModel();
		//Platos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		platos.RenderModel();
		//salsas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		salsa_roja.RenderModel();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		salsa_verde.RenderModel();
		//tabla
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tabla.RenderModel();
		//Trompo
		modelauxTacos = model;
		model = glm::translate(model, glm::vec3(-6.805f, 1.893f, -1.72f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		trompo.RenderModel();
		//Cuchillo
		model = modelauxTacos;
		model = glm::translate(model, glm::vec3(6.572f, -0.333f, -3.446f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cuchillo.RenderModel();
		//Servilletas
		model = modelauxTacos;
		model = glm::translate(model, glm::vec3(7.484f, 4.911f, 3.573f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		servilletas.RenderModel();

		//====== PERSONAJES ======

		//Muffin (Bluey)


		//Cucho (Don Gato y su Pandilla


		//Rey Helado (Hora de Aventura)


		//BMO (Hora de aventura)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 1.5f, -32.0f));
		modelauxBMO = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CuerpoBMO_M.RenderModel();

		//Botones
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.0f, -0.27f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BotonesBMO_M.RenderModel();

		//Letras
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		LetrasBMO_M.RenderModel();

		//Piernas
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernasBMO_M.RenderModel();

		//Brazo izquierdo
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.6f, -0.15f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzquierdoBMO_M.RenderModel();

		//Brazo derecho
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(-0.6f, -0.15f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDerechoBMO_M.RenderModel();

		//Gunter (Hora de aventura)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.73f, -24.0f));
		modelauxGunter = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CuerpoGunter_M.RenderModel();

		//Ojos
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.29f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		OjosGunter_M.RenderModel();

		//Pico
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.45f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PicoGunter_M.RenderModel();
		
		//Aletas
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		AletasGunter_M.RenderModel();

		//Patas
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PatasGunter_M.RenderModel();

		//Limonagrio (Hora de aventura)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.5f, 3.5f, 7.0f));
		modelauxLimonagrio = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CuerpoLimonagrio_M.RenderModel();

		//Piernas
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(0.0f, -2.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernasLimonagrio_M.RenderModel();

		//Manos
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(-0.19f, -0.25f, 0.25f));
		model = glm::scale(model, glm::vec3(0.395f, 0.395f, 0.395f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ManosLimonagrio_M.RenderModel();

		//Cabeza
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, 0.28f));
		modelauxLimonagrio = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CabezaLimonagrio_M.RenderModel();

		//Cara
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.57f));
		modelauxLimonagrio = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CaraLimonagrio_M.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}