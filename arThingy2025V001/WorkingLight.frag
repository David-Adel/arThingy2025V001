#version 330 core
// Input color from the vertex program.
//in vec4 v2f_color;
//layout (location=0) out vec4 out_color;
//void main()
//{
   // out_color = v2f_color;
	////out_color = vec4(1,0,0,1);
//}
// 
layout(location = 0) out vec4 out_color;
//layout(location=1) in vec4 v2f_color;
uniform vec4 EyePosW; 
uniform vec4 LightPosW;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;
uniform mat4 model_matrix;
in vec4 v2f_normalW; // normal;
in vec4 v2f_color;
in vec4 v2f_positionW; // Position in world space.

//void main(){
//	vec3 eye_position = vec3(EyePosW);
//	vec3 world_pos = vec3(v2f_positionW); // world_pos;
//	vec3 normal = vec3(v2f_normalW); // normal;
//	vec3 L = normalize( eye_position - world_pos);
//	vec3 V = normalize( eye_position - world_pos);
//	float difuza = max(0, dot(L,normal));
//	vec3 H = normalize(L + V );
//	float speculara = 0;
//	if( dot(L,normal) > 0.0)
//	{
//	     speculara =   pow( max(0, dot( H, normal)), material_shininess);
//	}	
//	out_color = v2f_color * (difuza + speculara);	
//}

////////////////////////////////////////////////////////////

//varying vec4 position;  // position of the vertex (and fragment) in world space
//varying vec3 varyingNormalDirection;  // surface normal vector in world space
vec3 varyingNormalDirection;  // surface normal vector in world space
 vec4 position;  // position of the vertex (and fragment) in world space

uniform mat4 m, v, p;
uniform mat4 v_inv;
 
struct lightSource
{
  vec4 position;
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation, linearAttenuation, quadraticAttenuation;
  float spotCutoff, spotExponent;
  vec3 spotDirection;
}; 
// 0.0, 1.0, 0.0, //constantAttenuation, linearAttenuation, quadraticAttenuation

lightSource light0 = lightSource(
  vec4(0.0,  0.0,  15.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
	0.0, 1.0, 0.0, 
  180.0, 0.0,
  vec3(0.0, 0.0, 0.0)
);
//vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);
 vec4 scene_ambient = vec4(0.5, 0.5, 0.5, 1.0);
struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};
  //vec4(0.2, 0.2, 0.2, 1.0), // ambient
  //vec4(1.0, 0.8, 0.8, 1.0), //diffuse
//vec4(1.0, 1.0, 1.0, 1.0), // specular;
 // 5.0 //shininess
material frontMaterial = material(
  vec4(.5, .5, .5, 1.0),
  vec4(0.8, 0.8, 0.8, 1.0), // 
  vec4(0.70, 0.70, 0.70, 1.0),
  10.0
);
 
void main()
{
  
 //light0.position =  LightPosW * -1; 
 light0.position = vec4(0.0,0.0,15.0,0.0);
  
  vec3 varyingNormalDirection = vec3(v2f_normalW);  // surface normal vector in world space
 vec4 position = v2f_positionW;  // position of the vertex (and fragment) in world space
  
  vec3 normalDirection = normalize(varyingNormalDirection);
  //vec3 viewDirection = normalize(vec3(v_inv * vec4(0.0, 0.0, 0.0, 1.0) - position));  
   vec3 viewDirection = normalize(vec3(EyePosW) - vec3(position));  
  vec3 lightDirection;
  float attenuation;
 
  if (0.0 == light0.position.w) // directional light?
    {
      attenuation = 1.0; // no attenuation
      lightDirection = normalize(vec3(light0.position));
    } 
  else // point light or spotlight (or other kind of light) 
    {
      vec3 positionToLightSource = vec3(light0.position - position);
      float distance = length(positionToLightSource);
      lightDirection = normalize(positionToLightSource);
      attenuation = 1.0 / (light0.constantAttenuation
                           + light0.linearAttenuation * distance
                           + light0.quadraticAttenuation * distance * distance);
 
      if (light0.spotCutoff <= 90.0) // spotlight?
	{
	  float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));
	  if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
	    {
	      attenuation = 0.0;
	    }
	  else
	    {
	      attenuation = attenuation * pow(clampedCosine, light0.spotExponent);   
	    }
	}
    }
 
  vec3 ambientLighting = vec3(scene_ambient) * vec3(frontMaterial.ambient);
 
  vec3 diffuseReflection = attenuation 
    * vec3(light0.diffuse) * vec3(frontMaterial.diffuse)
    * max(0.0, dot(normalDirection, lightDirection));
 
  vec3 specularReflection;
  if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
    {
      specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
    }
  else // light source on the right side
    {
      specularReflection = attenuation * vec3(light0.specular) * vec3(frontMaterial.specular) 
	* pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);
    }
 
  out_color = vec4(ambientLighting + diffuseReflection + specularReflection, 1.0) * v2f_color;
}
