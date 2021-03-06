#ifndef __BF_GUI_TOOLS_H__
#define __BF_GUI_TOOLS_H__

#include <String.h>
#include <Message.h>
#include <View.h>
#include <Window.h>

#include "BL_Tools.h"	
#include "BF_GUI_Setup.h"	
#include "BF_Msg.h"	


#define BF_GUI_DIALOG_MESSAGE_DATA_OK "bf_bOk"

uint32
BF_GUI_GetTextLength(BString & s_Text,float f_Width,BFont & o_Font);

class BF_GUI_DialogView:public BView{
public:		
								BF_GUI_DialogView(const BRect oRect,const char* pc_Name,uint32	i_FollowMode,uint32	i_Flags);
								
virtual bool					KeyDownExt(const char *bytes, int32 numBytes);
virtual void					SaveToMessage(BMessage *po_Message){};
virtual void 					MessageReceived(BMessage* po_Message);	
virtual void					MouseDown(BPoint point);	

virtual void					SetSetupFont(BF_GUI_Setup_Font *po_Font);
		BF_GUI_Setup_Font* 		Font(){return poFont;};
		
virtual	void					SetupUpdated();
		
protected:
		BF_GUI_Setup_Font 		*poFont;
};

class BF_GUI_VScrollBar:public BF_GUI_DialogView{
public:
								BF_GUI_VScrollBar(const BRect o_Rect,const char* pc_Name,uint32	i_FollowMode);
virtual	void					Draw(BRect o_Rect);

		void					SetLimits(int i_Limit,int i_VisibleLimit);
		void					SetCursor(int i_Cursor);
private:
		int						iLimit,iVisibleLimit,iCursor;
};


class BF_GUI_ViewFrame:public BF_GUI_DialogView{
public:
								BF_GUI_ViewFrame(BRect & o_Rect,int32 i_FollowMode);
virtual	void					Draw(BRect o_Rect);
};

BF_GUI_ViewFrame*
BF_GUI_ViewFrame_Create(BView *po_ForView,BView *po_Parent);

#include "BF_GUI_Edit.h"

class BF_GUI_ViewCheck:public BF_GUI_DialogView{  
public:
		BL_String					sTitle;		
				
								BF_GUI_ViewCheck(const BRect 		o_Rect,
												const char	*pc_Name,
												const char	*pc_Title,
												bool		b_Value,
												uint32		i_FollowMode,
												uint32		i_Flags);
								~BF_GUI_ViewCheck();									
virtual	void					Draw(BRect o_Rect);
virtual void					KeyDown(const char *bytes, int32 numBytes);
virtual void					Pulse(void);
virtual void 					AttachedToWindow(void);
virtual void 					MessageReceived(BMessage* po_Message);	
virtual void 					MakeFocus(bool focused = true);		

virtual void					MouseDown(BPoint point);	

virtual void					SaveToMessage(BMessage *po_Message);
protected:
		bool					bValue;
		bool					bPulseCursorShow;
		thread_id 				idThreadPulse;
		
		void					DrawCursor(bool b_Show);
};

class BF_GUI_ViewCheck_Style:public BF_GUI_ViewCheck{  
public:
								BF_GUI_ViewCheck_Style(const BRect 		o_Rect,
												const char	*pc_Name,
												const char	*pc_Title,
												uint32		*pi_SrcStyles,
												uint32		i_SrcStyle,
												uint32		i_FollowMode,
												uint32		i_Flags);

virtual void					SaveToMessage(BMessage *po_Message);
private:
		uint32					*piSrcStyles;
		uint32					iSrcStyle;											
};

class BF_GUI_ViewText:public BF_GUI_DialogView{
public:
		BString					sTitle;
				
								BF_GUI_ViewText(const BRect o_Rect,
												const char *pc_Name,
												const char *pc_Title,
												uint32	i_FollowMode,
												uint32	i_Flags,
												bool b_AlignCenter=true);
virtual	void					Draw(BRect o_Rect);
private:
		bool					bAlignCenter;
};

class BF_GUI_ViewProgress:public BF_GUI_DialogView{
public:
			
