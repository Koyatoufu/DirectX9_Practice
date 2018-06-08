matrix   matWorld;
matrix   matView;
matrix   matProj;
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


//버텍스의 하나의 정보
struct VS_IN
{
	//로컬영역상의 버텍스 위치
	vector      vPosition: POSITION;
	vector		vNormal : NORMAL;
	float2      vTex : TEXCOORD0;
};


struct VS_OUT
{
	//버텍스 쉐이딩안에서 연산한 결과 위치를 보내준다.
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


VS_OUT VS_DEFAULT_MAIN(VS_IN In)
{
	VS_OUT   Out = (VS_OUT)0;

	matrix   matWV = mul(matWorld, matView);
	matrix   matWVP = mul(matWV, matProj);

	Out.vPosition = mul(In.vPosition, matWVP);

	vector vInverseLight = vLightDir * -1.f;

	vInverseLight = normalize(vInverseLight);

	float fDot = dot(vInverseLight, In.vNormal);

	Out.vColor = vDiffuseLight * vDiffuseMtrl * fDot;

	Out.vTex = In.vTex;

	Out.vPos = Out.vPosition;

	return Out;
}

PS_OUT PS_DEFAULT_MAIN(PS_IN In)
{
	PS_OUT	Out = (PS_OUT)0;

//	Out.vColor = tex2D(BaseTex, In.vTexUV);

	Out.vColor = tex2D(Samp, In.vTex) * In.vColor;

	return Out;
}

//내가 호출해서 사용해야할 버텍스 , 픽셀셰이더의 함수를 결정해준다.
technique MyShader
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_DEFAULT_MAIN();
		PixelShader = compile ps_3_0 PS_DEFAULT_MAIN();
	}
}