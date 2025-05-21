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

float tiempoDurante;	
bool Ciclo_Dia;
const float tiempoCiclo = 1000.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
//Animacion
//Puertas
bool puertaAbierta = false;  // Controla si la puerta está abierta o cerrada
float anguloPuerta = 0.0f;  // Ángulo actual de la puerta
float velocidadPuerta = 2.0f; // Velocidad de apertura/cierre
float angulovaria = 0.0f;
static float anguloRotacion = 0.0f;

//Muffin
float MuffinAngulo = 0.0f;
glm::vec3 MuffinPos = glm::vec3(0.0f, 1.8f, 53.0f); // posición inicial

float MovPata = 0.0f;
float MovPataOffset;
bool Caminar = false;


//Dados
float movDado, rotDado;
float movDadoOffset, rotDadoOffset;
bool caer, girar;
bool dadoCaido = false;

//Hacha
float movHacha;
float movHachaOffset;
float rotHacha;
float rotHachaOffset;
bool avanza;
bool girarHacha=false;

//Bola
float movBola;
float movBolaOffset;
float rotBola;
float rotBolaOffset;
bool avanzaBola;
bool girarBola = false;



//Texturas
//Texture brickTexture;

//Modelos
Model Piso_M;
Model Laser_M;
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
Model AtrasBoliche_M;
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
//Puesto de hamburguesas
Model hamburguesas_Stripe;
//Jaula de bateo
Model jaulabateo;
Model pelota_jaulabateo;
Model bate_jaulabateo;
Model alfombra_jaulabateo;
Model lanzapelotas_jaulabateo;
//Dardos
Model puesto_Dardos;
Model dardo_Dardos;
Model cohetes_Dardos;
Model conejos_Dardos;
Model osos_Dardos;
Model gam_Dardos;
Model gaz_Dardos;
Model gro_Dardos;
//Hora de Aventura
//Rey Helado
Model CoronaReyHelado_M;
Model CuerpoReyHelado_M;
Model BrazosReyHelado_M;
Model ManoDerechaReyHelado_M;
Model ManoIzquierdaReyHelado_M;
Model BarbayPeloReyHelado_M;
Model CabezaReyHelado_M;
Model BocaReyHelado_M;
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
//Top Cat
//Cucho
Model Cuerpo_C;
Model Cabeza_C;
Model PataI_C;
Model PataD_C;
Model Cola_C;
Model ManoI_C;
Model ManoD_C;
Model BrazoI_C;
Model BrazoD_C;
//Don Gato
Model Cuerpo_TC;
Model Cabeza_TC;
Model PataI_TC;
Model PataD_TC;
Model BrazoI_TC;
Model BrazoD_TC;
Model Cola_TC;
//Benito
Model Cuerpo_B;
Model Cabeza_B;
Model PataI_B;
Model PataD_B;
Model BrazoI_B;
Model BrazoD_B;
//Bluey
// Bingo
Model cuerpo_Bingo;
Model brazouno_Bingo;
Model brazodos_Bingo;
Model patauno_Bingo;
Model patados_Bingo;
Model cola_Bingo;
//Bandit
Model cuerpo_Bandit;
Model brazouno_Bandit;
Model brazodos_Bandit;
Model patauno_Bandit;
Model patados_Bandit;
Model cola_Bandit;
//Stripe
Model cuerpo_Stripe;
Model brazouno_Stripe;
Model brazodos_Stripe;
Model patauno_Stripe;
Model patados_Stripe;
Model cola_Stripe;
//Muffin
Model cuerpo_Muffin;
Model ojouno_Muffin;
Model ojodos_Muffin;
Model cejauno_Muffin;
Model cejados_Muffin;
Model orejauno_Muffin;
Model orejados_Muffin;
Model hocico_Muffin;
Model cola_Muffin;
Model patauno_Muffin;
Model patados_Muffin;
Model brazouno_Muffin;
Model dedouno_Muffin;
Model dedodos_Muffin;
Model dedotres_Muffin;
Model dedocuatro_Muffin;
Model brazodos_Muffin;
Model dedocinco_Muffin;
Model dedoseis_Muffin;
Model dedosiete_Muffin;
Model dedoocho_Muffin;

Skybox skyboxdia;
Skybox skyboxnoche;

//materiales
Material Material_luminoso;
Material Material_oscuro;
Material Material_metalico;
Material Material_plastico;
Material Material_goma;
Material Material_vidrio;
Material Material_seda;
Material Material_madera;
Material Material_piso;
Material Material_Muffin;
Material Material_Gato;


bool bandera = false;


GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight, LightDAY, LightNIGHT;
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

	camera = Camera(glm::vec3(0.0f, 3.4f, 53.0), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 180.0f, 0.3f, 0.5f);

	//Modelos 
	Piso_M = Model();
	Piso_M.LoadModel("Models/Piso_obj.obj");
	Laser_M = Model();
	Laser_M.LoadModel("Models/Laser_obj.obj");
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
	AtrasBoliche_M = Model();
	AtrasBoliche_M.LoadModel("Models/AtrasBoliche_obj.obj");
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
	//Puesto de Hamburguesas
	hamburguesas_Stripe = Model();
	hamburguesas_Stripe.LoadModel("Models/hamburguesas_Stripe.obj");
	//Jaula de Bateo
	jaulabateo = Model();
	jaulabateo.LoadModel("Models/jaulabateo.obj");
	pelota_jaulabateo = Model();
	pelota_jaulabateo.LoadModel("Models/pelota_jaulabateo.obj");
	bate_jaulabateo = Model();
	bate_jaulabateo.LoadModel("Models/bate_jaulabateo.obj");
	alfombra_jaulabateo = Model();
	alfombra_jaulabateo.LoadModel("Models/alfombra_jaulabateo.obj");
	lanzapelotas_jaulabateo = Model();
	lanzapelotas_jaulabateo.LoadModel("Models/lanzapelotas_jaulabateo.obj");
	//Lanzamiento de Dardos
	puesto_Dardos = Model();
	puesto_Dardos.LoadModel("Models/puesto_Dardos.obj");
	dardo_Dardos = Model();
	dardo_Dardos.LoadModel("Models/dardo_Dardos.obj");
	cohetes_Dardos = Model();
	cohetes_Dardos.LoadModel("Models/cohetes_Dardos.obj");
	conejos_Dardos = Model();
	conejos_Dardos.LoadModel("Models/conejos_Dardos.obj");
	osos_Dardos = Model();
	osos_Dardos.LoadModel("Models/osos_Dardos.obj");
	gam_Dardos = Model();
	gam_Dardos.LoadModel("Models/globo_amarilloDardos.obj");
	gaz_Dardos = Model();
	gaz_Dardos.LoadModel("Models/globo_azulDardos.obj");
	gro_Dardos = Model();
	gro_Dardos.LoadModel("Models/globo_rosaDardos.obj");
	//Rey Helado
	CuerpoReyHelado_M = Model();
	CuerpoReyHelado_M.LoadModel("Models/ReyHelado/CuerpoReyHelado_obj.obj");
	CoronaReyHelado_M = Model();
	CoronaReyHelado_M.LoadModel("Models/ReyHelado/CoronaReyHelado_obj.obj");
	BrazosReyHelado_M = Model();
	BrazosReyHelado_M.LoadModel("Models/ReyHelado/BrazosReyHelado_obj.obj");
	ManoDerechaReyHelado_M = Model();
	ManoDerechaReyHelado_M.LoadModel("Models/ReyHelado/ManoDerechaReyHelado_obj.obj");
	ManoIzquierdaReyHelado_M = Model();
	ManoIzquierdaReyHelado_M.LoadModel("Models/ReyHelado/ManoIzquierdaReyHelado_obj.obj");
	BarbayPeloReyHelado_M = Model();
	BarbayPeloReyHelado_M.LoadModel("Models/ReyHelado/BarbayPeloReyHelado_obj.obj");
	CabezaReyHelado_M = Model();
	CabezaReyHelado_M.LoadModel("Models/ReyHelado/CabezaReyHelado_obj.obj");
	BocaReyHelado_M = Model();
	BocaReyHelado_M.LoadModel("Models/ReyHelado/BocaReyHelado_obj.obj");
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
	//Cucho
	Cuerpo_C = Model();
	Cuerpo_C.LoadModel("Models/Cucho/Cuerpo_C.obj");
	Cabeza_C = Model();
	Cabeza_C.LoadModel("Models/Cucho/Cabeza_C.obj");
	PataI_C = Model();
	PataI_C.LoadModel("Models/Cucho/pataI_C.obj");
	PataD_C = Model();
	PataD_C.LoadModel("Models/Cucho/pataD_C.obj");
	Cola_C = Model();
	Cola_C.LoadModel("Models/Cucho/Cola_C.obj");
	ManoI_C = Model();
	ManoI_C.LoadModel("Models/Cucho/manoI_C.obj");
	ManoD_C = Model();
	ManoD_C.LoadModel("Models/Cucho/manoD_C.obj");
	BrazoI_C = Model();
	BrazoI_C.LoadModel("Models/Cucho/brazoI_C.obj");
	BrazoD_C = Model();
	BrazoD_C.LoadModel("Models/Cucho/brazoD_C.obj");
	//Don Gato
	Cuerpo_TC = Model();
	Cuerpo_TC.LoadModel("Models/DonGato/Cuerpo_TC.obj");
	Cabeza_TC = Model();
	Cabeza_TC.LoadModel("Models/DonGato/Cabeza_TC.obj");
	PataI_TC = Model();
	PataI_TC.LoadModel("Models/DonGato/pataI_TC.obj");
	PataD_TC = Model();
	PataD_TC.LoadModel("Models/DonGato/pataD_TC.obj");
	BrazoI_TC = Model();
	BrazoI_TC.LoadModel("Models/DonGato/brazoI_TC.obj");
	BrazoD_TC = Model();
	BrazoD_TC.LoadModel("Models/DonGato/brazoD_TC.obj");
	Cola_TC = Model();
	Cola_TC.LoadModel("Models/DonGato/Cola_TC.obj");
	//Benito
	Cuerpo_B = Model();
	Cuerpo_B.LoadModel("Models/benito/Cuerpo_B.obj");
	Cabeza_B = Model();
	Cabeza_B.LoadModel("Models/benito/Cabeza_B.obj");
	PataI_B = Model();
	PataI_B.LoadModel("Models/benito/pataI_B.obj");
	PataD_B = Model();
	PataD_B.LoadModel("Models/benito/pataD_B.obj");
	BrazoI_B = Model();
	BrazoI_B.LoadModel("Models/benito/brazoI_B.obj");
	BrazoD_B = Model();
	BrazoD_B.LoadModel("Models/benito/brazoD_B.obj");
	//Bingo
	cuerpo_Bingo = Model();
	cuerpo_Bingo.LoadModel("Models/Bingo/cuerpo_Bingo.obj");
	brazouno_Bingo = Model();
	brazouno_Bingo.LoadModel("Models/Bingo/brazouno_Bingo.obj");
	brazodos_Bingo = Model();
	brazodos_Bingo.LoadModel("Models/Bingo/brazodos_Bingo.obj");
	patauno_Bingo = Model();
	patauno_Bingo.LoadModel("Models/Bingo/patauno_Bingo.obj");
	patados_Bingo = Model();
	patados_Bingo.LoadModel("Models/Bingo/patados_Bingo.obj");
	cola_Bingo = Model();
	cola_Bingo.LoadModel("Models/Bingo/cola_Bingo.obj");
	//Bandit
	cuerpo_Bandit = Model();
	cuerpo_Bandit.LoadModel("Models/Bandit/cuerpo_Bandit.obj");
	brazouno_Bandit = Model();
	brazouno_Bandit.LoadModel("Models/Bandit/brazouno_Bandit.obj");
	brazodos_Bandit = Model();
	brazodos_Bandit.LoadModel("Models/Bandit/brazodos_Bandit.obj");
	patauno_Bandit = Model();
	patauno_Bandit.LoadModel("Models/Bandit/patauno_Bandit.obj");
	patados_Bandit = Model();
	patados_Bandit.LoadModel("Models/Bandit/patados_Bandit.obj");
	cola_Bandit = Model();
	cola_Bandit.LoadModel("Models/Bandit/cola_Bandit.obj");
	//Stripe
	cuerpo_Stripe = Model();
	cuerpo_Stripe.LoadModel("Models/Stripe/cuerpo_Stripe.obj");
	brazouno_Stripe = Model();
	brazouno_Stripe.LoadModel("Models/Stripe/brazouno_Stripe.obj");
	brazodos_Stripe = Model();
	brazodos_Stripe.LoadModel("Models/Stripe/brazodos_Stripe.obj");
	patauno_Stripe = Model();
	patauno_Stripe.LoadModel("Models/Stripe/patauno_Stripe.obj");
	patados_Stripe = Model();
	patados_Stripe.LoadModel("Models/Stripe/patados_Stripe.obj");
	cola_Stripe = Model();
	cola_Stripe.LoadModel("Models/Stripe/cola_Stripe.obj");
	//Muffin
	cuerpo_Muffin = Model();
	cuerpo_Muffin.LoadModel("Models/Muffin/cuerpo_Muffin.obj");
	ojouno_Muffin = Model();
	ojouno_Muffin.LoadModel("Models/Muffin/ojouno_Muffin.obj");
	ojodos_Muffin = Model();
	ojodos_Muffin.LoadModel("Models/Muffin/ojodos_Muffin.obj");
	cejauno_Muffin = Model();
	cejauno_Muffin.LoadModel("Models/Muffin/cejauno_Muffin.obj");
	cejados_Muffin = Model();
	cejados_Muffin.LoadModel("Models/Muffin/cejados_Muffin.obj");
	orejauno_Muffin = Model();
	orejauno_Muffin.LoadModel("Models/Muffin/orejauno_Muffin.obj");
	orejados_Muffin = Model();
	orejados_Muffin.LoadModel("Models/Muffin/orejados_Muffin.obj");
	hocico_Muffin = Model();
	hocico_Muffin.LoadModel("Models/Muffin/hocico_Muffin.obj");
	cola_Muffin = Model();
	cola_Muffin.LoadModel("Models/Muffin/cola_Muffin.obj");
	patauno_Muffin = Model();
	patauno_Muffin.LoadModel("Models/Muffin/patauno_Muffin.obj");
	patados_Muffin = Model();
	patados_Muffin.LoadModel("Models/Muffin/patados_Muffin.obj");
	brazouno_Muffin = Model();
	brazouno_Muffin.LoadModel("Models/Muffin/brazouno_Muffin.obj");
	dedouno_Muffin = Model();
	dedouno_Muffin.LoadModel("Models/Muffin/dedouno_Muffin.obj");
	dedodos_Muffin = Model();
	dedodos_Muffin.LoadModel("Models/Muffin/dedodos_Muffin.obj");
	dedotres_Muffin = Model();
	dedotres_Muffin.LoadModel("Models/Muffin/dedotres_Muffin.obj");
	dedocuatro_Muffin = Model();
	dedocuatro_Muffin.LoadModel("Models/Muffin/dedocuatro_Muffin.obj");
	brazodos_Muffin = Model();
	brazodos_Muffin.LoadModel("Models/Muffin/brazodos_Muffin.obj");
	dedocinco_Muffin = Model();
	dedocinco_Muffin.LoadModel("Models/Muffin/dedocinco_Muffin.obj");
	dedoseis_Muffin = Model();
	dedoseis_Muffin.LoadModel("Models/Muffin/dedoseis_Muffin.obj");
	dedosiete_Muffin = Model();
	dedosiete_Muffin.LoadModel("Models/Muffin/dedosiete_Muffin.obj");
	dedoocho_Muffin = Model();
	dedoocho_Muffin.LoadModel("Models/Muffin/dedoocho_Muffin.obj");



	std::vector<std::string> skyboxdiaFaces;
	skyboxdiaFaces.push_back("Textures/Skybox/lake_rt.jpg");
	skyboxdiaFaces.push_back("Textures/Skybox/lake_lf.jpg");
	skyboxdiaFaces.push_back("Textures/Skybox/lake_dn.jpg");
	skyboxdiaFaces.push_back("Textures/Skybox/lake_up.jpg");
	skyboxdiaFaces.push_back("Textures/Skybox/lake_bk.jpg");
	skyboxdiaFaces.push_back("Textures/Skybox/lake_ft.jpg");


	skyboxdia = Skybox(skyboxdiaFaces);

	std::vector<std::string> skyboxnocheFaces;
	skyboxnocheFaces.push_back("Textures/Skybox/lake-n_rt.jpg");
	skyboxnocheFaces.push_back("Textures/Skybox/lake-n_lf.jpg");
	skyboxnocheFaces.push_back("Textures/Skybox/lake-n_dn.jpg");
	skyboxnocheFaces.push_back("Textures/Skybox/lake-n_up.jpg");
	skyboxnocheFaces.push_back("Textures/Skybox/lake-n_bk.jpg");
	skyboxnocheFaces.push_back("Textures/Skybox/lake-n_ft.jpg");

	skyboxnoche = Skybox(skyboxnocheFaces);

	Material_luminoso = Material(5.0f, 256);
	Material_oscuro = Material(0.3f, 8);
	Material_metalico = Material(5.0f, 1024);       // Alto brillo como metal pulido
	Material_plastico = Material(0.8f, 64);         // Brillo suave típico de plástico
	Material_goma = Material(0.05f, 1);             // Prácticamente sin brillo
	Material_vidrio = Material(3.5f, 256);          // Brillo similar al vidrio
	Material_seda = Material(0.4f, 16);             // Brillo suave como tela
	Material_madera = Material(0.2f, 8);
	Material_piso = Material(0.25f, 16);
	Material_Muffin = Material(0.35f, 32);
	Material_Gato = Material(0.3f, 16);


	//==================DIRECCIONAL==================

	//Contador de luces direccionales
	LightDAY = DirectionalLight(1.0f, 1.0f, 0.9f, 0.4f, 0.6f, 0.0f, -1.0f, 0.0f);
	LightNIGHT = DirectionalLight(0.8f, 0.8f, 1.0f, 0.1f, 0.2f, 0.0f, -1.0f, 0.0f);

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

	//Luz morada
	spotLights[1] = SpotLight(1.0f, 0.0f, 1.0f,
		//Intensidad ambiental y tonalidad
		2.0f, 1.0f,
		//Posición x, y, z
		29.4f, 1.5f, 8.0f,
		//Dirección de la luz
		-1.0f, 0.0f, 1.0f,
		//No poner en 0.0f, 0.0f, 0.0f en la linea de abajo
		1.0f, 0.05f, 0.0f,
		//Ángulo de apertura
		8.0f);
	spotLightCount++;

	//Luz amarilla
	spotLights[2] = SpotLight(1.0f, 1.0f, 0.0f,
		//Intensidad ambiental y tonalidad
		2.0f, 1.0f,
		//Posición x, y, z
		-29.4f, 1.5f, 8.0f,
		//Dirección de la luz
		1.0f, 0.0f, 1.0f,
		//No poner en 0.0f, 0.0f, 0.0f en la linea de abajo
		1.0f, 0.05f, 0.0f,
		//Ángulo de apertura
		8.0f);
	spotLightCount++;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	
	//Iluminacion
	tiempoDurante = 0.0f;
	Ciclo_Dia = true;

	//Movimiento de patas
	MovPataOffset = 3.0f;

	//Dados
	movDado = 0.0f;
	movDadoOffset = 0.05f;
	rotDado = 0.0f;
	rotDadoOffset = 5.0f;
	caer = true;

	//Hacha
	movHacha = 0.0f;
	movHachaOffset = 0.5f;
	rotHacha = 0.0f;
	rotHachaOffset = 1.0f;
	avanza = true;

	//Bola
	movBola = 0.0f;
	movBolaOffset = 0.1f;
	rotBola = 0.0f;
	rotBolaOffset = 1.0f;
	avanzaBola=true;

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		angulovaria += 1.0f * deltaTime;
		anguloRotacion += 1.0f; // Ajusta este valor para cambiar la velocidad de rotación

		tiempoDurante += deltaTime;
		if (tiempoDurante >= tiempoCiclo) { Ciclo_Dia = !Ciclo_Dia; tiempoDurante = 0.0f; }

		float angle = (tiempoDurante / tiempoCiclo) * M_PI;
		float xDir = cos(angle);

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Ciclo del dia y la noche
		if (Ciclo_Dia) {
			LightDAY.SetDirection(xDir, -0.25f, 0.0f);
			shaderList[0].SetDirectionalLight(&LightDAY);
			skyboxdia.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else {
			LightNIGHT.SetDirection(xDir, -0.25f, 0.0f);
			shaderList[0].SetDirectionalLight(&LightNIGHT);
			skyboxnoche.DrawSkybox(camera.calculateViewMatrix(), projection);
		}


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
		if (Ciclo_Dia) { shaderList[0].SetDirectionalLight(&LightDAY); }
		else { shaderList[0].SetDirectionalLight(&LightNIGHT); }


		//Pasar luces al shader
		if (Ciclo_Dia)
			shaderList[0].SetPointLights(pointLights, pointLightCount - 3);
		else
			shaderList[0].SetPointLights(pointLights, pointLightCount);

		bandera = mainWindow.getarticulacion2();
		if (mainWindow.getarticulacion2() == 1.0f) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else {
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
		}


		glm::mat4 model(1.0);
		glm::mat4 modelauxlamp(1.0);
		glm::mat4 modelauxbebidas(1.0);
		glm::mat4 modelauxPizzas(1.0);
		glm::mat4 modelauxDados(1.0);
		glm::mat4 modelauxBoliche(1.0);
		glm::mat4 modelauxTopo(1.0);
		glm::mat4 modelauxPuertas(1.0);
		glm::mat4 modelauxTacos(1.0);
		glm::mat4 modelauxReyHelado(1.0);
		glm::mat4 modelauxReyHelado2(1.0);
		glm::mat4 modelauxBMO(1.0);
		glm::mat4 modelauxGunter(1.0);
		glm::mat4 modelauxLimonagrio(1.0);
		glm::mat4 modelauxCucho(1.0);
		glm::mat4 modelauxJaulaB(1.0);
		glm::mat4 modelauxJaulaB2(1.0);
		glm::mat4 modelauxDardos(1.0);
		glm::mat4 modelauxBingo(1.0);
		glm::mat4 modelauxBandit(1.0);
		glm::mat4 modelauxStripe(1.0);
		glm::mat4 modelauxMuffin(1.0);
		glm::mat4 modelauxMuffin2(1.0);

		//Piso de la Feria
		model = glm::mat4(1.0);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_piso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Piso_M.RenderModel();

		//Laser 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 1.5f, 8.0f));
		model = glm::rotate(model, -60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_luminoso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Laser_M.RenderModel();

		//Laser 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 1.5f, 8.0f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_luminoso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Laser_M.RenderModel();

		//Rejas
		model = glm::mat4(1.0);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaN_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(10.0f, 8.49f, 50.842f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaN_2.RenderModel();

		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(-30.161f, 7.5f, -42.403f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaR_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(-44.141f, 7.5f, -27.561f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaR_2.RenderModel();

		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(42.612f, 13.861f, -28.45f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaV_1.RenderModel();
		model = modelauxPuertas;
		model = glm::translate(model, glm::vec3(27.255f, 13.861f, -43.279f));
		model = glm::rotate(model, anguloPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuertaV_2.RenderModel();

		//Máquinas para introducir moneda
		//Máquina para lanzamiento de dados
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -0.03f, -32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para línea de boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.5f, -0.03f, -32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para jaula de bateo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, -0.03f, -3.5f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para lanzamiento de hacha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(37.0f, -0.03f, -3.5f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para dardos y globos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.5f, -0.03f, 32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Máquina para golpea al topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(21.0f, -0.03f, 32.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MaquinaMoneda_M.RenderModel();

		//Bancas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.5f, 1.2, 17.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		banca_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.5f, 1.2f, 17.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		banca_M.RenderModel();

		//Bocinas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, 1.5f, -40.0));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		bocina.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.5f, -40.0));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		bocina.RenderModel();

		//Botes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, 0.9f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		bote_b.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 0.9f, 0.0));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bote_b.RenderModel();

		//Postes de luz
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_seda.UseMaterial(uniformSpecularIntensity, uniformShininess);
		farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-34.0f, 5.0f, -25.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_seda.UseMaterial(uniformSpecularIntensity, uniformShininess);
		farola.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(34.0f, 5.0f, -25.0));
		modelauxlamp = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		poste.RenderModel();
		model = modelauxlamp;
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_seda.UseMaterial(uniformSpecularIntensity, uniformShininess);
		farola.RenderModel();

		//====== ATRACCIONES ======
		//Lanzamiento de hacha
		girarHacha = mainWindow.getarticulacion4();
		if (girarHacha==1) {
			if (movHacha > -30.0f)
			{
				movHacha -= movHachaOffset * deltaTime;
				rotHacha -= rotHachaOffset * deltaTime;
			}
			else
			{
				avanza = false;
			}
		}
		else {
			if (movHacha < 0.0f)
			{
				movHacha += movHachaOffset * deltaTime;
				rotHacha += rotHachaOffset * deltaTime;
			}
			else
			{
				avanza = true;
			}
		}
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 3.2f, -3.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cabina.RenderModel();
		//diana
		model = glm::translate(model, glm::vec3(15.0f, 5.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		diana.RenderModel();
		//Hacha
		model = glm::translate(model, glm::vec3(movHacha -3.0f,-5.0f, 0.0f));
		model = glm::rotate(model, rotHacha * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		hacha_M.RenderModel();

		//Mesa de dados
		//Base de la mesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, 2.0f, -32.0f));
		modelauxDados = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Base_M.RenderModel();

		//Borde de la mesa
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(0.0f, 1.51f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Borde_M.RenderModel();

		//Tablero de la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(0.0f, 1.15f, 0.0f));
		modelauxDados = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tablero_M.RenderModel();

		//Monedas decorativas para la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.08f, -0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Moneda_M.RenderModel();

		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.08f, 0.2f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Moneda_M.RenderModel();

		dadoCaido = mainWindow.getarticulacion3();
		if (dadoCaido == 1) {
			if (movDado > -1.0f)
			{
				movDado -= movDadoOffset * deltaTime;
				rotDado -= rotDadoOffset * deltaTime;
			}
			else
			{
				caer = false;
			}
		}
		else {
			if (movDado < 0.0f)
			{
				movDado += movDadoOffset * deltaTime;
				rotDado += rotDadoOffset * deltaTime;
			}
			else
			{
				caer = true;
			}
		}

		//Dados para la mesa de dados
		model = modelauxDados;
		model = glm::translate(model, glm::vec3(2.0f, 0.11f - movDado, 1.0f));
		model = glm::rotate(model, rotDado * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dado_M.RenderModel();

		model = modelauxDados;
		//model = glm::translate(model, glm::vec3(2.0f, 0.11f, 1.2f));
		model = glm::translate(model, glm::vec3(2.0f, 0.11f - movDado, 1.2f));
		model = glm::rotate(model, rotDado * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dado_M.RenderModel();

		//Línea de Boliche
		//Pista de boliche
		girarHacha = mainWindow.getarticulacion5();
		if (girarHacha == 1) {
			if (movBola > -14.0f)
			{
				movBola -= movBolaOffset * deltaTime;
				rotBola -= rotBolaOffset * deltaTime;
			}
			else
			{
				avanzaBola = false;
			}
		}
		else {
			if (movBola < 0.0f)
			{
				movBola += movBolaOffset * deltaTime;
				rotBola += rotBolaOffset * deltaTime;
			}
			else
			{
				avanzaBola = true;
			}
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 0.0f, -28.0f));
		modelauxBoliche = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PistaBoliche_M.RenderModel();

		//Canaleta izqueirda de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-2.8f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CanaletaBoliche_M.RenderModel();

		//Canaleta derecha de boliche
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(2.8f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CanaletaBoliche_M.RenderModel();

		//Parte Trasera
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, -9.3f));
		model = glm::scale(model, glm::vec3(0.405f, 0.405f, 0.405f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		AtrasBoliche_M.RenderModel();

		//Bola de boliche
		model = modelauxBoliche;
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, 8.0f));
		model = glm::translate(model, glm::vec3(0.0f + movBola*0.2, 1.0f, movBola + 8.0f));
		model = glm::rotate(model, rotBola * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BolaBoliche_M.RenderModel();

		//Bolos
		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -5.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.35f, 0.6f, -5.6f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.35f, 0.6f, -5.6f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.7f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.7f, 0.6f, -6.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-1.05f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(-0.35f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(0.35f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		model = modelauxBoliche;
		model = glm::translate(model, glm::vec3(1.05f, 0.6f, -6.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bolo_M.RenderModel();

		//Golpea al topo
		//Mesa de golpear al topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 1.4f, 32.0f));
		modelauxTopo = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MesaTopo_M.RenderModel();

		//Letrero golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.3f, -1.75f));
		model = glm::scale(model, glm::vec3(0.3f, 0.37f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		LetreroTopo_M.RenderModel();

		//Hoyos
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(-1.35f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(1.35f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		HoyoTopo_M.RenderModel();

		//Aleatorizar topos
		double tiempotopos = 0.0;
		int numeroAleatorio = 1;

		srand(static_cast<unsigned int>(time(0)));
		double tiempoActualTopos = glfwGetTime();
		if (tiempoActualTopos - tiempotopos >= 0.9) {
			numeroAleatorio = (rand() % 3) + 1;
			tiempotopos = tiempoActualTopos;
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TopoBluey_M.RenderModel();

		//Mesa para mazo de golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(2.93f, 1.43f, 0.0f));
		modelauxTopo = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MesaMazoTopo_M.RenderModel();

		//Mazo de golpea al topo
		model = modelauxTopo;
		model = glm::translate(model, glm::vec3(0.0f, 0.24f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MazoTopo_M.RenderModel();

		///Lanzamiento de Dardos
		float cicloTotal = 100.0f;
		float cic = fmod(angulovaria, cicloTotal);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.2f, 3.36f, -6.7f));
		model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
		modelauxDardos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puesto_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-22.0f, -6.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_seda.UseMaterial(uniformSpecularIntensity, uniformShininess);
		conejos_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-22.0f, -6.6f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cohetes_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(22.0f, -6.2f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_seda.UseMaterial(uniformSpecularIntensity, uniformShininess);
		osos_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(22.0f, -6.6f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cohetes_Dardos.RenderModel();

		// --- Primer dardo (centro) ---
		model = modelauxDardos;
		bool enVuelo = cic >= 20.0f && cic < 80.0f;
		bool impactado = cic >= 80.0f;
		float gX = -5.1f;
		float gY = 10.05f;
		float gZ = -21.1f;
		float iX1 = 0.0f;
		float iY1 = -9.5f;
		float iZ1 = 24.0f;

		float dX1 = iX1;
		float dY1 = iY1;
		float dZ1 = iZ1;

		if (enVuelo) {
			float progreso = (cic - 20.0f) / 60.0f;
			dX1 = iX1 + (gX - iX1) * progreso;
			dY1 = iY1 + (gY - iY1) * progreso;
			dZ1 = iZ1 + (gZ - iZ1) * progreso + sin(progreso * M_PI) * 5.0f;
		}
		else if (impactado) {
			dX1 = gX;
			dY1 = gY;
			dZ1 = gZ;
		}

		model = glm::translate(model, glm::vec3(dX1, dY1, dZ1));
		if (enVuelo || impactado) {
			model = glm::rotate(model, glm::radians(cic * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dardo_Dardos.RenderModel();

		// --- Segundo dardo (derecha) ---
		model = modelauxDardos;
		float cicloDardo2 = fmod(angulovaria + 15.0f, cicloTotal);
		enVuelo = cicloDardo2 >= 20.0f && cicloDardo2 < 80.0f;
		impactado = cicloDardo2 >= 80.0f;
		float oX2 = 4.8f;
		float oY2 = 1.1f;
		float oZ2 = -21.0f;
		float iX2 = 4.4f;
		float iY2 = -9.5f;
		float iZ2 = 24.0f;

		float dX2 = iX2;
		float dY2 = iY2;
		float dZ2 = iZ2;

		if (enVuelo) {
			float progreso = (cicloDardo2 - 20.0f) / 60.0f;
			dX2 = iX2 + (oX2 - iX2) * progreso;
			dY2 = iY2 + (oY2 - iY2) * progreso;
			dZ2 = iZ2 + (oZ2 - iZ2) * progreso + sin(progreso * M_PI) * 5.0f;
		}
		else if (impactado) {
			dX2 = oX2 + 0.3f;
			dY2 = oY2;
			dZ2 = oZ2;
		}

		model = glm::translate(model, glm::vec3(dX2, dY2, dZ2));
		if (enVuelo || impactado) {
			model = glm::rotate(model, glm::radians(cicloDardo2 * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dardo_Dardos.RenderModel();

		// --- Tercer dardo (izquierda) ---
		model = modelauxDardos;
		float cicloDardo3 = fmod(angulovaria + 15.0f, cicloTotal);
		enVuelo = cicloDardo3 >= 20.0f && cicloDardo3 < 80.0f;
		impactado = cicloDardo3 >= 80.0f;
		float oX3 = 13.6f;
		float oY3 = -2.2f;
		float oZ3 = -21.0f;

		float iX3 = -4.4f;
		float iY3 = -9.5f;
		float iZ3 = 24.0f;

		float dX3 = iX3;
		float dY3 = iY3;
		float dZ3 = iZ3;

		if (enVuelo) {
			float progreso = (cicloDardo3 - 20.0f) / 60.0f;
			dX3 = iX3 + (oX3 - iX3) * progreso;
			dY3 = iY3 + (oY3 - iY3) * progreso;
			dZ3 = iZ3 + (oZ3 - iZ3) * progreso + sin(progreso * M_PI) * 5.0f;
		}
		else if (impactado) {
			dX3 = oX3 - 0.3f;
			dY3 = oY3;
			dZ3 = oZ3;
		}

		model = glm::translate(model, glm::vec3(dX3, dY3, dZ3));
		if (enVuelo || impactado) {
			model = glm::rotate(model, glm::radians(cicloDardo3 * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dardo_Dardos.RenderModel();

		//Primer Fila
		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-11.2f, 11.05f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gam_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-5.1f, 11.05f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gaz_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(1.1f, 11.05f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gro_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(7.2f, 11.05f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gam_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(13.6f, 11.05f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gaz_Dardos.RenderModel();

		//Tercer Fila
		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-11.2f, -2.2f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gaz_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-5.1f, -2.2f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gro_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(1.1f, -2.2f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gam_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(7.2f, -2.2f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gaz_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(13.6f, -2.2f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gro_Dardos.RenderModel();

		//Segunda Fila
		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-11.2f, 4.7f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gro_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(-5.1f, 4.5f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gam_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(1.1f, 4.5f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gaz_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(7.2f, 4.5f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gro_Dardos.RenderModel();

		model = modelauxDardos;
		model = glm::translate(model, glm::vec3(13.6f, 4.5f, -21.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gam_Dardos.RenderModel();

		//Jaula de Bateo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.2f, 3.0f, 29.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
		modelauxJaulaB = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		jaulabateo.RenderModel();

		model = modelauxJaulaB;
		model = glm::translate(model, glm::vec3(24.5f, -25.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_seda.UseMaterial(uniformSpecularIntensity, uniformShininess);
		alfombra_jaulabateo.RenderModel();

		model = modelauxJaulaB;
		model = glm::translate(model, glm::vec3(24.5f, -5.4f, 0.0f));
		float bateRotacion = 45.0f * sin(glm::radians(angulovaria * 2.0f));
		model = glm::rotate(model, glm::radians(bateRotacion), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(bateRotacion * 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		bate_jaulabateo.RenderModel();

		model = modelauxJaulaB;
		model = glm::translate(model, glm::vec3(-34.2f, -1.0f, -0.6f));
		modelauxJaulaB2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		lanzapelotas_jaulabateo.RenderModel();

		model = modelauxJaulaB2;
		float ciclo = angulovaria - floor(angulovaria / 100.0f) * 100.0f;
		bool lanzado = ciclo < 10.0f;
		bool trayectoria = ciclo >= 10.0f && ciclo < 60.0f;
		bool golpeado = ciclo >= 60.0f && ciclo < 65.0f;
		bool rebote = ciclo >= 65.0f;
		float iX = 0.0f;
		float iY = 0.0f;
		float iZ = 0.0f;
		float pelotaX = 0.0f;
		float pelotaY = 0.0f;
		float pelotaZ = 0.0f;

		if (lanzado) {
			float disparado = ciclo / 10.0f;
			pelotaX = iX + 0.3f * sin(glm::radians(disparado * 720.0f));
			pelotaY = iY + 0.2f * cos(glm::radians(disparado * 360.0f));
			pelotaZ = iZ;
		}
		else if (trayectoria) {
			float direccion = (ciclo - 10.0f) / 50.0f;
			pelotaX = iX + direccion * 59.0f;
			pelotaY = iY + 3.0f * sin(glm::radians(direccion * 180.0f));
			pelotaZ = iZ + 1.0f * sin(glm::radians(direccion * 120.0f));
		}
		else if (golpeado) {
			float direcc = (ciclo - 60.0f) / 5.0f;
			pelotaX = iX + 59.0f;
			pelotaY = iY + 3.0f + direcc * 5.0f;
			pelotaZ = iZ + 1.0f + direcc * 3.0f;
		}
		else {
			float regreso = (ciclo - 65.0f) / 35.0f;
			pelotaX = iX + 56.0f - regreso * 15.0f;
			pelotaY = iY + 8.0f + regreso * 10.0f;
			pelotaZ = iZ + 4.0f + regreso * 5.0f;
		}
		model = glm::translate(model, glm::vec3(pelotaX, pelotaY, pelotaZ));
		float velocidad = rebote || golpeado ? 45.0f : 15.0f;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_goma.UseMaterial(uniformSpecularIntensity, uniformShininess);
		pelota_jaulabateo.RenderModel();


		//====== PUESTOS ======
		//Puesto de bebidas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.5f, 3.25f, 10.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puesto_bebidas.RenderModel();
		//Aguas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		aguas.RenderModel();
		//Botellas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_vidrio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		botellas.RenderModel();
		//Latas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		latas.RenderModel();
		//Vasos
		modelauxbebidas = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//1
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//2
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//3
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//4
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//5
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//6
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = modelauxbebidas;
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//7
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//8
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//9
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//10
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//11
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//12
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		vasos.RenderModel();
		//Tarro
		model = modelauxbebidas;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tarro.RenderModel();

		//Puesto de Pizzas
		//Puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.5f, 3.0f, 10.0f));
		modelauxPizzas = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoPizzas_M.RenderModel();

		//Pizzas
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaLimon_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaPeperoni_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaQueso_M.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PizzaHawaiana_M.RenderModel();

		//Platos
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(0.4f, 0.71f, 0.8f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		platos.RenderModel();

		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(-8.95f, 0.71f, 0.8f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		platos.RenderModel();

		//Servilletas
		model = modelauxPizzas;
		model = glm::translate(model, glm::vec3(0.0f, -0.23f, 0.82f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		servilletas.RenderModel();

		//Puesto de tacos
		//Puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, 3.25f, -10.0f));
		model = glm::scale(model, glm::vec3(0.37f, 0.37f, 0.37f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puesto_tacos.RenderModel();
		//Tacos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tacos2.RenderModel();
		//Comal
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		comal.RenderModel();
		//Platos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_plastico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		platos.RenderModel();
		//salsas
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		salsa_roja.RenderModel();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		salsa_verde.RenderModel();
		//tabla
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_madera.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tabla.RenderModel();
		//Trompo
		modelauxTacos = model;
		if (anguloRotacion >= 360.0f) {
			anguloRotacion -= 360.0f;
		}
		model = glm::translate(model, glm::vec3(-6.805f, 1.893f, -1.72f));
		model = glm::rotate(model, glm::radians(anguloRotacion), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		trompo.RenderModel();
		//Cuchillo
		model = modelauxTacos;
		model = glm::translate(model, glm::vec3(6.572f, -0.333f, -3.446f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cuchillo.RenderModel();
		//Servilletas
		model = modelauxTacos;
		model = glm::translate(model, glm::vec3(7.484f, 4.911f, 3.573f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		servilletas.RenderModel();

		//Puesto de Hamburguesas
		//Puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, 0.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		hamburguesas_Stripe.RenderModel();

		//====== PERSONAJES ======
		//Muffin (Bluey)
		if (mainWindow.turnLeft)
			MuffinAngulo += 2.0f;

		if (mainWindow.turnRight)
			MuffinAngulo -= 2.0f;

		if (mainWindow.moveForward)
		{
			if (!Caminar) {
				MovPata += MovPataOffset * deltaTime;
				if (MovPata > 20.0f) 
					Caminar = true;
			}
			else
			{
				MovPata -= MovPataOffset * deltaTime;
				if (MovPata < -20.0f)
					Caminar = false;
			}
			float rad = glm::radians(MuffinAngulo);
			MuffinPos.x -= sin(rad) * 0.1f;
			MuffinPos.z -= cos(rad) * 0.1f;
		}

		if (mainWindow.moveBackward)
		{
			if (!Caminar) {
				MovPata += MovPataOffset * deltaTime;
				if (MovPata > 20.0f)
					Caminar = true;
			}
			else
			{
				MovPata -= MovPataOffset * deltaTime;
				if (MovPata < -20.0f)
					Caminar = false;
			}
			float rad = glm::radians(MuffinAngulo);
			MuffinPos.x += sin(rad) * 0.1f;
			MuffinPos.z += cos(rad) * 0.1f;
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, MuffinPos);
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(MuffinAngulo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelauxMuffin = model;
		model = glm::scale(model, glm::vec3(0.044f, 0.048f, 0.044f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cuerpo_Muffin.RenderModel();

		//Ojo Derecho
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(-0.58f, 0.36f, -0.32f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_luminoso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ojouno_Muffin.RenderModel();

		//Ceja Derecha
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(-0.77f, 0.95f, -0.36f));
		model = glm::scale(model, glm::vec3(0.045f, 0.045f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cejauno_Muffin.RenderModel();

		//Ojo Izquierdo
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(-0.58f, 0.36f, 0.32f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_luminoso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ojodos_Muffin.RenderModel();

		//Ceja Izquierda
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(-0.77f, 0.95f, 0.36f));
		model = glm::scale(model, glm::vec3(0.045f, 0.045f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cejados_Muffin.RenderModel();

		//Oreja Derecha
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -0.4f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		orejauno_Muffin.RenderModel();

		//Oreja Izquierda
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.4f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		orejados_Muffin.RenderModel();

		//Hocico
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(-0.6f, -0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		hocico_Muffin.RenderModel();

		//Pata Derecha
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -0.4f));
		model = glm::rotate(model, MovPata * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		patauno_Muffin.RenderModel();

		//Pata Izquierda
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.4f));
		model = glm::rotate(model, MovPata * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		patados_Muffin.RenderModel();

		//Cola
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(0.72f, -0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.045f, 0.04f));
		model = glm::rotate(model, sin(glm::radians(angulovaria * 1)), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cola_Muffin.RenderModel();

		//Brazo Izquierdo
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -0.78f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		modelauxMuffin2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		brazouno_Muffin.RenderModel();

		//Dedo uno
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedouno_Muffin.RenderModel();

		//Dedo dos
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, 1.6f, -7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedodos_Muffin.RenderModel();

		//Dedo tres
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, -1.7f, -7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedotres_Muffin.RenderModel();

		//Dedo cuatro
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedocuatro_Muffin.RenderModel();

		//Brazo Derecho
		model = modelauxMuffin;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.78f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		modelauxMuffin2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		brazodos_Muffin.RenderModel();

		//Dedo cinco
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedocinco_Muffin.RenderModel();

		//Dedo seis
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, 1.6f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedoseis_Muffin.RenderModel();

		//Dedo siete
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, -1.7f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedosiete_Muffin.RenderModel();

		//Dedo ocho
		model = modelauxMuffin2;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dedoocho_Muffin.RenderModel();

		//Bingo NPC (Bluey)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 2.0f, -2.7f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelauxBingo = model;
		model = glm::scale(model, glm::vec3(0.044f, 0.048f, 0.044f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Muffin.UseMaterial(uniformSpecularIntensity, uniformShininess);
		cuerpo_Bingo.RenderModel();
		//Brazo Izquierdo
		model = modelauxBingo;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -0.76f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazouno_Bingo.RenderModel();
		//Brazo Derecho
		model = modelauxBingo;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.76f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazodos_Bingo.RenderModel();
		//Pata Derecha
		model = modelauxBingo;
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, -0.5f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patauno_Bingo.RenderModel();
		//Pata Izquierda
		model = modelauxBingo;
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, 0.5f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patados_Bingo.RenderModel();
		//Cola
		model = modelauxBingo;
		model = glm::translate(model, glm::vec3(0.72f, -0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.045f, 0.04f));
		model = glm::rotate(model, sin(glm::radians(angulovaria * 1)), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cola_Bingo.RenderModel();

		//Bandit NPC (Bluey)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.2f, 3.3f, 34.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelauxBandit = model;
		model = glm::scale(model, glm::vec3(0.044f, 0.048f, 0.044f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo_Bandit.RenderModel();
		//Brazo Izquierdo
		model = modelauxBandit;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -0.9f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazouno_Bandit.RenderModel();
		//Brazo Derecho
		model = modelauxBandit;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.9f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazodos_Bandit.RenderModel();
		//Pata Derecha
		model = modelauxBandit;
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -0.5f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patauno_Bandit.RenderModel();
		//Pata Izquierda
		model = modelauxBandit;
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.5f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patados_Bandit.RenderModel();
		//Cola
		model = modelauxBandit;
		model = glm::translate(model, glm::vec3(0.85f, -1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.045f, 0.04f));
		model = glm::rotate(model, sin(glm::radians(angulovaria * 1)), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cola_Bandit.RenderModel();

		//Stripe (Bluey)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, 2.8f, -11.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelauxStripe = model;
		model = glm::scale(model, glm::vec3(0.044f, 0.048f, 0.044f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo_Stripe.RenderModel();
		//Brazo Izquierdo
		model = modelauxStripe;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -0.92f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazouno_Stripe.RenderModel();
		//Brazo Derecho
		model = modelauxStripe;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.92f));
		model = glm::scale(model, glm::vec3(0.05f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazodos_Stripe.RenderModel();
		//Pata Derecha
		model = modelauxStripe;
		model = glm::translate(model, glm::vec3(0.0f, -1.4f, -0.5f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patauno_Stripe.RenderModel();
		//Pata Izquierda
		model = modelauxStripe;
		model = glm::translate(model, glm::vec3(0.0f, -1.4f, 0.5f));
		model = glm::scale(model, glm::vec3(0.045f, 0.055f, 0.045f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patados_Stripe.RenderModel();
		//Cola
		model = modelauxStripe;
		model = glm::translate(model, glm::vec3(0.77f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.045f, 0.04f));
		model = glm::rotate(model, sin(glm::radians(angulovaria * 1)), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cola_Stripe.RenderModel();

		//Cucho (Don Gato y su Pandilla)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, 2.37f, -12.5f));
		model = glm::scale(model, glm::vec3(0.28f, 0.28f, 0.28f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		modelauxCucho = model;
		Cuerpo_C.RenderModel();
		//Cabeza
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(0.0f, 4.082f, -0.056f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cabeza_C.RenderModel();
		//Patas
		//Pata izquierda
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(1.0f, -3.943f, 0.196f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PataI_C.RenderModel();
		//Pata derecha
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-1.0f, -3.943f, 0.196f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PataD_C.RenderModel();
		//Brazos
		//Brazo izquierdo
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(1.085f, 1.686f, -0.029f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoI_C.RenderModel();
		//Mano
		model = glm::translate(model, glm::vec3(1.663f, -1.661f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ManoI_C.RenderModel();
		//Brazo derecho
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-1.085f, 1.686f, -0.029f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoD_C.RenderModel();
		//Mano
		model = glm::translate(model, glm::vec3(-1.663f, -1.661f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ManoD_C.RenderModel();
		//Cola
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-0.064f, -0.187f, -0.426f));
		model = glm::rotate(model, sin(glm::radians(angulovaria * 2)), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cola_C.RenderModel();

		//Don Gato (Don Gato y su Pandilla)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.5f, 2.4f, 7.5f));
		model = glm::scale(model, glm::vec3(0.27f, 0.27f, 0.27f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		modelauxCucho = model;
		Cuerpo_TC.RenderModel();
		//Cabeza
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(0.0f, 3.618f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cabeza_TC.RenderModel();
		//Patas
		//Pata izquierda
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(0.9f, -5.25f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PataI_TC.RenderModel();
		//Pata derecha
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-0.9f, -5.25f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PataD_TC.RenderModel();
		//Brazos
		//Brazo izquierdo
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(1.5f, 1.8f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoI_TC.RenderModel();
		//Brazo derecho
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-1.5f, 1.8f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoD_TC.RenderModel();
		//Cola
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-0.064f, -0.187f, -0.326f));
		model = glm::rotate(model, cos(glm::radians(angulovaria)), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cola_TC.RenderModel();

		//Benito (Don Gato y su Pandilla)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.5f, 1.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.27f, 0.27f, 0.27f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		modelauxCucho = model;
		Cuerpo_B.RenderModel();
		//Cabeza
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(0.0f, 2.624f, -0.143f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cabeza_B.RenderModel();
		//Patas
		//Pata izquierda
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(0.884f, -2.622f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PataI_B.RenderModel();
		//Pata derecha
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-0.884f, -2.622f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PataD_B.RenderModel();
		//Brazos
		//Brazo izquierdo
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(2.074f, 1.575f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoI_B.RenderModel();
		//Brazo derecho
		model = modelauxCucho;
		model = glm::translate(model, glm::vec3(-2.074f, 1.575f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Gato.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoD_B.RenderModel();


		//Rey Helado (Hora de Aventura)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, 2.4f, 32.0f));
		modelauxReyHelado = model;
		modelauxReyHelado2 = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CuerpoReyHelado_M.RenderModel();

		//Brazos
		model = modelauxReyHelado;
		model = glm::translate(model, glm::vec3(0.0f, 1.25f, 0.0f));
		model = glm::rotate(model, -30 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, sin(glm::radians(angulovaria)), glm::vec3(1.0f, 0.0f, 0.0f));
		modelauxReyHelado = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazosReyHelado_M.RenderModel();

		//Mano derecha
		model = modelauxReyHelado;
		model = glm::translate(model, glm::vec3(-1.55f, -2.1f, 0.95f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ManoDerechaReyHelado_M.RenderModel();

		//Mano izquierda
		model = modelauxReyHelado;
		model = glm::translate(model, glm::vec3(1.55f, -2.1f, 0.95f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ManoIzquierdaReyHelado_M.RenderModel();

		//Cabeza
		model = modelauxReyHelado2;
		model = glm::translate(model, glm::vec3(0.0f, 2.4f, 0.9f));
		modelauxReyHelado = model;
		modelauxReyHelado2 = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CabezaReyHelado_M.RenderModel();

		//Barba y pelo
		model = modelauxReyHelado2;
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, -0.38f));
		modelauxReyHelado2 = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BarbayPeloReyHelado_M.RenderModel();

		//Boca
		model = modelauxReyHelado2;
		model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.75f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BocaReyHelado_M.RenderModel();

		//Corona
		model = modelauxReyHelado;
		model = glm::translate(model, glm::vec3(0.0f, 0.55f, -0.65f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_luminoso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CoronaReyHelado_M.RenderModel();

		//BMO (Hora de aventura)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 1.5f, -32.0f));
		modelauxBMO = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CuerpoBMO_M.RenderModel();

		//Botones
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.0f, -0.27f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BotonesBMO_M.RenderModel();

		//Letras
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		LetrasBMO_M.RenderModel();

		//Piernas
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernasBMO_M.RenderModel();

		//Brazo izquierdo
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(0.6f, -0.15f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoIzquierdoBMO_M.RenderModel();

		//Brazo derecho
		model = modelauxBMO;
		model = glm::translate(model, glm::vec3(-0.6f, -0.15f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_metalico.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoDerechoBMO_M.RenderModel();

		//Gunter (Hora de aventura)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.73f, -24.0f));
		modelauxGunter = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CuerpoGunter_M.RenderModel();

		//Ojos
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.29f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_luminoso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		OjosGunter_M.RenderModel();

		//Pico
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.45f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_luminoso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PicoGunter_M.RenderModel();

		//Aletas
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		AletasGunter_M.RenderModel();

		//Patas
		model = modelauxGunter;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PatasGunter_M.RenderModel();

		//Limonagrio (Hora de aventura)
		//Cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.5f, 3.5f, 7.0f));
		modelauxLimonagrio = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CuerpoLimonagrio_M.RenderModel();

		//Piernas
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(0.0f, -2.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernasLimonagrio_M.RenderModel();

		//Manos
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(-0.19f, -0.25f, 0.25f));
		model = glm::scale(model, glm::vec3(0.395f, 0.395f, 0.395f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ManosLimonagrio_M.RenderModel();

		//Cabeza
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(0.0f, 1.7f, 0.28f));
		modelauxLimonagrio = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CabezaLimonagrio_M.RenderModel();

		//Cara
		model = modelauxLimonagrio;
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.57f));
		modelauxLimonagrio = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_oscuro.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CaraLimonagrio_M.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
