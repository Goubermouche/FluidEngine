#  
                   GLSL.std.450                     main    
                   res/Shaders/Normal/BasicDiffuseShader.glsl   6    ?     #version 460 core

layout(location = 0) out vec4 o_Color;

struct VertexOutput
{
	vec4 Color;
};

layout(location = 0) in VertexOutput Input;

void main()
{
	o_Color = Input.Color;
}     
 GL_GOOGLE_cpp_style_line_directive    GL_GOOGLE_include_directive      main      
   o_Color      VertexOutput             Color        Input   J entry-point main    J client vulkan100    J target-env spirv1.5 J target-env vulkan1.2    J entry-point main    G  
          G                 !                               	         ;  	   
                          ;                       +                                   6               ?                 A              =           >  
      ?  8  