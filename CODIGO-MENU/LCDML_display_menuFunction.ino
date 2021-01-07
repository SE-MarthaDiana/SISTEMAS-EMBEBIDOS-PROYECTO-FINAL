/* ===================================================================== *
 *                                                                       *
   Menu Callback Función
 *                                                                       *
   =====================================================================*/


// *********************************************************************
void mFunc_information(uint8_t param)   //función para la información
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);


    lcd.setCursor(0, 0);
    lcd.print(F("Maceta"));
    lcd.setCursor(0, 1);
    lcd.print(F("inteligente v1.0"));
    lcd.setCursor(0, 2);
    lcd.print(F("Martha Isai y Juan"));
    lcd.setCursor(0, 3);
    lcd.print(F("algun boton salir"));
  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

    if (LCDML.BT_checkAny()) { //checamos si algun botón es presionado

      LCDML.FUNC_goBackToMenu();
    }
  }

  if (LCDML.FUNC_close())
  {

  }
}

// *********************************************************************
void mFunc_screensaver(uint8_t param)       //función para el screensaver
// *********************************************************************
{


  if (LCDML.FUNC_setup())
  {

    LCDML_UNUSED(param);

    LCDML.FUNC_setLoopInterval(100);
  }

  if (LCDML.FUNC_loop())
  {
    //leemos las variables de los sensores y las desplegamos en el screensaver
   
    moisture_percentage =analogRead(pinTierra);
    temperature = dht.readTemperature();
    Humid = dht.readHumidity();
    lux = LightSensor.GetLightIntensity();
    lcd.setCursor(0, 0);
    lcd.print(F("  H Tierra "));
    lcd.print(moisture_percentage);
    lcd.setCursor(0, 1);
    lcd.print(F("  Luz "));
    lcd.print(lux);
    lcd.print(F(" lx"));
    lcd.setCursor(0, 2);
    lcd.print(F("  Temp "));
    lcd.print(temperature);
    lcd.print(F(" C"));
    lcd.setCursor(0, 3); // set cursor
    lcd.print(F("  H aire "));
    lcd.print(Humid);
    lcd.print(F("%"));
    delay(2000);

    if (LCDML.BT_checkAny())    //checar si alguna tecla es presionada
    {
      LCDML.FUNC_goBackToMenu();  //regresar al menú anterior
    }
  }

  if (LCDML.FUNC_close())
  {

    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)      //función para regresar
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);

    LCDML.FUNC_goBackToMenu(1);
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)    //función para ir a la raíz del menú
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);

    LCDML.MENU_goRoot();
  }
}


// *********************************************************************
void riego_encender(uint8_t param)    //función para encender la bomba
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
   
    LCDML_UNUSED(param);
    digitalWrite(bomba, LOW);   // encendemos el rele osea la bomba
    LCDML.FUNC_goBackToMenu();

  }
}
// *********************************************************************
void riego_apagar(uint8_t param)    //función para apagar la bomba
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    
    LCDML_UNUSED(param);
    digitalWrite(bomba, HIGH);    // apagamos la bomba
    LCDML.FUNC_goBackToMenu();

  }
}
///////////////////////////////////////////////////////////////////////////////
//         Función de intervalo de la bomba de agua                          //
///////////////////////////////////////////////////////////////////////////////
uint8_t g_button_value = 0; // contador de valor de botón (variable global)
void riego_intervalo(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);

    // mostrar LCD contenido
    lcd.setCursor(0, 0);
    lcd.print(F("Regar durante n seg"));
    // restaurar el valor del boton
    g_button_value = 0;

    // Desactive el protector de pantalla para esta función hasta que se cierre
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

    if (LCDML.BT_checkAny()) // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
    {
      if (LCDML.BT_checkDown()) // compruebe si se presiona el botón
      {
        LCDML.BT_resetDown(); // restablecer el botón izquierdo
        g_button_value++;

        // actualizar el contenido de la pantalla LCD
        lcd.setCursor(14, 0); // poner cursor
        lcd.print(g_button_value); // imprimir cambiar contenido

      }
      if (LCDML.BT_checkEnter()) {

        
        digitalWrite(bomba, LOW);    // apagamos la bomba
        delay(g_button_value * 1000);
        digitalWrite(bomba, HIGH);



        LCDML.FUNC_goBackToMenu();      // deja esta función
      }
    }



  }

  if (LCDML.FUNC_close())
  {

  }
}

/////////////////////////////////////////////////////////////////////////////
//Funciones para la lampara 1
/////////////////////////////////////////////////////////////////////////////

