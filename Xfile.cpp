#include "Xfile.h"

Xfile::~Xfile(){
	if( pTextureMappingShader != NULL )
		pTextureMappingShader->Release();
	if( pTexDM != NULL )
		pTexDM->Release();
	if( pTexSM != NULL )
		pTexSM->Release();
	if( pSphere != NULL )
		pSphere->Release();
}
LPDIRECT3DTEXTURE9 Xfile::LoadTexture(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if ( FAILED(D3DXCreateTextureFromFile(g_pd3dDevice , filename, &ret)) )
	{
		OutputDebugString("텍스처 로딩 실패: ");
		OutputDebugString(filename);
		OutputDebugString("\n");
	}
	return ret;
}

LPD3DXEFFECT Xfile::LoadShader(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename )
{
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;


#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif


	D3DXCreateEffectFromFile(g_pd3dDevice, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);


	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
	if(!ret && pError)
	{
		int size  = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();


		if(ack)
		{
			char* str = new char[size];
			//            sprintf(str, (const char*)ack, size);
			OutputDebugString(str);
			delete [] str;
		}
	}


	return ret;
}
/*
g_pd3dDevice: D3D 장치
filename: 읽어올 쉐이더 파일의 이름
NULL: 쉐이더를 컴파일 할 때 추가로 사용할 #define 정의
NULL: #include 지시문을 처리할 때 사용할 인터페이스 포인터
dwShaderFlags: 쉐이더를 컴파일 할 때 사용할 플래그
NULL: 매개변수 공유에 사용할 이펙트 풀
ret: 로딩된 이펙트를 저장할 포인터
pError: 컴파일러 에러 메시지를 가리킬 포인터
*/
LPD3DXMESH Xfile::LoadModel(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename)
{
	LPD3DXMESH ret = NULL;
	if ( FAILED(D3DXLoadMeshFromX(filename,D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL,NULL,NULL,NULL, &ret)) )
	{
		OutputDebugString("모델 로딩 실패 : ");
		OutputDebugString(filename);
		OutputDebugString("\n");
	};
	return ret;
}

VOID Xfile::SetTexture(LPD3DXEFFECT xfile, D3DXHANDLE parameter,LPDIRECT3DTEXTURE9 texture)
{
	xfile->SetTexture(parameter,texture);
}

VOID Xfile::SetMatrix(LPD3DXEFFECT xfile,D3DXHANDLE parameter,D3DXMATRIX *matrix)
{
	xfile->SetMatrix(parameter,matrix);
}
/*
filename: 로딩해 올 메쉬의 파일명
D3DXMESH_SYSTEMMEM: 시스템 메모리에 메쉬를 로딩할 것
gpD3DDevice: D3D 장치
NULL: 인접 삼각형 데이터를 따로 구해오지 않음.
NULL: 머테리얼(material) 정보를 따로 구해오지 않음
NULL: 이펙트 인스턴스를 따로 구해오지 않음
NULL: 머테리얼 수를 따로 구해오지 않음
ret: 로딩해온 메쉬를 저장할 포인터 
*/
HRESULT Xfile::InitballMesh(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * texD,const char * texS,const char * shader,const char * model)
{
	// 텍스처 로딩
	pTexDM = Xfile::LoadTexture(g_pd3dDevice,texD);
	if (!pTexDM)
	{
		return E_FAIL;
	}

	pTexSM = Xfile::LoadTexture(g_pd3dDevice,texS);
	if (!pTexSM)	
	{
		return E_FAIL;
	}

	// 쉐이더 로딩
	pTextureMappingShader = Xfile::LoadShader(g_pd3dDevice,shader);
	if (!pTextureMappingShader)
	{
		return E_FAIL;
	}

	// 모델 로딩
	pSphere = Xfile::LoadModel(g_pd3dDevice,model);
	if (!pSphere)
	{
		return E_FAIL;
	}
	return S_OK;

}


VOID Xfile::SetViewprojtexture(D3DXMATRIX projection,D3DXVECTOR4 light)
{
	
	Xfile::SetMatrix(pTextureMappingShader,"gProjectionMatrix",  &projection);
	Xfile::pTextureMappingShader->SetVector("gLightColor", &light);
	Xfile::pTextureMappingShader->SetTexture("DiffuseMap_Tex", pTexDM);
	Xfile::pTextureMappingShader->SetTexture("SpecularMap_Tex", pTexSM);
}
VOID Xfile::SetView(D3DXMATRIX view)
{
	Xfile::SetMatrix(pTextureMappingShader,"gViewMatrix",  &view);
}

VOID Xfile::DrawMyballShader(D3DXMATRIX world)
{
	Xfile::SetMatrix(pTextureMappingShader,"gWorldMatrix",&world);
	UINT numPasses = 0;
	Xfile::pTextureMappingShader->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i )
	{
		Xfile::pTextureMappingShader->BeginPass(i);
		{
			Xfile::pSphere->DrawSubset(0);
		}
		Xfile::pTextureMappingShader->EndPass();
	}

	Xfile::pTextureMappingShader->End();
}
