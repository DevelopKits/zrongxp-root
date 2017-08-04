//#include "StdAfx.h"
#include "Xml.h"

CxXml2::CxXml2()
{
	m_pDoc = NULL;
}

CxXml2::~CxXml2()
{
	Close();
}

BOOL CxXml2::Load(LPCWSTR lpszPath, LPCWSTR lpszProgID)
{
	CoInitialize(NULL);
	if(lpszProgID)
	{
		CLSID	clsID;
		if(CLSIDFromProgID(_bstr_t(lpszProgID),&clsID))
		{
			return FALSE;
		}
		if(m_pDoc != NULL)
		{
			Close();
		}
		if(CoCreateInstance(clsID, NULL, CLSCTX_INPROC_SERVER,IID_IXMLDOMDocument, (void**)&m_pDoc))
		{
			return FALSE;
		}
	}
	if(lpszPath)
	{	
		VARIANT_BOOL bRet;
		if(m_pDoc->load(_variant_t(lpszPath), &bRet) != S_OK)
		{
			return FALSE;
		}
	}
	return TRUE;
}

IXMLDOMNode *CxXml2::Create(LPCWSTR lpszProgID)
{
	if (m_pDoc != NULL)
	{
		return m_pDoc;
	}
	if (lpszProgID != NULL)
	{
		CLSID	clsID;

		if (CLSIDFromProgID(_bstr_t(lpszProgID), &clsID))
		{
			return NULL;
		}
		if (m_pDoc != NULL)
		{ 
			Close();
		}
		if (CoCreateInstance(clsID, NULL, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (void**)&m_pDoc))
		{
			return NULL;
		}
	}
	return m_pDoc;
}

BOOL CxXml2::LoadXML(LPCWSTR sXml, LPCWSTR lpszProgID)
{
	if(lpszProgID)
	{
		CLSID	clsID;
		if(CLSIDFromProgID(_bstr_t(lpszProgID),&clsID))
			return 0;
		if(m_pDoc)
			Close();
		if(CoCreateInstance(clsID, NULL, CLSCTX_INPROC_SERVER,IID_IXMLDOMDocument, (void**)&m_pDoc))
			return 0;
	}
	if(sXml)
	{
		VARIANT_BOOL bRet;
		HRESULT		hr=m_pDoc->loadXML(CString(sXml).AllocSysString(),&bRet);
		if(hr!=S_OK)
			return 0;
	}
	return 1;
}

IXMLDOMNode *CxXml2::CreateEle(LPCTSTR lpszName)
{
	IXMLDOMElement	*pNode;
	m_pDoc->createElement(CComBSTR(lpszName),&pNode);
	return pNode;
}

IXMLDOMNode *CxXml2::GetFirstChildNode(IXMLDOMNode *pNode)
{
	IXMLDOMNode *pRoot;
	if(pNode->get_firstChild(&pRoot))
		return 0;
	return pRoot;
}

IXMLDOMNode *CxXml2::GetRoot()
{
	if( m_pDoc == NULL )
		return NULL;
	IXMLDOMNode *pRoot = GetFirstChildNode(m_pDoc);
	if (pRoot != NULL)
	{
		while(GetType(pRoot) != NODE_ELEMENT)
		{
			pRoot = GetNetSib(pRoot);
		}
	}
	return pRoot;
}

DOMNodeType CxXml2::GetType(IXMLDOMNode *pNode)
{
	DOMNodeType tNode;
	if(pNode->get_nodeType(&tNode))
		return (DOMNodeType)0;
	return tNode;
}

int CxXml2::GetChdCnt(IXMLDOMNode *pNode)
{	
	long iCnt;
	IXMLDOMNodeList *pAtt;
	if(pNode->get_childNodes(&pAtt))
		return -1;
	if(pAtt->get_length(&iCnt))
		iCnt=-1;
	return iCnt;
}

int CxXml2::GetAttCnt(IXMLDOMNode *pNode)
{
	IXMLDOMNamedNodeMap *pAtt;
	long				iCnt;
	if(pNode->get_attributes(&pAtt))
		return -1;
	if(pAtt->get_length(&iCnt))
		iCnt=-1;
	return iCnt;
}

CString CxXml2::GetName(IXMLDOMNode *pNode)
{
	CComBSTR	sName;
	
	if(pNode->get_nodeName(&sName))
		return _T("");
	return (TCHAR*)_bstr_t(sName);
}

IXMLDOMNode *CxXml2::GetLastChild(IXMLDOMNode *pNode)
{
	IXMLDOMNode *pRoot;
	if(pNode->get_lastChild(&pRoot))
		return 0;
	return pRoot;
}

IXMLDOMNode *CxXml2::GetNetSib(IXMLDOMNode *pNode)
{
	IXMLDOMNode *pRoot;
	if(pNode->get_nextSibling(&pRoot) == S_OK)
	{
		return pRoot;
	}
	return NULL;
}

IXMLDOMNode *CxXml2::GetPreSib(IXMLDOMNode *pNode)
{
	IXMLDOMNode *pRoot;
	if(pNode->get_previousSibling(&pRoot))
		return 0;
	return pRoot;
}

