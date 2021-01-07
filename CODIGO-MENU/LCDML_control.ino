// *********************************************************************
// controles:
// (0) Control serial
// (1) Control analogo
// (2) Control digital
// (3) Control encoder
// (4) Control Keypad
// (5) Control IRMP remote
// (6) Control joystick
// (7) Control I2C PCF8574
// *********************************************************************

#define _LCDML_CONTROL_cfg      3       //elegimos control con encoder

// *********************************************************************
// *************** (0) CONTROL SERIAL *******************
// *********************************************************************
#if(_LCDML_CONTROL_cfg == 0)
// settings
# define _LCDML_CONTROL_serial_enter           'e'
# define _LCDML_CONTROL_serial_up              'w'
# define _LCDML_CONTROL_serial_down            's'
# define _LCDML_CONTROL_serial_left            'a'
# define _LCDML_CONTROL_serial_right           'd'
# define _LCDML_CONTROL_serial_quit            'q'


# define _LCDML_EVENT_command                'c'
# define _LCDML_EVENT_char_0                 '0'
# define _LCDML_EVENT_char_1                 '1'
# define _LCDML_EVENT_char_2                 '2'
# define _LCDML_EVENT_char_3                 '3'
# define _LCDML_EVENT_char_4                 '4'
# define _LCDML_EVENT_char_5                 '5'
# define _LCDML_EVENT_char_6                 '6'
# define _LCDML_EVENT_char_7                 '7'
# define _LCDML_EVENT_char_8                 '8'
# define _LCDML_EVENT_char_9                 '9'
// *********************************************************************

void lcdml_menu_control(void)
{

  if (LCDML.BT_setup()) {
    // runs only once
  }

  if (LCDML.CE_setup()) {

    Serial.println("CE_setup()");
  }


  if (Serial.available()) {

    switch (Serial.read())
    {
      case _LCDML_CONTROL_serial_enter:  LCDML.BT_enter(); break;
      case _LCDML_CONTROL_serial_up:     LCDML.BT_up();    break;
      case _LCDML_CONTROL_serial_down:   LCDML.BT_down();  break;
      case _LCDML_CONTROL_serial_left:   LCDML.BT_left();  break;
      case _LCDML_CONTROL_serial_right:  LCDML.BT_right(); break;
      case _LCDML_CONTROL_serial_quit:   LCDML.BT_quit();  break;

      case _LCDML_EVENT_command:  LCDML.CE_set(0);   break;
      case _LCDML_EVENT_char_0:   LCDML.CE_set(1);   break;
      case _LCDML_EVENT_char_1:   LCDML.CE_set(2);   break;
      case _LCDML_EVENT_char_2:   LCDML.CE_set(3);   break;
      case _LCDML_EVENT_char_3:   LCDML.CE_set(4);   break;
      case _LCDML_EVENT_char_4:   LCDML.CE_set(5);   break;
      case _LCDML_EVENT_char_5:   LCDML.CE_set(6);   break;
      case _LCDML_EVENT_char_6:   LCDML.CE_set(7);   break;
      case _LCDML_EVENT_char_7:   LCDML.CE_set(8);   break;
      case _LCDML_EVENT_char_8:   LCDML.CE_set(9);   break;
      case _LCDML_EVENT_char_9:   LCDML.CE_set(10);  break;
      default: break;
    }
  }
}

// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************





// *********************************************************************
// *************** (1) CONTROL ANALOGO *********************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 1)

unsigned long g_LCDML_DISP_press_time = 0;

#define _LCDML_CONTROL_analog_pin              0

#define _LCDML_CONTROL_analog_enter_min        850     // Button Enter
#define _LCDML_CONTROL_analog_enter_max        920
#define _LCDML_CONTROL_analog_up_min           520     // Button Up
#define _LCDML_CONTROL_analog_up_max           590
#define _LCDML_CONTROL_analog_down_min         700     // Button Down
#define _LCDML_CONTROL_analog_down_max         770
#define _LCDML_CONTROL_analog_back_min         950     // Button Back
#define _LCDML_CONTROL_analog_back_max         1020
#define _LCDML_CONTROL_analog_left_min         430     // Button Left
#define _LCDML_CONTROL_analog_left_max         500
#define _LCDML_CONTROL_analog_right_min        610     // Button Right
#define _LCDML_CONTROL_analog_right_max        680
// *********************************************************************

