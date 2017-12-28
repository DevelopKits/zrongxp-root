#pragma once

// �ļ���Ϣ
struct imageinfo
{
	// �ļ�����
	CString file;
	// ͼƬ���
	int width;
	// ͼƬ�߶�
	int height;
};

// �ļ�������Ϣ
struct imagelayoutinfo
{
	// �ļ�����
	CString file;
	// ͼƬλ��
	RECT rect;
};

// �ļ�������Ϣ
struct posinfo
{
	// ͼƬ��Ϣ
	imageinfo info;
	// λ��
	int pos;
	// �ܳ���
	int size;
};

// ִ���������Ĳ���
struct taskparam
{
	// �ļ�·��
	CString filepath;
	// ���߳�
	DWORD uithread;
};

extern void task(DWORD param);
extern int convert(LPCWSTR filepath, DWORD uithread);
