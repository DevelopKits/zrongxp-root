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
	imageinfo info;
	int pos;
	int size;
};


extern int convert(LPCWSTR filepath, DWORD uithread);