matrix			matWorld;
matrix			matView;
matrix			matProj;

bool			bColl;

texture			BaseTexture;

sampler BaseTex = sampler_state
{
	Texture = (BaseTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_IN
{
	vector vPosition : POSITION;
	vector vNormal : NORMAL;
	float2 vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	vector	vPosition : POSITION;
	vector  vColor : COLOR0;
	float2  vTexUV : TEXCOORD0;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	matrix		matWV = mul(matWorld, matView);
	matrix		matWVP = mul(matWV, matProj);
	Out.vPosition = mul(In.vPosition, matWVP);

	Out.vTexUV = In.vTexUV;

	return Out;
}

// PixelShader
struct PS_IN
{
	vector	vColor : COLOR0;
	float2	vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector	vColor : COLOR0;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT	Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseTex, In.vTexUV);

	// 	if(bColl)
	// 	{
	// 		Out.vColor = vector(1.f, 0.f, 0.f, 1.f);
	// 	}
	// 	else
	// 	{
	// 		Out.vColor = vector(0.f, 0.f, 1.f, 1.f);
	// 	}

	return Out;
}

technique ObjectShader
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
}
