#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"


/* USB report descriptor, size must match usbconfig.h */
PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
	/*
	 * Device Class Definition for Human Interface Devices (HID) Version 1.11
	 * Appendix B: Boot Interface Descriptors
	 */
	0X05, 0X01,   // USAGE PAGE (GENERIC DESKTOP)
	0x09, 0x06,   // Usage (Keyboard)
	0xA1, 0x01,   // Collection (Application)

		// MODIFIERS BYTE (8 x 1 bit)
		0X05, 0X07,   // USAGE PAGE (KEYBOARD)
		0x19, 0xE0,   // Usage Minimum (224)
		0x29, 0xE7,   // Usage Maximum (231)
		0x15, 0x00,   // Logical Minimum (0)
		0x25, 0x01,   // Logical Maximum (1)
		0x75, 0x01,   // Report Size (1)
		0x95, 0x08,   // Report Count (8)
		0x81, 0x02,   // Input (Data, Var, Abs)

		// BYTE 1 - RESERVED
		0x95, 0x01,   // Report Count (1)
		0x75, 0x08,   // Report Size (8)
		0x81, 0x01,   // Input (Constant, Arr, Abs)

		0x95, 0x05,   // Report Count (5)
		0x75, 0x01,   // Report Size (1)
		0X05, 0X08,   // USAGE PAGE (LEDS)
		0x19, 0x01,   // Usage Minimum (1)
		0x29, 0x05,   // Usage Maximum (5)
		0x91, 0x02,   // Output (Data, Var, Abs)

		0x95, 0x01,   // Report Count (1)
		0x75, 0x03,   // Report Size (3)
		0x91, 0x01,   // Output (Constant, Arr, Abs)

		// KEYCODE BYTES (6 x 8 bits)
		0x95, 0x06,   // Report Count (6)
		0x75, 0x08,   // Report Size (8)
		0x15, 0x00,   // Logical Minimum (0)
		0x25, 0x65,   // Logical Maximum (101)
		0X05, 0X07,   // USAGE PAGE (KEYBOARD)
		0x19, 0x00,   // Usage Minimum (0)
		0x29, 0x65,   // Usage Maximum (101)
		0x81, 0x00,   // Input (Data, Arr, Abs)

	0xC0          // End Collection
};

static uchar reportBuffer[8]; // buffer for HID reports
static uchar tempReportBuffer[2][8]; // temp buffer copied to reportBuffer
static uchar reportPointer; // to one of the bytes between 2 and 7 in the 8-byte report

static uchar idleRate;   /* repeat rate for keyboards, never used for mice */


/* KEYCODES */

#define LAYER 0XFF // for internal layer switching (never sent to host)

#define KEY_A   0x04 // a and A
#define KEY_B   0x05 // b and B
#define KEY_C   0x06 // c and C
#define KEY_D   0x07 // d and D
#define KEY_E   0x08 // e and E
#define KEY_F   0x09 // f and F
#define KEY_G   0x0A // g and G
#define KEY_H   0x0B // h and H
#define KEY_I   0x0C // i and I
#define KEY_J   0x0D // j and J
#define KEY_K   0x0E // k and K
#define KEY_L   0x0F // l and L
#define KEY_M   0x10 // m and M
#define KEY_N   0x11 // n and N
#define KEY_O   0x12 // o and O
#define KEY_P   0x13 // p and P
#define KEY_Q   0x14 // q and Q
#define KEY_R   0x15 // r and R
#define KEY_S   0x16 // s and S
#define KEY_T   0x17 // t and T
#define KEY_U   0x18 // u and U
#define KEY_V   0x19 // v and V
#define KEY_W   0x1A // w and W
#define KEY_X   0x1B // x and X
#define KEY_Y   0x1C // y and Y
#define KEY_Z   0x1D // z and Z

#define KEY_1   0x1E // 1 and !
#define KEY_2   0x1F // 2 and @
#define KEY_3   0x20 // 3 and #
#define KEY_4   0x21 // 4 and $
#define KEY_5   0x22 // 5 and %
#define KEY_6   0x23 // 6 and ^
#define KEY_7   0x24 // 7 and &
#define KEY_8   0x25 // 8 and *
#define KEY_9   0x26 // 9 and (
#define KEY_0   0x27 // 0 and )

