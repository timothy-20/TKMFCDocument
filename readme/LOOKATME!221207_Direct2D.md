# LOOT AT ME!

> **date**: 22.12.07. - 22.12.09. <br>
> **author**: timothy-20 <br>
> **subject**: Direct2D를 이용한 windows app 그래픽에 대하여.<br>
> **project name**: TKMFCApplication221201

[렌더링 대상, 디바이스 리소스](https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/render-targets--devices--and-resources)
---
먼저 창에 원을 그리기 위한 구성 멤버 변수 및 함수입니다. 이는 Direct2D에 정의된 리소스의 몇몇 예입니다. MSDN에서 설명하는 개념과 더불어 해석해보도록 하겠습니다.

```c++
ID2D1HwndRenderTarget* p_renderTarget;

//definition
interface DX_DECLARE_INTERFACE("2cd90698-12e2-11dc-9fed-001143a055f9") ID2D1HwndRenderTarget  : public ID2D1RenderTarget
```
> 렌더링 대상, 단순히 프로그램이 그릴 위치를 나타냅니다. 일반적으로 창을 대상으로 합니다.
> **ID2D1HwndRenderTarget** 클래스는 [**ID2D1RenderTarger**](https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1/nn-d2d1-id2d1rendertarget) 인터페이스의 구현체입니다. 

디바이스는 실제로 픽셀을 그리는 항목을 나타내는 추상적인 개념입니다.
1. 하드웨어 디바이스는 더 빠른 성능을 위해 GPU를 사용합니다.
2. 소프트웨어 디바이스는 CPU(및 내장 그래픽)를 사용합니다.

앱이 렌더링 대상을 만들 때, 디바이스가 암시적으로 만들어집니다. 이때 렌더링 대상은 hw 혹은 sw 디바이스와 연결됩니다.

---

```c++
ID2D1SolidColorBrush* p_brush;
D2D1_ELLIPSE m_ellipse;
```
> 단색 브러시 방식으로 선을 그리는 **ID2D1SolidColorBrush** 클래스와 타원(도형)을 그리는 **D2D1_ELLIPSE** 구조체입니다.

**리소스**는 프로그램에서 그리기에 사용하는 개체입니다.<br>
일부 리소스는 하드웨어 가속의 이점을 누릴 수 있으며, 해당 리소스는 항상 hw, sw 디바이스와 연결되어 **디바이스 종속**적인 형태입니다. 디바이스를 사용할 수 없게 되면,
새 디바이스에 다시 그려져야 합니다.
> - **브러시**: 선과 영역의 그리기 방식을 제어합니다. 단색 브러시와 그라데이션 브러시가 있습니다.<br>
> - **메시**: 삼각형으로 구성된 셰이프입니다(객체의 외관을 구현하기 위한 다각형(polygon)들의 집합). GPU에서 직접 사용 가능합니다.

사용되는 디사이브와 관계없이 CPU 메모리에 저장되는 **디바이스 독립**적인 형태의 리소스도 있습니다. 이들은 디바이스가 재생성되더라도 다시 그려질 필요가 없습니다.

> - **스트로크 스타일**: 선의 모양을 제어합니다.<br>
> - **기하 도형**: 선과 곡선의 집합입니다.

---

```c++
ID2D1Factory* p_factory;

void CalculateLayout();
HRESULT CreateGraphicsResources();
void DiscardGraphicsResources();
void OnPaint();
void ReSize();
```

소스 코드
---
```c++
//TKMainWindow.h
#pragma once
#include "TKBaseWindow.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

template<typename T>
void TKSafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class TKMainWindow : public TKBaseWindow<TKMainWindow>
{
private:
	ID2D1Factory* p_factory;
	ID2D1HwndRenderTarget* p_renderTarget;
	ID2D1SolidColorBrush* p_brush;
	D2D1_ELLIPSE m_ellipse;

	void CalculateLayout();
	HRESULT CreateGraphicsResources();
	void DiscardGraphicsResources();
	void OnPaint();
	void ReSize();

public:
	TKMainWindow() : p_factory(NULL), p_renderTarget(NULL), p_brush(NULL), m_ellipse({}) { }
	PCWSTR ClassName() const { return L"TKMainWindow"; }
	LRESULT HandleMessage(UINT umsg, WPARAM wparam, LPARAM lparam);
};
```

```c++
//TKMainWindow.cpp
#include "TKMainWindow.h"

void TKMainWindow::CalculateLayout()
{
if (this->p_renderTarget != nullptr)
{
D2D1_SIZE_F size = this->p_renderTarget->GetSize();
const float x = size.width / 2;
const float y = size.height / 2;
const float radius = min(x, y);
this->m_ellipse = D2D1::Ellipse(D2D1::Point2(x, y), radius, radius);
}
}

HRESULT TKMainWindow::CreateGraphicsResources()
{
HRESULT handleResult = S_OK;

if (this->p_renderTarget == NULL)
{
RECT rect = {};

::GetClientRect(this->m_hwnd, &rect);

D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);
handleResult = this->p_factory->CreateHwndRenderTarget(
D2D1::RenderTargetProperties(),
D2D1::HwndRenderTargetProperties(this->m_hwnd, size),
&p_renderTarget
);

if (SUCCEEDED(handleResult))
{
const D2D1_COLOR_F color = D2D1::ColorF(1.0F, 1.0F, 0.0F);
handleResult = this->p_renderTarget->CreateSolidColorBrush(color, &this->p_brush);

if (SUCCEEDED(handleResult))
this->CalculateLayout();
}
}

return handleResult;
}

void TKMainWindow::DiscardGraphicsResources()
{
::TKSafeRelease(&this->p_renderTarget);
::TKSafeRelease(&this->p_brush);
}

void TKMainWindow::OnPaint()
{
HRESULT handleResult = CreateGraphicsResources();

if (SUCCEEDED(handleResult))
{
PAINTSTRUCT paint;

::BeginPaint(this->m_hwnd, &paint);

this->p_renderTarget->BeginDraw();
this->p_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
this->p_renderTarget->FillEllipse(this->m_ellipse, this->p_brush);
handleResult = this->p_renderTarget->EndDraw();

if (FAILED(handleResult) || handleResult == D2DERR_RECREATE_TARGET)
this->DiscardGraphicsResources();

::EndPaint(this->m_hwnd, &paint);
}
}

void TKMainWindow::ReSize()
{
if (this->p_renderTarget != nullptr)
{
RECT rect;

::GetClientRect(this->m_hwnd, &rect);

D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);

this->p_renderTarget->Resize(size);
this->CalculateLayout();
::InvalidateRect(this->m_hwnd, &rect, FALSE);
}
}

LRESULT TKMainWindow::HandleMessage(UINT umsg, WPARAM wparam, LPARAM lparam)
{
switch (umsg)
{
case WM_CREATE:
if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->p_factory)))
return -1;

return 0;

case WM_PAINT:
{
/*PAINTSTRUCT ps;
HDC hdc = BeginPaint(this->m_hwnd, &ps);
FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
EndPaint(this->m_hwnd, &ps);*/

this->OnPaint();
}
return 0;

case WM_SIZE:
this->ReSize();
return 0;

case WM_CLOSE:
if (MessageBox(this->m_hwnd, L"Do you want quit?", L"Notice", MB_OKCANCEL) == IDOK)
::DestroyWindow(this->m_hwnd);

return 0;

case WM_DESTROY:
this->DiscardGraphicsResources();
::TKSafeRelease(&this->p_factory);
::PostQuitMessage(0);
return 0;
}

return ::DefWindowProc(this->m_hwnd, umsg, wparam, lparam);
}
```