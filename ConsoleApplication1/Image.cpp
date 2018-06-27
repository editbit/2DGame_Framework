#include "stdafx.h"
#include "Image.h"
Image::Image()
	: _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _blendImage(NULL), _transColor(RGB(0, 0, 0))
{
}
Image::~Image()
{
}

HRESULT Image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->redID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->redID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->redID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	
	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::release(void)
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명 컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	// 알파블렌드 이미지 정보가 있다면
	if (_blendImage)
	{
		//이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		// 포인터 삭제
		SAFE_DELETE(_blendImage);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			sourWidth,		//복사될 이미지 가로크기
			sourHeight,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,					//복사 시작지점
			sourWidth,		//복사 영역 가로크기
			sourHeight,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	// 알파블렌드를 처음 사용한다면
	// 알파블렌드를 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,					//복사할 장소의 DC
			0,					//복사될 좌표 시작점 X
			0,					//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

		//3. 블렌드이미지를 화면에 그린다
		// 알파블렌드
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할 때
	{
		// 알파블렌드
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// 알파블렌드를 처음 사용한다면
	// 알파블렌드를 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,					//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

		//3. 블렌드이미지를 화면에 그린다
		// 알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할 때
	{
		// 알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	// 알파블렌드를 처음 사용한다면
	// 알파블렌드를 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,					//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			sourWidth,		//복사될 이미지 가로크기
			sourHeight,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,					//복사 시작지점
			sourWidth,		//복사 영역 가로크기
			sourHeight,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 블렌드이미지를 화면에 그린다
									// 알파블렌드
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할 때
	{
		// 알파블렌드
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}
