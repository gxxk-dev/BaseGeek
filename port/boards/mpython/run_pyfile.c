// BaseGeek-RunPyFile 2024 Gxxk
// 以 非模块(__main__为__name__) 方式地执行 本地文件代码/模块 
// 本模块是BaseGeek的一部分。
// BaseGeek是自由软件，按照AGPL v3+进行许可。
// AGPL v3+(指 AGPL V3-or-later):https://www.gnu.org/licenses/agpl.txt

#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"
#include "lib/utils/pyexec.h"
#include "py/lexer.h"

// 运行已frozen的(指写死进固件的)模块
STATIC mp_obj_t raw_run_frozen_module(mp_obj_t file_name){
    mp_int_t return_num=pyexec_frozen_module(mp_obj_str_get_str(file_name));
    return mp_obj_new_bool(return_num);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(raw_run_frozen_module_obj, raw_run_frozen_module);

// 运行用户存储内的文件
STATIC mp_obj_t run_pyfile(mp_obj_t file_name){
    mp_int_t return_num=pyexec_file_if_exists(mp_obj_str_get_str(file_name));
    return mp_obj_new_bool(return_num);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(file_run_obj, run_pyfile);

// 进入单次REPL
STATIC mp_obj_t enter_repl(){
    return mp_obj_new_int(pyexec_friendly_repl());
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(enter_repl_obj, enter_repl);

STATIC const mp_rom_map_elem_t run_py_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_RunPy) },
    { MP_ROM_QSTR(MP_QSTR_RunFrozenModule), MP_ROM_PTR(&raw_run_frozen_module_obj) },
    { MP_ROM_QSTR(MP_QSTR_RunPyFile), MP_ROM_PTR(&file_run_obj) },
    { MP_ROM_QSTR(MP_QSTR_EnterREPL), MP_ROM_PTR(&enter_repl_obj) },
};
STATIC MP_DEFINE_CONST_DICT( run_py_module_globals, run_py_module_globals_table);

const mp_obj_module_t run_py_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&run_py_module_globals,
};