void lcdml_menu_control(void)
{

  if (LCDML.BT_setup()) {
    // runs only once
  }

  if ((millis() - g_LCDML_DISP_press_time) >= 200) {
    g_LCDML_DISP_press_time = millis(); // reset debounce timer

    uint16_t value = analogRead(_LCDML_CONTROL_analog_pin);  // analog pin for keypad

    if (value >= _LCDML_CONTROL_analog_enter_min && value <= _LCDML_CONTROL_analog_enter_max) {
      LCDML.BT_enter();
    }
    if (value >= _LCDML_CONTROL_analog_up_min    && value <= _LCDML_CONTROL_analog_up_max)    {
      LCDML.BT_up();
    }
    if (value >= _LCDML_CONTROL_analog_down_min  && value <= _LCDML_CONTROL_analog_down_max)  {
      LCDML.BT_down();
    }
    if (value >= _LCDML_CONTROL_analog_left_min  && value <= _LCDML_CONTROL_analog_left_max)  {
      LCDML.BT_left();
    }
    if (value >= _LCDML_CONTROL_analog_right_min && value <= _LCDML_CONTROL_analog_right_max) {
      LCDML.BT_right();
    }
    if (value >= _LCDML_CONTROL_analog_back_min  && value <= _LCDML_CONTROL_analog_back_max)  {
      LCDML.BT_quit();
    }
  }
}
// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************






// *********************************************************************
// *************** (2) CONTROL DIGITAL ***********************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 2)

unsigned long g_LCDML_DISP_press_time = 0;

#define _LCDML_CONTROL_digital_low_active      0
#define _LCDML_CONTROL_digital_enable_quit     1
#define _LCDML_CONTROL_digital_enable_lr       1
#define _LCDML_CONTROL_digital_enter           8
#define _LCDML_CONTROL_digital_up              9
#define _LCDML_CONTROL_digital_down            10
#define _LCDML_CONTROL_digital_quit            11
#define _LCDML_CONTROL_digital_left            12
#define _LCDML_CONTROL_digital_right           13
// *********************************************************************
void lcdml_menu_control(void)
{
  // If something must init, put in in the setup condition
  if (LCDML.BT_setup()) {

    pinMode(_LCDML_CONTROL_digital_enter      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_up         , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_down       , INPUT_PULLUP);
# if(_LCDML_CONTROL_digital_enable_quit == 1)
    pinMode(_LCDML_CONTROL_digital_quit     , INPUT_PULLUP);
# endif
# if(_LCDML_CONTROL_digital_enable_lr == 1)
    pinMode(_LCDML_CONTROL_digital_left     , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_right    , INPUT_PULLUP);
# endif
  }

#if(_LCDML_CONTROL_digital_low_active == 1)
#  define _LCDML_CONTROL_digital_a !
#else
#  define _LCDML_CONTROL_digital_a
#endif

  uint8_t but_stat = 0x00;

  bitWrite(but_stat, 0, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_enter)));
  bitWrite(but_stat, 1, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_up)));
  bitWrite(but_stat, 2, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_down)));
#if(_LCDML_CONTROL_digital_enable_quit == 1)
  bitWrite(but_stat, 3, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_quit)));
#endif
#if(_LCDML_CONTROL_digital_enable_lr == 1)
  bitWrite(but_stat, 4, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_left)));
  bitWrite(but_stat, 5, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_right)));
#endif

  if (but_stat > 0) {
    if ((millis() - g_LCDML_DISP_press_time) >= 200) {
      g_LCDML_DISP_press_time = millis(); // reset press time

      if (bitRead(but_stat, 0)) {
        LCDML.BT_enter();
      }
      if (bitRead(but_stat, 1)) {
        LCDML.BT_up();
      }
      if (bitRead(but_stat, 2)) {
        LCDML.BT_down();
      }
      if (bitRead(but_stat, 3)) {
        LCDML.BT_quit();
      }
      if (bitRead(but_stat, 4)) {
        LCDML.BT_left();
      }
      if (bitRead(but_stat, 5)) {
        LCDML.BT_right();
      }
    }
  }
}
// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************






// *********************************************************************
// *************** (3) CONTROL ENCODER ****************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 3)

// definiciones globales
#define encoder_A_pin       13
#define encoder_B_pin       6
#define encoder_button_pin  8

#define g_LCDML_CONTROL_button_long_press    800   // ms
#define g_LCDML_CONTROL_button_short_press   120   // ms


#include <Encoder.h>

Encoder ENCODER(encoder_A_pin, encoder_B_pin);

unsigned long  g_LCDML_CONTROL_button_press_time = millis();
bool  g_LCDML_CONTROL_button_prev       = HIGH;

