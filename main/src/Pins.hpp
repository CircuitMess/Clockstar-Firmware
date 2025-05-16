#ifndef CLOCKSTAR_LIBRARY_PINS_HPP
#define CLOCKSTAR_LIBRARY_PINS_HPP

#define BTN_DOWN 40
#define BTN_UP 38
#define BTN_SELECT 39
#define BTN_ALT 37

#define BTN_LEFT BTN_UP
#define BTN_RIGHT BTN_DOWN
#define BTN_A BTN_SELECT
#define BTN_B BTN_ALT

#define RGB_R 8
#define RGB_G 7
#define RGB_B 6

#define PIN_BL 9
#define PIN_BUZZ 11
#define PIN_BATT 10
#define PIN_CHARGE 36 // TODO this is actually USB detect pin idk if they act the same

#define I2C_SDA 4
#define I2C_SCL 5

#define TFT_SCK 48
#define TFT_MOSI 34
#define TFT_DC 33
#define TFT_RST 47

#define JIG_STATUS 13 // TODO this might be different

#define IMU_INT1 41
#define IMU_INT2 42

#endif //CLOCKSTAR_LIBRARY_PINS_HPP
