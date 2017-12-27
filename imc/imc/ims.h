#pragma once


// 文件信息
struct imageinfo
{
	// 文件名称
	CString file;
	// 图片宽度
	int width;
	// 图片高度
	int height;
};

// 文件布局信息
struct imagelayoutinfo
{
	// 文件名称
	CString file;
	// 图片位置
	RECT rect;
};

// 文件布局信息
struct posinfo
{
	imageinfo info;
	int pos;
	int size;
};


extern int convert(LPCWSTR filepath, DWORD uithread);