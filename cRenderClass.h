

class cRenderClass
{
public:

	cRenderClass(const int, const int);
	~cRenderClass();

	void setViewport2D();
	void setViewport3D(GLint, GLint);

	void create(int argc, _TCHAR* argv[]);
	void initShaders();
	void loop();

	void render(int);
	void render2(int);
	void drawPixel(int, int);	

	inline void clear(){memset( m_buffer, 0, sizeof(float)*m_sw*m_sh*4 );}
	inline void pointSize(int size){m_point_size = size;}
	inline void colour(float r, float g, float b)
	{
		m_colour.r = r;
		m_colour.g = g;
		m_colour.b = b;
	}

	inline void OpenGL2_0(bool value){m_OPENGL_2_0_SUPPORTED = value;}
	inline bool OpenGL2_0(){return m_OPENGL_2_0_SUPPORTED;}
	
	class cShaderInfo	ShaderInfo;

private:

	int		 m_sw, m_sh;
	int		 m_point_size;
	float	*m_buffer;
	sRGB	 m_colour;
	bool	m_OPENGL_2_0_SUPPORTED;
};