#include "stdafx.h"
#include "Image.h"


Image::Image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE)
{
}


Image::~Image()
{
}

HRESULT Image::init(int width, int height)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// hdc와 호환되는 HDC를 생성하여 hMemDC 초기화
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;

	// 투명키 컬러 셋팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	// 리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->redID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// hdc와 호환되는 HDC를 생성하여 hMemDC 초기화
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->redID));
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;

	// 투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{// 재초기화 방지용, 이미지 정보에 값이 들어있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// hdc와 호환되는 HDC를 생성하여 hMemDC 초기화
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	// 투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::release(void)
{
	// 이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo != NULL)
	{
		// 이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOldBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		// 포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		// 투명 컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

void Image::render(HDC hdc)
{
}

void Image::render(HDC hdc, int destX, int destY)
{
}
