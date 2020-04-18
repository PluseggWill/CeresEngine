#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <d3d11.h>
#include "d3dUtil.h"

class Texture
{
protected:
	ID3D11ShaderResourceView* mTexture;

public:
	Texture();
	~Texture();

public:
	bool InitTexture(ID3D11Device* device, LPCSTR filename);
	ID3D11ShaderResourceView* GetTexture();
};

#endif // !TEXTURE_H
