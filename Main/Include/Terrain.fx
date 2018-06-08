matrix      matWorld;
matrix      matView;
matrix      matProj;


vector      vLightDir;

//�������� ����
vector      vDiffuseMtrl;
vector      vAmbientMtrl;

//���� ���� ����
vector      vDiffuseLight;
vector      vAmbientLight;

//�÷��̾� ��ġ
vector      vTargetPos;
float		fRange;
float		fPower;
float		fAngle;



texture     TerrainTexture;
texture     AlphaTexture;
texture     GlassTexture;
texture     TargetTexture;



//���ؽ� �ϳ��� ����
struct VS_IN
{
	//���û��� ���ؽ� ��ġ
	vector  vPosition : POSITION;
	vector  vNormal : NORMAL;
	float2  vTex :  TEXCOORD0;
};

struct VS_OUT
{
	vector   vPosition : POSITION;
	vector   vColor : COLOR0;
	vector   vVtxPos : COLOR1;
	float2   vTex : TEXCOORD0;
};

struct PS_IN
{
	vector  vColor : COLOR0;
	vector   vVtxPos : COLOR1;
	float2  vTex : TEXCOORD0;
};

struct PS_OUT
{
	vector   vColor : COLOR0;
};

sampler OriTex = sampler_state
{
	Texture = (TerrainTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};



sampler AlphaTex = sampler_state
{
	Texture = (AlphaTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};


sampler GlassTex = sampler_state
{
	Texture = (GlassTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler TargetTex = sampler_state
{
	Texture = (TargetTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};




VS_OUT VS_DIFFUSE_MAIN(VS_IN In)
{
	VS_OUT   Out = (VS_OUT)0;

	matrix   matWV = mul(matWorld, matView);
	matrix   matWVP = mul(matWV, matProj);

	Out.vPosition = mul(In.vPosition, matWVP);

	vector vWorldPos = mul(In.vPosition, matWorld);

	vector vInverseLightDir = vLightDir * -1.f;

	float fDot = dot(In.vNormal, vInverseLightDir);

	Out.vColor = vDiffuseMtrl * vDiffuseLight * fDot;

	Out.vVtxPos = vWorldPos;

	Out.vTex = In.vTex;

	return Out;
}

PS_OUT PS_DIFFUSE_MAIN(PS_IN In)
{
	PS_OUT   Out = (PS_OUT)0;

	float2  vNewTex = In.vVtxPos.xz / 1.f;


		vector vTexColor = tex2D(OriTex, vNewTex) * In.vColor;
	vector vAlphaColor = (vector)0;

	vector vGlassColor = tex2D(GlassTex, vNewTex) * In.vColor;
	vector vTargetColor = tex2D(TargetTex, In.vTex);

	vTexColor = vTexColor *(1.f - vTargetColor) + vGlassColor *vTargetColor;

	if (vTargetPos.x - fRange < In.vVtxPos.x && In.vVtxPos.x <= vTargetPos.x + fRange
		&& vTargetPos.z - fRange < In.vVtxPos.z && In.vVtxPos.z <= vTargetPos.z + fRange)
	{
		vector  vAlphaUV = (vector)0;

		vAlphaUV.x = (In.vVtxPos.x - (vTargetPos.x - fRange)) / (fRange *2.f);
		vAlphaUV.y = ((vTargetPos.z + fRange) - In.vVtxPos.z) / (fRange *2.f);

		vector  vTmp = vAlphaUV;
		vTmp.x -= 0.5f;
		vTmp.y -= 0.5f;

		vAlphaUV.x = cos(fAngle) * vTmp.x - sin(fAngle) * vTmp.y + 0.5f;
		vAlphaUV.y = sin(fAngle) * vTmp.x + cos(fAngle) * vTmp.y + 0.5f;

		vAlphaUV.x = saturate(vAlphaUV.x);
		vAlphaUV.y = saturate(vAlphaUV.y);

		vAlphaColor = tex2D(AlphaTex, vAlphaUV);

	}

	Out.vColor = vTexColor + (vAlphaColor * fPower);

	return Out;
}

technique MyShader
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_DIFFUSE_MAIN();
		PixelShader = compile ps_3_0 PS_DIFFUSE_MAIN();
	}
};
