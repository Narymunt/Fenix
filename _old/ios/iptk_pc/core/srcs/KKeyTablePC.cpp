#include	<windows.h>
//#include	<winuser.h>
#include	"KKeyTable.h"

#ifndef VM_OEM_PLUS
#define VK_OEM_PLUS 0xBB
#endif
#ifndef VK_OEM_COMMA
#define VK_OEM_COMMA 0xBC
#endif
#ifndef VK_OEM_MINUS
#define VK_OEM_MINUS 0xBD
#endif
#ifndef VK_OEM_PERIOD
#define VK_OEM_PERIOD 0xBE
#endif
#ifndef VK_OEM_1
#define VK_OEM_1 0xBA
#endif
#ifndef VK_OEM_2
#define VK_OEM_2 0xBF
#endif
#ifndef VK_OEM_3
#define VK_OEM_3 0xC0
#endif
#ifndef VK_OEM_4
#define VK_OEM_4 0xDB
#endif
#ifndef VK_OEM_5
#define VK_OEM_5 0xDC
#endif
#ifndef VK_OEM_6
#define VK_OEM_6 0xDD
#endif
#ifndef VK_OEM_7
#define VK_OEM_7 0xDE
#endif
#ifndef VK_OEM_8
#define VK_OEM_8 0xDF
#endif


KeyStroke			KeyboardLayout[] =
{
K_VK_LEFT  ,	VK_LEFT ,
K_VK_UP ,VK_UP ,
K_VK_DOWN ,VK_DOWN ,
K_VK_RIGHT	, VK_RIGHT ,
K_VK_SPACE ,  VK_SPACE ,
K_VK_L_SHIFT , VK_LSHIFT ,
K_VK_R_SHIFT , VK_RSHIFT ,
K_VK_RETURN , VK_RETURN ,
K_VK_R_CONTROL ,  VK_RCONTROL ,
K_VK_L_CONTROL , VK_LCONTROL ,
K_VK_F1 , VK_F1 ,
K_VK_F2 ,VK_F2 ,
K_VK_F3 ,VK_F3 ,
K_VK_F4 ,VK_F4 ,
K_VK_F5 ,VK_F5 ,
K_VK_F6 ,VK_F6 ,
K_VK_F7 ,VK_F7 ,
K_VK_F8 ,VK_F8 ,
K_VK_F9 ,VK_F9 ,
K_VK_F10 ,VK_F10 ,
K_VK_F11 ,VK_F11 ,
K_VK_F12 ,VK_F12 ,
K_VK_BACK , VK_BACK ,
K_VK_TAB ,VK_TAB ,
K_VK_ESCAPE , VK_ESCAPE ,
K_VK_A ,0x41,
K_VK_B ,0x42,
K_VK_C ,0x43,
K_VK_D ,0x44,
K_VK_E ,0x45,
K_VK_F ,0x46,
K_VK_G ,0x47,
K_VK_H ,0x48,
K_VK_I ,0x49,
K_VK_J ,0x4a,
K_VK_K ,0x4b,
K_VK_L ,0x4c,
K_VK_M ,0x4d,
K_VK_N ,0x4e,
K_VK_O ,0x4f,
K_VK_P ,0x50,
K_VK_Q ,0x51,
K_VK_R ,0x52,
K_VK_S ,0x53,
K_VK_T ,0x54,
K_VK_U ,0x55,
K_VK_V ,0x56,
K_VK_W ,0x57,
K_VK_X ,0x58,
K_VK_Y ,0x59,
K_VK_Z ,0x5A,
K_VK_0, 0x30,
K_VK_1,0x31,
K_VK_2,0x32,
K_VK_3 ,0x33,
K_VK_4 ,0x34,
K_VK_5 ,0x35,
K_VK_6 ,0x36,
K_VK_7 ,0x37,
K_VK_8 ,0x38,
K_VK_9,0x39,
K_VK_NUM0, 0x60,
K_VK_NUM1,0x61,
K_VK_NUM2,0x62,
K_VK_NUM3 ,0x63,
K_VK_NUM4 ,0x64,
K_VK_NUM5 ,0x65,
K_VK_NUM6 ,0x66,
K_VK_NUM7 ,0x67,
K_VK_NUM8 ,0x68,
K_VK_NUM9,0x69 ,
K_VK_MULTIPLY ,VK_MULTIPLY,
K_VK_ADD ,VK_ADD,
K_VK_SUBTRACT ,VK_SUBTRACT,
K_VK_DECIMAL ,VK_DECIMAL,
K_VK_DIVIDE ,VK_DIVIDE,
K_VK_CLEAR ,VK_CLEAR,
K_VK_MENU ,VK_MENU,
K_VK_LWIN ,VK_LWIN,
K_VK_RWIN , VK_RWIN,
K_VK_NUMLOCK ,VK_NUMLOCK,
K_VK_SCROLL ,VK_SCROLL,
K_VK_OEM_1 ,VK_OEM_1    ,     // 0xBA   // ';:' for US
K_VK_OEM_PLUS , VK_OEM_PLUS  ,  // 0xBB   // '+' any country
K_VK_OEM_COMMA ,VK_OEM_COMMA ,//    0xBC   // ',' any country
K_VK_OEM_MINUS   ,VK_OEM_MINUS  ,  // 0xBD   // '-' any country
K_VK_OEM_PERIOD , VK_OEM_PERIOD , // 0xBE   // '.' any country
K_VK_OEM_2     , VK_OEM_2 ,  // 0xBF   // '/?' for US
K_VK_OEM_3     ,  VK_OEM_3 , //  0xC0   // '`~' for US
K_VK_OEM_4,VK_OEM_4,         // 0xDB  //  '[{' for US
K_VK_OEM_5 ,VK_OEM_5,        // 0xDC  //  '\|' for US
K_VK_OEM_6 ,  VK_OEM_6,     //  0xDD  //  ']}' for US
K_VK_OEM_7 ,   VK_OEM_7 ,   //  0xDE  //  ''"' for US
K_VK_END , VK_END ,
K_VK_HOME , VK_HOME ,
K_VK_DEL , VK_DELETE ,
K_VK_INSERT , VK_INSERT ,
K_VK_SNAPSHOT , VK_SNAPSHOT ,
K_VK_PRIOR ,VK_PRIOR ,
K_VK_NEXT ,VK_NEXT ,
K_VK_ERROR , 9999 
};
