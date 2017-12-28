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
	// 图片信息
	imageinfo info;
	// 位置
	int pos;
	// 总长度
	int size;
};

// 执行任务打包的参数
struct taskparam
{
	// 文件路径
	CString filepath;
	// 主线程
	DWORD uithread;
};

extern void task(DWORD param);
extern int convert(LPCWSTR filepath, DWORD uithread);