#define ENTER   0x28 // Return (ENTER)
#define ESC     0x29 // ESCAPE
#define BK_SP   0x2A // DELETE (Backspace)
#define TAB     0x2B // Tab
#define SPACE   0x2C // Spacebar
#define MINUS   0x2D // - and (underscore)
#define EQUAL   0x2E // = and +
#define BKT_L   0x2F // [ and {
#define BKT_R   0x30 // ] and }
#define BK_SL   0x64 // \ and |
#define HASH    0x32 // Non-US # and ~
#define SEMCL   0x33 // ; and :
#define QUOTE   0x34 // ‘ and “
#define GRAVE   0x35 // Grave Accent and Tilde
#define COMMA   0x36 //, and <
#define FSTOP   0x37 // . and >
#define SLASH   0x38 // / and ?
#define CPSLK   0x39 // Caps Lock

#define F1      0x3A // F1
#define F2      0x3B // F2
#define F3      0x3C // F3
#define F4      0x3D // F4
#define F5      0x3E // F5
#define F6      0x3F // F6
#define F7      0x40 // F7
#define F8      0x41 // F8
#define F9      0x42 // F9
#define F10     0x43 // F10
#define F11     0x44 // F11
#define F12     0x45 // F12

#define PRTSC   0x46 // PrintScreen
#define SCLCK   0x47 // Scroll Lock
#define PAUSE   0x48 // Pause
#define INS     0x49 // Insert
#define HOME    0x4A // Home
#define PG_UP   0x4B // PageUp
#define DEL     0x4C // Delete Forward
#define END     0x4D // End
#define PG_DN   0x4E // PageDown

#define ARR_R   0x4F // RightArrow
#define ARR_L   0x50 // LeftArrow
#define ARR_D   0x51 // DownArrow
#define ARR_U   0x52 // UpArrow

#define CTL_L 0xE0 // LeftControl
#define SFT_L 0xE1 // LeftShift
#define ALT_L 0xE2 // LeftAlt
#define GUI_L 0xE3 // Left GUI
#define CTL_R 0xE4 // RightControl
#define SFT_R 0xE5 // RightShift
#define ALT_R 0xE6 // RightAlt
#define GUI_R 0xE7 // Right GUI



/* KEY FLAGS */

static uchar flags[256] = { 0 };
static uchar modifiers[256] = { 0 };

#define IS_NORMAL_KEY    0b00000000
#define IS_MODIFIER      0b00000001
#define IS_LAYER_SWITCH  0b00000010

void initFlags()
{
	flags[CTL_L] = IS_MODIFIER;
	flags[SFT_L] = IS_MODIFIER;
	flags[ALT_L] = IS_MODIFIER;
	flags[GUI_L] = IS_MODIFIER;

	flags[CTL_R] = IS_MODIFIER;
	flags[SFT_R] = IS_MODIFIER;
	flags[ALT_R] = IS_MODIFIER;
	flags[GUI_R] = IS_MODIFIER;

	flags[LAYER] = IS_LAYER_SWITCH;


	modifiers[CTL_L] = 0b00000001;
	modifiers[SFT_L] = 0b00000010;
	modifiers[ALT_L] = 0b00000100;
	modifiers[GUI_L] = 0b00001000;

	modifiers[CTL_R] = 0b00010000;
	modifiers[SFT_R] = 0b00100000;
	modifiers[ALT_R] = 0b01000000;
	modifiers[GUI_R] = 0b10000000;
}


/* KEYBOARD LAYOUT */

#define LAYER_A  0
#define LAYER_B  1
static uchar current_layer = LAYER_A;

typedef enum {LEFT_HAND, RIGHT_HAND} hand_t;

static uchar codes[2][5][12] = {

	// layer A
	{
		{   INS, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5,   KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, BK_SP },
		{   ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T,   KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, QUOTE },
		{ SFT_L, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G,   KEY_H, KEY_J, KEY_K, KEY_L, SEMCL, SFT_R },
		{ EQUAL, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,   KEY_N, KEY_M, COMMA, FSTOP, SLASH, MINUS },
		{   TAB, CTL_L,   0x0, ALT_L, GUI_L, LAYER,   SPACE, GUI_R, ALT_R,   0x0, CTL_R, ENTER }
	},

	// layer B
	{
		{   F12,    F1,    F2,    F3,    F4,    F5,      F6,    F7,    F8,    F9,   F10,   F11 },
		{   ESC,   0x0, QUOTE,   0x0,  HOME, PG_UP,     TAB,   0x0, ARR_U, BKT_L, BKT_R, GRAVE },
		{ SFT_L,   0x0, GRAVE,   0x0,   END, PG_DN,    HASH, ARR_L, ARR_D, ARR_R,   0x0, SFT_R },
		{ PRTSC,   0x0,   0x0,   0x0,   0x0,   0x0,   QUOTE,   0x0,   0x0,   0x0, BK_SL,   DEL },
		{   TAB, CTL_L,   0x0, ALT_L, GUI_L, LAYER,     TAB, GUI_R, ALT_R,   0x0, CTL_R, ENTER }
	}

};