void Encender_L1(uint8_t param)       //función para encer L1
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);
    for (int i = 0; i < NUMPIXELS; i++) {

      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
      pixels.show();
      delay(100);
    }

    LCDML.FUNC_goBackToMenu();
  }
}
void Apagar_L1(uint8_t param)     //Función para apagar L1
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);
    L1_aux = 0;

    pixels.clear();
    pixels.show();

    LCDML.FUNC_goBackToMenu();
  }
}

void L1_intervalo(uint8_t param)    //función para el intervalo de luz
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);

    // mostrar LCD contenido
    lcd.setCursor(0, 0);
    lcd.print(F("Prender n horas"));
    // restaurar el valor del boton
    g_button_value = 0;

    // Desactive el protector de pantalla para esta función hasta que se cierre
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

    if (LCDML.BT_checkAny()) // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
    {
      if (LCDML.BT_checkDown()) // compruebe si se presiona el botón
      {
        LCDML.BT_resetDown(); // restablecer el botón izquierdo
        g_button_value++;
        if (g_button_value > 24)
        { lcd.setCursor(9, 0);
          lcd.print(" ");
          g_button_value = 0;
        }

        // actualizar el contenido de la pantalla LCD
        lcd.setCursor(8, 0); // poner cursor
        lcd.print(g_button_value); // imprimir cambiar contenido

      }
      if (LCDML.BT_checkEnter()) {

        L1_aux = g_button_value * 3.6e+6;
        for (int i = 0; i < NUMPIXELS; i++) {


          pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
          pixels.show();
          delay(100);
          iniciaTempo = millis();
        }



        LCDML.FUNC_goBackToMenu();      // deja esta función
      }
    }


  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {

  }
}

void L1_intensidad(uint8_t param) //función para la intensidad de la L1
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);

    // mostrar LCD contenido
    lcd.setCursor(0, 0);
    lcd.print(F("Intensidad n"));
    // restaurar el valor del boton
    g_button_value = 0;

    // Desactive el protector de pantalla para esta función hasta que se cierre
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

    if (LCDML.BT_checkAny()) // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
    {
      if (LCDML.BT_checkDown()) // compruebe si se presiona el botón
      {
        LCDML.BT_resetDown(); // restablecer el botón izquierdo
        g_button_value++;
        if (g_button_value > 10)

        {
          g_button_value = 0;
          lcd.setCursor(12, 0);
          lcd.print(" ");
        }

        // actualizar el contenido de la pantalla LCD
        lcd.setCursor(11, 0); // poner cursor
        lcd.print(g_button_value); // imprimir cambiar contenido

      }
      if (LCDML.BT_checkEnter()) {

        brillo1 = (g_button_value * 25) + 5;




        LCDML.FUNC_goBackToMenu();      // deja esta función
      }
    }



  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {

  }
}
//*********************************************************************
//********funciones para los distintos colores*************************
//*********************************************************************
void L1_rojo(uint8_t param)   //color rojo
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r1 = 255;
    g1 = 0;
    b1 = 0;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L1_azul(uint8_t param)     //color azul
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r1 = 0;
    g1 = 0;
    b1 = 255;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L1_verde(uint8_t param)      //color verde
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r1 = 0;
    g1 = 255;
    b1 = 0;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L1_violeta(uint8_t param)      //color violeta
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r1 = 255;
    g1 = 10;
    b1 = 255;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L1_naranja(uint8_t param)    //color naranja
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r1 = 255;
    g1 = 87;
    b1 = 34;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));

    }
    pixels.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L1_amarillo(uint8_t param)   //color amarillo
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r1 = 255;
    g1 = 235;
    b1 = 59;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels.show();
  }

  LCDML.FUNC_goBackToMenu();
}
void L1_blanco(uint8_t param)   //color blanco
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r1 = 255;
    g1 = 255;
    b1 = 255;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels.show();
  }

  LCDML.FUNC_goBackToMenu();
}


/////////////////////////////////////////////////////////////////////////////
//Funciones para la lampara 2
/////////////////////////////////////////////////////////////////////////////
void Encender_L2(uint8_t param)     // Función para encender la L2
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);
    for (int i = 0; i < NUMPIXELS; i++) {


      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
      pixels2.show();
      delay(100);
    }

    LCDML.FUNC_goBackToMenu();
  }
}
void Apagar_L2(uint8_t param)   //función para apagar la L2
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {

    LCDML_UNUSED(param);
    L2_aux = 0;

    pixels2.clear();
    pixels2.show();

    LCDML.FUNC_goBackToMenu();
  }
}

