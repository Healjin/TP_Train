/**
 *@file ExtLab2.h
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@brief Contain functions to control the ExtLab2 card
 */

#ifndef EXTLAB2_H_
#define EXTLAB2_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>

void Select_display_bus();
void Select_control_bus();
void Valide_datas_bus_to_extlab2();
void Init_Rotate_button();
void Init_Extlab2();

#endif /* EXTLAB2_H_ */
