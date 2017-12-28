// imc.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ims.h"
using namespace Gdiplus;
using namespace std;

#define WIDTH 1024
#define HEIGHT 2048
// 返回GDI+的
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

// 返回图片尺寸
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
// 查找文件
void SearchFiles(const CString &szPathx, std::multimap<int, imageinfo> &datas)
{
	CString         path = szPathx + L"\\*.*";
	WIN32_FIND_DATA data;
	HANDLE			hFind = FindFirstFile(path, &data);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	// 遍历查找文件
	WCHAR	*pt;
	imageinfo info;
	while (FindNextFile(hFind, &data))
	{
		// 跳过所有的目录
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			continue;
		}
		// 跳过 convert_out.png
		if (wcscmp(data.cFileName, L"convert_out.png") == 0)
		{
			continue;
		}
		// 查找后缀
		pt = wcsrchr(data.cFileName, L'.');
		if (pt != NULL)
		{
			// 将后缀转化成小写
			_wcslwr(pt);
			if (wcscmp(pt, L".jpg") != 0 &&
				wcscmp(pt, L".png") != 0)
			{
				continue;
			}
		}
		// 文件信息容器
		GetImageSize(szPathx + L"\\", data.cFileName, info);
		datas.insert(std::pair<int, imageinfo>(9999 - info.height, info));
	}
	// 关闭
	FindClose(hFind);
}
// 判断在容器中是否有交集
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
// 返回图片该图片存放的位置 
BOOL FindRect(imageinfo &info, RECT &out, std::vector<imagelayoutinfo> &used)
{
	// 最大的容器
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
			// 图片的宽度超标了
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
	// 没有空间了
	return FALSE;
}
// 保存文件
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

// 开始转化
int convert(LPCWSTR filepath, DWORD uithread)
{
	// 初始化GDI+
	GdiplusStartupInput myGdiplusStartupInput;
	ULONG_PTR pMyGdiToken;
	GdiplusStartup(&pMyGdiToken, &myGdiplusStartupInput, NULL);
	// 读取文件信息，并按照图片的高排序
	std::multimap<int, imageinfo> datas;
	SearchFiles(filepath, datas);
	// 预生成的图片
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
	// 保存文件
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