void L2_intervalo(uint8_t param)    //función para el intervalo de la L2
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);

    // mostrar LCD contenido
    lcd.setCursor(0, 0);
    lcd.print(F("Prender n horas"));
    // restaurar el valor del boton
    g_button_value = 0;

    // Desactive el protector de pantalla para esta función hasta que se cierre
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

    if (LCDML.BT_checkAny()) // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
    {
      if (LCDML.BT_checkDown()) // compruebe si se presiona el botón
      {
        LCDML.BT_resetDown(); // restablecer el botón izquierdo
        g_button_value++;
        if (g_button_value > 24)
        { lcd.setCursor(9, 0);
          lcd.print(" ");
          g_button_value = 0;
        }


        // actualizar el contenido de la pantalla LCD
        lcd.setCursor(8, 0); // poner cursor
        lcd.print(g_button_value); // imprimir cambiar contenido

      }
      if (LCDML.BT_checkEnter()) {

        L2_aux = g_button_value * 3.6e+6;
        for (int i = 0; i < NUMPIXELS; i++) {


          pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
          pixels2.show();
          delay(100);
          iniciaTempo2 = millis();
        }



        LCDML.FUNC_goBackToMenu();      // deja esta función
      }
    }



  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {
    //aquí puede restablecer algunas variables globales o no hacer nada
  }
}

void L2_intensidad(uint8_t param)   //Función para la intensidad de la L2
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove las advertencias del compilador cuando no se usa la variable param:
    LCDML_UNUSED(param);

    // mostrar LCD contenido
    lcd.setCursor(0, 0);
    lcd.print(F("Intensidad n"));
    // restaurar el valor del boton
    g_button_value = 0;

    // Desactive el protector de pantalla para esta función hasta que se cierre
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

    if (LCDML.BT_checkAny()) // compruebe si se presiona algún botón (entrar, arriba, abajo, izquierda, derecha)
    {
      if (LCDML.BT_checkDown()) // compruebe si se presiona el botón
      {
        LCDML.BT_resetDown(); // restablecer el botón izquierdo
        g_button_value++;
        if (g_button_value > 10)
        { g_button_value = 0;
          lcd.setCursor(12, 0);
          lcd.print(" ");
        }


        // actualizar el contenido de la pantalla LCD
        lcd.setCursor(11, 0); // poner cursor
        lcd.print(g_button_value); // imprimir cambiar contenido

      }
      if (LCDML.BT_checkEnter()) {

        brillo2 = (g_button_value * 25) + 5;

        LCDML.FUNC_goBackToMenu();      // deja esta función
      }
    }


  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {
    //aquí puede restablecer algunas variables globales o no hacer nada
  }
}
//*********************************************************************
//********funciones para los distintos colores*************************
//*********************************************************************
void L2_rojo(uint8_t param)   //color rojo
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 255;
    g2 = 0;
    b2 = 0;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
    }
    pixels2.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L2_azul(uint8_t param)   //color azul
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 0;
    g2 = 0;
    b2 = 255;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
    }
    pixels2.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L2_verde(uint8_t param)    //color verde
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 0;
    g2 = 255;
    b2 = 0;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
    }
    pixels2.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L2_violeta(uint8_t param)    //color violeta
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 255;
    g2 = 10;
    b2 = 255;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
    }
    pixels2.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L2_naranja(uint8_t param)    //color naranja
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 255;
    g2 = 87;
    b2 = 34;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));

    }
    pixels2.show();
  }

  LCDML.FUNC_goBackToMenu();
}

void L2_amarillo(uint8_t param)   //color amarillo
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 255;
    g2 = 235;
    b2 = 59;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
    }
    pixels2.show();
  }

  LCDML.FUNC_goBackToMenu();
}
void L2_blanco(uint8_t param)   //color blanco
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 255;
    g2 = 255;
    b2 = 255;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
    }
    pixels2.show();
  }

  LCDML.FUNC_goBackToMenu();
}
//*********************************************************************
//********MODO PLANTA**************************************************
//*********************************************************************
void planta_a(uint8_t param)   //color blanco
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 255;
    g2 = 0;
    b2 = 0;
    r1 = 255;
    g1 = 0;
    b1 = 0;
    modo_a=1;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels2.show();
    pixels.show();
    iniciaTempo = millis();
  }

  LCDML.FUNC_goBackToMenu();
}
void planta_b(uint8_t param)   //color blanco
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 50;
    g2 = 200;
    b2 = 30;
    r1 = 50;
    g1 = 200;
    b1 = 30;
    modo_b=1;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels2.show();
    pixels.show();
    iniciaTempo = millis();
  }

  LCDML.FUNC_goBackToMenu();
}
void planta_c(uint8_t param)   //color blanco
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    r2 = 255;
    g2 = 255;
    b2 = 255;
    r1 = 255;
    g1 = 255;
    b1 = 255;
    modo_c=1;
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(r2, g2, b2));
      pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
    }
    pixels2.show();
    pixels.show();
    iniciaTempo = millis();
  }

  LCDML.FUNC_goBackToMenu();
}
