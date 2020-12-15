// *********************************************************************
// *************************Proyecto final******************************
//****************************Equipo 01*********************************
//************************Maceta inteligente****************************
// *********************************************************************

// *********************************************************************
// incluimos las librerias necesarias y declaramos los pines
// *********************************************************************
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib2.h>
#include <BH1750FVI.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        4 // On Trinket or Gemma, suggest changing this to 1
#define PIN2        5
#define NUMPIXELS 16 // Popular NeoPixel ring size
#define bomba 3
#define pinTierra A5
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
#define DHTPIN 11
#define DHTTYPE DHT11
// creamos los objetos necesarios para el dht, el sensor de luminosidad y los aros led
DHT dht(DHTPIN, DHTTYPE);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContHighRes);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

// *********************************************************************
// COnfiguraciones para el display LCD
// *********************************************************************
#define _LCDML_DISP_cols  20                  //20 filas
#define _LCDML_DISP_rows  4                   //4 columnas

#define _LCDML_DISP_cfg_cursor                     0x7E   // Simbolo del cursor
#define _LCDML_DISP_cfg_scrollbar                  1      // habilitamos la scrollbar

LiquidCrystal_I2C lcd(0x27, _LCDML_DISP_cols, _LCDML_DISP_rows);    //Creamos el objeto para la LCD

const uint8_t scroll_bar[5][8] = {                                  //Creamos la acrollbar
  {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001},
  {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001},
  {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001},
  {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001},
  {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}
};

// *********************************************************************
// Prototipos de las funciones
// *********************************************************************
void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();

// *********************************************************************
// Creamos las variables globales
// *********************************************************************
int moisture_percentage = 0;
float temperature;
int Humid;
int lux;
int dia;
int mes;
int anno;
int hora;
int minuto;
int autoriego = 0;
int brillo1 = 255, brillo2 = 255;
int r1 = 255, g1 = 10, b1 = 255;
int r2 = 255, g2 = 10, b2 = 255;
unsigned long iniciaTempo, iniciaTempo2;
int L1_aux = 0, L2_aux;
bool autoriego_aux = false;

// *********************************************************************
// Objetos del menú
// *********************************************************************
LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // raíz del menú
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// Creación del menú y sus funciones
// *********************************************************************

LCDML_add         (0  , LCDML_0          , 1  , "Informacion"        , mFunc_information);
LCDML_add         (1  , LCDML_0          , 3  , "Riego"              , NULL);
LCDML_add         (2  , LCDML_0_3        , 1  , "Manual"             , NULL);
LCDML_add         (3  , LCDML_0_3_1      , 1  , "Encender"           , riego_encender);
LCDML_add         (4  , LCDML_0_3_1      , 2  , "Apagar"             , riego_apagar);
LCDML_add         (5  , LCDML_0_3_1      , 3  , "Regresar"           , mFunc_back);
LCDML_add         (6 , LCDML_0_3         , 2  , "Intervalos"         , riego_intervalo);
LCDML_add         (7 , LCDML_0_3         , 3  , "Modos"              , NULL);
LCDML_add         (8 , LCDML_0_3_3       , 1  , "Humedad 80%"        , humedad_80);
LCDML_add         (9 , LCDML_0_3_3       , 2  , "Humedad 60%"        , humedad_60);
LCDML_add         (10 , LCDML_0_3_3      , 3  , "Humedad 40%"        , humedad_40);
LCDML_add         (11 , LCDML_0_3_3      , 4  , "Humedad 20%"        , humedad_20);
LCDML_add         (12 , LCDML_0_3_3      , 5  , "Desactivar"         , humedad_0);
LCDML_add         (13 , LCDML_0_3_3      , 6  , "Regresar"           , mFunc_back);
LCDML_add         (14 , LCDML_0_3        , 4  , "Regresar"           , mFunc_back);
LCDML_add         (15 , LCDML_0          , 4  , "Luz"                , NULL);
///////////////////////////////////////////////////////////////////////////////////////////////
LCDML_add         (16 , LCDML_0_4        , 1  , "Lampara 1"          , NULL);
LCDML_add         (17 , LCDML_0_4_1      , 1  , "Manual"             , NULL);
LCDML_add         (18 , LCDML_0_4_1_1    , 1  , "Encender"           , Encender_L1);
LCDML_add         (19 , LCDML_0_4_1_1    , 2  , "Apagar"             , Apagar_L1);
LCDML_add         (20 , LCDML_0_4_1_1    , 3 , "Regresar"            , mFunc_back);
LCDML_add         (21 , LCDML_0_4_1      , 2  , "Intervalo"          , L1_intervalo);
LCDML_add         (22 , LCDML_0_4_1      , 3  , "Intensidad"         , L1_intensidad);
LCDML_add         (23 , LCDML_0_4_1      , 4  , "Color"              , NULL);
LCDML_add         (24 , LCDML_0_4_1_4    , 1  , "Rojo"               , L1_rojo);
LCDML_add         (25 , LCDML_0_4_1_4    , 2  , "Azul"               , L1_azul);
LCDML_add         (26 , LCDML_0_4_1_4    , 3  , "Verde"              , L1_verde);
LCDML_add         (27 , LCDML_0_4_1_4    , 4  , "Violeta"            , L1_violeta);
LCDML_add         (28 , LCDML_0_4_1_4    , 5  , "Naranja"            , L1_naranja);
LCDML_add         (29 , LCDML_0_4_1_4    , 6  , "Amarillo"           , L1_amarillo);
LCDML_add         (30 , LCDML_0_4_1_4    , 7  , "Blanco"             , L1_blanco);
LCDML_add         (31 , LCDML_0_4_1_4    , 8  , "Regresar"           , mFunc_back);
LCDML_add         (32 , LCDML_0_4_1      , 5  , "Regresar"           , mFunc_back);
//////////////////////////////////////////////////////////////////////////////////////////////////
LCDML_add         (33 , LCDML_0_4        , 2  , "Lampara 2"          , NULL);
LCDML_add         (34 , LCDML_0_4_2      , 1  , "Manual"             , NULL);
LCDML_add         (35 , LCDML_0_4_2_1    , 1  , "Encender"           , Encender_L2);
LCDML_add         (36 , LCDML_0_4_2_1    , 2  , "Apagar"             , Apagar_L2);
LCDML_add         (37 , LCDML_0_4_2_1    , 3 , "Regresar"            , mFunc_back);
LCDML_add         (38 , LCDML_0_4_2      , 2  , "Intervalo"          , L2_intervalo);
LCDML_add         (39 , LCDML_0_4_2      , 3  , "Intensidad"         , L2_intensidad);
LCDML_add         (40 , LCDML_0_4_2      , 4  , "Color"              , NULL);
LCDML_add         (41 , LCDML_0_4_2_4    , 1  , "Rojo"               , L2_rojo);
LCDML_add         (42 , LCDML_0_4_2_4    , 2  , "Azul"               , L2_azul);
LCDML_add         (43 , LCDML_0_4_2_4    , 3  , "Verde"              , L2_verde);
LCDML_add         (44 , LCDML_0_4_2_4    , 4  , "Violeta"            , L2_violeta);
LCDML_add         (45 , LCDML_0_4_2_4    , 5  , "Naranja"            , L2_naranja);
LCDML_add         (46 , LCDML_0_4_2_4    , 6  , "Amarillo"           , L2_amarillo);
LCDML_add         (47 , LCDML_0_4_2_4    , 7  , "Blanco"             , L2_blanco);
LCDML_add         (48 , LCDML_0_4_2_4    , 8  , "Regresar"           , mFunc_back);
LCDML_add         (49 , LCDML_0_4_2      , 5  , "Regresar"           , mFunc_back);
LCDML_add         (50 , LCDML_0_4        , 3  , "Regresar"           , mFunc_back);
LCDML_add       (51 , LCDML_0            , 5  , "Salvapantallas"     , mFunc_screensaver);


