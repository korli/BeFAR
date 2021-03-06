#ifndef __BF_NODE_H__
#define __BF_NODE_H__

#include <String.h>
#include <Node.h>
#include <Entry.h>
#include <Bitmap.h>
#include "BL_Tools.h"

#define BF_ROSTER_LOAD_NORMAL 			0
#define BF_ROSTER_LOAD_TYPE 			1
#define BF_ROSTER_LOAD_SICON 			2
#define BF_ROSTER_LOAD_LICON 			4
#define BF_ROSTER_LOAD_PERMS 			8
#define BF_ROSTER_LOAD_NODE_DIR			16
#define BF_ROSTER_LOAD_NODE_LINK		32
#define BF_ROSTER_LOAD_NODE_FILE		64
#define BF_ROSTER_LOAD_NODE_PARENTDIR	128
#define BF_ROSTER_LOAD_NODE_ALL_REAL  	(BF_ROSTER_LOAD_NODE_DIR+BF_ROSTER_LOAD_NODE_LINK+BF_ROSTER_LOAD_NODE_FILE)
#define BF_ROSTER_LOAD_NODE_ALL  		(BF_ROSTER_LOAD_NODE_DIR+BF_ROSTER_LOAD_NODE_LINK+BF_ROSTER_LOAD_NODE_FILE+BF_ROSTER_LOAD_NODE_PARENTDIR)

enum{
	BF_NODE_TYPE_UNKNOWN=0,
	BF_NODE_TYPE_FILE,
	BF_NODE_TYPE_DIR,
	BF_NODE_TYPE_LINK,
	BF_NODE_TYPE_PARENTDIR,	
};

// type of select_action
enum{
	BF_NODE_SELECT_OFF=0,
	BF_NODE_SELECT_ON,
	BF_NODE_SELECT_INVERT
};

class	BF_NodeCollection;
class 	BF_NodeList;

#define BF_NODE_STYLE_DEFAULT		0

class BF_Node:public BL_Object{
public:
		BL_String 			sName,sType;			
		off_t				iSize;
		time_t				uCreateTime,uAccessTime,uModifyTime;
		int					iType;
		bool				bSelect;
		bool				bLink;
		int32				iStyles;
		node_ref			uNodeRef;
		mode_t				uPerms;
		BBitmap				*poSIcon,*poLIcon; // small and large icons //
		BF_NodeList			*ploChild;		
		
							BF_Node(const char *pc_Name=NULL);
							BF_Node(const BF_Node &o_FromNode,bool b_SetIcon=true);
							BF_Node(BF_Node *po_FromNode,bool b_SetIcon=true);
virtual						~BF_Node();		
		
		void				Set(const BF_Node &o_FromNode,bool b_SetIcon=true);
		void				Set(BF_Node *po_FromNode,bool b_SetIcon=true);

		const char*			Name() const;
		int					Type() const;
		
		void				PermsTo(BL_String & s_Res) const;

		void				SetSelect(uint i_SelectAction);
		bool 				CheckByMask(const char *pc_Mask) const;
		int8				CompareCreateTime(const BF_Node &o_CompNode) const;		
		bool				ConvertNameByMask(const BString & s_Mask,BString & s_NewName) const;
		const BString*		ConvertNameByMaskExt(const BString & s_Mask,BString & s_NewName) const;
		
		void				AllocLIcon();
		void				AllocSIcon();				
		void				FreeSIcon();

		void				CopySIconFrom(BBitmap *po_SIcon);   
		
private:		};

class BF_Volume:public BF_Node{
public:		
							BF_Volume();
		
		void				LoadInfo();
		bool				Load(const char *pc_Name,int i_NodeLoadStyles);
		
		off_t				iCapacity,iFree;
		bool				bBootVolume,bReadOnly,bRemovable,bPersistent,bShared;		
		bool				bKnowsQuery;
		bool				bLoadedOk;
};

class BF_Path:public BL_Object{
public:						
static	bool				GetPathForCurrentApp(BL_String & s_Path);

							BF_Path(const char *pc_Value=NULL);
virtual						~BF_Path();

		const char*			Path() const;
		const BL_String		String() const;
		const BL_String     PathWFS() const; // without first slash
		
		void				SetTo(const char *pc_Path);		
		void				operator = (const BL_String & s_From);
		bool 				operator == (const char *pc_ComparePath) const;						
		
