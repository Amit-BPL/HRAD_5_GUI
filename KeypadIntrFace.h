#ifndef KEYPADINTRFACE_H_
#define KEYPADINTRFACE_H_

#include "CcAbstLayer.h"

#if MRAD3K6W
		/*	Initial 4 values in StationsOfmA[] array is dummy values to take care mA value pointer not to go below zero value	*/
	const unsigned short StationsOfmA[mAPTR_LIST_MAX + 1] = {0, 0, 0, 0, 15, 20, 25, 32, 40, 50, 70};
		/*	Values in StdmAsValues[] array (below array) is x10 values of mAs. eg: 10 = 1mAs	*/
	const unsigned short StdmAsValues[mASPTR_LIST_MAX] = {0, 0, 0, 0, 2, 5, 10, 13, 16, 20, 25, 32, 40, 50, 63, 80, 100, 125, 160, 200, 250, 320, 400, 500, 630, 800, 1000, 1250, 1600, 2000};
#elif (MRAD4K4W||MRAD5K0W)
		
//	#if MRAD5K0IDR_ENABLE	
		const unsigned short StationsOfmA[mAPTR_LIST_MAX] = {0, 0, 0, 0, 10, 20, 40, 50, 70, 100};
		const unsigned short StdmAsValues[mASPTR_LIST_MAX] = {0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 10, 13, 16, 20, 25, 32, 40, 50, 63, 80, 100, 125, 160, 200, 250, 320, 400, 500, 630, 800, 1000, 1250, 1600, 2000, 2500};
//	#else
		/*	Initial 4 values in StationsOfmA[] array is dummy values to take care mA value pointer not to go below zero value	*/
//	const unsigned short StationsOfmA[mAPTR_LIST_MAX] = {0, 0, 0, 0, 20, 32, 40, 50, 70, 100};
		/*	Values in StdmAsValues[] array (below array) is x10 values of mAs. eg: 10 = 1mAs	*/
//	const unsigned short StdmAsValues[mASPTR_LIST_MAX] = {0, 0, 0, 0, 10, 13, 16, 20, 25, 32, 40, 50, 63, 80, 100, 125, 160, 200, 250, 320, 400, 500, 630, 800, 1000, 1250, 1600, 2000, 2500};
#endif	

