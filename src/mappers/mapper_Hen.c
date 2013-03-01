/*
 * mapper_Hen.c
 *
 *  Created on: 6/ott/2011
 *      Author: fhorse
 */

#include "mappers.h"
#include "mem_map.h"

WORD prg_rom_32k_max;
BYTE type;

void map_init_Hen(BYTE model) {
	prg_rom_32k_max = (info.prg_rom_16k_count >> 1) - 1;

	switch (model) {
		case HEN_177:
		case HEN_FANKONG:
			EXTCL_CPU_WR_MEM(Hen_177);
			break;
		case HEN_XJZB:
			EXTCL_CPU_WR_MEM(Hen_xjzb);
			info.mapper_extend_wr = TRUE;
			break;
	}

	if (info.reset >= HARD) {
		map_prg_rom_8k(4, 0, 0);
	}

	type = model;
}

void extcl_cpu_wr_mem_Hen_177(WORD address, BYTE value) {
	if (type != HEN_FANKONG) {
		if (value & 0x20) {
			mirroring_H();
		} else {
			mirroring_V();
		}
	}

	control_bank(prg_rom_32k_max)
	map_prg_rom_8k(4, 0, value);
	map_prg_rom_8k_update();
}

void extcl_cpu_wr_mem_Hen_xjzb(WORD address, BYTE value) {
	if ((address < 0x5000) || (address > 0x5FFF)) {
		return;
	}

	value >>= 1;
	control_bank(prg_rom_32k_max)
	map_prg_rom_8k(4, 0, value);
	map_prg_rom_8k_update();
}