		const BString 		GetVolume(bool b_CleanVolume=false) const;			
virtual	bool				GoParent();
virtual	bool				GoLocalDir(const BString & s_LocalDir);

		bool				InFolder(const char *pc_ParentPath) const;

		bool				LastDir(BString & s) const;
		const BL_String		LastDir() const;
		bool				Compare(const char *pc_Path);		

		bool				IsEmpty() const;
		bool				IsVirtualRoot()const ;
		
		bool				IsStorageKit() const;
		
		
protected:
		BL_String			sValue;		

friend class	BF_FilesPath;	
};

class BF_FilesPath:public BF_Path{
public:
							BF_FilesPath(const char *pc_Value=NULL);
							BF_FilesPath(const BF_Path & o_SrcPath);
							BF_FilesPath(const BF_FilesPath & o_SrcPath);
		
		void 				SetTo(const BF_FilesPath &o_Path);							
		void				SetTo(const char *pc_Path,const node_ref *pu_Ref);										
		node_ref&			NodeRef() const;
		BBitmap*			LoadSIcon();
		bool				CheckNodeRef(const node_ref & u_NodeRef) const;		
		bool				Compare(const BF_FilesPath &o_SomePath);
		
		void 				operator = (const BF_FilesPath &o_Path);
		void 				operator = (const BF_Path &o_Path);
		
virtual	bool				GoParent();		
virtual	bool				GoLocalDir(const BString & s_LocalDir);

		bool				IsVolumeReadOnly() const;
		bool				IsExisting() const;
		
		status_t			Create();

private:
		node_ref			uNodeRef;			
};

typedef enum{
BF_NODELIST_SORT_NAME=0,
BF_NODELIST_SORT_SIZE,
BF_NODELIST_SORT_DATE,
BF_NODELIST_SORT_TYPE,
BF_NODELIST_SORT_EXT,
BF_NODELIST_SORT_UNSORTED,
BF_NODELIST_SORT_END
}BF_NodeList_SortType;

#define BF_SORT_STYLE_DIRFIRST	1

#define BF_NODELIST_NODETYPE_NONE		0
#define BF_NODELIST_NODETYPE_FILES		1
#define BF_NODELIST_NODETYPE_DIRS		2
#define BF_NODELIST_NODETYPE_LINKS		4
#define BF_NODELIST_NODETYPE_ALL		7

class BF_NodeCollection:public BL_Collection{
public:
		BF_Path				*poPath;							
		
							BF_NodeCollection(bool b_DeleteItems=false);		
							~BF_NodeCollection();
									
										  	
	  	void				CopyTo(BF_NodeCollection & lo_Dest,bool b_CopyIcons) const;
	  	
	  	BF_Node*			NodeByName(const char *pc_Name) const;
	  	BF_Node*			NodeAt(int32 i_Index) const;
	  	BF_Node*			NodeByRef(node_ref & u_Ref) const;
	  	int32				IndexByName(const char *pc_Name) const;
	  	
	  	void				SetSelectAll(uint i_SelectAction,const char *pc_Mask=NULL,int i_What=BF_NODELIST_NODETYPE_ALL);
	  	uint64				GetSelecting(BF_NodeCollection & lo_Result) const;
	  	
	  	uint64				SizeAll(bool b_WithChilds=false) const;
	  	uint64				CountAll(bool b_WithChilds=false) const;
	  	uint64				CountRealNodes() const;
  		uint64				CountSelected() const;
	  	void				SelectedInfo(uint64 & i_Bytes,uint64 & i_Count) const;
	  	void				LoadChilds(int i_WhatRosterLoad=BF_ROSTER_LOAD_NODE_ALL_REAL);
	
		void				MakePath(const char *pc_Path);
		void				SetSelfPath(BF_Path* po_NewPath);
		
		void				MakeSelfNodes();
		
		void				Sort(BF_NodeList_SortType i_SortType);
		
private:
		bool				bSelfPath; // true : delete poPath in destructor 	
public:	
static  uint32 				iSortStyle;		
};

#define BF_NodeCollection_New(plo_Node,o_Path) BF_NodeCollection *plo_Node;plo_Node = new BF_NodeCollection();plo_Node->SetSelfPath(&o_Path)

class BF_NodeList:public BF_NodeCollection{
public:
							BF_NodeList(bool b_DeleteItems=true);		
};




#endif
