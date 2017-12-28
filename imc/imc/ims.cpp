// imc.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ims.h"
using namespace Gdiplus;
using namespace std;

#define WIDTH 1024
#define HEIGHT 2048
// ����GDI+��
void GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num, size;
	Gdiplus::GetImageEncodersSize(&num, &size);
	Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT i = 0; i < num; ++i)
	{
		if (_wcsicmp(pImageCodecInfo[i].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[i].Clsid;
			break;
		}
	}
	free(pImageCodecInfo);
}

// ����ͼƬ�ߴ�
void GetImageSize(CString &folder, LPCWSTR file, imageinfo &info)
{
	Bitmap bmp(folder + file);
	if (bmp.GetLastStatus() == Ok)
	{
		info.file = file;
		info.width = bmp.GetWidth();
		info.height = bmp.GetHeight();
	}
}
// �����ļ�
void SearchFiles(const CString &szPathx, std::multimap<int, imageinfo> &datas)
{
	CString         path = szPathx + L"\\*.*";
	WIN32_FIND_DATA data;
	HANDLE			hFind = FindFirstFile(path, &data);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	// ���������ļ�
	WCHAR	*pt;
	imageinfo info;
	while (FindNextFile(hFind, &data))
	{
		// �������е�Ŀ¼
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			continue;
		}
		// ���� convert_out.png
		if (wcscmp(data.cFileName, L"convert_out.png") == 0)
		{
			continue;
		}
		// ���Һ�׺
		pt = wcsrchr(data.cFileName, L'.');
		if (pt != NULL)
		{
			// ����׺ת����Сд
			_wcslwr(pt);
			if (wcscmp(pt, L".jpg") != 0 &&
				wcscmp(pt, L".png") != 0)
			{
				continue;
			}
		}
		// �ļ���Ϣ����
		GetImageSize(szPathx + L"\\", data.cFileName, info);
		datas.insert(std::pair<int, imageinfo>(9999 - info.height, info));
	}
	// �ر�
	FindClose(hFind);
}
// �ж����������Ƿ��н���
BOOL IntersectRects(std::vector<imagelayoutinfo> &used, RECT &rc)
{
	RECT t;
	for (int i = 0; i < used.size(); i++)
	{
		if (::IntersectRect(&t, &rc, &used[i].rect))
		{
			return TRUE;
		}
	}
	return FALSE;
}
// ����ͼƬ��ͼƬ��ŵ�λ�� 
BOOL FindRect(imageinfo &info, RECT &out, std::vector<imagelayoutinfo> &used)
{
	// ��������
	RECT rc;
	imagelayoutinfo layout;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			rc.left = x;
			rc.top = y;
			rc.right = rc.left + info.width + 2;
			rc.bottom = rc.top + info.height + 2;
			// ͼƬ�Ŀ�ȳ�����
			if (rc.right > WIDTH)
			{
				break;
			}
			if (!IntersectRects(used, rc))
			{
				out = rc;
				layout.file = info.file;
				layout.rect = rc;
				used.push_back(layout);
				return TRUE;
			}
		}
	}
	// û�пռ���
	return FALSE;
}
// �����ļ�
void SaveFile(Bitmap &bmp, LPCWSTR filepath, LPCWSTR type)
{
	CLSID cls;
	GetEncoderClsid(type, &cls);
	bmp.Save(filepath, &cls);
}
// 
void task(DWORD param)
{
	taskparam *pm = (taskparam*)param;
	if (pm)
	{
		convert(pm->filepath, pm->uithread);
		delete pm;
	}
}

// ��ʼת��
int convert(LPCWSTR filepath, DWORD uithread)
{
	// ��ʼ��GDI+
	GdiplusStartupInput myGdiplusStartupInput;
	ULONG_PTR pMyGdiToken;
	GdiplusStartup(&pMyGdiToken, &myGdiplusStartupInput, NULL);
	// ��ȡ�ļ���Ϣ��������ͼƬ�ĸ�����
	std::multimap<int, imageinfo> datas;
	SearchFiles(filepath, datas);
	// Ԥ���ɵ�ͼƬ
	RECT rc;
	std::vector<imagelayoutinfo> used;
	int i = 1;
	for (std::multimap<int, imageinfo>::iterator it = datas.begin(); it != datas.end(); it++)
	{
		posinfo *info = new posinfo;
		info->info = it->second;
		info->pos = i;
		info->size = datas.size();
		::PostThreadMessage(uithread, WM_USER + 1000, (WPARAM)info, 0);
		FindRect(it->second, rc, used);
		i++;
	}
	// �����ļ�
	Bitmap bmp(WIDTH, HEIGHT);
	Graphics gs(&bmp);
	for (int i = 0; i < used.size(); i++)
	{
		imagelayoutinfo &info = used[i];
		Bitmap bs(filepath + CString(L"\\") + info.file);
		gs.DrawImage(&bs, info.rect.left + 1, info.rect.top + 1, info.rect.right - info.rect.left - 2, info.rect.bottom - info.rect.top - 2);
	}
	SaveFile(bmp, filepath + CString(L"\\convert_out.png"), L"image/png");
	return 0;
}