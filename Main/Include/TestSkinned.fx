static const int MAX_MATRICES = 100;

float4x3 matWorldMatrixArray[MAX_MATRICES]:WORLDMATRIXARRAY;
float4x4 matViewProj : VIEWPROJECTION;

bool	 bColl;

//Light's Direction
vector   vLightDir;

//Light's Attribute
vector	vDiffuseLight;
vector  vAmientLight;

//Object's Mtrl 
vector	vDiffuseMtrl;
vector  vAmbientMtr;

texture  vTmpTexture;

sampler Samp = sampler_state
{
	Texture = (vTmpTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_IN
{
	vector      vPosition: POSITION;
	float4		vBlendWeights    : BLENDWEIGHT;
	float4		vBlendIndices    : BLENDINDICES;
	vector		vNormal : NORMAL;
	float2      vTex : TEXCOORD0;
};


struct VS_OUT
{
	vector   vPosition : POSITION;
	float2   vTex : TEXCOORD0;
	vector   vColor : COLOR0;
	vector   vPos : COLOR1;
};

struct PS_IN
{
	vector vColor : COLOR0;
	vector vPos : COLOR1;
	float2 vTex : TEXCOORD0;
};

struct PS_OUT
{
	vector   vColor  : COLOR0;
};


VS_OUT VS_DEFAULT_MAIN(VS_IN In,uniform int nNumBone)
{
	VS_OUT   Out = (VS_OUT)0;
	float3 vPos = 0.0f;
	float3 vNormal = 0.0f;
	float3 vLastWeight = 0.0f;

	// Compensate for lack of UBYTE4 on Geforce3
	int4 IndexVector = D3DCOLORtoUBYTE4(i.BlendIndices);

	// cast the vectors to arrays for use in the for loop below
	float BlendWeightsArray[4] = (float[4])In.vBlendWeights;
	int   IndexArray[4] = (int[4])IndexVector;

	// calculate the pos/normal using the "normal" weights 
	//        and accumulate the weights to calculate the last weight
	for (int iBone = 0; iBone < NumBones - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(i.Pos, mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		Normal += mul(i.Normal, mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;

	// Now that we have the calculated weight, add in the final influence
	Pos += (mul(i.Pos, mWorldMatrixArray[IndexArray[NumBones - 1]]) * LastWeight);
	Normal += (mul(i.Normal, mWorldMatrixArray[IndexArray[NumBones - 1]]) * LastWeight);

	// transform position from world space into view and then projection space
	o.Pos = mul(float4(Pos.xyz, 1.0f), matViewProj);

	// normalize normals
	Normal = normalize(Normal);

	// Shade (Ambient + etc.)
	o.Diffuse.xyz = MaterialAmbient.xyz + Diffuse(Normal) * MaterialDiffuse.xyz;
	o.Diffuse.w = 1.0f;

	// copy the input texture coordinate through
	o.Tex0 = i.Tex0.xy;

	return Out;
}

PS_OUT PS_DEFAULT_MAIN(PS_IN In)
{
	PS_OUT	Out = (PS_OUT)0;

	//	Out.vColor = tex2D(BaseTex, In.vTexUV);

	Out.vColor = tex2D(Samp, In.vTex) * In.vColor;

	return Out;
}

technique MyShader
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_DEFAULT_MAIN();
		PixelShader = compile ps_3_0 PS_DEFAULT_MAIN();
	}
}