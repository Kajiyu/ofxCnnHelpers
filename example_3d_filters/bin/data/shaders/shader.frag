#version 120

#extension GL_EXT_gpu_shader4 : require

varying vec4 colorVarying;

void main(){
	gl_FragColor = colorVarying;
}