#define _LCDML_DISP_cnt    51           //definimos el numero de elementos que tiene nuestro menú

LCDML_createMenu(_LCDML_DISP_cnt);      //creamos el menú

// *********************************************************************
// SETUP
// *********************************************************************
void setup()
{
  //inicializamos los objetos
  Serial.begin(9600);
  Wire.begin();
  LightSensor.begin();
  dht.begin();
  lcd.init();
  lcd.backlight();

  // caracteres especiales para la scrollbar
  lcd.createChar(0, (uint8_t*)scroll_bar[0]);
  lcd.createChar(1, (uint8_t*)scroll_bar[1]);
  lcd.createChar(2, (uint8_t*)scroll_bar[2]);
  lcd.createChar(3, (uint8_t*)scroll_bar[3]);
  lcd.createChar(4, (uint8_t*)scroll_bar[4]);

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // habilitamos Menu Rollover
  LCDML.MENU_enRollover();

  LCDML.SCREEN_enable(mFunc_screensaver, 10000); // definimos el screensaver a 10 segundos
  //inicializamos los dos aros LED y los apagamos
  pixels.begin();
  pixels2.begin();
  pixels.setBrightness(brillo1);
  pixels2.setBrightness(brillo2);
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
    pixels.show();
    pixels2.show();
    delay(300);
  }
  pixels.clear();
  pixels2.clear();
  pixels.show();
  pixels2.show();
}

// *********************************************************************
// LOOP
// *********************************************************************
void loop()
{
  //leemos los valores de los sensores y los mandamos por el puerto serial a la esp32
  LCDML.loop();
  moisture_percentage = (-0.3165) * analogRead(pinTierra) + 321.52;
  lux = LightSensor.GetLightIntensity();
  Humid = dht.readHumidity();
  Serial.println("-5");
  Serial.println(Humid);
  temperature = dht.readTemperature();
  Serial.println("-4");
  Serial.println(temperature);
  lux = LightSensor.GetLightIntensity();
  Serial.println("-3");
  Serial.println(lux);
  moisture_percentage = (-0.3165) * analogRead(pinTierra) + 321.52;
  Serial.println("-2");
  Serial.println(moisture_percentage);
  //creamos un ciclo para la función de autorriego
  if (autoriego_aux == true)
  {

    if (moisture_percentage < autoriego)
    { pinMode(bomba, OUTPUT);
      digitalWrite(bomba, LOW);
    }
    else
    {
      digitalWrite(bomba, HIGH);
    }
  }
  //creamos un ciclo para la función de intervalo de luz
  unsigned long currentMillis = millis();
  if (L1_aux != 0) {
    if (currentMillis - iniciaTempo > L1_aux) {
      pixels.clear();
      pixels.show();
    }
  }
  unsigned long currentMillis2 = millis();
  if (L2_aux != 0) {
    if (currentMillis2 - iniciaTempo2 > L2_aux) {
      pixels2.clear();
      pixels2.show();
    }
  }

  pixels.setBrightness(brillo1);
  pixels2.setBrightness(brillo2);
  pixels.show();
  pixels2.show();
}
//función para el sensor
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  lux = LightSensor.GetLightIntensity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
}
