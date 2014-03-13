uniform sampler2D frontBuffer;
uniform sampler2D backBuffer;
uniform sampler3D volume;
uniform sampler1D transferFunction;
uniform int width;
uniform int height;
void main (void)
{
	vec2 readTexCoord=vec2(gl_FragCoord.x/float(width),gl_FragCoord.y/float(height));

	vec3  ray_out		= texture2D	(backBuffer,  readTexCoord).xyz;
	vec3  ray_in		= texture2D	(frontBuffer, readTexCoord).xyz;
	vec3  ray_dir		= normalize	(ray_out - ray_in);

    vec4 colorFinal = vec4(0, 0, 0, 0);
    
    vec3 pos = ray_in;
    vec3 st = ray_dir * 0.005; // step
    
    for(int i = 0; i < 500; i++)
    {
	    vec4 src = texture1D(transferFunction,texture3D(volume,vec3(pos)).x);
	    if(src.a>0.0){
			src.a *= 0.05;
			src.rgb *= src.a;
			colorFinal = (1.0 - colorFinal.a)*src + colorFinal;
			
			if(colorFinal.a >= 0.95)
				break;
		}
		
		pos += st;
		
		if(pos.x > 1.0 || pos.y > 1.0 || pos.z > 1.0 || pos.x < 0.0 || pos.y < 0.0 || pos.z < 0.0)
			break;
    }
    
	gl_FragColor  =  colorFinal;//vec4(ray_in,1); ;
}
