#include "Xfile.h"

Xfile::~Xfile(){
	if( gpTextureMappingShader != NULL )
		gpTextureMappingShader->Release();
	if( texDM != NULL )
		texDM->Release();
	if( texSM != NULL )
		texSM->Release();
	if( gpSphere != NULL )
		gpSphere->Release();
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
	if ( FAILED(D3DXLoadMeshFromX(filename,D3DXMESH_SYSTEMMEM, g_pd3dDevice,
		NULL,NULL,NULL,NULL, &ret)) )
	{
		OutputDebugString("�� �ε� ����: ");
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
	texDM = Xfile::LoadTexture(g_pd3dDevice,texD);
	if (!texDM)
	{
		return E_FAIL;
	}

	texSM = Xfile::LoadTexture(g_pd3dDevice,texS);
	if (!texSM)	
	{
		return E_FAIL;
	}

	// ���̴� �ε�
	gpTextureMappingShader = Xfile::LoadShader(g_pd3dDevice,shader);
	if (!gpTextureMappingShader)
	{
		return E_FAIL;
	}

	// �� �ε�
	gpSphere = Xfile::LoadModel(g_pd3dDevice,model);
	if (!gpSphere)
	{
		return E_FAIL;
	}
	return S_OK;

}


VOID Xfile::set_viewprojtexture(D3DXMATRIX projection,D3DXVECTOR4 light)
{
	
	Xfile::SetMatrix(gpTextureMappingShader,"gProjectionMatrix",  &projection);
	Xfile::gpTextureMappingShader->SetVector("gLightColor", &light);
	Xfile::gpTextureMappingShader->SetTexture("DiffuseMap_Tex", texDM);
	Xfile::gpTextureMappingShader->SetTexture("SpecularMap_Tex", texSM);
}
VOID Xfile::set_view(D3DXMATRIX view)
{
	Xfile::SetMatrix(gpTextureMappingShader,"gViewMatrix",  &view);
}

VOID Xfile::DrawMyballShader(D3DXMATRIX world)
{
	Xfile::SetMatrix(gpTextureMappingShader,"gWorldMatrix",&world);
	UINT numPasses = 0;
	Xfile::gpTextureMappingShader->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i )
		{
			Xfile::gpTextureMappingShader->BeginPass(i);
			{
				Xfile::gpSphere->DrawSubset(0);
			}
			Xfile::gpTextureMappingShader->EndPass();
		}
	}
	Xfile::gpTextureMappingShader->End();
}