#if MRAD3K6W
	#if APR_SAVE_EN
	unsigned char AprKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] ={0};//@@@@@@@@@@
	unsigned short Apr_mASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] ={0};
	const unsigned short EepromLocForAPR[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY]	=	{
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
	};

	const unsigned char AprDefltKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// KV	
		{{76,	72,	80,	80},	{70,	72,	72,	72},	{84,	90,	80,	86},	{72,	82,	66,	76},	{68,	70,	78,	80},	{78,	88,	80,	92},	{85,	95,	90,	82},	{70,	58,	58,	47},	{72,	58,	58,	47}},
		{{72,	68,	76,	76},	{66,	68,	68,	68},	{80,	86,	77,	81},	{69,	78,	63,	73},	{65,	67,	72,	74},	{72,	82,	74,	84},	{80,	87,	80,	76},	{66,	56,	56,	46},	{69,	56,	56,	46}},
		{{68,	64,	72,	72},	{62,	64,	64,	64},	{76,	80,	74,	76},	{66,	74,	60,	68},	{62,	64,	66,	68},	{64,	72,	68,	76},	{75,	78,	78,	72},	{62,	54,	54,	45},	{65,	54,	54,	45}},
		{{64,	60,	68,	68},	{58,	60,	60,	60},	{65,	69,	68,	70},	{63,	71,	57,	63},	{59,	61,	60,	62},	{58,	64,	62,	68},	{58,	62,	61,	56},	{58,	52,	52,	44},	{60,	52,	52,	44}},
		{{60,	56,	64,	64},	{54,	56,	56,	56},	{60,	66,	60,	64},	{60,	66,	54,	60},	{56,	58,	54,	56},	{54,	62,	56,	62},	{53,	58,	56,	51},	{54,	50,	50,	43},	{57,	50,	50,	43}},
		{{52,	48,	56,	56},	{50,	52,	52,	52},	{52,	57,	52,	56},	{52,	54,	50,	52},	{48,	50,	50,	52},	{52,	56,	50,	54},	{50,	56,	51,	48},	{48,	46,	46,	40},	{48,	46,	46,	40}}
	};

	const unsigned short Apr_DefltmASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// mAs	
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{160,	250,	125,	200},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1000,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{125,	200,	100,	200},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	800,	800,	500},	{80,	50,	32,	25},	{250,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{100,	160,	80,	160},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	630},	{630,	800,	630,	500},	{80,	50,	32,	25},	{200,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{63,	160,	63,	160},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{400,	500,	400,	400},	{80,	50,	32,	25},	{200,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{63,	125,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{320,	400,	320,	320},	{80,	50,	32,	25},	{160,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{80,	100,	40,	80},	{200,	320,	125,	160},	{100,	100,	125,	125},	{320,	500,	320,	500},	{250,	320,	320,	250},	{50,	32,	20,	16},	{125,	40,	32,	20}}
	};
	#else
	const unsigned char AprKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// KV	
		{{76,	72,	80,	80},	{70,	72,	72,	72},	{100,	100,	80,	92},	{72,	82,	66,	76},	{68,	70,	78,	80},	{78,	88,	80,	92},	{76,	100,	78,	74},	{70,	58,	58,	47},	{72,	58,	58,	47}},
		{{72,	68,	76,	76},	{66,	68,	68,	68},	{100,	100,	77,	87},	{69,	78,	63,	73},	{65,	67,	72,	74},	{72,	82,	74,	84},	{70,	89,	72,	68},	{66,	56,	56,	46},	{68,	56,	56,	46}},
		{{68,	64,	72,	72},	{62,	64,	64,	64},	{100,	100,	74,	82},	{66,	74,	60,	68},	{62,	64,	66,	68},	{64,	72,	68,	76},	{64,	81,	66,	62},	{62,	54,	54,	45},	{64,	54,	54,	45}},
		{{64,	60,	68,	68},	{58,	60,	60,	60},	{100,	100,	68,	74},	{63,	71,	57,	63},	{59,	61,	60,	62},	{58,	64,	62,	68},	{58,	62,	60,	56},	{58,	52,	52,	44},	{60,	52,	52,	44}},
		{{60,	56,	64,	64},	{54,	56,	56,	56},	{94,	94,	64,	68},	{60,	66,	54,	60},	{56,	58,	54,	56},	{54,	62,	56,	62},	{52,	58,	54,	50},	{54,	50,	50,	43},	{56,	50,	50,	43}},
		{{52,	48,	56,	56},	{50,	52,	52,	52},	{52,	57,	52,	56},	{52,	54,	50,	52},	{48,	50,	50,	52},	{52,	56,	50,	54},	{50,	54,	50,	48},	{48,	46,	46,	40},	{48,	46,	46,	40}}
	};

	//const unsigned char Apr_mA_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	//// mA	
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{200,	200,	200,	200},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}}
	//};

	const unsigned short Apr_mASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// mAs	
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{160,	320,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	800,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{125,	250,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1000,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{100,	200,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	630},	{630,	1000,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{63,	160,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1300,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{63,	160,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1300,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{80,	160,	40,	80},	{200,	320,	125,	160},	{100,	100,	125,	125},	{320,	500,	320,	500},	{250,	400,	250,	250},	{50,	32,	20,	16},	{160,	40,	32,	20}}
	};

	//const unsigned short Apr_Time_mS_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	//// Time	
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	630},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{250,	250,	250,	10},	{250,	250,	250,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{250,	250,	250,	10},	{250,	250,	250,	10},	{40,	80,	20,	40},	{200,	320,	125,	160},	{100,	100,	125,	125},	{320,	500,	320,	500},	{250,	400,	250,	250},	{100,	63,	40,	32},	{160,	80,	63,	40}}
	//};
	#endif
#elif (MRAD4K4W||MRAD5K0W)
	#if APR_SAVE_EN
	unsigned char AprKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] ={0};//@@@@@@@@@@
	unsigned short Apr_mASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] ={0};
	const unsigned short EepromLocForAPR[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY]	=	{
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
		{{10,	16,	22,	28},	{34,	40,	46,	52},	{58,	64,	70,	76},	{82,	88,	94,	100},	{106,	112,	118,	124},	{130,	136,	142,	148},	{154,	160,	166,	172},	{178,	184,	190,	196},	{202,	208,	214,	220}},
	};

	const unsigned char AprDefltKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// KV	
		{{76,	72,	80,	80},	{70,	72,	72,	72},	{100,	100,	80,	92},	{72,	82,	66,	76},	{68,	70,	78,	80},	{78,	88,	80,	92},	{76,	100,	78,	74},	{70,	58,	58,	47},	{72,	58,	58,	47}},
		{{72,	68,	76,	76},	{66,	68,	68,	68},	{100,	100,	77,	87},	{69,	78,	63,	73},	{65,	67,	72,	74},	{72,	82,	74,	84},	{70,	89,	72,	68},	{66,	56,	56,	46},	{68,	56,	56,	46}},
		{{68,	64,	72,	72},	{62,	64,	64,	64},	{100,	100,	74,	82},	{66,	74,	60,	68},	{62,	64,	66,	68},	{64,	72,	68,	76},	{64,	81,	66,	62},	{62,	54,	54,	45},	{64,	54,	54,	45}},
		{{64,	60,	68,	68},	{58,	60,	60,	60},	{100,	100,	68,	74},	{63,	71,	57,	63},	{59,	61,	60,	62},	{58,	64,	62,	68},	{58,	62,	60,	56},	{58,	52,	52,	44},	{60,	52,	52,	44}},
		{{60,	56,	64,	64},	{54,	56,	56,	56},	{94,	94,	64,	68},	{60,	66,	54,	60},	{56,	58,	54,	56},	{54,	62,	56,	62},	{52,	58,	54,	50},	{54,	50,	50,	43},	{56,	50,	50,	43}},
		{{52,	48,	56,	56},	{50,	52,	52,	52},	{52,	57,	52,	56},	{52,	54,	50,	52},	{48,	50,	50,	52},	{52,	56,	50,	54},	{50,	54,	50,	48},	{48,	46,	46,	40},	{48,	46,	46,	40}}
	};

	const unsigned short Apr_DefltmASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// mAs	
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{160,	320,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	800,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{125,	250,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1000,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{100,	200,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	630},	{630,	1000,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{63,	160,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1250,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{63,	160,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1250,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{80,	160,	40,	80},	{200,	320,	125,	160},	{100,	100,	125,	125},	{320,	500,	320,	500},	{250,	400,	250,	250},	{50,	32,	20,	16},	{160,	40,	32,	20}}
	};
	#else
	const unsigned char AprKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// KV	
		{{76,	72,	80,	80},	{70,	72,	72,	72},	{100,	100,	80,	92},	{72,	82,	66,	76},	{68,	70,	78,	80},	{78,	88,	80,	92},	{76,	100,	78,	74},	{70,	58,	58,	47},	{72,	58,	58,	47}},
		{{72,	68,	76,	76},	{66,	68,	68,	68},	{100,	100,	77,	87},	{69,	78,	63,	73},	{65,	67,	72,	74},	{72,	82,	74,	84},	{70,	89,	72,	68},	{66,	56,	56,	46},	{68,	56,	56,	46}},
		{{68,	64,	72,	72},	{62,	64,	64,	64},	{100,	100,	74,	82},	{66,	74,	60,	68},	{62,	64,	66,	68},	{64,	72,	68,	76},	{64,	81,	66,	62},	{62,	54,	54,	45},	{64,	54,	54,	45}},
		{{64,	60,	68,	68},	{58,	60,	60,	60},	{100,	100,	68,	74},	{63,	71,	57,	63},	{59,	61,	60,	62},	{58,	64,	62,	68},	{58,	62,	60,	56},	{58,	52,	52,	44},	{60,	52,	52,	44}},
		{{60,	56,	64,	64},	{54,	56,	56,	56},	{94,	94,	64,	68},	{60,	66,	54,	60},	{56,	58,	54,	56},	{54,	62,	56,	62},	{52,	58,	54,	50},	{54,	50,	50,	43},	{56,	50,	50,	43}},
		{{52,	48,	56,	56},	{50,	52,	52,	52},	{52,	57,	52,	56},	{52,	54,	50,	52},	{48,	50,	50,	52},	{52,	56,	50,	54},	{50,	54,	50,	48},	{48,	46,	46,	40},	{48,	46,	46,	40}}
	};

	//const unsigned char Apr_mA_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	//// mA	
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{100,	100,	160,	160},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}},
	//	{{100,	100,	100,	50},	{100,	100,	100,	50},	{200,	200,	200,	200},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{100,	100,	100,	100},	{50,	50,	50,	50},	{100,	50,	50,	50}}
	//};

	const unsigned short Apr_mASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	// mAs	
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{160,	320,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	800,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{125,	250,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1000,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{100,	200,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	630},	{630,	1000,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{320,	320,	320,	320},	{320,	320,	320,	320},	{63,	160,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1300,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{63,	160,	50,	100},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1300,	800,	500},	{80,	50,	32,	25},	{320,	63,	50,	32}},
		{{250,	250,	250,	250},	{250,	250,	250,	250},	{80,	160,	40,	80},	{200,	320,	125,	160},	{100,	100,	125,	125},	{320,	500,	320,	500},	{250,	400,	250,	250},	{50,	32,	20,	16},	{160,	40,	32,	20}}
	};

	//const unsigned short Apr_Time_mS_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	//// Time	
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	800},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	800,	400,	630},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{320,	320,	320,	10},	{320,	320,	320,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{250,	250,	250,	10},	{250,	250,	250,	10},	{63,	160,	32,	63},	{320,	400,	200,	320},	{160,	160,	320,	320},	{400,	630,	400,	630},	{630,	1250,	800,	500},	{160,	100,	63,	50},	{320,	125,	100,	63}},
	//	{{250,	250,	250,	10},	{250,	250,	250,	10},	{40,	80,	20,	40},	{200,	320,	125,	160},	{100,	100,	125,	125},	{320,	500,	320,	500},	{250,	400,	250,	250},	{100,	63,	40,	32},	{160,	80,	63,	40}}
	//};
	#endif
#endif

unsigned char NewCalibPtrSel = 0x00;

extern signed char LowPowrModeEntryBfr[];
extern unsigned char LowPowerModeLockVar, FaultExplainRequest;
extern unsigned short SystemSleepTmr2;
	
extern void Delay_100nSec(unsigned char);
extern void Delay_1uSec(unsigned int);
extern char Normalise_XrayParamtr(unsigned char);
extern void ShowCalibResult(unsigned char);
extern void PopPresetProtocol(void);
extern void SavPresetExposeProtocol(void);
extern void SavAprExposeProtocol(void);

extern CONTROL_PARAMETER CntrlPrmtrs;
extern Uc_States eUc_States;

#endif
