// 此处头文件用于访问mPy API
#include "py/dynruntime.h"

// HelloWorld程序 懂得都懂
STATIC mp_obj_t hello_world() {
    mp_printf(&mp_plat_print,"Hello World！\n");
    return mp_const_none;
}
// 绑定对应函数
STATIC MP_DEFINE_CONST_FUN_OBJ_0(HelloWorld, hello_world);

// 导入模块时调用此处 注册对应对象
mp_obj_t mpy_init(mp_obj_fun_bc_t *self, size_t n_args, size_t n_kw, mp_obj_t *args) {
    // 标准结构 函数结尾的 MP_DYNRUNTIME_INIT_EXIT 也一样 勿动
    MP_DYNRUNTIME_INIT_ENTRY

    // 注册HelloWorld函数
    mp_store_global(MP_QSTR_HelloWorld, MP_OBJ_FROM_PTR(&HelloWorld));
    
    
    MP_DYNRUNTIME_INIT_EXIT
}