#include "Resource.h"
#include "kwToolScene.h"
#include "kwApplication.h"
#include "kwImage.h"
#include "kwResources.h"
#include "kwTile.h"
#include "kwObject.h"
#include "kwInput.h"
#include "kwTilePalette.h"
#include "Resource.h"

extern kw::Application application;

namespace kw
{

    ToolScene::ToolScene()
    {
    }

    ToolScene::~ToolScene()
    {
    }

    void ToolScene::Initialize()
    {
        Scene::Initialize();
        TilePalette::Initiailize();
    }

    void ToolScene::Update()
    {
        Scene::Update();

        Vector2  temp = Input::GetMousePos();


        if (Input::GetKey(eKeyCode::LBUTTON))
        {
            Vector2 pos = Input::GetMousePos();
            pos = TilePalette::GetTilePos(pos);

            UINT tileIndex = TilePalette::GetIndex();
            TilePalette::CreateTile(tileIndex, pos);
        }
    }

    void ToolScene::Render(HDC hdc)
    {
        HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        int maxRow = application.GetHeight() / TILE_SIZE_Y + 1;
        int maxColumn = application.GetWidth() / TILE_SIZE_X + 1;

        for (size_t y = 0; y < maxRow; y++)
        {
            MoveToEx(hdc, 0, TILE_SIZE_Y * y, NULL);
            LineTo(hdc, application.GetWidth(), TILE_SIZE_Y * y);
        }        

        for (size_t x = 0; x < maxColumn; x++)
        {
            MoveToEx(hdc, TILE_SIZE_X * x, 0, NULL);
            LineTo(hdc, TILE_SIZE_X * x, application.GetHeight());
        }

        (HPEN)SelectObject(hdc, oldPen);
        DeleteObject(redPen);

        Scene::Render(hdc);
    }

    void ToolScene::Release()
    {
        Scene::Release();
    }

    void ToolScene::OnEnter()
    {
    }

    void ToolScene::OnExit()
    {
    }
}

LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        //512 384
        //HMENU mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
        //SetMenu(hWnd, mMenubar);
        kw::Image* tile = kw::Resources::Load<kw::Image>(L"TileAtlas", L"..\\Resources\\Tile.bmp");
        RECT rect = { 0, 0, tile->GetWidth(), tile->GetHeight() };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        // 윈도우 크기 변경및 출력 설정
        SetWindowPos(hWnd
            , nullptr, 1600, 0
            , rect.right - rect.left
            , rect.bottom - rect.top
            , 0);
        ShowWindow(hWnd, true);
    }
    case WM_LBUTTONDOWN:
    {

        if (GetFocus())
        {
            ::POINT mousePos = {};
            ::GetCursorPos(&mousePos);
            ::ScreenToClient(application.GetToolHwnd(), &mousePos);

            int x = mousePos.x / TILE_SIZE_X;
            int y = mousePos.y / TILE_SIZE_Y;

            int index = (y * 8) + (x % 8);

            kw::TilePalette::SetIndex(index);
        }
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
            //case IDM_ABOUT:
            //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //    break;
            //case IDM_EXIT:
            //    DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        kw::Image* tile = kw::Resources::Find<kw::Image>(L"TileAtlas");
        BitBlt(hdc, 0, 0, tile->GetWidth(), tile->GetHeight(), tile->GetHdc(), 0, 0, SRCCOPY);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}