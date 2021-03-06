#ifndef __BF_GUI_NODEPANEL_H__
#define __BF_GUI_NODEPANEL_H__

#include <View.h>
#include <Window.h>
#include "BL_Tools.h"
#include "BF_Node.h"
#include "BF_GUI_Setup.h"
#include "BF_GUI_DlgViews.h"
#include "BF_GUI_Func.h"
///
enum {
	BF_NODEPANEL_MODE_FULL=0,
	BF_NODEPANEL_MODE_COLS
};
///
#define BF_NODEPANEL_FULL_NAME		1
#define BF_NODEPANEL_FULL_DATE		2
#define BF_NODEPANEL_FULL_SIZE		4
#define BF_NODEPANEL_FULL_TYPE		8
#define BF_NODEPANEL_FULL_SICON		16
#define BF_NODEPANEL_FULL_ALL		255
///
#define BF_NODEPANEL_COLS_NAME		1
#define BF_NODEPANEL_COLS_SICON		32
///
#define BF_NODEPANEL_PULSE_NONE		0
#define BF_NODEPANEL_PULSE_MOVEUP	1
#define BF_NODEPANEL_PULSE_MOVEDOWN	2
#define BF_NODEPANEL_PULSE_ALL		255
///

#define BF_NODEPANEL_COPY_NOTETYPES_FIELD "bf_iCopyNodeTypes" // BMessage field for copy_task with node_types

///
class BF_GUI_NodePanel:public BF_GUI_Panel{
/* public members */
public:
		float					fWidth,fNodesHeight,fNodeHeight,fColTitleHeight,fNodeInfoHeight,fSelInfoHeight;
		
		float					fFullName,fFullType,fFullSize,fFullDate,fFullSIcon;
		uint32					iModeFullStyles;
		
		float 					fColsName,fColsSIcon,fColsColWidth;
		uint32					iModeColsStyles;
		uint32					iColsColCount,iColsNodesInCol;
		
		uint32					iMode;
		BF_NodeList_SortType	iSortType;
	
		
		int32					iNavFirstIndex;
		int32					iNavCursorIndex;
		int32					iNodesOnScreen;
///////////////////////  for inheriting ///////////////////////////////////////////////////

								BF_GUI_NodePanel(const BRect & o_Rect,bool b_WinPos_OnLeft);
								~BF_GUI_NodePanel();

virtual void					DrawPanel(BRect & o_Rect);
virtual void					FrameResized(float width, float height);
virtual BRect					ClientRect();
virtual void					Calc();

virtual	void					OnEnable(bool b_Enable);

virtual bool 					OnMouseDown(BPoint & o_Point);
virtual bool 					OnMouseUp(BPoint & o_Point);
virtual void 					MouseMoved(BPoint o_Point,uint32 i_Transit,const BMessage *message);

virtual	void					PrepareKeysMenu();
virtual void					PrepareTopMenuItem(BF_GUI_TopMenu_HItem *po_HItem);	// must be calling from child
virtual	void					PrepareHotKeys(bool b_Focused); 					// must be calling from child, before child_code

virtual bool					OnKeyDown(const char *bytes, int32 numBytes);
virtual bool					OnBeforeKeyDown(const char *bytes, int32 numBytes);

virtual void					ChangeSortType(BF_NodeList_SortType i_NewSortType);

virtual void					RefreshNodeList();

virtual	bool 					NavChangeCursor(int i_NewCursor,bool b_DrawNodes=true,bool b_ChangeVars=true);
virtual	bool					NavEnter();		
virtual	void					NavGoParentDir();

virtual	void 					DrawListInfo(bool b_DrawBack);

virtual	void					ActionRename_Run(BF_NodeCollection & lo_Node,BL_String & s_NewName);// must runed from childs
virtual	void					ActionDelete_Run(BF_NodeCollection & lo_Node);					// must runed from childs
virtual	void					ActionCopyTo_Run(BL_String & s_Path,BF_NodeCollection & lo_Node); // must runed from childs
virtual	void					ActionMoveTo_Run(BL_String & s_Path,BF_NodeCollection & lo_Node); // must runed from childs
virtual	void					ActionMakeDir_Run(BL_String & s_Title);
virtual	void					ActionCopyFrom_Run(BL_String & s_Path,BF_NodeCollection & lo_Node,bool b_Move);

virtual	void 					Action_SwitchShowIcons();		
virtual void					OnFocus(bool b_Focused);

virtual void 					MessageReceived(BMessage* po_Message);

virtual void					StoreVars(BF_GUI_Setup_Vars_Panel & o_Setup) const;
///////////////////////  ne dlya nasledovaniy ///////////////////////////////////////////////////
		
