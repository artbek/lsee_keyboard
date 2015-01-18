$(function() {

	$("body").trigger("readCurrentMapping");

	$("body").on("currentMappingReadSuccessfully", function(e, args) {
		console.log("Whole layout:");
		console.log(args.layout);
		drawLayout(args.layout);
	});


	var keycodes = {
		"---":   "",
		LAY_B:   0xFF, // LAYER B
		SLAYR:   0xFE, // LAY_B + SFT_R
		LAY_C:   0xFD, // LAYER C

		KEY_A:   0x04, // a and A
		KEY_B:   0x05, // b and B
		KEY_C:   0x06, // c and C
		KEY_D:   0x07, // d and D
		KEY_E:   0x08, // e and E
		KEY_F:   0x09, // f and F
		KEY_G:   0x0A, // g and G
		KEY_H:   0x0B, // h and H
		KEY_I:   0x0C, // i and I
		KEY_J:   0x0D, // j and J
		KEY_K:   0x0E, // k and K
		KEY_L:   0x0F, // l and L
		KEY_M:   0x10, // m and M
		KEY_N:   0x11, // n and N
		KEY_O:   0x12, // o and O
		KEY_P:   0x13, // p and P
		KEY_Q:   0x14, // q and Q
		KEY_R:   0x15, // r and R
		KEY_S:   0x16, // s and S
		KEY_T:   0x17, // t and T
		KEY_U:   0x18, // u and U
		KEY_V:   0x19, // v and V
		KEY_W:   0x1A, // w and W
		KEY_X:   0x1B, // x and X
		KEY_Y:   0x1C, // y and Y
		KEY_Z:   0x1D, // z and Z

		KEY_1:   0x1E, // 1 and !
		KEY_2:   0x1F, // 2 and @
		KEY_3:   0x20, // 3 and #
		KEY_4:   0x21, // 4 and $
		KEY_5:   0x22, // 5 and %
		KEY_6:   0x23, // 6 and ^
		KEY_7:   0x24, // 7 and &
		KEY_8:   0x25, // 8 and *
		KEY_9:   0x26, // 9 and (
		KEY_0:   0x27, // 0 and )

		ENTER:   0x28, // Return (ENTER)
		ESC:     0x29, // ESCAPE
		BK_SP:   0x2A, // DELETE (Backspace)
		TAB:     0x2B, // Tab
		SPACE:   0x2C, // Spacebar
		MINUS:   0x2D, // - and (underscore)
		EQUAL:   0x2E, // = and +
		BKT_L:   0x2F, // [ and {
		BKT_R:   0x30, // ] and }
		BK_SL:   0x64, // \ and |
		HASH:    0x32, // Non-US # and ~
		SEMCL:   0x33, // ; and :
		QUOTE:   0x34, // ‘ and “
		GRAVE:   0x35, // Grave Accent and Tilde
		COMMA:   0x36, //, and <
		FSTOP:   0x37, // . and >
		SLASH:   0x38, // / and ?
		CPSLK:   0x39, // Caps Lock

		F1:      0x3A, // F1
		F2:      0x3B, // F2
		F3:      0x3C, // F3
		F4:      0x3D, // F4
		F5:      0x3E, // F5
		F6:      0x3F, // F6
		F7:      0x40, // F7
		F8:      0x41, // F8
		F9:      0x42, // F9
		F10:     0x43, // F10
		F11:     0x44, // F11
		F12:     0x45, // F12

		PRTSC:   0x46, // PrintScreen
		SCLCK:   0x47, // Scroll Lock
		PAUSE:   0x48, // Pause
		INS:     0x49, // Insert
		HOME:    0x4A, // Home
		PG_UP:   0x4B, // PageUp
		DEL:     0x4C, // Delete Forward
		END:     0x4D, // End
		PG_DN:   0x4E, // PageDown

		ARR_R:   0x4F, // RightArrow
		ARR_L:   0x50, // LeftArrow
		ARR_D:   0x51, // DownArrow
		ARR_U:   0x52, // UpArrow

		CTL_L:   0xE0, // LeftControl
		SFT_L:   0xE1, // LeftShift
		ALT_L:   0xE2, // LeftAlt
		GUI_L:   0xE3, // Left GUI
		CTL_R:   0xE4, // RightControl
		SFT_R:   0xE5, // RightShift
		ALT_R:   0xE6, // RightAlt
		GUI_R:   0xE7, // Right GUI
	};

	var select_template = $('<select class="keycode" />');
	for (var k in keycodes) {
		select_template.append('<option value="' + keycodes[k] + '">' + k + '</option>');
	}


	$("body").on("change", ".keycode", function() {
		var data = {
			layer: $(this).data("layer"),
			row: $(this).data("row"),
			col: $(this).data("col"),
			code: $(this).val(),
		};
		$("body").trigger("writeMapping", {data: data});
	});


	function drawLayout(codes) {
		var tables = [];

		for (var layer = 0; layer < 3; layer++) {
			var table = $("<table />");
			for (var row = 0; row < 5; row++) {
				var tr = $("<tr />");
				for (var col = 0; col < 12; col++) {
					var select = select_template.clone();
					select.val(codes[layer][row][col]);
					select.data("layer", layer);
					select.data("row", row);
					select.data("col", col);
					tr.append($("<td>").append(select));
				}
				table.append(tr);
			}
			tables.push(table);
		}

		for (var i = 0; i < tables.length; i++) {
			$("#working").hide();
			$("#layout").append("<h2>Layer " + (i + 1) + "</h2>");
			$("#layout").append(tables[i]);
		}
	}




});