// *********************************************************************
void lcdml_menu_control(void)
// *********************************************************************
{
  // declaramos variables para esta función
  int32_t g_LCDML_CONTROL_Encoder_position = ENCODER.read();
  bool g_LCDML_button                      = digitalRead(encoder_button_pin);


  if (LCDML.BT_setup())
  {


    // habilitamos las pull ups de los pines
    pinMode(encoder_A_pin      , INPUT_PULLUP);
    pinMode(encoder_B_pin      , INPUT_PULLUP);
    pinMode(encoder_button_pin  , INPUT_PULLUP);
  }

  // checamos si el encoder gira a la direccipon A
  if (g_LCDML_CONTROL_Encoder_position <= -3)
  {

    if (g_LCDML_button == LOW)
    {

      LCDML.BT_left();


      g_LCDML_CONTROL_button_prev = HIGH;
    }
    else
    {
      LCDML.BT_down();
    }


    ENCODER.write(g_LCDML_CONTROL_Encoder_position + 4);
  }

  // Checamos si el encoder gira en dirección B
  else if (g_LCDML_CONTROL_Encoder_position >= 3)
  {

    if (g_LCDML_button == LOW)
    {

      LCDML.BT_right();


      g_LCDML_CONTROL_button_prev = HIGH;
    }
    else
    {
      LCDML.BT_up();
    }


    ENCODER.write(g_LCDML_CONTROL_Encoder_position - 4);
  }
  else
  {



    if (g_LCDML_button == LOW && g_LCDML_CONTROL_button_prev == HIGH)
    {
      g_LCDML_CONTROL_button_prev = LOW;
      g_LCDML_CONTROL_button_press_time = millis();
    }


    else if (g_LCDML_button == HIGH && g_LCDML_CONTROL_button_prev == LOW)
    {
      g_LCDML_CONTROL_button_prev = HIGH;


      if ((millis() - g_LCDML_CONTROL_button_press_time) >= g_LCDML_CONTROL_button_long_press)
      {

        LCDML.BT_quit();
      }

      else if ((millis() - g_LCDML_CONTROL_button_press_time) >= g_LCDML_CONTROL_button_short_press)
      {

        LCDML.BT_enter();
      }
    }


    else
    {

    }
  }
}
// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************





// *********************************************************************
// *************** (4) CONTROL KEYPAD ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 4)

#include <Keypad.h>

#define _LCDML_CONTROL_keypad_rows 4 // Four rows
#define _LCDML_CONTROL_keypad_cols 3 // Three columns

char keys[_LCDML_CONTROL_keypad_rows][_LCDML_CONTROL_keypad_cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'#', '0', '*'}
};
byte rowPins[_LCDML_CONTROL_keypad_rows] = { 9, 8, 7, 6 };
byte colPins[_LCDML_CONTROL_keypad_cols] = { 12, 11, 10 };
// objects
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, _LCDML_CONTROL_keypad_rows, _LCDML_CONTROL_keypad_cols );
// *********************************************************************
void lcdml_menu_control(void)
{

  if (LCDML.BT_setup()) {

  }
  char key = kpd.getKey();
  if (key)
  {
    switch (key)
    {
      // this is the default configuration
      case '#': LCDML.BT_enter(); break;
      case '2': LCDML.BT_up();    break;
      case '8': LCDML.BT_down();  break;
      case '4': LCDML.BT_left();  break;
      case '6': LCDML.BT_right(); break;
      case '*': LCDML.BT_quit();  break;

      // when you want to use all characters you have to use the CE_ functionality
      // CE stands for "custom event" and you can define 64 evetns
      // the following code is only an example

      default: break;
    }
  }
}
// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************


// *********************************************************************
// *************** (5) CONTROL IR REMOTE ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 5)

#define IRMP_INPUT_PIN PA0
#define IRMP_PROTOCOL_NAMES 1
#include <irmpSelectMain15Protocols.h>

#include <irmp.c.h>

IRMP_DATA irmp_data[1];

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

void handleReceivedIRData();

// *********************************************************************

void lcdml_menu_control(void)
{

  if (LCDML.BT_setup()) {

    irmp_init();
  }

  if (irmp_get_data(&irmp_data[0]))
  {

    switch (irmp_data[0].command)
    {
      case 0x52: LCDML.BT_enter(); break;
      case 0x50: LCDML.BT_up();    break;
      case 0x51: LCDML.BT_down();  break;
      case 0x55: LCDML.BT_left();  break;
      case 0x56: LCDML.BT_right(); break;
      case 0x23: LCDML.BT_quit();  break;
      default: break;
    }
  }
}
// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************



// *********************************************************************
// *************** (6) CONTROL JOYSTICK ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 6)
unsigned long g_LCDML_DISP_press_time = 0;

