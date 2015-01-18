#define NUMBER_OF_LAYERS 3

static uchar codes[NUMBER_OF_LAYERS][5][12] = {

	// layer A
	{
		{   ESC,   INS,   0x0,   0x0,   0x0,   DEL,   BK_SP,   0x0, KEY_9, KEY_0, MINUS, EQUAL },
		{   ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T,   KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, QUOTE },
		{ SFT_L, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G,   KEY_H, KEY_J, KEY_K, KEY_L, SEMCL, SFT_R },
		{ LAY_B, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,   KEY_N, KEY_M, COMMA, FSTOP, SLASH, SLAYR },
		{   TAB, CTL_L,   0x0, ALT_L, GUI_L, LAY_C,   SPACE,   0x0,  HASH,   0x0, CTL_R, ENTER }
	},

	// layer B
	{
		{   F12,    F1,    F2,    F3,    F4,    F5,      F6,    F7, BKT_L, BKT_R,   F10,   F11 },
		{   TAB,   0x0, KEY_1, KEY_2, KEY_3,   0x0,   KEY_0, KEY_1, KEY_2, KEY_3,   0x0, GRAVE },
		{ SFT_L,   0x0, KEY_4, KEY_5, KEY_6,   0x0,     0x0, KEY_4, KEY_5, KEY_6,   0x0, SFT_R },
		{ LAY_B,   0x0, KEY_7, KEY_8,   0x0,   0x0,     0x0, KEY_7, KEY_8, KEY_9, BK_SL, SLAYR },
		{   TAB, CTL_L,   0x0, ALT_L, GUI_L, LAY_C,     0x0,   0x0, PRTSC,   0x0, CTL_R, ENTER }
	},

	// layer C
	{
		{   F12,   0x0,   0x0,   0x0,   0x0,   0x0,   BK_SP,   0x0, BKT_L, BKT_R,   0x0,   0x0 },
		{   TAB,   0x0,   0x0,   0x0,   0x0,   0x0,   PG_UP, PG_DN, BKT_L, BKT_R,   0x0, GRAVE },
		{ SFT_L,   0x0,   0x0,   0x0,   0x0,   0x0,   ARR_L, ARR_D, ARR_U, ARR_R,   0x0, SFT_R },
		{ LAY_B,   0x0,   0x0,   0x0,   0x0,   0x0,    HOME,   END,   0x0,   0x0, BK_SL, SLAYR },
		{   TAB, CTL_L,   0x0, ALT_L, GUI_L, LAY_C,     0x0,   0x0,   0x0,   0x0, CTL_R, ENTER }
	}

};

