#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"
#include "keycodes.h"
#include "mapping.h"


/**
 * USB report descriptor, size must match usbconfig.h
 *
 * Device Class Definition for Human Interface Devices (HID) Version 1.11
 * Appendix B: Boot Interface Descriptors
 */
PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
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

#define REPORT_POINTER_FIRST_INDEX 2
#define REPORT_POINTER_LAST_INDEX 7
// Points to byte number <REPORT_POINTER_FIRST_INDEX> initially and then
// increased with every key down detected up to byte number <REPORT_POINTER_LAST_INDEX>.
static uchar reportPointer = REPORT_POINTER_FIRST_INDEX;

static void increaseReportPointer(void)
{
	reportPointer++;
	if (reportPointer > REPORT_POINTER_LAST_INDEX) {
		reportPointer = REPORT_POINTER_LAST_INDEX;
	}
}




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
	flags[SLAYR] = IS_LAYER_SWITCH | IS_MODIFIER;


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

// Make sure the layer key is not released before normal key.
// It makes the keyboard more forgiving.
#define DEFAULT_LAYER_PERSISTENCE 3;
static char layer_persistence_timeout = DEFAULT_LAYER_PERSISTENCE;

typedef enum {LEFT_HAND, RIGHT_HAND} hand_t;


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

	reportPointer = REPORT_POINTER_FIRST_INDEX;

	layer_persistence_timeout--;
	if (layer_persistence_timeout < 0) {
		layer_persistence_timeout = 0;
	}
}


static uchar idleRate;   /* repeat rate for keyboards, never used for mice */

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
	uchar keycode_a;
	uchar keycode_b;

	for (col = offset; col < (6 + offset); col++) {
		if (~pin & (1 << col_pins[col])) {

			keycode_a = codes[LAYER_A][row][col];
			keycode_b = codes[LAYER_B][row][col];

			if (flags[keycode_a] & IS_LAYER_SWITCH) {
				current_layer = LAYER_B;
				layer_persistence_timeout = DEFAULT_LAYER_PERSISTENCE;
				if (flags[keycode_a] & IS_MODIFIER) {
					keycode_a = SFT_R;
					keycode_b = SFT_R;
				} else {
					continue; // layer key alone has no scan code to send
				}
			}

			tempReportBuffer[LAYER_A][reportPointer] = keycode_a;
			tempReportBuffer[LAYER_B][reportPointer] = keycode_b;
			increaseReportPointer();
		}
	}
}


static void scanForPressedKeys(void)
{
	uchar row;
	if (layer_persistence_timeout == 0) {
		current_layer = LAYER_A;
	}

	for (row = 0; row < 5; row++) {
		PORTD &= ~(1 << row_pins[row]);

		// Prevent potential sync issues. (Chapter 14.2.4 in data sheet of ATMEGA 328)
		asm("nop");

		if (PINB) updateTempBuffers(PINB, LEFT_HAND, row);
		if (PINC) updateTempBuffers(PINC, RIGHT_HAND, row);

		// if not efficient enought we should be able to drop it
		memcpy(reportBuffer, tempReportBuffer[current_layer], sizeof(reportBuffer));

		reportBuffer[0] = 0;
		uchar i;
		for (i = REPORT_POINTER_FIRST_INDEX; i < REPORT_POINTER_LAST_INDEX; i++) {
			if (flags[reportBuffer[i]] & IS_MODIFIER) {
				reportBuffer[0] |= modifiers[reportBuffer[i]];
			}
		}

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

