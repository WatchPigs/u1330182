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

int
#if defined(_M_CEE_PURE)
__clrcall
#else
WINAPI
#endif
wWinMain(_In_ HINSTANCE i_hInstance, _In_opt_ HINSTANCE i_hPrevInstance, _In_ LPWSTR i_lpCmdLine, _In_ int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600, true);

	if (bSuccess)
	{
		Engine::AssetManager::get_instance().AddSprite("GoodGuy", "data\\GoodGuy.dds");
		Engine::AssetManager::get_instance().AddSprite("BadGuy", "data\\BadGuy.dds");

		bool bQuit = false;

		//W = 87, A = 65, S = 83, D = 68, I = 73, J = 74, K = 75, L = 76, Q = 81
		enum KeyCode { W, A, S, D, I, J, K, L, Q };

		bool keyStates[8] = { 0 };

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
			case 73:
				keyStates[I] = bWentDown;
				break;
			case 74:
				keyStates[J] = bWentDown;
				break;
			case 75:
				keyStates[K] = bWentDown;
				break;
			case 76:
				keyStates[L] = bWentDown;
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

				if (Engine::AssetManager::get_instance().FindSprite("GoodGuy"))
				{
					static float			moveDist = .01f;

					static GLib::Point2D	Offset = { -180.0f, -100.0f };

					if (keyStates[W]) Offset.y += moveDist;
					if (keyStates[A]) Offset.x -= moveDist;
					if (keyStates[S]) Offset.y -= moveDist;
					if (keyStates[D]) Offset.x += moveDist;

					GLib::Render(*Engine::AssetManager::get_instance().FindSprite("GoodGuy"), Offset, 0.0f, 0.0f);
				}
				if (Engine::AssetManager::get_instance().FindSprite("BadGuy"))
				{
					static float			moveDist = .01f;

					static GLib::Point2D	Offset = { 180.0f, -100.0f };

					if (keyStates[I]) Offset.y += moveDist;
					if (keyStates[J]) Offset.x -= moveDist;
					if (keyStates[K]) Offset.y -= moveDist;
					if (keyStates[L]) Offset.x += moveDist;

					GLib::Render(*Engine::AssetManager::get_instance().FindSprite("BadGuy"), Offset, 0.0f, 0.0f);
				}

				GLib::Sprites::EndRendering();
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (Engine::AssetManager::get_instance().FindSprite("player")) Engine::AssetManager::get_instance().DeleteSprite("player");
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}