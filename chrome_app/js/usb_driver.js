$(function() {

	var dev_info = {
		"vendorId": 5824,
		"productId": 1000
	};

	// layer - row - column
	var layout = [];
	var queue = [];

	for (var layer = 0; layer < 3; layer++) {
		layout[layer] = [];
		for (var row = 0; row < 5; row++) {
			layout[layer][row] = [];
			for (var col = 0; col < 12; col++) {
				queue.push({
					layer: layer,
					row: row,
					col: col
				});
			}
		}
	}

	var processing = false;
	var usbProcess = null;
	var globalConnection = null;
	var interfaceClaimed = false;

	$("body").on("readCurrentMapping", function() {

		document.body.style.cursor = 'wait';
		prepareUsbInterface();

		usbProcess = setInterval(function() {
			if (! interfaceClaimed) return;

			if (queue.length > 0) {

				if (! processing) {
					processing = true;
					var data = queue.pop();
					usbReadCode(data, function(report) {
						console.debug(report);
						$("#working").text($("#working").text() + ".");
						if (report.length > 1) {
							var layer = report[1];
							var row = report[2];
							var col = report[3];
							var code = report[4];
							layout[layer][row][col] = code;
						}
						processing = false;
					});
				} else {
					// wait until finished processing
				}

			} else {

				document.body.style.cursor = 'default';
				$("body").trigger("currentMappingReadSuccessfully", {layout: layout});
				clearInterval(usbProcess);

				chrome.usb.releaseInterface(globalConnection, 1, function() {
					if (chrome.runtime.lastError) {
						console.debug(chrome.runtime.lastError.message);
					}
				});

			}

		}, 200);

	});



	$("body").on("writeMapping", function(e, args) {
		document.body.style.cursor = 'wait';
		usbWriteCode(args.data, function(msg) {
			console.log(msg);
			document.body.style.cursor = 'default';
		});
	});


	function usbWriteCode(data, callback) {
		var transferInfoOut = {
			"direction": "out",
			"endpoint": 0x07,
			"data": str2ab(String.fromCharCode(0, data.layer, data.row, data.col, data.code))
		};

		chrome.usb.interruptTransfer(globalConnection, transferInfoOut, function(d) {
			if (chrome.runtime.lastError) {
				console.debug(chrome.runtime.lastError.message);
				callback([chrome.runtime.lastError.message]);
			} else {
				callback("OK");
			}
		});
	}


	function usbReadCode(data, callback) {

		var transferInfoOut = {
			"direction": "out",
			"endpoint": 0x07,
			"data": str2ab(String.fromCharCode(1, data.layer, data.row, data.col))
		};

		chrome.usb.interruptTransfer(globalConnection, transferInfoOut, function(d) {
			if (chrome.runtime.lastError) {
				console.debug(chrome.runtime.lastError.message);
				callback([chrome.runtime.lastError.message]);
			} else {
				var transferInfoIn = {
					"direction": "in",
					"endpoint": 0x88,
					"length": 8,
				};

				chrome.usb.interruptTransfer(globalConnection, transferInfoIn, function(d) {
					if (chrome.runtime.lastError) {
						console.debug(chrome.runtime.lastError.message);
						callback([chrome.runtime.lastError.message]);
					} else {
						var str = ab2str(d.data);

						var report = [];
						report[0] = str.charCodeAt(0);
						report[1] = str.charCodeAt(1);
						report[2] = str.charCodeAt(2);
						report[3] = str.charCodeAt(3);
						report[4] = str.charCodeAt(4);
						report[5] = str.charCodeAt(5);
						report[6] = str.charCodeAt(6);
						report[7] = str.charCodeAt(7);

						callback(report);
					}
				});

			}
		});

	}


	function prepareUsbInterface(data, callback) {
		chrome.usb.getDevices(dev_info, function(devices) {
			for (var d in devices) {
				chrome.usb.openDevice(devices[d], function(connection) {
					if (connection) {
						globalConnection = connection;

						chrome.usb.claimInterface(connection, 1, function(w) {
							if (chrome.runtime.lastError) {
								callback([chrome.runtime.lastError.message]);
							} else {
								interfaceClaimed = true;
							}
						});
					} else {
						console.error("Error opening device: " + chrome.runtime.lastError.message);
						callback([chrome.runtime.lastError.message]);
					}
				});
			}
		});
	}


	// http://updates.html5rocks.com/2012/06/How-to-convert-ArrayBuffer-to-and-from-String
	function ab2str(arraybuffer_data) {
		return String.fromCharCode.apply(null, new Uint8Array(arraybuffer_data));
	}


	// http://updates.html5rocks.com/2012/06/How-to-convert-ArrayBuffer-to-and-from-String
	function str2ab(str) {
		var buf = new ArrayBuffer(str.length * 2); // 2 bytes for each char
		var bufView = new Uint8Array(buf);
		for (var i=0, strLen=str.length; i<strLen; i++) {
			bufView[i] = str.charCodeAt(i);
		}
		return buf;
	}

});
