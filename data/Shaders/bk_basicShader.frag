#version 440

#define numTextures 8

#define AMBIENT 0
#define DIFFUSE 1
#define SPECULAR 2
#define GLOSSINESS 3
#define SELFILUMINATED 4
#define ALPHA 5
#define BUMP 6
#define REFLECTION 7
#define REFRACTION 8

in vec4 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec3 camPos;
uniform vec3 camEye;

struct tAttenuation{
		float constant;
		float linear;
		float exponential;
};

struct tPointLight{
	vec3 position;
	vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
	tAttenuation attenuation;
};

uniform tPointLight pointLight;

//struct tMaterial{
//    vec4 ambientColor;
//    vec4 diffuseColor;
//    vec4 specularColor;
//    vec4 glossinessColor;
//    vec4 selfIluminatedColor;
//    vec4 alphaColor;
//    vec4 bumpColor;
//    vec4 reflectionColor;
//    vec4 refractionColor;
//};

//uniform tMaterial material;

uniform vec4 material[numTextures];

uniform sampler2D myTextures[numTextures];

out vec4 fragColor;

void main(void)
{
	vec3 textura[numTextures];
    for(int i = 0; i < numTextures; i++){
        textura[i] = texture(myTextures[i],fragTexCoord).rgb * (1.0f - material[i].w) + material[i].rgb * material[i].w;
    }
    if(material[BUMP].w < 1.0f){
        textura[BUMP] = fragNormal * textura[BUMP];
    } else {
        textura[BUMP] = fragNormal;
    }
    textura[BUMP] = fragNormal;
    vec3 lightVector = pointLight.position-vec3(fragPosition);

    float angDiffuse;
    angDiffuse = dot(-textura[BUMP],lightVector)/length(lightVector);

    vec3 rLight = reflect(-lightVector,textura[BUMP]);

    float angSpecular;
    angSpecular = dot(-camEye,rLight)/length(rLight);
    if(angSpecular > 10.0f)
        angSpecular = 0;

    vec3 color = textura[DIFFUSE] * pointLight.ambientIntensity +
    			 textura[DIFFUSE] * pointLight.diffuseIntensity * pointLight.color  * clamp(angDiffuse,0,1)+
           		 textura[SPECULAR].x * pointLight.color * clamp(pow(angSpecular,textura[GLOSSINESS].x * 100),0,1) +
           		 textura[SELFILUMINATED];
       //if(gl_FrontFacing){
       //fragColor = vec4(vec3(1-length(fragPosition.xyz-camPos)*0.001f),1.0f) * vec4(color,textura[ALPHA].x+1.0f);
       //fragColor = vec4(color,textura[ALPHA].x);
       fragColor = vec4(color,1.0f);
       //fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
       //}else
       //fragColor = vec4(1.0f,0.0f,0.0f,0.0f);
}

