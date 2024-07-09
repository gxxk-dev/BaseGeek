// BaseGeek-RawOled 2024 Gxxk
// 以C的方式操作OLED屏幕 通过部分特性提升性能
// 本模块是BaseGeek的一部分。
// BaseGeek是自由软件，按照AGPL v3+进行许可。
// AGPL v3+(指 AGPL V3-or-later):https://www.gnu.org/licenses/agpl.txt
#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"
#include "drivers/startup/oled.h"
#include "drivers/startup/startup.h"
// 神笔gcc不让oled_init_cmd共享使用www.
const uint8_t oled_init_cmd_[] = {
    SET_DISP_OFF,               // display off
	SET_DISP_CLK_DIV, 0x80,     // timing and driving scheme
	SET_MUX_RATIO, 0x3f,        // 0xa8
	SET_DISP_OFFSET, 0x00,      // 0xd3
	SET_DISP_START_LINE | 0x00, // start line
	SET_CHARGE_PUMP,  0x10,     // 0x10 if external_vcc else 0x14,
	SET_MEM_ADDR, 0x00,         // address setting
	SET_SEG_REMAP | 0x01,       // column addr 127 mapped to SEG0
	SET_COM_OUT_DIR | 0x08,     // scan from COM[N] to COM0
	SET_COM_PIN_CFG, 0x12,
	SET_CONTRACT_CTRL, 0xcf,
	SET_PRECHARGE, 0x22,        // 0x22 if self.external_vcc else 0xf1,
	SET_VCOM_DESEL, 0x40,       // 0.83*Vcc
	SET_ENTIRE_ON,              // output follows RAM contents
	SET_NORM_INV,       
	SET_DISP_ON                 // on
};

// 重写 Oled屏幕初始化实现工作频率自定义
bool oled_init_(int freq) {
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
    conf.master.clk_speed = freq;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_MASTER_RX_BUF_DISABLE,
                       I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_initialized = true;
    
    for (int i = 0; i < sizeof(oled_init_cmd_); i++) {
        if (write_cmd(oled_init_cmd_[i]) != ESP_OK) {
            return false;
        }
    }
    return true;
}

// 反转屏幕色彩 SET_NORM_INV | (invert & 1)
STATIC mp_obj_t invert(mp_obj_t invert) {
    write_cmd( SET_NORM_INV | (mp_obj_get_int(invert) & 1) );
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(invert_obj, invert);

STATIC mp_obj_t init(mp_obj_t freq) { // 初始化 连接OLED屏
    int freq_ = mp_obj_get_int(freq);
    if (i2c_initialized) return mp_const_true;
    return mp_obj_new_bool(oled_init_(freq_));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(init_obj, init);

STATIC mp_obj_t deinit(){ // 断开与OLED屏的连接
    oled_deinit();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(deinit_obj, deinit);

STATIC mp_obj_t set_pixel(mp_obj_t x, mp_obj_t y, mp_obj_t color){ // 绘制指定位置的像素
    int16_t x_ = mp_obj_get_int(x);
    int16_t y_ = mp_obj_get_int(y);
    int16_t color_ = mp_obj_get_int(color);
    oled_drawPixel(x_, y_, color_);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(set_pixel_obj, set_pixel);

// 以(x,y)为起始点绘制文字
// 仅支持 ASCII 32-127 内的字符 大小8x8
STATIC mp_obj_t disp_char(mp_obj_t str,mp_obj_t x, mp_obj_t y){ 
    char *str_ = strdup(mp_obj_str_get_str(str));
    int16_t x_ = mp_obj_get_int(x);
    int16_t y_ = mp_obj_get_int(y);
    oled_print(str_, x_, y_);
    free(str_);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(disp_char_obj, disp_char);

STATIC mp_obj_t clear(){ // 清屏
    oled_clear();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(clear_obj,clear);

STATIC mp_obj_t show(){
    oled_show();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(show_obj,show);

// 绘制开机图像图像(本来想绘制可自行指定的图像的 结果技术力受限做不到啊)
STATIC mp_obj_t draw_bootpic() {
    oled_drawImg(img_mpython);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(draw_bootpic_obj,draw_bootpic);

STATIC mp_obj_t poweroff(){ // 关闭显示屏电源
    write_cmd(SET_DISP_OFF);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(poweroff_obj,poweroff);

STATIC mp_obj_t poweron(){ // 开启显示屏电源
    write_cmd(SET_DISP_ON);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(poweron_obj,poweron);

STATIC mp_obj_t contrast(mp_obj_t contrast){ // 设置亮度(0-255)
    write_cmd(SET_CONTRAST);
    write_cmd((uint8_t)mp_obj_get_int(contrast));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(contrast_obj, contrast);

STATIC const mp_rom_map_elem_t raw_oled_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_RawOled) },
    { MP_ROM_QSTR(MP_QSTR_Init), MP_ROM_PTR(&init_obj) },
    { MP_ROM_QSTR(MP_QSTR_Deinit), MP_ROM_PTR(&deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_SetPixel), MP_ROM_PTR(&set_pixel_obj) },
    { MP_ROM_QSTR(MP_QSTR_DispChar), MP_ROM_PTR(&disp_char_obj) },
    { MP_ROM_QSTR(MP_QSTR_Clear), MP_ROM_PTR(&clear_obj)},
    { MP_ROM_QSTR(MP_QSTR_Show), MP_ROM_PTR(&show_obj)},
    { MP_ROM_QSTR(MP_QSTR_DrawBootPic), MP_ROM_PTR(&draw_bootpic_obj)},
    { MP_ROM_QSTR(MP_QSTR_Invert), MP_ROM_PTR(&invert_obj)},
    { MP_ROM_QSTR(MP_QSTR_PowerOff), MP_ROM_PTR(&poweroff_obj)},
    { MP_ROM_QSTR(MP_QSTR_PowerOn), MP_ROM_PTR(&poweron_obj)},
    { MP_ROM_QSTR(MP_QSTR_Contrast), MP_ROM_PTR(&contrast_obj)},
};
STATIC MP_DEFINE_CONST_DICT(raw_oled_module_globals, raw_oled_module_globals_table);

const mp_obj_module_t raw_oled_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&raw_oled_module_globals,
};