								BF_GUI_ViewProgress(const BRect o_Rect,
												const char *pc_Name,
												const char *pc_Title,
												uint32	i_FollowMode,
												uint32	i_Flags,
												int64 *pi_Count=NULL,
												int64 *pi_Index=NULL);
								~BF_GUI_ViewProgress();
		void					SetLimit(int64 i_Count);
		void					Step(int64 i_Delta=1);
		void					SetControls(int64 *pi_Count,
											int64 *pi_Index);
		
		
virtual	void					Draw(const BRect o_Rect);
virtual void 					MessageReceived(BMessage* po_Message);

virtual void 					AttachedToWindow(void);
virtual void					Pulse(void);

		

private:
		BString					sTitle;
		int64					iCount,iIndex;
		float					fDelta;
		int64 					*piCount;
		int64 					*piIndex;		
};

/*
#define SIZE_SHADOW_X  	10.0
#define SIZE_SHADOW_Y  	9.0
#define SIZE_SPACE		10.0
#define SIZE_FRAME		10.0
#define SIZE_FRAME2		4.0
*/


#define BG_GUI_DIALOG_WINRESIZE_NONE			0
#define BG_GUI_DIALOG_WINRESIZE_MOVE_CENTER		1
#define BG_GUI_DIALOG_WINRESIZE_MOVE_RCENTER	2
#define BG_GUI_DIALOG_WINRESIZE_RESIZE_ALL		3

class BF_GUI_DlgPanel:public BView{
public:
								BF_GUI_DlgPanel(const BRect & o_Rect,
												const char *pc_Title,		
												const char *pc_Name,
												int i_FollowMode,
												int i_Styles,
												bool b_DoubleBorder=true);
virtual	void					Draw(BRect o_Rect);																
virtual void					MouseDown(BPoint point);
virtual void 					MessageReceived(BMessage* po_Message);	
		void					LocalBounds(BRect & o_Rect);			
		
		void					SetSizeBy(float f_X,float f_Y);
		void					SetHeightFromLastChild();
		void 					MoveToCenter(BView *po_View);		
		
		void					AddMenu(BRect & o_Rect,BL_List *plo_Menu,bool b_RectInited=false);
		void					AddOkCancelMenu(BRect & o_Rect,bool b_RectInited=false);

public:
		float					fShadowX,fShadowY;
		float					fBorderH,fBorderTop,fBorderBottom;				
		
protected:
		BString					sTitle;																
								
};

class BF_GUI_Dialog:public BF_GUI_DlgPanel{
public:
								BF_GUI_Dialog(
										const BRect & o_Rect,
										const char *pc_Title,		
										const char *pc_Name,
										const BMessage &o_Message,
										uint32	i_WinResizeType, // BG_GUI_DIALOG_WINRESIZE_NONE
										bool b_DoubleBorder=true);
virtual void 					MessageReceived(BMessage* po_Message);		
virtual void 					AttachedToWindow(void);

virtual void					MouseDown(BPoint point);

		void					EnableDialog(bool b_Enable);
		void					FocusFirstView();
		
		BMessage*				Message();

protected:
		BMessage 				oMessage;
		uint32					iWinResizeType;
		
virtual void					Save(BMessage& o_Message);
virtual	bool					ReadyForClose(){return true;};
};

	
/* plo_MenuItem will be deleted in this function */
int32
BF_Dialog_Alert(const char *pc_Title,const char *pc_Text,
				BL_List *plo_MenuItem=NULL,
				const char *pc_Text1=NULL);

void 
BF_Dialog_Alert_Sep(const char *pc_Title,const char *pc_Text,
 				BL_List *plo_MenuItem, // may be NULL for standart Ok menu //
				BView *po_ViewOwner,
				const char *pc_Text1=NULL,
				int32	i_MessageWhat=BF_MSG_PANEL_FOCUS_AND_ENABLE);
				
void 
BF_Dialog_Alert_Sep_Error(status_t uRes,BView *po_ViewOwner);		

#include "BF_GUI_DlgViews_Menu.h"

#endif
