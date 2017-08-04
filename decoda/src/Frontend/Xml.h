#pragma once
#include <comdef.h>
#include <msxml.h>
#include <atlstr.h>

	class CxXml2
	{
	public:
		CxXml2();
		~CxXml2();
	protected:
		IXMLDOMDocument	*m_pDoc;
	public:
		IXMLDOMNode	*Create(LPCWSTR lpszProgID = L"MSXML2.DOMDocument.3.0");
		BOOL		Load(LPCWSTR lpszFilePath = NULL, LPCWSTR lpszProgID = L"MSXML2.DOMDocument.3.0");//lpszFilePath加载的文件，为空将不加载文件，lpszProgID生成解析器版本，为空将不生成解析器
		BOOL		LoadXML(LPCWSTR sXml, LPCWSTR lpszProgID = L"MSXML2.DOMDocument.3.0");//lpszFilePath加载的文件，为空将不加载文件，lpszProgID生成解析器版本，为空将不生成解析器
		IXMLDOMNode	*GetRoot();
		IXMLDOMNode	*GetParent(IXMLDOMNode *pNode);
		IXMLDOMNode	*GetFirstChildNode(IXMLDOMNode *pNode);
		IXMLDOMNode	*GetLastChild(IXMLDOMNode *pNode);
		IXMLDOMNode	*GetNetSib(IXMLDOMNode *pNode);
		IXMLDOMNode	*GetPreSib(IXMLDOMNode *pNode);
		IXMLDOMNode	*GetAtt(IXMLDOMNode *pNode, int nAtt);
		IXMLDOMNode	*GetAtt(IXMLDOMNode *pNode, LPCTSTR lpszAtt);
		CString		GetNodeAtt(IXMLDOMNode *pNode, LPCTSTR lpszAtt);
		CString		GetNodeAtt(IXMLDOMNode *pNode, int index);
		HRESULT		SetAtt(IXMLDOMElement *pNode, LPCTSTR lpszAtt, LPCTSTR lpszVal);
		int			GetAttCnt(IXMLDOMNode *pNode);
		int			GetChdCnt(IXMLDOMNode *pNode);
		IXMLDOMNode	*GetNode(LPCWSTR lpszPath = L"fo/user/");
		IXMLDOMNode	*GetNode(IXMLDOMNode *pNode, LPCWSTR lpszPath = L"fo/user/");
		IXMLDOMNode	*InsChd(IXMLDOMNode *pParNode, LPCWSTR lpszNode, IXMLDOMNode *pNodeBef = 0);
		IXMLDOMNode	*AppendChild(IXMLDOMNode *pNode, IXMLDOMNode *pParNode = NULL);
		IXMLDOMNode	*CreateEle(LPCTSTR lpszName);
		HRESULT		Del(IXMLDOMNode *pNode);
		HRESULT		SetText(IXMLDOMNode *pNode, LPCTSTR lpszText);
		CString		GetName(IXMLDOMNode *pNode);
		CString		GetVal(IXMLDOMNode *pNode);
		CString		GetText(IXMLDOMNode *pNode);
		DOMNodeType	GetType(IXMLDOMNode *pNode);
		BOOL		Save(LPCTSTR lpszFile = NULL);
		void		Close();
		CString		GetPath();
		BOOL        IsNodeHasChild(IXMLDOMNode *pNode);
	};
