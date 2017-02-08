#version 120
#extension GL_EXT_gpu_shader4 : require

uniform vec4 globalColor = vec4(1.0);
uniform	sampler2D tex;			// we use this to sample depth data for our boxes.
uniform float time=0.0;	// we get this from our ofApp, it's a time value moving from 0 to 1 every 30 seconds
uniform float width;
uniform float height;

varying vec4 colorVarying;

vec3 ycrcvToRgb (vec3 ycrcb) {
  vec3 rgb;
  rgb.r = ycrcb.r + 1.40200*ycrcb.g;
  rgb.g = ycrcb.r - 0.34414*ycrcb.b - 0.71414*ycrcb.g;
  rgb.b = ycrcb.r + 1.77200*ycrcb.b;
  return rgb;
}

void main() {
  float iCount = 200.0;

  // instanceX :: -0.5 ~ 0.5
  // instanceY :: -0.5 ~ 0.5
  float instanceX = (mod(gl_InstanceID, width) - width/2.0) / width;
	float instanceY = ((gl_InstanceID/width) - height/2.0) / height;

  float timeDependentInstanceXValue = mod(instanceX * 0.25 , 1.0);

  // samplePos :: vec2(0.0 ~ 1.0, 0.0 ~ 1.0)
  vec2 samplePos = vec2(instanceX+0.5, instanceY+0.5);
  float pixelDepth = texture2D(tex,samplePos).b;
  vec3 inColor = vec3(0.5, 0.2, texture2D(tex, samplePos).r);
  vec3 outColor = ycrcvToRgb(inColor);
  colorVarying = vec4(outColor.r, outColor.g, outColor.b ,1.0);

  vec4 vPos = gl_Vertex;
  vPos = vPos + vec4(instanceX*25.0*300.0,instanceY*25.0*62.0, 0.0,0.0);
  gl_Position = gl_ModelViewProjectionMatrix * vPos  ;
}
