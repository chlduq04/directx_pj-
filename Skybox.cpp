#include "SkyBox.h"   
   
CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 pd3dDevice)   
{   
    m_pd3dDevice = pd3dDevice;   
    m_pVB        = NULL;   
}   
   
CSkyBox::~CSkyBox()   
{   
    REL(m_pVB);   
    for(int i = 0; i < 7; i++)   
    {   
        REL(m_pTexture[i]);   
    }   
}   
   
HRESULT CSkyBox::InitVB()   
{   
    VERTEX  g_Vertices[] =    
    {   //Front   
        {-1.0f, 1.0f,-1.0f,  0.0f, 0.0f, 0.0f,0.0f},   
        { 1.0f, 1.0f,-1.0f,  1.0f, 0.0f, 1.0f,0.0f},   
        {-1.0f,-1.0f,-1.0f,  0.0f, 1.0f, 0.0f,1.0f},   
        { 1.0f,-1.0f,-1.0f,  1.0f, 1.0f, 1.0f,1.0f},   
   
        //Back   
        {-1.0f, 1.0f, 1.0f,  1.0f,0.0f,  1.0f,0.0f },   
        {-1.0f,-1.0f, 1.0f,  1.0f,1.0f,  1.0f,1.0f },   
        { 1.0f, 1.0f, 1.0f,  0.0f,0.0f,  0.0f,0.0f },   
        { 1.0f,-1.0f, 1.0f,  0.0f,1.0f,  0.0f,1.0f },   
   
        //Up   
        {-1.0f, 1.0f, 1.0f,  0.0f,0.0f,  0.0f,0.0f },   
        { 1.0f, 1.0f, 1.0f,  1.0f,0.0f,  1.0f,0.0f },   
        {-1.0f, 1.0f,-1.0f,  0.0f,1.0f,  0.0f,1.0f },   
        { 1.0f, 1.0f,-1.0f,  1.0f,1.0f,  1.0f,1.0f },   
   
        //Down   
        {-1.0f,-1.0f, 1.0f,  0.0f,1.0f,  0.0f,1.0f },   
        {-1.0f,-1.0f,-1.0f,  0.0f,0.0f,  0.0f,0.0f },   
        { 1.0f,-1.0f, 1.0f,  1.0f,1.0f,  1.0f,1.0f },   
        { 1.0f,-1.0f,-1.0f,  1.0f,0.0f,  1.0f,0.0f },   
   
        //Right   
        { 1.0f, 1.0f,-1.0f,  0.0f,0.0f,  0.0f,0.0f },   
        { 1.0f, 1.0f, 1.0f,  1.0f,0.0f,  1.0f,0.0f },   
        { 1.0f,-1.0f,-1.0f,  0.0f,1.0f,  0.0f,1.0f },   
        { 1.0f,-1.0f, 1.0f,  1.0f,1.0f,  1.0f,1.0f },   
   
        //Left   
        {-1.0f, 1.0f,-1.0f,  1.0f,0.0f,  1.0f,0.0f },   
        {-1.0f,-1.0f,-1.0f,  1.0f,1.0f,  1.0f,1.0f },   
        {-1.0f, 1.0f, 1.0f,  0.0f,0.0f,  0.0f,0.0f },   
        {-1.0f,-1.0f, 1.0f,  0.0f,1.0f,  0.0f,1.0f }   
   
    };   
   
    if (FAILED(m_pd3dDevice->CreateVertexBuffer(   
                                        24 * sizeof(VERTEX),   
                                        0,   
                                        VERTEXFVF,   
                                        D3DPOOL_DEFAULT,   
                                        &m_pVB,   
                                        NULL)))   
    {   
        return E_FAIL;   
    }   
   
    void * pVertices = NULL;   
   
    if (FAILED(m_pVB->Lock( 0, sizeof(g_Vertices), (void**)&pVertices, 0)))   
    {   
        return E_FAIL;   
    }   
   
    memcpy( pVertices, g_Vertices, sizeof(g_Vertices) );   
    m_pVB->Unlock();   
   
    return S_OK;   
}   
HRESULT CSkyBox::InitTexture(){
	if(!SUCCEEDED(SetTexture("SkyBox_Front.jpg",0))){
		return E_FAIL;
	}
	if(!SUCCEEDED(SetTexture("SkyBox_Back.jpg",1))){
		return E_FAIL;
	}
	if(!SUCCEEDED(SetTexture("SkyBox_Top.jpg",2))){
		return E_FAIL;
	}
	if(!SUCCEEDED(SetTexture("SkyBox_Bottom.jpg",3))){
		return E_FAIL;
	}
	if(!SUCCEEDED(SetTexture("SkyBox_Right.jpg",4))){
		return E_FAIL;
	}
	if(!SUCCEEDED(SetTexture("SkyBox_Left.jpg",5))){
		return E_FAIL;
	}
	if(!SUCCEEDED(SetTexture("SkyBox_Right.jpg",6))){
		return E_FAIL;
	}   
	return S_OK;
}   
HRESULT CSkyBox::SetTexture(const char *TextureFile, int ps)   
{   
    if (FAILED(D3DXCreateTextureFromFile( m_pd3dDevice,   
                                            TextureFile,   
                                            &m_pTexture[ps])))   
    {   
        return E_FAIL;   
    }   
       
    return S_OK;   
}   
   
void CSkyBox::Render()   
{   
    D3DXMATRIX  matWorld;   
	D3DXMATRIX	matTrans;
    D3DXMatrixScaling(&matWorld, 180.0f, 180.0f, 180.0f);   
	D3DXMatrixTranslation(&matTrans,MAXBOUNDX/2,0.0f,MAXBOUNDZ/2);
	matWorld *= matTrans;
    m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);     
//    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);   
//    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);   
    m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX));   
    m_pd3dDevice->SetFVF(VERTEXFVF);   
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);   
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);   
       
//    m_pd3dDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);   
//    m_pd3dDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);   
   
    for(int i = 0; i < 6; i++)   
    {   
        m_pd3dDevice->SetTexture(0, m_pTexture[i]);   
        m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, i*4, 2);   
    }   
   
}  