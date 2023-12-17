//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: pointLight.cpp
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Demonstrates using a point light with D3DX objects.  You can orbit
//       the scene using the left and right arrow keys.  In addition you can 
//       elevate the camera with the up and down arrow keys.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"

//
// Globals
//

IDirect3DDevice9* Device = 0; 

const int Width  = 1080;
const int Height = 720;
 
ID3DXMesh* Objects[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
D3DXMATRIX  Worlds[14];
D3DMATERIAL9 Mtrls[14];

//
// Framework Functions
//
bool Setup()
{
	//
	// Create objects.
	//

	D3DXCreateSphere(Device, 0.7, 20, 20, &Objects[0], 0); //Head
	D3DXCreateSphere(Device, 0.1, 20, 20, &Objects[1], 0); //Left eye 
	D3DXCreateSphere(Device, 0.1, 20, 20, &Objects[2], 0); //Right eye
	D3DXCreateBox(Device, 1.5, 2, 0.6, &Objects[3], 0); //Body
	D3DXCreateBox(Device, 0.7, 1.3, 0.5, &Objects[4], 0); //neck
	D3DXCreateBox(Device, 0.2, 1.7, 0.4, &Objects[5], 0); //Left hand
	D3DXCreateBox(Device, 0.2, 1.7, 0.4, &Objects[6], 0); //Right hand
	D3DXCreateBox(Device, 0.3, 2.5, 0.2, &Objects[7], 0); //Left leg
	D3DXCreateBox(Device, 0.3, 2.5, 0.2, &Objects[8], 0); //Right leg
	D3DXCreateSphere(Device, 0.3, 25, 25, &Objects[9], 0); //Left shoulder
	D3DXCreateSphere(Device, 0.3, 25, 25, &Objects[10], 0); //Right shoulder
	D3DXCreateBox(Device, 0.3, 0.07, 0.25, &Objects[11], 0); //Mouth
	D3DXCreateBox(Device, 500, 0.01, 15, &Objects[12], 0); //Floor
	D3DXCreateBox(Device, 500, 0.2, 5, &Objects[13], 0); //Sky

	//
	// Build world matrices - position the objects in world space.
	//

	D3DXMatrixTranslation(&Worlds[0], 0.0f, 1.9f, 0.0f);
	D3DXMatrixTranslation(&Worlds[1], -0.22f, 2.2f, -0.6f);
	D3DXMatrixTranslation(&Worlds[2], 0.22f, 2.2f, -0.6f);
	D3DXMatrixTranslation(&Worlds[3], 0.0f, 0.1f, 0.0f);//Body
	D3DXMatrixTranslation(&Worlds[4], 0.0f, 1.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[5], 1.0f, 0.2f, 0.0f);
	D3DXMatrixTranslation(&Worlds[6], -1.0f, 0.2f, 0.0f);
	D3DXMatrixTranslation(&Worlds[7], -0.5f, -1.5f, 0.0f);
	D3DXMatrixTranslation(&Worlds[8], 0.5f, -1.5f, 0.0f);
	D3DXMatrixTranslation(&Worlds[9], -0.95f, 1.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[10], 0.95f, 1.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[11], 0.0f, 1.88f, -0.58f);
	D3DXMatrixTranslation(&Worlds[12], 0.0f, -3.0f, -0.7f);
	D3DXMatrixTranslation(&Worlds[13], 0.0f, 4.0f, 0.0f);


	//
	// Setup the object's materials.
	//

	Mtrls[0] = d3d::YELLOW_MTRL;
	Mtrls[1] = d3d::BLACK_MTRL;
	Mtrls[2] = d3d::BLACK_MTRL;
	Mtrls[3] = d3d::YELLOW_MTRL;
	Mtrls[4] = d3d::BLUE_MTRL;
	Mtrls[5] = d3d::RED_MTRL;
	Mtrls[6] = d3d::RED_MTRL;
	Mtrls[7] = d3d::RED_MTRL;
	Mtrls[8] = d3d::RED_MTRL;
	Mtrls[9] = d3d::BLUE_MTRL;
	Mtrls[10] = d3d::BLUE_MTRL;
	Mtrls[11] = d3d::RED_MTRL;
	Mtrls[12] = d3d::GREEN_MTRL;
	Mtrls[13] = d3d::BLUE_MTRL;

	//
	// Setup a point light.  Note that the point light
	// is positioned at the origin.
	//

	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
	D3DXCOLOR   c = d3d::WHITE;
	D3DLIGHT9 point = d3d::InitPointLight(&pos, &c);

	//
	// Set and Enable the light.
	//

	Device->SetLight(0, &point);
	Device->LightEnable(0, true);

	//
	// Set lighting related render states.
	//

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.25f, // 45 - degree
			(float)Width / (float)Height,
			1.0f,
			1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

void Cleanup()
{
	for(int i = 0; i < 14; i++)
		d3d::Release<ID3DXMesh*>(Objects[i]);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		// 
		// Update the scene: update camera position.
		//

		static float angle  = (3.0f * D3DX_PI) / 2.0f;
		static float height = 5.0f;
	
		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			angle -= 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
			angle += 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
			height += 5.0f * timeDelta;

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
			height -= 5.0f * timeDelta;

		D3DXVECTOR3 position( cosf(angle) * 7.0f, height, sinf(angle) * 7.0f );
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		Device->SetTransform(D3DTS_VIEW, &V);

		//
		// Draw the scene:
		//
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		for(int i = 0; i < 14; i++)
		{
			// set material and world matrix for ith object, then render
			// the ith object.
			Device->SetMaterial(&Mtrls[i]);
			Device->SetTransform(D3DTS_WORLD, &Worlds[i]);
			Objects[i]->DrawSubset(0);
		}

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}


//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, (LPCWSTR)"InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, (LPCWSTR)"Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}