varying vec3 vN;
varying vec3 v; 
#define MAX_LIGHTS 4

void main (void) 
{ 
	vec3 N = normalize(vN);
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
   
   for (int i=0;i<MAX_LIGHTS;i++)
   {
   	  float insideSpot = 1.0;
      vec3 L = normalize(gl_LightSource[i].position.xyz - v); 
      vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0) 
      vec3 R = normalize(-reflect(L,N)); 
   
      //calculate Ambient Term: 
      vec4 Iamb = gl_FrontLightProduct[i].ambient; 

      if (gl_LightSource[i].spotCutoff <= 90.0)
      {
      	float clampedCosine = max(0.0, dot(-L, normalize(gl_LightSource[i].spotDirection)));
      	if (clampedCosine < cos(radians(gl_LightSource[i].spotCutoff))) // outside of spotlight cone?
      	{
      		insideSpot = 0.0;
      	}
      }
      //calculate Diffuse Term: 
      vec4 Idiff =  gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
      Idiff = insideSpot * clamp(Idiff, 0.0, 1.0); 
   
      // calculate Specular Term:
      vec4 Ispec = gl_FrontLightProduct[i].specular 
             * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
      Ispec = insideSpot * clamp(Ispec, 0.0, 1.0); 
  
      finalColor += Iamb + Idiff + Ispec;
   }
   
   // write Total Color: 
   gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor; 
}