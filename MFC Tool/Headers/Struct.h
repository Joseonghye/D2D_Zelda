#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tTextureInfo;
	D3DXVECTOR3 tCenter;
}TEXINFO;

typedef struct tagTile {
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	DWORD dwDrawID;
	DWORD dwOption;
}TILE;

typedef struct tagInfo
{
	DIR eDir;

	D3DXVECTOR3 vPos;
	//D3DXVECTOR3 vDir;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vScale;

	D3DXMATRIX matScale;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matTrans;
	D3DXMATRIX matRevol;
	D3DXMATRIX matWorld;
	tagInfo()
	{
		ZeroMemory(&vPos, sizeof(D3DXVECTOR3));
//		ZeroMemory(&vDir, sizeof(D3DXVECTOR3));
		ZeroMemory(&vSize, sizeof(D3DXVECTOR3));
		ZeroMemory(&vScale, sizeof(D3DXVECTOR3));

		ZeroMemory(&matScale, sizeof(D3DXMATRIX));
		ZeroMemory(&matRotateZ, sizeof(D3DXMATRIX));
		ZeroMemory(&matTrans, sizeof(D3DXMATRIX));
		ZeroMemory(&matRevol, sizeof(D3DXMATRIX));
		ZeroMemory(&matWorld, sizeof(D3DXMATRIX));
	}
}INFO;

#endif