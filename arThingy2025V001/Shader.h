#ifndef SHADER_H
#define SHADER_H


// prevent multiple inclusions of header file

// holds an active shader


class Shader
{
private:

	

public:
	GLuint vertexShader= 0;
	GLuint geoShader = 0;
	GLuint fragmentShader = 0;
	GLint positionAtribID = 0;
	GLint colorAtribID = 0;
	GLuint g_ShaderProgram = 0;
	GLuint g_SimpleShaderProgram = 0;

	GLint g_uniformMVP = -1;
	//GLint g_uniformModelMatrix = -1;
	GLint g_uniformEyePosW = -1;

	GLint g_uniformColor = -1;

	// Light uniform variables.
	GLint g_uniformLightPosW = -1;
	GLint g_uniformLightColor = -1;
	GLint g_uniformAmbient = -1;

	// Material properties.
	GLint g_uniformMaterialEmissive = -1;
	GLint g_uniformMaterialDiffuse = -1;
	GLint g_uniformMaterialSpecular = -1;
	GLint g_uniformMaterialShininess = -1;




	glm::mat4 model_matrix, view_matrix, projection_matrix;


	//materials
	unsigned int material_shininess;
	float material_kd;
	float material_ks;

	//attenuation
	float attenuation_kC;
	float attenuation_kL;
	float attenuation_kQ;

//	GLint g_uniformMVP = -1;
	GLint g_model_matrix = -1;
	GLint g_view_matrix = -1;
	GLint g_projection_matrix = -1;
//	GLint g_uniformLightPosW = -1;





	Shader(int latPtsInit, int longPtsInit, int initialRin) // parameters need to be changed to names of shader files
	{
		
		
		
		// set up shader for main surface
		
		vertexShader = LoadShader(GL_VERTEX_SHADER, "WorkingLight.vert");
		geoShader = LoadShader(GL_GEOMETRY_SHADER, "WorkingLight.geog");
		fragmentShader = LoadShader(GL_FRAGMENT_SHADER, "WorkingLight.frag");
		std::vector<GLuint> shaders2;
		//shaders.clear();
		shaders2.push_back(vertexShader);
		shaders2.push_back(geoShader);
		shaders2.push_back(fragmentShader);
		// Create the shader program.
		g_ShaderProgram = CreateShaderProgram(shaders2);
		assert(g_ShaderProgram != 0);

		g_uniformEyePosW = glGetUniformLocation(g_ShaderProgram, "EyePosW");

		positionAtribID = glGetAttribLocation(g_ShaderProgram, "in_position");
		colorAtribID = glGetAttribLocation(g_ShaderProgram, "in_color");
		g_uniformMVP = glGetUniformLocation(g_ShaderProgram, "MVP");
		// Light properties.
		g_uniformLightPosW = glGetUniformLocation(g_ShaderProgram, "LightPosW");
		g_uniformLightColor = glGetUniformLocation(g_ShaderProgram, "LightColor");


	};
	void setType(int x); // set type
	GLuint LoadShader(GLenum shaderType, const std::string& shaderFile);
	GLuint CreateShaderProgram(std::vector<GLuint> shaders);
	
};

#endif