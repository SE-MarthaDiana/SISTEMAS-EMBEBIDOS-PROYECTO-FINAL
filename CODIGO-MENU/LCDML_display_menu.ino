// =====================================================================
// Función de salida
// =====================================================================

/* ******************************************************************** */
void lcdml_menu_clear()
/* ******************************************************************** */
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

/* ******************************************************************** */
void lcdml_menu_display()
/* ******************************************************************** */
{
  // actualizar contenido
  // ***************
  if (LCDML.DISP_checkMenuUpdate()) {
    // limpiamos el menú
    // ***************
    LCDML.DISP_clear();

    // declaración de algunas variables
    // ***************
    char content_text[_LCDML_DISP_cols];  // save the content text of every menu element

    LCDMenuLib2_menu *tmp;

    uint8_t i = LCDML.MENU_getScroll();
    uint8_t maxi = _LCDML_DISP_rows + i;
    uint8_t n = 0;

    // checamos si el elemento tiene hijos
    if ((tmp = LCDML.MENU_getDisplayedObj()) != NULL)
    {
      // loop para desplegar las lineas
      do
      {
        // checamos si el elemento del menú tiene alguna condición
        if (tmp->checkCondition())
        {
          // cgecamos el tipo de elemento
          if (tmp->checkType_menu() == true)
          {
            // desplegamos el contenido normal
            LCDML_getContent(content_text, tmp->getID());
            lcd.setCursor(1, n);
            lcd.print(content_text);
          }
          else
          {
            if (tmp->checkType_dynParam()) {
              tmp->callback(n);
            }
          }
          // incrementamos las variables
          i++;
          n++;
        }
        // ir al siguiente hermano
      } while (((tmp = tmp->getSibling(1)) != NULL) && (i < maxi));
    }
  }

  if (LCDML.DISP_checkMenuCursorUpdate())
  {
    // inicializar las variables
    uint8_t n_max             = (LCDML.MENU_getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.MENU_getChilds());
    uint8_t scrollbar_min     = 0;
    uint8_t scrollbar_max     = LCDML.MENU_getChilds();
    uint8_t scrollbar_cur_pos = LCDML.MENU_getCursorPosAbs();
    uint8_t scroll_pos        = ((1.*n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos);


    // desplegamos las filas
    for (uint8_t n = 0; n < n_max; n++)
    {

      lcd.setCursor(0, n);


      if (n == LCDML.MENU_getCursorPos()) {
        lcd.write(_LCDML_DISP_cfg_cursor);
      } else {
        lcd.write(' ');
      }

      // borrar o reiniciar la scrollbar
      if (_LCDML_DISP_cfg_scrollbar == 1) {
        if (scrollbar_max > n_max) {
          lcd.setCursor((_LCDML_DISP_cols - 1), n);
          lcd.write((uint8_t)0);
        }
        else {
          lcd.setCursor((_LCDML_DISP_cols - 1), n);
          lcd.print(' ');
        }
      }
    }

    // mostrar la scrollbar
    if (_LCDML_DISP_cfg_scrollbar == 1) {
      if (scrollbar_max > n_max) {

        if (scrollbar_cur_pos == scrollbar_min) {

          lcd.setCursor((_LCDML_DISP_cols - 1), 0);
          lcd.write((uint8_t)1);
        } else if (scrollbar_cur_pos == (scrollbar_max - 1)) {

          lcd.setCursor((_LCDML_DISP_cols - 1), (n_max - 1));
          lcd.write((uint8_t)4);
        } else {

          lcd.setCursor((_LCDML_DISP_cols - 1), scroll_pos / n_max);
          lcd.write((uint8_t)(scroll_pos % n_max) + 1);
        }
      }
    }
  }
}
