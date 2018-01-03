
// imcDlg.h : 头文件
//

#pragma once
#include "ims.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Thread.h"

// CimcDlg 对话框
class CimcDlg : public CDialogEx
{
// 构造
public:
	CimcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
