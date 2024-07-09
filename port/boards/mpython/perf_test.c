// BaseGeek-PerfTest 2024 Gxxk
// 以 时间(单位us) 和 内存(单位bytes) 为单位，测试函数的运行性能
// 本模块是BaseGeek的一部分。
// BaseGeek是自由软件，按照AGPL v3+进行许可。
// AGPL v3+(指 AGPL V3-or-later):https://www.gnu.org/licenses/agpl.txt

#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"
/* // TODO: 修Bug!
#include "extmod/utime_mphal.h"
#include "py/gc.h"
#include "ports/esp32/mphalport.h"
#include "py/objdict.c"


STATIC mp_obj_t single_test(mp_obj_t func){
    gc_info_t info;gc_info(&info);size_t start_free_ram=info.free;
    mp_uint_t start_time=mp_hal_ticks_us();

    mp_call_function_0(func);

    gc_info_t info;gc_info(&info);size_t end_free_ram=info.free;
    mp_uint_t end_time=mp_hal_ticks_us();

    mp_obj_t result = mp_obj_new_dict(0); // 创建空字典
    mp_add_di(result, MP_QSTR_time, mp_obj_new_int(start_free_ram-end_free_ram));
    mp_obj_dict_set(result, MP_QSTR_ram, mp_obj_new_int(end_time-start_time));
    
    return result
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(single_test_obj,single_test);*/
STATIC const mp_rom_map_elem_t perf_test_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_PerfTest) },
    //{ MP_ROM_QSTR(MP_QSTR_SingleTest), MP_ROM_PTR(&single_test_obj)},
};
STATIC MP_DEFINE_CONST_DICT(perf_test_module_globals, perf_test_module_globals_table);

const mp_obj_module_t perf_test_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&perf_test_module_globals,
};