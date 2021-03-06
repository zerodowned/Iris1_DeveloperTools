#pragma once 

#include "GumpCheckbox.h"
#include "GumpRadioPropertyPage.h"

class CGumpRadio : public CGumpCheckbox
{
	// Construction
public:
	CGumpRadio(CGumpPtr pNormal, CGumpPtr pChecked, int iGroupID=0, bool bCheck=false);

	virtual BOOL	FromString( XML::Node* node );
	virtual CString	GetString(BOOL bBegin) const;
	static	CGumpEntity* CreateFromNode( XML::Node* node );

	// Overrides
	virtual CDiagramEntity* Clone();
	virtual void			Draw( CDC* dc, CRect rect );

public:
	int m_iGroupID;
	int GetGroupID() const { return m_iGroupID; }
	void SetGroupID(int iGroupID) { m_iGroupID = iGroupID; }

private:
	CGumpRadioPropertyPage	m_page;
};
