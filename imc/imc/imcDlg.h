
// imcDlg.h : ͷ�ļ�
//

#pragma once
#include "ims.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Thread.h"

// CimcDlg �Ի���
class CimcDlg : public CDialogEx
{
// ����
public:
	CimcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
	void proc(imageinfo &info, int pos, int size);
	void func(TaskInfo *pm);
	CProgressCtrl m_proc;
	CButton m_start;
	CEdit m_folder;
	CEdit m_width;
};
