#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include <DirectXColors.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"
#include "AssetManager.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600, true);

	if (bSuccess)
	{
		AssetManager::get_instance().AddSprite("player", "data\\GoodGuy.dds");

		bool bQuit = false;

		//enum KeyCode { W = 87, A = 65, S = 83, D = 68, Q = 81 };
		enum KeyCode { W, A, S, D, Q };

		bool keyStates[4] = { 0 };

		GLib::SetKeyStateChangeCallback([&keyStates, &bQuit](unsigned int i_VKeyID, bool bWentDown) -> void {
#ifdef _DEBUG
			const size_t	lenBuffer = 65;
			char			Buffer[lenBuffer];

			sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
			OutputDebugStringA(Buffer);
#endif // __DEBUG
			switch (i_VKeyID)
			{
			case 87:
				keyStates[W] = bWentDown;
				break;
			case 65:
				keyStates[A] = bWentDown;
				break;
			case 83:
				keyStates[S] = bWentDown;
				break;
			case 68:
				keyStates[D] = bWentDown;
				break;
			case 81:
				bQuit = bWentDown;
			}
			});

		do
		{
			GLib::Service(bQuit);
			if (!bQuit)
			{
				GLib::BeginRendering(DirectX::Colors::Blue);
				GLib::Sprites::BeginRendering();

				if (AssetManager::get_instance().FindSprite("player"))
				{
					static float			moveDist = .01f;

					static GLib::Point2D	Offset = { -180.0f, -100.0f };

					if (keyStates[W]) Offset.y -= moveDist;
					if (keyStates[A]) Offset.x -= moveDist;
					if (keyStates[S]) Offset.y += moveDist;
					if (keyStates[D]) Offset.x += moveDist;

					GLib::Render(*AssetManager::get_instance().FindSprite("player"), Offset, 0.0f, 0.0f);
				}
				GLib::Sprites::EndRendering();
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (AssetManager::get_instance().FindSprite("player")) AssetManager::get_instance().DeleteSprite("player");
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}