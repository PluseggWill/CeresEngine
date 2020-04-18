#include "Texture.h"

Texture::Texture()
{
	mTexture = NULL;
}

Texture::~Texture()
{
	ReleaseCOM(mTexture);
}

bool Texture::InitTexture(ID3D11Device* device, LPCSTR filename)
{
	D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &mTexture, NULL);
	return true;
}