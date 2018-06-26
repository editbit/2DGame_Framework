#pragma once

//=============================================================
//	## Image ## (앞으로 계속 업데이트 된다)
//=============================================================
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	// 리소스 로딩
		LOAD_FILE,			// 파일로 로딩
		LOAD_EMPTY,			// 빈 비트맵 로딩
		LOAD_END			
	};

	typedef struct TagImage
	{
		DWORD		redID;		// 리소스 ID,		unsigned long
		HDC			hMemDC;		// 메모리 DC
		HBITMAP		hBit;		// 비트맵
		HBITMAP		hOBit;	// 올드 비트맵
		int			width;		// 이미지 가로 크기
		int			height;		// 이미지 세로 크기
		BYTE		loadType;	// 이미지 로드 타입,	unsigned char

		TagImage()
		{
			redID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		// 이미지 정보
	CHAR*			_fileName;		// 이미지 이름
	BOOL			_isTrans;		// 배경색 유무( true이면 배경 지우기 )
	COLORREF		_transColor;	// 지울 배경색 RGB 코드 ( 마젠타 = RGB(255, 0, 255) )
	
public:
	Image();
	~Image();

	// 빈 비트맵으로 초기화
	HRESULT init(int width, int height);
	// 이미지 리소스로 초기화( 사용 안함 )
	HRESULT init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화 ( 주로 사용 )
	HRESULT init(const char * fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// 해제
	void release(void);
	
	// 렌더
	void render(HDC hdc, int destX=0, int destY=0);
	
	// DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	
};