		void					ActionCopyTo_Start();		
		void					ActionDelete_Start();
		void					ActionMoveTo_Start();	
		void					ActionMakeDir_Start();
		void					ActionRename_Start();
		
		bool					ModeShowSIcon();
		void					SetModeShowSIcon(bool b_ShowIcons);				
		
		bool 					NavToStart();
		bool 					NavToEnd();		
		bool 					NavDown();
		bool 					NavUp();
		bool 					NavRight();		
		bool 					NavLeft();					
		bool 					NavPgDown();		
		bool 					NavPgUp();				
		
		bool					NavSelect(bool b_CursorGoNext=true);
		bool					NavSelectAll_0(int32 i_Key);
		void					NavSelectAll_1(BMessage *po_Message);						
		void					NavDeselectAll();
		
		void					DrawStringRight(const char *pc_Text,BPoint &o_Point,float f_Width);
		void					DrawStringCenter(const char *pc_Text,BPoint &o_Point,float f_Width);
		
		void 					DrawLines(bool b_OnlyNodes);
		void 					DrawColTitles();
		void 					DrawSelListInfo(bool b_DrawBack);
		void					DrawNodeInfo();
		void 					DrawNodes(bool b_DrawBackground=false);		
		void					DrawNodeAt(int32 i_Index);
		void 					DrawNode(
										int32 i_NodeIndex,
										bool b_ItCursor,
										BPoint &oPoint,
										BRect & oRect,
										char *pc_Buffer,									
										BRect *po_RectBound, /* maybe NULL */
										bool b_DrawBackground,
										bool b_UsePoint=false);
		void 					DrawNodeSelf( /* wrapper for prev method  */
										int32 i_NodeIndex,
										bool b_ItCursor,										
										bool b_DrawBackground,
										bool b_OffScreen=false);
		void					DrawNode_CursorBack(
										BF_Node *po_Node,
										BRect&	oRect, // for internal using, don`t disturbe about initing this var
										BPoint&	oPoint, // control_var, needing init pre-setting
										float f_Width,
										bool b_Cursor);										
		void 					DrawNode_SetNodeColor(BF_Node *po_Node,bool b_IsFocus);
		void					DrawMove_ColsDown();
		void					DrawMove_ColsUp();
		void					DrawMove_ColsRight();
		void					DrawMove_ColsLeft();	
		void					DrawMove_FullUp();
		void					DrawMove_FullDown();		
		
		void 					Action_Alert(const char *pc_Title,const char *pc_Text);  
		
		BF_NodeCollection*		Nodes_GetSelecting();
		BF_Node*				Nodes_Focus();
virtual	void					Nodes_Add(BF_Node *po_Node,BF_NodeCollection *plo_Node);  		// mozet nasledovastsya
virtual	void					Nodes_Remove( BF_Node *po_Node, BF_NodeCollection *plo_Node);	// mozet nasledovastsya
virtual	void					Nodes_Update( BF_Node *po_Node, BF_NodeCollection *plo_Node);	// mozet nasledovastsya
virtual	void					Nodes_GetAll(BF_NodeList& lo_ResultNode,bool b_ReqIcons);   	// mozet nasledovastsya
virtual	void					Nodes_SetSelectingByName( BF_NodeList* plo_ReqNode,uint i_SelAction,bool b_ReqUpdate=true); // mozet nasledovastsya
		
		void					PulseAction_Add(int32 i_NewActions);
		void					PulseAction_Remove(int32 i_NewActions);		
virtual void					Pulse(void);		


		void					PanelSetup_0();
		void					PanelSetup_1(BMessage *po_Message);		
//////////////////////////////////////////////////////////////////////////
								
/* private members */
protected:				
		BF_NodeList				loNode;		
		int32					iPulseActions;	// BF_NODEPANEL_PULSE_NONE				
		
		BString					sNodeSelMask;
		bool					bSelectDirAlso;						
		bool					bCanSelect;
		
		BL_String				sDictDir;
		
private:		
		thread_id 				idThreadPulse;
																				
};


#endif
