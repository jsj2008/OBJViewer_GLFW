#version 400

#define numTextures 8

#define AMBIENT 8
#define DIFFUSE 0
#define SPECULAR 1
#define GLOSSINESS 2
#define SELFILUMINATED 3
#define ALPHA 4
#define BUMP 5
#define REFLECTION 6
#define REFRACTION 7

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

uniform vec4 material[numTextures];
uniform sampler2D myTextures[numTextures];

out vec4 fragColor;

void main(void){
	vec3 textura[numTextures];
    for(int i = 0; i < numTextures; i++){
        textura[i] = texture(myTextures[i],fragTexCoord).rgb * (1.0f - material[i].w) + material[i].rgb * material[i+1].w;
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

    vec3 amb = textura[DIFFUSE] * textura[AMBIENT];
    vec3 dif = textura[DIFFUSE] * pointLight.diffuseIntensity * pointLight.color  * angDiffuse;
    vec3 spe = textura[SPECULAR] * pointLight.diffuseIntensity * pointLight.color  * pow(angSpecular,textura[GLOSSINESS].x*100);
    vec3 self = textura[SELFILUMINATED];

    float atte = (1.0 / (1.0 + pointLight.attenuation.linear * lightDistance * lightDistance));

    //vec3 color = amb + atte*(dif + spe) + self;
    vec3 color = atte*(dif + spe) + self;

    fragColor = vec4(color,textura[ALPHA]);
//    fragColor = vec4(1.0f,1.0f,1.0f,1.0f);

}