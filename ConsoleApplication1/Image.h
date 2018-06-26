#pragma once

//=============================================================
//	## Image ## (������ ��� ������Ʈ �ȴ�)
//=============================================================
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	// ���ҽ� �ε�
		LOAD_FILE,			// ���Ϸ� �ε�
		LOAD_EMPTY,			// �� ��Ʈ�� �ε�
		LOAD_END			
	};

	typedef struct TagImage
	{
		DWORD		redID;		// ���ҽ� ID,		unsigned long
		HDC			hMemDC;		// �޸� DC
		HBITMAP		hBit;		// ��Ʈ��
		HBITMAP		hOldBit;	// �õ� ��Ʈ��
		int			width;		// �̹��� ���� ũ��
		int			height;		// �̹��� ���� ũ��
		BYTE		loadType;	// �̹��� �ε� Ÿ��,	unsigned char

		TagImage()
		{
			redID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		// �̹��� ����
	CHAR*			_fileName;		// �̹��� �̸�
	BOOL			_isTrans;		// ���� ����( true�̸� ��� ����� )
	COLORREF		_transColor;	// ���� ���� RGB �ڵ� ( ����Ÿ = RGB(255, 0, 255) )
	
public:
	Image();
	~Image();

	// �� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height);
	// �̹��� ���ҽ��� �ʱ�ȭ( ��� ���� )
	HRESULT init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ ( �ַ� ��� )
	HRESULT init(char * fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// ����
	void release(void);
	
	// ����
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	
	// DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	
};