/* MICRO-TO-KEYBOARD CONFIG */

//PD2 - DATA+
//PD4 - DATA-
static uchar row_pins[] = {PD0, PD1, PD7, PD6, PD5};
static uchar col_pins[] = {
	PB0, PB5, PB4, PB3, PB2, PB1, // left hand
	PC1, PC2, PC3, PC4, PC5, PC0  // right hand
};

void initPins()
{
	// rows
	static uchar temp_r;
	for (temp_r = 0; temp_r < 5; temp_r++) {
		DDRD |= (1 << row_pins[temp_r]); // output
		PORTD |= (1 << row_pins[temp_r]); // set high initially
	}

	// columns
	DDRB = 0x00; // input
	DDRC = 0x00; // input
	PORTB = 0xff; // pull up
	PORTC = 0xff; // pull up
}


/* ------------------------------------------------------------------------- */

static void clearReport(void)
{
	/*
	 * Device Class Definition for Human Interface Devices (HID) Version 1.11
	 * Appendix B: Boot Interface Descriptors
	 *
	 * Byte 0   - modifiers
	 * Byte 1   - reserved for OEM use
	 * Byte 2-7 - keycodes
	 */

	memset(reportBuffer, 0, sizeof(reportBuffer[0]) * 8);
	memset(tempReportBuffer, 0, sizeof(tempReportBuffer[0][0]) * 2 * 8);

	// points to byte 2 initially and increased with every key down detected
	reportPointer = 2;
}


usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t    *rq = (void *)data;

	if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {    /* class request type */
		if (rq->bRequest == USBRQ_HID_GET_REPORT) {  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
			/* we only have one report type, so don't look at wValue */
			clearReport();
			usbMsgPtr = (void *)&reportBuffer;
			return sizeof(reportBuffer);
		} else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
			usbMsgPtr = &idleRate;
			return 1;
		} else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
			idleRate = rq->wValue.bytes[1];
		}
	} else {
		/* no vendor specific requests implemented */
	}
	return 0;   /* default for not implemented requests: return no data back to host */
}


void updateTempBuffers(int pin, hand_t hand, uchar row)
{
	uchar offset = 0;
	if (hand == RIGHT_HAND) offset = 6;

	uchar col;

	for (col = offset; col < (6 + offset); col++) {
		if (~pin & (1 << col_pins[col])) {

			if (flags[codes[LAYER_A][row][col]] & IS_LAYER_SWITCH) {
				current_layer = LAYER_B;
				continue; // layer key has no scan code to send
			}

			if (flags[codes[LAYER_A][row][col]] & IS_MODIFIER) {
				tempReportBuffer[LAYER_A][0] |= modifiers[codes[LAYER_A][row][col]];
				tempReportBuffer[LAYER_B][0] |= modifiers[codes[LAYER_B][row][col]];
			} else {
				tempReportBuffer[LAYER_A][reportPointer] = codes[LAYER_A][row][col];
				tempReportBuffer[LAYER_B][reportPointer] = codes[LAYER_B][row][col];
				reportPointer++;
				if (reportPointer > 7) reportPointer = 7;
			}
		}
	}
}


static void scanForPressedKeys(void)
{
	uchar row;
	current_layer = LAYER_A;

	for (row = 0; row < 5; row++) {
		PORTD &= ~(1 << row_pins[row]);

		// Prevent potential sync issues.
		// (Chapter 14.2.4 in data sheet of ATMEGA 328)
		asm("nop");

		if (PINB) updateTempBuffers(PINB, LEFT_HAND, row);
		if (PINC) updateTempBuffers(PINC, RIGHT_HAND, row);

		// if not efficient enought we should be able to drop it
		memcpy(reportBuffer, tempReportBuffer[current_layer], sizeof(reportBuffer));

		PORTD |= (1 << row_pins[row]); // turn PB0 into 1
	}
}


/* MAIN */

int __attribute__((noreturn)) main(void)
{
	initFlags();
	usbInit();
	initPins();

	sei();

	for (;;) {
		usbPoll();
		scanForPressedKeys();

		if (usbInterruptIsReady()) {
			usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
			clearReport();
		}
	}
}

