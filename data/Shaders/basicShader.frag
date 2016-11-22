#version 400

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

uniform float amount[numTextures];
uniform vec3 material[numTextures];
uniform sampler2D myTextures[numTextures];

out vec4 fragColor;

void main(void){
	vec3 textura[numTextures];
    for(int i = 0; i < numTextures; i++){
        textura[i] = texture(myTextures[i],fragTexCoord).rgb * amount[i];
    }
//    if(material[BUMP].w < 1.0f){
//        textura[BUMP] = fragNormal * textura[BUMP];
//    } else {
//        textura[BUMP] = normalize(fragNormal);
//    }
    textura[BUMP] = normalize(fragNormal);

    float lightDistance = distance(pointLight.position,fragPosition.xyz);

    vec3 lightVector = normalize(pointLight.position-fragPosition.xyz);

    float angDiffuse = clamp(dot(textura[BUMP],lightVector),0,1);

    vec3 r = reflect(-lightVector,textura[BUMP]);
    vec3 v = normalize(camPos-fragPosition.xyz);
    float angSpecular = clamp(dot(v,r),0,1);

    vec3 amb = textura[DIFFUSE] * material[AMBIENT];
    vec3 dif = textura[DIFFUSE] * pointLight.diffuseIntensity * pointLight.color  * angDiffuse;
    vec3 spe = textura[SPECULAR] * pointLight.diffuseIntensity * pointLight.color  * pow(angSpecular,textura[GLOSSINESS].x*100);
    vec3 self = textura[SELFILUMINATED];

    float atte = (1.0 / (1.0 + pointLight.attenuation.linear * lightDistance * lightDistance));

    vec3 color = amb + atte*(dif + spe) + self;
//    vec3 color = atte*(dif + spe) + self;

    fragColor = vec4(color,textura[ALPHA]);
//    fragColor = vec4(1.0f,1.0f,1.0f,1.0f);

}