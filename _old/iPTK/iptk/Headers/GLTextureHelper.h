
//#ifdef TARGET_OS_IPHONE
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
//#endif

typedef struct
{
	char			*filename;
	int				originalWidth;
	int				originalHeight;
	int				width;
	int				height;
	int				bpp;
	bool			useColorkey;
	int				R_colorkey;
	int				G_colorkey;
	int				B_colorkey;
	unsigned char	*pixels;
	unsigned int	textureID;
	
} JadeImage_t;

class GLTextureHelper
	{
	public:
		GLTextureHelper();
		~GLTextureHelper(void);
		
		void	clearSurface(char * surface, int w, int h, int bpp, int R, int G, int B, int A);
		bool	LoadWatermark();
		bool	isEyeRetina();
		void	listFonts();
		bool	loadText(const char *text, const char * fontname, int fontsize);
		bool	LoadTexture(const char *szTextureFile );
		bool	LoadTextureEx(const char *szTextureFile  );
		int		LoadFileTGA(JadeImage_t *textureObject);
		
		GLint	getHeight(void) { return _nHeight; }
		GLint	getWidth(void) { return _nWidth; }
		GLint	getTextureSize(void) { return _texSize; }
		bool	getEyeRetina(void) { return _eyeRetina; }
		
		
	protected:
		
		GLubyte *	_pData;
		GLint		_nWidth;
		GLint		_nHeight;
		GLint		_texSize;
		bool		_eyeRetina;
		
	};
