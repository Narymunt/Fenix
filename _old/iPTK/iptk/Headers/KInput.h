// Released under MIT License
/*
 Copyright (c) 2010 by Julien Meyer. Web: http://www.jmApp.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


#ifndef API_KINPUT__
#define API_KINPUT__

#define		ISDOWN			true
#define		ISUP			false



enum		EKeyboardLayout	{ 
	K_VK_LEFT=0  ,
	K_VK_UP ,
	K_VK_DOWN ,
	K_VK_RIGHT	,
	K_VK_SPACE , 
	K_VK_L_SHIFT , 
	K_VK_R_SHIFT ,
	K_VK_RETURN ,
	K_VK_R_CONTROL , 
	K_VK_L_CONTROL ,
	K_VK_F1 ,
	K_VK_F2 ,
	K_VK_F3 , K_VK_F4 , K_VK_F5 , K_VK_F6 , K_VK_F7 , K_VK_F8 , K_VK_F9 , K_VK_F10 ,K_VK_F11 , K_VK_F12 ,
	K_VK_BACK , K_VK_TAB ,
	K_VK_ESCAPE ,
	K_VK_A ,
	K_VK_B ,
	K_VK_C ,
	K_VK_D ,
	K_VK_E ,
	K_VK_F ,
	K_VK_G ,
	K_VK_H ,
	K_VK_I ,
	K_VK_J ,
	K_VK_K ,
	K_VK_L ,
	K_VK_M ,
	K_VK_N ,
	K_VK_O ,
	K_VK_P ,
	K_VK_Q ,
	K_VK_R ,
	K_VK_S ,
	K_VK_T ,
	K_VK_U ,
	K_VK_V ,
	K_VK_W ,
	K_VK_X ,
	K_VK_Y ,
	K_VK_Z ,
	K_VK_0,
	K_VK_1,
	K_VK_2,
	K_VK_3 ,
	K_VK_4 ,
	K_VK_5 ,
	K_VK_6 ,
	K_VK_7 ,
	K_VK_8 ,
	K_VK_9,
	K_VK_NUM0 ,K_VK_NUM1 ,K_VK_NUM2 ,K_VK_NUM3 ,K_VK_NUM4 ,K_VK_NUM5 ,K_VK_NUM6 ,K_VK_NUM7 ,K_VK_NUM8 ,K_VK_NUM9  ,
	K_VK_MULTIPLY ,
	K_VK_ADD ,
	K_VK_SUBTRACT ,
	K_VK_DECIMAL ,
	K_VK_DIVIDE ,
	K_VK_CLEAR ,
	K_VK_MENU ,
	K_VK_LWIN ,
	K_VK_RWIN , 
	K_VK_NUMLOCK ,
	K_VK_SCROLL ,
	K_VK_OEM_1,K_VK_OEM_PLUS ,      
	K_VK_OEM_COMMA ,  
	K_VK_OEM_MINUS   ,  
	K_VK_OEM_PERIOD , 
	K_VK_OEM_2     ,     
	K_VK_OEM_3     ,     
	K_VK_OEM_4      ,    
	K_VK_OEM_5     ,     
	K_VK_OEM_6    ,      
	K_VK_OEM_7  ,
	K_VK_END , 
	K_VK_HOME , K_VK_DEL , 
	K_VK_INSERT ,
	K_VK_SNAPSHOT ,
	K_VK_PRIOR ,
	K_VK_NEXT ,
	K_VK_ERROR       
};

struct	KeyStroke
{
	EKeyboardLayout	toucheID ;
	unsigned	short		KeyCode ;
};


extern	KeyStroke			KeyboardLayout[] ;


/*
//KeyStroke			KeyboardLayout[101] =
int				KeyboardLayout[101] =
{
	K_VK_LEFT  ,	0x7b ,
	K_VK_UP , 0x7e ,
	K_VK_DOWN ,0x7d ,
K_VK_RIGHT	, 0x7c ,
K_VK_SPACE ,  0x31 ,
K_VK_L_SHIFT , 0x38 ,
K_VK_R_SHIFT , 0x3c ,
K_VK_RETURN , 0x24 ,
K_VK_R_CONTROL ,  0x3e ,
K_VK_L_CONTROL , 0x3b ,
K_VK_F1 , 0x7a ,
K_VK_F2 ,0x78 ,
K_VK_F3 ,0x63 ,
K_VK_F4 ,0x76 ,
K_VK_F5 ,0x60 ,
K_VK_F6 ,0x61 ,
K_VK_F7 ,0x62 ,
K_VK_F8 ,0x64 ,
K_VK_F9 ,0x65 ,
K_VK_F10 ,0x6d ,
K_VK_F11 ,0x67 ,
K_VK_F12 ,0x6f ,
K_VK_BACK , 0x33 ,
K_VK_TAB ,0x30 ,
K_VK_ESCAPE , 0x35 ,
K_VK_A ,0x00,
K_VK_B ,0x0b,
K_VK_C ,0x08,
K_VK_D ,0x02,
K_VK_E ,0x0e,
K_VK_F ,0x03,
K_VK_G ,0x05,
K_VK_H ,0x04,
K_VK_I ,0x22,
K_VK_J ,0x26,
K_VK_K ,0x28,
K_VK_L ,0x25,
K_VK_M ,0x2e,
K_VK_N ,0x2d,
K_VK_O ,0x1f,
K_VK_P ,0x23,
K_VK_Q ,0x0c,
K_VK_R ,0x0f,
K_VK_S ,0x01,
K_VK_T ,0x11,
K_VK_U ,0x20,
K_VK_V ,0x09,
K_VK_W ,0x0d,
K_VK_X ,0x07,
K_VK_Y ,0x10,
K_VK_Z ,0x06,
K_VK_0, 0x1d,
K_VK_1,0x12,
K_VK_2,0x13,
K_VK_3 ,0x14,
K_VK_4 ,0x15,
K_VK_5 ,0x17,
K_VK_6 ,0x16,
K_VK_7 ,0x1a,
K_VK_8 ,0x1c,
K_VK_9,0x19,
K_VK_NUM0, 0x52,
K_VK_NUM1,0x53,
K_VK_NUM2,0x54,
K_VK_NUM3 ,0x55,
K_VK_NUM4 ,0x56,
K_VK_NUM5 ,0x57,
K_VK_NUM6 ,0x58,
K_VK_NUM7 ,0x59,
K_VK_NUM8 ,0x5b,
K_VK_NUM9,0x5c ,
K_VK_MULTIPLY ,0x43,
K_VK_ADD ,0x45,
K_VK_SUBTRACT ,0x4e,
K_VK_DECIMAL ,0x41,
K_VK_DIVIDE ,0x4b,
	K_VK_CLEAR ,0x47,
	K_VK_MENU ,0x37,
	K_VK_LWIN , 0x3a,
	K_VK_RWIN , 0x3d,
	K_VK_NUMLOCK ,0x39,
	K_VK_SCROLL ,0x6b,
	K_VK_OEM_1 ,0x29    ,     // 0xBA   // ';:' for US
	K_VK_OEM_PLUS , 0x18  ,  // 0xBB   // '+' any country
	K_VK_OEM_COMMA ,0x2b ,//    0xBC   // ',' any country
	K_VK_OEM_MINUS   ,0x1b  ,  // 0xBD   // '-' any country
	K_VK_OEM_PERIOD , 0x2f , // 0xBE   // '.' any country
	K_VK_OEM_2     , 0x2c ,  // 0xBF   // '/?' for US
	K_VK_OEM_3     ,  0x32 , //  0xC0   // '`~' for US
	K_VK_OEM_4,0x21,         // 0xDB  //  '[{' for US
	K_VK_OEM_5 ,0x2a,        // 0xDC  //  '\|' for US
	K_VK_OEM_6 ,  0x1e,     //  0xDD  //  ']}' for US
	K_VK_OEM_7 ,   0x27,    //  0xDE  //  ''"' for US
	K_VK_END , 119 ,
	K_VK_HOME , 115 ,
	K_VK_DEL , 117 ,
	K_VK_INSERT ,114  ,
	K_VK_SNAPSHOT , 105 ,  //F13
	K_VK_PRIOR ,116,
	K_VK_NEXT ,121,

	K_VK_ERROR , 0xff
};
*/
struct	sFinger	
{
	short		x,y ;
	bool		pressed ;
};

