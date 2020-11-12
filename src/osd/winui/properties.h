// For licensing and usage information, read docs/winui_license.txt
//****************************************************************************

#ifndef PROPERTIES_H
#define PROPERTIES_H

/* Get title string to display in the top of the property page,
 * Called also in ui_audit.cpp
 */
char* GameInfoTitle(OPTIONS_TYPE opt_type, UINT nIndex);

/* Called in winui.cpp to create the property page */
void InitPropertyPage(HINSTANCE hInst, HWND hWnd, HICON hIcon, OPTIONS_TYPE opt_type, int folder_id, int game_num);

#define PROPERTIES_PAGE 0
#define AUDIT_PAGE      1

void InitPropertyPageToPage(HINSTANCE hInst, HWND hWnd, HICON hIcon, OPTIONS_TYPE opt_type, int folder_id, int game_num, int start_page);
void InitDefaultPropertyPage(HINSTANCE hInst, HWND hWnd);

/* Get Help ID array for WM_HELP and WM_CONTEXTMENU */
DWORD_PTR GetHelpIDs(void);

/* Get Game status text string */
const char* GameInfoStatus(int driver_index, BOOL bRomStatus);

/* Property sheet info for layout.c */
typedef struct
{
	BOOL bOnDefaultPage;
//  BOOL (*pfnFilterProc)(const machine_config *drv, const game_driver *gamedrv);
	BOOL (*pfnFilterProc)(uint32_t driver_index);
	DWORD dwDlgID;
	DLGPROC pfnDlgProc;
} PROPERTYSHEETINFO;

extern const PROPERTYSHEETINFO g_propSheets[];

BOOL PropSheetFilter_Vector(const machine_config *drv, const game_driver *gamedrv);

INT_PTR CALLBACK GamePropertiesDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK GameOptionsProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

int PropertiesCurrentGame(HWND hDlg);

// from propertiesms.h (MESSUI)

BOOL MessPropertiesCommand(HWND hWnd, WORD wNotifyCode, WORD wID, BOOL *changed);
BOOL g_bModifiedSoftwarePaths = FALSE;
INT_PTR CALLBACK GameMessOptionsProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL PropSheetFilter_Config(const machine_config *drv, const game_driver *gamedrv);

#include "datamap.h"
void MessBuildDataMap(datamap *properties_datamap);


#endif