#define _LCDML_CONTROL_analog_pinx A0
#define _LCDML_CONTROL_analog_piny A1
#define _LCDML_CONTROL_digitalread 33


#define _LCDML_CONTROL_analog_up_min 612
#define _LCDML_CONTROL_analog_up_max 1023
#define _LCDML_CONTROL_analog_down_min 0
#define _LCDML_CONTROL_analog_down_max 412
#define _LCDML_CONTROL_analog_left_min 612
#define _LCDML_CONTROL_analog_left_max 1023
#define _LCDML_CONTROL_analog_right_min 0
#define _LCDML_CONTROL_analog_right_max 412
// *********************************************************************
void lcdml_menu_control(void)
{

  if (LCDML.BT_setup()) {

    pinMode (_LCDML_CONTROL_digitalread, INPUT);
  }

  if ((millis() - g_LCDML_DISP_press_time) >= 200) {
    g_LCDML_DISP_press_time = millis(); // reset debounce timer

    uint16_t valuex = analogRead(_LCDML_CONTROL_analog_pinx);  // analogpinx
    uint16_t valuey = analogRead(_LCDML_CONTROL_analog_piny);  // analogpinx
    uint16_t valuee = digitalRead(_LCDML_CONTROL_digitalread);  //digitalpinenter


    if (valuey >= _LCDML_CONTROL_analog_up_min && valuey <= _LCDML_CONTROL_analog_up_max) {
      LCDML.BT_up();  // up
    }
    if (valuey >= _LCDML_CONTROL_analog_down_min && valuey <= _LCDML_CONTROL_analog_down_max) {
      LCDML.BT_down();  // down
    }
    if (valuex >= _LCDML_CONTROL_analog_left_min && valuex <= _LCDML_CONTROL_analog_left_max) {
      LCDML.BT_left();  // left
    }
    if (valuex >= _LCDML_CONTROL_analog_right_min && valuex <= _LCDML_CONTROL_analog_right_max) {
      LCDML.BT_right();  // right
    }

    if (valuee == true) {
      LCDML.BT_enter(); // enter
    }


  }
}
// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************

// *********************************************************************
// *************** (7) CONTROL PCF8574 ****************************
// *********************************************************************

#elif(_LCDML_CONTROL_cfg == 7)
unsigned long g_LCDML_DISP_press_time = 0;
#define PCF8574_1 0x26

#define PCF8574_Pin0 254
#define PCF8574_Pin1 253
#define PCF8574_Pin2 251
#define PCF8574_Pin3 247
#define PCF8574_Pin4 239
#define PCF8574_Pin5 223
#define PCF8574_Pin6 191
#define PCF8574_Pin7 127


#define _LCDML_CONTROL_PCF8574_enable_quit    0
#define _LCDML_CONTROL_PCF8574_enable_lr      0

#define _LCDML_CONTROL_PCF8574_enter          PCF8574_Pin0
#define _LCDML_CONTROL_PCF8574_up             PCF8574_Pin1
#define _LCDML_CONTROL_PCF8574_down           PCF8574_Pin2
#define _LCDML_CONTROL_PCF8574_left           PCF8574_Pin3
#define _LCDML_CONTROL_PCF8574_right          PCF8574_Pin4
#define _LCDML_CONTROL_PCF8574_quit           PCF8574_Pin5
// **********************************************************
void lcdml_menu_control(void)
{

  if (LCDML.BT_setup()) {

  }

  if ((millis() - g_LCDML_DISP_press_time) >= 200) {
    g_LCDML_DISP_press_time = millis();

    Wire.write(0xff); // All pins as input?
    Wire.requestFrom(PCF8574_1, 1);
    if (Wire.available()) {
      switch (Wire.read())
      {
        case _LCDML_CONTROL_PCF8574_enter:  LCDML.BT_enter(); break;
        case _LCDML_CONTROL_PCF8574_up:     LCDML.BT_up();    break;
        case _LCDML_CONTROL_PCF8574_down:   LCDML.BT_down();  break;
#if(_LCDML_CONTROL_PCF8574_enable_quit == 1)
        case _LCDML_CONTROL_PCF8574_quit:   LCDML.BT_quit();  break;
#endif

#if(_LCDML_CONTROL_PCF8574_enable_lr   == 1)
        case _LCDML_CONTROL_PCF8574_left: LCDML.BT_left(); break;
        case _LCDML_CONTROL_PCF8574_right:   LCDML.BT_right();  break;
#endif

        default: break;
      }
    }
  }
}
// *********************************************************************
// ******************************* Fin *********************************
// *********************************************************************


#else
#error _LCDML_CONTROL_cfg is not defined or not in range
#endif
