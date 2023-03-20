#include "kwToolScene.h"
#include "kwApplication.h"
#include "kwImage.h"
#include "kwResources.h"
#include "kwTile.h"
#include "kwObject.h"
#include "kwInput.h"

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

        kw::Image* tile = kw::Resources::Find<kw::Image>(L"TileAtlas");
        Tile* test = object::Instantiate<Tile>(eLayerType::Tile);
        test->InitializeTile(tile, 0);
    }

    void ToolScene::Update()
    {
        Scene::Update();
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
        //case WM_KEYDOWN:
        //{

        //}

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


        //Ellipse(hdc, 500, 500, 600, 700);
        //RoundRect(hdc, 200, 200, 300, 300, 500, 500);

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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