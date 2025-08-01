# Clockstar Firmware

> Build & Code Your Own Smartwatch

# Building

To build the Clockstar base firmware, you'll need the ESP-IDF. You can find the getting started
guide [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/). The
production firmware is built using IDF version 5.1,
commit [3a45d4e](https://github.com/espressif/esp-idf/tree/3a45d4e949a174e8829a2e4c86c421b030ceac5a).

### ESP-IDF patching

Contained in the repository is [ESP-IDF.patch](ESP-IDF.patch).
The patch addresses [issues](https://github.com/espressif/esp-idf/issues/11690) in IDF v5.1
related to FPU registers during context switching.

For proper code functioning, apply this patch onto your ESP-IDF installation path using:

```shell
cd /esp-idf-path/
git apply ESP-IDF.patch
```

Clone all submodules from the project root

```shell
git submodule update --init --recursive
```

### LovyanGFX patching

Contained in the repository is [LovyanGFX.patch](LovyanGFX.patch).
Apply it onto the cloned LovyanGFX submodule:

```shell
cd components/LovyanGFX
git apply ../../LovyanGFX.patch
```

After patching everything, in the root directory of the project:

**To build the firmware** run ```idf.py build```

**To upload the firmware to the device** run ```idf.py -p <PORT> flash```. Replace `<PORT>` with
the port Clockstar is attached to, for ex. ```COM6``` or ```/dev/ttyACM0```.

### Merging a single binary file

After building (or flashing) the firmware, you can merge the resulting files into a single
binary file. This is useful for sharing a build or flashing it directly onto the board.

The necessary tool for this is [esptool](https://github.com/espressif/esptool), which comes
preinstalled with ESP-IDF

From the project root go into your build folder (usually just /build):

```shell
cd build
esptool --chip esp32s3 merge_bin --fill-flash-size 4MB -o ../Clockstar.bin --flash_mode dio 
--flash_freq 80m --flash_size 4MB 0x0 bootloader/bootloader.bin 0x10000 Clockstar-Firmware.bin 
0x8000 
partition_table/partition-table.bin 0x2f6000 storage.bin
```

# Restoring the stock firmware

To restore the stock firmware, you can download the prebuilt binary on
the [releases page](https://github.com/CircuitMess/Clockstar-Firmware/releases) of this
repository
and flash it manually using esptool:

```shell
esptool -c esp32s3 -b 921600 -p <PORT> write_flash 0 Clockstar-Firmware.bin
```

Alternatively, you can also do so using [CircuitBlocks](https://code.circuitmess.com/) by
logging in, clicking the "Restore Firmware" button in the top-right corner, and following the
on-screen instructions.