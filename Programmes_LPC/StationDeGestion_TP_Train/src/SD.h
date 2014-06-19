/*
 *@file SD.h
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@briefs Resume functions on SD.c
 */
 
#include "LPC17xx.h"
#include <cr_section_macros.h>
#include "SPI.h"
#include "ExtLab2.h"
#include "Ecran.h"
void init_SD();
void Read_SD_one_block();
void Read_SD_multi_block(uint32_t n_block_depart,uint32_t n_block_arrive);
void Clear_pin();
void Set_pin();
void Write_SD();
void Read_SD_multiBLocks();

#endif /* POLICE_H_ */