CString CxXml2::GetVal(IXMLDOMNode *pNode)
{
	VARIANT rVal;
	if(pNode->get_nodeValue(&rVal))
		return _T("");
	return rVal;
}

IXMLDOMNode *CxXml2::GetAtt(IXMLDOMNode *pNode, LPCTSTR lpszAtt)
{
	IXMLDOMNamedNodeMap		*pAtt;
	IXMLDOMNode				*pRoot;
	if(pNode->get_attributes(&pAtt))
		return 0;
	if(pAtt->getNamedItem(_bstr_t(lpszAtt),&pRoot))
		pRoot=0;
	return pRoot;
}

IXMLDOMNode *CxXml2::GetAtt(IXMLDOMNode *pNode, int nAtt)
{
	IXMLDOMNamedNodeMap		*pAtt;
	IXMLDOMNode				*pRoot;
	if(pNode->get_attributes(&pAtt))
		return 0;
	if(pAtt->get_item(nAtt,&pRoot))
       pRoot = 0;
	return pRoot;
}

IXMLDOMNode *CxXml2::GetNode(LPCWSTR lpszPath)
{
	IXMLDOMNode *pNode = NULL;
	if (m_pDoc != NULL)
	{
		if(m_pDoc->selectSingleNode(CComBSTR(lpszPath),&pNode))
		{
			return NULL;
		}
	}
	return pNode;
}

IXMLDOMNode *CxXml2::GetNode(IXMLDOMNode *pNode, LPCWSTR lpszPath)
{
	IXMLDOMNode *pRet;
	if(pNode->selectSingleNode(CComBSTR(lpszPath),&pRet))
		return 0;
	return pRet;
}

CString CxXml2::GetText(IXMLDOMNode *pNode)
{
	CComBSTR	strText;
	pNode->get_text(&strText);
	return CString(strText);
}

BOOL CxXml2::Save(LPCTSTR lpszFile)
{
	CComBSTR sPath;
	if(lpszFile)
		sPath=lpszFile;
	else
		m_pDoc->get_url(&sPath);
	return m_pDoc->save(_variant_t(sPath))==S_OK;
}

IXMLDOMNode *CxXml2::InsChd(IXMLDOMNode *pParNode, LPCWSTR lpszNode, IXMLDOMNode *pNodeBef)
{
	IXMLDOMElement *pNewNode;
	if(m_pDoc->createElement((wchar_t*)_bstr_t(lpszNode),&pNewNode)!=S_OK)
		return 0;
	IXMLDOMNode *pOutNode;
	if(pNodeBef)
		pParNode->insertBefore(pNewNode,_variant_t(pNodeBef),&pOutNode);
	else
		pParNode->appendChild(pNewNode,&pOutNode);
	pNewNode->Release();
	return pOutNode;
}

void CxXml2::Close()
{
	if (m_pDoc != NULL)
	{
		m_pDoc->Release();
	}
}

CString CxXml2::GetNodeAtt(IXMLDOMNode *pNode, LPCTSTR lpszAtt)
{
	IXMLDOMNode *pNodeAtt = GetAtt(pNode, lpszAtt);
	if(pNodeAtt==0)
		return _T("");
	return GetText(pNodeAtt);
}

CString CxXml2::GetNodeAtt(IXMLDOMNode *pNode, int index)
{
	IXMLDOMNode *pNodeAtt = GetAtt(pNode, index);
	if(pNodeAtt == NULL)
	{
		return _T("");
	}
	return GetText(pNodeAtt);
}

IXMLDOMNode *CxXml2::AppendChild(IXMLDOMNode *pNode, IXMLDOMNode *pParNode)
{
	IXMLDOMNode *pRoot;
	if(pParNode)
		pParNode->appendChild(pNode,&pRoot);
	else
		m_pDoc->appendChild(pNode,&pRoot);
	return pRoot;
}

HRESULT CxXml2::SetAtt(IXMLDOMElement *pNode, LPCTSTR lpszAtt, LPCTSTR lpszVal)
{
	return pNode->setAttribute(CComBSTR(lpszAtt),_variant_t(lpszVal));
}

HRESULT CxXml2::SetText(IXMLDOMNode *pNode, LPCTSTR lpszText)
{
	return pNode->put_text(_bstr_t(lpszText));
}

HRESULT CxXml2::Del(IXMLDOMNode *pNode)
{
	IXMLDOMNode *pAtt = GetParent(pNode);
	return pAtt->removeChild(pNode,0);
}

IXMLDOMNode *CxXml2::GetParent(IXMLDOMNode *pNode)
{
	IXMLDOMNode *pAtt;
	pNode->get_parentNode(&pAtt);
	return pAtt;
}

CString CxXml2::GetPath()
{
	CComBSTR sPath;
	m_pDoc->get_url(&sPath);
	return sPath.m_str;
}

BOOL CxXml2::IsNodeHasChild(IXMLDOMNode *pNode)
{
	VARIANT_BOOL bHasChild = FALSE;
	pNode->hasChildNodes(&bHasChild);
	return bHasChild;
}