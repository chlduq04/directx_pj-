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
		OutputDebugString("�ؽ�ó �ε� ����: ");
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


	// ���̴� �ε��� ������ ��� outputâ�� ���̴�
	// ������ ������ ����Ѵ�.
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
g_pd3dDevice: D3D ��ġ
filename: �о�� ���̴� ������ �̸�
NULL: ���̴��� ������ �� �� �߰��� ����� #define ����
NULL: #include ���ù��� ó���� �� ����� �������̽� ������
dwShaderFlags: ���̴��� ������ �� �� ����� �÷���
NULL: �Ű����� ������ ����� ����Ʈ Ǯ
ret: �ε��� ����Ʈ�� ������ ������
pError: �����Ϸ� ���� �޽����� ����ų ������
*/
LPD3DXMESH Xfile::LoadModel(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename)
{
	LPD3DXMESH ret = NULL;
	if ( FAILED(D3DXLoadMeshFromX(filename,D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL,NULL,NULL,NULL, &ret)) )
	{
		OutputDebugString("�� �ε� ���� : ");
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
filename: �ε��� �� �޽��� ���ϸ�
D3DXMESH_SYSTEMMEM: �ý��� �޸𸮿� �޽��� �ε��� ��
gpD3DDevice: D3D ��ġ
NULL: ���� �ﰢ�� �����͸� ���� ���ؿ��� ����.
NULL: ���׸���(material) ������ ���� ���ؿ��� ����
NULL: ����Ʈ �ν��Ͻ��� ���� ���ؿ��� ����
NULL: ���׸��� ���� ���� ���ؿ��� ����
ret: �ε��ؿ� �޽��� ������ ������ 
*/
HRESULT Xfile::InitballMesh(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * texD,const char * texS,const char * shader,const char * model)
{
	// �ؽ�ó �ε�
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

	// ���̴� �ε�
	pTextureMappingShader = Xfile::LoadShader(g_pd3dDevice,shader);
	if (!pTextureMappingShader)
	{
		return E_FAIL;
	}

	// �� �ε�
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
