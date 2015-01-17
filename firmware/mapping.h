static uchar codes[2][5][12] = {

	// layer A
	{
		{   ESC,   INS,   0x0,   0x0,   0x0, BKT_L,   BKT_R, SLAYR, KEY_9, KEY_0, MINUS, EQUAL },
		{   ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T,   KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, QUOTE },
		{ SFT_L, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G,   KEY_H, KEY_J, KEY_K, KEY_L, SEMCL, SFT_R },
		{ LAYER, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,   KEY_N, KEY_M, COMMA, FSTOP, SLASH, LAYER },
		{   TAB, CTL_L,   0x0, ALT_L, GUI_L, LAYER,   SPACE, LAYER,  HASH,   0x0, CTL_R, ENTER }
	},

	// layer B
	{
		{   F12,    F1,    F2,    F3,    F4,    F5,      F6,    F7,    F8,    F9,   F10,   F11 },
		{   TAB,   0x0, KEY_1, KEY_2, KEY_3, PG_UP,     0x0,   0x0,   0x0, ARR_U, ARR_R, GRAVE },
		{ SFT_L,   0x0, KEY_4, KEY_5, KEY_6, PG_DN,   BK_SP,   0x0, ARR_L, ARR_D,   0x0, SFT_R },
		{ LAYER,   0x0, KEY_7, KEY_8, KEY_9, KEY_0,     0x0,   0x0,   0x0,   0x0, BK_SL, LAYER },
		{   DEL, CTL_L,   0x0, ALT_L, GUI_L, LAYER,   BK_SP, LAYER, PRTSC,   0x0, SFT_R, ENTER }
	}

};

