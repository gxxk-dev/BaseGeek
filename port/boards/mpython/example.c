#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"

// 一个将以example.add_ints(a, b)的形式被调用的函数
STATIC mp_obj_t example_add_ints(mp_obj_t a_obj, mp_obj_t b_obj) {
    // 从mpy参数中获取到真实的整数值
    int a = mp_obj_get_int(a_obj);
    int b = mp_obj_get_int(b_obj);

    // 计算 然后转换为mpy对象 作为返回值返回
    return mp_obj_new_int(a + b);
}
// 绑定上方定义的函数至Python中的对象
STATIC MP_DEFINE_CONST_FUN_OBJ_2(example_add_ints_obj, example_add_ints);
// MP_DEFINE_CONST_FUN_OBJ_【X】中的X代表参数名称 此处这个函数的第一个参数在后面定义模块属性会用到

// 此处定义示例模块的属性
// 内容为属性名（字符串）与 mPy 对象引用的键/值对
// 所有 标识符/字符串 都应为 MP_QSTR_xxx
STATIC const mp_rom_map_elem_t example_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_example) }, // 模块名称
    { MP_ROM_QSTR(MP_QSTR_add_ints), MP_ROM_PTR(&example_add_ints_obj) }, // 模块函数-add_ints
};
STATIC MP_DEFINE_CONST_DICT(example_module_globals, example_module_globals_table);

// 定义模块对象
const mp_obj_module_t example_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&example_module_globals,
};