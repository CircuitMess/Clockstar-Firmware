# Clockstar Firmware
> Build & Code Your Own Smartwatch

# Building
To build the Clockstar base firmware, you'll need the ESP-IDF. You can find the getting started 
guide [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/). The 
production firmware is built using IDF version 5.1, commit [3a45d4e](https://github.com/espressif/esp-idf/tree/3a45d4e949a174e8829a2e4c86c421b030ceac5a).


### ESP-IDF patching
Contained in the repository is [ESP-IDF.patch](ESP-IDF.patch).
The patch addresses [issues](https://github.com/espressif/esp-idf/issues/11690) in IDF v5.1
related to FPU registers during context switching.

For proper code functioning, apply this patch onto your ESP-IDF installation path using:
```shell
cd /esp-idf-path/
git apply ESP-IDF.patch
```

After patching, in the root directory of the project:

**To build the firmware** run ```idf.py build```

**To upload the firmware to the device** run ```idf.py -p <PORT> flash```. Replace `<PORT>` with 
the port Clockstar is attached to, for ex. ```COM6``` or ```/dev/ttyUSB0```.

# Restoring the stock firmware
To restore the stock firmware, you can download the prebuilt binary on the [releases page](https://github.com/CircuitMess/Clockstar-Firmware/releases) of this repository 
and flash it manually using esptool:
```shell
esptool -c esp32 -b 921600 -p <PORT> write_flash 0 Clockstar-Firmware.bin
```

Alternatively, you can also do so using [CircuitBlocks](https://code.circuitmess.com/) by 
logging in, clicking the "Restore Firmware" button in the top-right corner, and following the 
on-screen instructions. 