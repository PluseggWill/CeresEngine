
// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 posH			: SV_POSITION;	// XYZW position (System Value Position)
	float4 color		: COLOR;        // RGBA color
	float3 posW			: POSITION;
	float3 normal		: NORMAL;
	float2 texU			: TEXCOORD0;
};

struct DirLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 direction;
	float pad;
};

struct Material
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 reflect;
};

cbuffer Light : register(b0)
{
	DirLight gDirLight;
	float3 gEyePosW;
	Material gMat;
};

void ComputeDirLight(Material mat, DirLight L, float3 normal, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = -L.direction;
	ambient = mat.ambient * L.ambient;

	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.specular.w);

		diffuse = diffuseFactor * mat.diffuse * L.diffuse;
		spec = specFactor * mat.specular * L.specular;
	}
}

Texture2D testTexture;
SamplerState samplerState;

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal);

	float3 toEyeW = normalize(gEyePosW - input.posW);

	// Start with a sum of zero. 
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Sum the light contribution from each light source.
	float4 A, D, S;

	ComputeDirLight(gMat, gDirLight, input.normal, toEyeW, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	float4 litColor = ambient + diffuse + spec;

	// Common to take alpha from diffuse material.
	litColor.a = gMat.diffuse.a;

	//return litColor;
	return testTexture.Sample(samplerState, input.texU);
	//return input.color;
}