class KInput
{
private:
	static			sFinger			finger[2] ;
	
	static bool		_screenPressed;
	static int		_xScreenHit;
	static int		_yScreenHit;
	static int		_tapeCount;
	static float	_xAcc;
	static float	_yAcc;
	static float	_zAcc;
	
	static int		midX, midY;
	static			bool	_btPressed ;
	static			long	_mx,_my ;
public:
		
	static void		initInput(int windowHandle);
	static void		hidePointer();
	static bool		isPressed(int keyCode);
	static void		mousePointerTo(int x, int y);
	static int		getMouseX();
	static int		getMouseY();		
	static bool		getLeftButtonState();
	static void		showPointer();
	
	// iPhone specific 
	static float	getAccelerationX();
	static float	getAccelerationY();
	static float	getAccelerationZ();
	static void		setAccelerometer(float x, float y, float z);
	static int		getScreenTap();
	static bool		isScreenPressed(int *hitX=0, int *hitY=0);
	static bool		isScreenReleased(int *hitX, int *hitY);
	//max 2 fingers  : 0 or 1
	static	sFinger*		getFinger( short fingerid ) ;
	

	//do not use unless you know what you're doing
	static void		setFingerPosition( int fingerid , short	x , short y , bool pressed ) ;
	static void		swapFingerPosition(int fingerid1, int fingerid2);
	
	static void		setScreenPressed(int tapCount, int x, int y);
	static void		setScreenMoving(int x, int y);
	static void		setScreenReleased();
	

	
};

#endif // API_KINPUT__