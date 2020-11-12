// For licensing and usage information, read docs/winui_license.txt
// MASTER
//****************************************************************************

/***************************************************************************

  dialogs.c

  Dialog box procedures go here

***************************************************************************/


#ifdef _MSC_VER
#ifndef NONAMELESSUNION
#define NONAMELESSUNION
#endif
#endif

// standard windows headers
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h> // ShellExecute
#include <commctrl.h>

// standard C headers
#include <tchar.h>

// MAMEUI headers
#include "bitmask.h"
#include "treeview.h"
#include "resource.h"
#include "mui_opts.h"
#include "help.h"
#include "properties.h"  // For GetHelpIDs

// MAME headers
#include "winutf8.h"

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

static struct ComboBoxHistoryTab
{
	const wchar_t*  m_pText;
	const int       m_pData;
} g_ComboBoxHistoryTab[] =
{
	{ TEXT("Artwork"),          TAB_ARTWORK },
	{ TEXT("Boss"),             TAB_BOSSES },
	{ TEXT("Cabinet"),          TAB_CABINET },
	{ TEXT("Control Panel"),    TAB_CONTROL_PANEL },
	{ TEXT("Cover"),            TAB_COVER },
	{ TEXT("End"),              TAB_ENDS },
	{ TEXT("Flyer"),            TAB_FLYER },
	{ TEXT("Game Over"),        TAB_GAMEOVER },
	{ TEXT("How To"),           TAB_HOWTO },
	{ TEXT("Logo"),             TAB_LOGO },
	{ TEXT("Marquee"),          TAB_MARQUEE },
	{ TEXT("PCB"),              TAB_PCB },
	{ TEXT("Scores"),           TAB_SCORES },
	{ TEXT("Select"),           TAB_SELECT },
	{ TEXT("Snapshot"),         TAB_SCREENSHOT },
	{ TEXT("Title"),            TAB_TITLE },
	{ TEXT("Versus"),           TAB_VERSUS },
	{ TEXT("All"),              TAB_ALL },
	{ TEXT("None"),             TAB_NONE }
};


static string g_FilterText;

#define NUM_EXCLUSIONS  12
#define NUMHISTORYTAB   ARRAY_LENGTH(g_ComboBoxHistoryTab)

/* Pairs of filters that exclude each other */
static DWORD filterExclusion[NUM_EXCLUSIONS] =
{
	IDC_FILTER_CLONES,      IDC_FILTER_ORIGINALS,
	IDC_FILTER_NONWORKING,  IDC_FILTER_WORKING,
	IDC_FILTER_UNAVAILABLE, IDC_FILTER_AVAILABLE,
	IDC_FILTER_RASTER,      IDC_FILTER_VECTOR,
	IDC_FILTER_HORIZONTAL,  IDC_FILTER_VERTICAL,
	IDC_FILTER_ARCADE,      IDC_FILTER_MESS,
};

static void DisableFilterControls(HWND hWnd, LPCFOLDERDATA lpFilterRecord, LPCFILTER_ITEM lpFilterItem, DWORD dwFlags);
static void EnableFilterExclusions(HWND hWnd, DWORD dwCtrlID);
static DWORD ValidateFilters(LPCFOLDERDATA lpFilterRecord, DWORD dwFlags);
static void OnHScroll(HWND hWnd, HWND hwndCtl, UINT code, int pos);

/***************************************************************************/

const char * GetFilterText(void)
{
	return g_FilterText.c_str();
}

INT_PTR CALLBACK ResetDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	BOOL resetFilters  = false;
	BOOL resetGames    = false;
	BOOL resetUI       = false;
	BOOL resetDefaults = false;

	switch (Msg)
	{
	case WM_INITDIALOG:
		return true;

	case WM_HELP:
		/* User clicked the ? from the upper right on a control */
		HelpFunction((HWND)((LPHELPINFO)lParam)->hItemHandle, MAMEUICONTEXTHELP, HH_TP_HELP_WM_HELP, GetHelpIDs());
		break;

	case WM_CONTEXTMENU:
		HelpFunction((HWND)wParam, MAMEUICONTEXTHELP, HH_TP_HELP_CONTEXTMENU, GetHelpIDs());

		break;

	case WM_COMMAND :
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK :
			resetFilters  = Button_GetCheck(GetDlgItem(hDlg, IDC_RESET_FILTERS));
			resetGames    = Button_GetCheck(GetDlgItem(hDlg, IDC_RESET_GAMES));
			resetDefaults = Button_GetCheck(GetDlgItem(hDlg, IDC_RESET_DEFAULT));
			resetUI       = Button_GetCheck(GetDlgItem(hDlg, IDC_RESET_UI));
			if (resetFilters || resetGames || resetUI || resetDefaults)
			{

				TCHAR temp[400];
				_tcscpy(temp, TEXT(MAMEUINAME));
				_tcscat(temp, TEXT(" will now reset the following\n"));
				_tcscat(temp, TEXT("to the default settings:\n\n"));

				if (resetDefaults)
					_tcscat(temp, TEXT("Global game options\n"));
				if (resetGames)
					_tcscat(temp, TEXT("Individual game options\n"));
				if (resetFilters)
					_tcscat(temp, TEXT("Custom folder filters\n"));
				if (resetUI)
				{
					_tcscat(temp, TEXT("User interface settings\n\n"));
					_tcscat(temp, TEXT("Resetting the User Interface options\n"));
					_tcscat(temp, TEXT("requires exiting "));
					_tcscat(temp, TEXT(MAMEUINAME));
					_tcscat(temp, TEXT(".\n"));
				}
				_tcscat(temp, TEXT("\nDo you wish to continue?"));
				if (MessageBox(hDlg, temp, TEXT("Restore Settings"), IDOK) == IDOK)
				{
					if (resetFilters)
						ResetFilters();

					if (resetGames)
						ResetAllGameOptions();

					if (resetDefaults)
						ResetGameDefaults();

					// This is the only case we need to exit and restart for.
					if (resetUI)
					{
						ResetGUI();
						EndDialog(hDlg, 1);
						return true;
					} else {
						EndDialog(hDlg, 0);
						return true;
					}
				} else {
					// Give the user a chance to change what they want to reset.
					break;
				}
			}
		// Nothing was selected but OK, just fall through
		case IDCANCEL :
			EndDialog(hDlg, 0);
			return true;
		}
		break;
	}
	return 0;
}

INT_PTR CALLBACK InterfaceDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CHOOSECOLOR cc;
	COLORREF choice_colors[16];
	TCHAR tmp[4];
	int i = 0;
	BOOL bRedrawList = false;
	int nCurSelection = 0;
	int nHistoryTab = 0;
	int nPatternCount = 0;
	int value = 0;

	switch (Msg)
	{
	case WM_INITDIALOG:
		Button_SetCheck(GetDlgItem(hDlg,IDC_START_GAME_CHECK),GetGameCheck());
		Button_SetCheck(GetDlgItem(hDlg,IDC_JOY_GUI),GetJoyGUI());
		Button_SetCheck(GetDlgItem(hDlg,IDC_KEY_GUI),GetKeyGUI());
		Button_SetCheck(GetDlgItem(hDlg,IDC_OVERRIDE_REDX),GetOverrideRedX());
		Button_SetCheck(GetDlgItem(hDlg,IDC_HIDE_MOUSE),GetHideMouseOnStartup());

		// Get the current value of the control
		SendDlgItemMessage(hDlg, IDC_CYCLETIMESEC, TBM_SETRANGE, (WPARAM)false, (LPARAM)MAKELONG(0, 60)); /* [0, 60] */
		value = GetCycleScreenshot();
		SendDlgItemMessage(hDlg,IDC_CYCLETIMESEC, TBM_SETPOS, true, value);
		_itot(value,tmp,10);
		SendDlgItemMessage(hDlg,IDC_CYCLETIMESECTXT,WM_SETTEXT,0, (WPARAM)tmp);

		Button_SetCheck(GetDlgItem(hDlg,IDC_STRETCH_SCREENSHOT_LARGER), GetStretchScreenShotLarger());
		Button_SetCheck(GetDlgItem(hDlg,IDC_FILTER_INHERIT), GetFilterInherit());
		Button_SetCheck(GetDlgItem(hDlg,IDC_NOOFFSET_CLONES), GetOffsetClones());

		for (int i = 0; i < NUMHISTORYTAB; i++)
		{
			(void)ComboBox_InsertString(GetDlgItem(hDlg, IDC_HISTORY_TAB), i, g_ComboBoxHistoryTab[i].m_pText);
			(void)ComboBox_SetItemData(GetDlgItem(hDlg, IDC_HISTORY_TAB), i, g_ComboBoxHistoryTab[i].m_pData);
		}

		if (GetHistoryTab() < MAX_TAB_TYPES)
			(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_HISTORY_TAB), GetHistoryTab());
		else
			(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_HISTORY_TAB), GetHistoryTab()-TAB_SUBTRACT);

		(void)ComboBox_AddString(GetDlgItem(hDlg, IDC_SNAPNAME), TEXT("Gamename"));
		(void)ComboBox_SetItemData(GetDlgItem(hDlg, IDC_SNAPNAME), nPatternCount++, "%g");
		(void)ComboBox_AddString(GetDlgItem(hDlg, IDC_SNAPNAME), TEXT("Gamename + Increment"));
		(void)ComboBox_SetItemData(GetDlgItem(hDlg, IDC_SNAPNAME), nPatternCount++, "%g%i");
		(void)ComboBox_AddString(GetDlgItem(hDlg, IDC_SNAPNAME), TEXT("Gamename/Gamename"));
		(void)ComboBox_SetItemData(GetDlgItem(hDlg, IDC_SNAPNAME), nPatternCount++, "%g/%g");
		(void)ComboBox_AddString(GetDlgItem(hDlg, IDC_SNAPNAME), TEXT("Gamename/Gamename + Increment"));
		(void)ComboBox_SetItemData(GetDlgItem(hDlg, IDC_SNAPNAME), nPatternCount++, "%g/%g%i");
		(void)ComboBox_AddString(GetDlgItem(hDlg, IDC_SNAPNAME), TEXT("Gamename/Increment"));
		(void)ComboBox_SetItemData(GetDlgItem(hDlg, IDC_SNAPNAME), nPatternCount, "%g/%i");
		//Default to this setting
		(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_SNAPNAME), nPatternCount++);

		{
			const char* snapname = GetSnapName();
			if (core_stricmp(snapname,"%g" )==0)
				(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_SNAPNAME), 0);
			else
			if (core_stricmp(snapname,"%g%i" )==0)
				(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_SNAPNAME), 1);
			else
			if (core_stricmp(snapname,"%g/%g" )==0)
				(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_SNAPNAME), 2);
			else
			if (core_stricmp(snapname,"%g/%g%i" )==0)
				(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_SNAPNAME), 3);
			else
			if (core_stricmp(snapname,"%g/%i" )==0)
				(void)ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_SNAPNAME), 4);
		}

		SendDlgItemMessage(hDlg, IDC_SCREENSHOT_BORDERSIZE, TBM_SETRANGE, (WPARAM)false, (LPARAM)MAKELONG(0, 100)); /* [0, 100] */
		value = GetScreenshotBorderSize();
		SendDlgItemMessage(hDlg,IDC_SCREENSHOT_BORDERSIZE, TBM_SETPOS, true, value);
		_itot(value,tmp,10);
		SendDlgItemMessage(hDlg,IDC_SCREENSHOT_BORDERSIZETXT,WM_SETTEXT,0, (WPARAM)tmp);

		//return true;
		break;

	case WM_HELP:
		/* User clicked the ? from the upper right on a control */
		HelpFunction((HWND)((LPHELPINFO)lParam)->hItemHandle, MAMEUICONTEXTHELP, HH_TP_HELP_WM_HELP, GetHelpIDs());
		break;

	case WM_CONTEXTMENU:
		HelpFunction((HWND)wParam, MAMEUICONTEXTHELP, HH_TP_HELP_CONTEXTMENU, GetHelpIDs());
		break;
	case WM_HSCROLL:
		HANDLE_WM_HSCROLL(hDlg, wParam, lParam, OnHScroll);
		break;
	case WM_COMMAND :
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDC_SCREENSHOT_BORDERCOLOR:
		{
			for (i=0;i<16;i++)
				choice_colors[i] = GetCustomColor(i);

			cc.lStructSize = sizeof(CHOOSECOLOR);
			cc.hwndOwner   = hDlg;
			cc.rgbResult   = GetScreenshotBorderColor();
			cc.lpCustColors = choice_colors;
			cc.Flags       = CC_ANYCOLOR | CC_RGBINIT | CC_SOLIDCOLOR;
			if (!ChooseColor(&cc))
				return true;
			for (i=0; i<16; i++)
				SetCustomColor(i,choice_colors[i]);
			SetScreenshotBorderColor(cc.rgbResult);
			UpdateScreenShot();
			return true;
		}
		case IDOK :
		{
			BOOL checked = false;

			SetGameCheck(Button_GetCheck(GetDlgItem(hDlg, IDC_START_GAME_CHECK)));
			SetJoyGUI(Button_GetCheck(GetDlgItem(hDlg, IDC_JOY_GUI)));
			SetKeyGUI(Button_GetCheck(GetDlgItem(hDlg, IDC_KEY_GUI)));
			SetOverrideRedX(Button_GetCheck(GetDlgItem(hDlg, IDC_OVERRIDE_REDX)));
			SetHideMouseOnStartup(Button_GetCheck(GetDlgItem(hDlg,IDC_HIDE_MOUSE)));

			if( Button_GetCheck(GetDlgItem(hDlg,IDC_RESET_PLAYSTATS ) ) )
			{
				ResetPlayCount( -1 );
				ResetPlayTime( -1 );
				bRedrawList = true;
			}
			value = SendDlgItemMessage(hDlg,IDC_CYCLETIMESEC, TBM_GETPOS, 0, 0);
			if( GetCycleScreenshot() != value )
			{
				SetCycleScreenshot(value);
			}
			value = SendDlgItemMessage(hDlg,IDC_SCREENSHOT_BORDERSIZE, TBM_GETPOS, 0, 0);
			if( GetScreenshotBorderSize() != value )
			{
				SetScreenshotBorderSize(value);
				UpdateScreenShot();
			}
			value = SendDlgItemMessage(hDlg,IDC_HIGH_PRIORITY, TBM_GETPOS, 0, 0);
			checked = Button_GetCheck(GetDlgItem(hDlg,IDC_STRETCH_SCREENSHOT_LARGER));
			if (checked != GetStretchScreenShotLarger())
			{
				SetStretchScreenShotLarger(checked);
				UpdateScreenShot();
			}
			checked = Button_GetCheck(GetDlgItem(hDlg,IDC_FILTER_INHERIT));
			if (checked != GetFilterInherit())
			{
				SetFilterInherit(checked);
				// LineUpIcons does just a ResetListView(), which is what we want here
				PostMessage(GetMainWindow(),WM_COMMAND, MAKEWPARAM(ID_VIEW_LINEUPICONS, false),(LPARAM)NULL);
			}
			checked = Button_GetCheck(GetDlgItem(hDlg,IDC_NOOFFSET_CLONES));
			if (checked != GetOffsetClones())
			{
				SetOffsetClones(checked);
				// LineUpIcons does just a ResetListView(), which is what we want here
				PostMessage(GetMainWindow(),WM_COMMAND, MAKEWPARAM(ID_VIEW_LINEUPICONS, false),(LPARAM)NULL);
			}
			nCurSelection = ComboBox_GetCurSel(GetDlgItem(hDlg,IDC_SNAPNAME));
			if (nCurSelection != CB_ERR) {
				const char* snapname_selection = (const char*)ComboBox_GetItemData(GetDlgItem(hDlg,IDC_SNAPNAME), nCurSelection);
				if (snapname_selection) {
					SetSnapName(snapname_selection);
				}
			}
			EndDialog(hDlg, 0);

			nCurSelection = ComboBox_GetCurSel(GetDlgItem(hDlg,IDC_HISTORY_TAB));
			if (nCurSelection != CB_ERR)
				nHistoryTab = ComboBox_GetItemData(GetDlgItem(hDlg,IDC_HISTORY_TAB), nCurSelection);
			EndDialog(hDlg, 0);
			if( GetHistoryTab() != nHistoryTab )
			{
				SetHistoryTab(nHistoryTab, true);
				ResizePickerControls(GetMainWindow());
				UpdateScreenShot();
			}
			if( bRedrawList )
			{
				UpdateListView();
			}
			return true;
		}
		case IDCANCEL :
			EndDialog(hDlg, 0);
			return true;
		}
		break;
	}
	return 0;
}

INT_PTR CALLBACK FilterDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static DWORD dwFilters;
	static DWORD dwpFilters;
	static LPCFOLDERDATA lpFilterRecord;
	string strText;
	int i = 0;

	switch (Msg)
	{
	case WM_INITDIALOG:
	{
		LPTREEFOLDER folder = GetCurrentFolder();
		LPTREEFOLDER lpParent = NULL;
		LPCFILTER_ITEM g_lpFilterList = GetFilterList();

		dwFilters = 0;

		if (folder)
		{
			char tmp[80];

			win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_EDIT), g_FilterText.c_str());
			Edit_SetSel(GetDlgItem(hDlg, IDC_FILTER_EDIT), 0, -1);
			// Mask out non filter flags
			dwFilters = folder->m_dwFlags & F_MASK;
			// Display current folder name in dialog titlebar
			snprintf(tmp,ARRAY_LENGTH(tmp),"Filters for %s Folder",folder->m_lpTitle);
			win_set_window_text_utf8(hDlg, tmp);
			if ( GetFilterInherit() )
			{
				BOOL bShowExplanation = false;
				lpParent = GetFolder( folder->m_nParent );
				if( lpParent )
				{
					/* Check the Parent Filters and inherit them on child,
					 * No need to promote all games to parent folder, works as is */
					dwpFilters = lpParent->m_dwFlags & F_MASK;
					/*Check all possible Filters if inherited solely from parent, e.g. not being set explicitly on our folder*/
					if( (dwpFilters & F_CLONES) && !(dwFilters & F_CLONES) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_CLONES)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_CLONES), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_NONWORKING) && !(dwFilters & F_NONWORKING) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_NONWORKING)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_NONWORKING), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_UNAVAILABLE) && !(dwFilters & F_UNAVAILABLE) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_UNAVAILABLE)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_UNAVAILABLE), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_VECTOR) && !(dwFilters & F_VECTOR) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_VECTOR)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_VECTOR), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_RASTER) && !(dwFilters & F_RASTER) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_RASTER)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_RASTER), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_ORIGINALS) && !(dwFilters & F_ORIGINALS) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_ORIGINALS)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_ORIGINALS), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_WORKING) && !(dwFilters & F_WORKING) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_WORKING)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_WORKING), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_AVAILABLE) && !(dwFilters & F_AVAILABLE) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_AVAILABLE)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_AVAILABLE), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_HORIZONTAL) && !(dwFilters & F_HORIZONTAL) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_HORIZONTAL)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_HORIZONTAL), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_VERTICAL) && !(dwFilters & F_VERTICAL) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_VERTICAL)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_VERTICAL), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_ARCADE) && !(dwFilters & F_ARCADE) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_ARCADE)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_ARCADE), strText.c_str());
						bShowExplanation = true;
					}
					if( (dwpFilters & F_MESS) && !(dwFilters & F_MESS) )
					{
						/*Add a Specifier to the Checkbox to show it was inherited from the parent*/
						strText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_MESS)).append(" (*)");
						win_set_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_MESS), strText.c_str());
						bShowExplanation = true;
					}
					/*Do not or in the Values of the parent, so that the values of the folder still can be set*/
					//dwFilters |= dwpFilters;
				}
				if( ! bShowExplanation )
				{
					ShowWindow(GetDlgItem(hDlg, IDC_INHERITED), false );
				}
			}
			else
				ShowWindow(GetDlgItem(hDlg, IDC_INHERITED), false );

			// Find the matching filter record if it exists
			lpFilterRecord = FindFilter(folder->m_nFolderId);

			// initialize and disable appropriate controls
			for (i = 0; g_lpFilterList[i].m_dwFilterType; i++)
				DisableFilterControls(hDlg, lpFilterRecord, &g_lpFilterList[i], dwFilters);
		}
		SetFocus(GetDlgItem(hDlg, IDC_FILTER_EDIT));
		return false;
	}
	case WM_HELP:
		// User clicked the ? from the upper right on a control
		HelpFunction((HWND)((LPHELPINFO)lParam)->hItemHandle, MAMEUICONTEXTHELP,
			 HH_TP_HELP_WM_HELP, GetHelpIDs());
		break;

	case WM_CONTEXTMENU:
		HelpFunction((HWND)wParam, MAMEUICONTEXTHELP, HH_TP_HELP_CONTEXTMENU, GetHelpIDs());
		break;

	case WM_COMMAND:
	{
		WORD wID = GET_WM_COMMAND_ID(wParam, lParam);
		WORD wNotifyCode = GET_WM_COMMAND_CMD(wParam, lParam);
		LPTREEFOLDER folder = GetCurrentFolder();
		LPCFILTER_ITEM g_lpFilterList = GetFilterList();

		switch (wID)
		{
		case IDOK:
			dwFilters = 0;

			g_FilterText = win_get_window_text_utf8(GetDlgItem(hDlg, IDC_FILTER_EDIT));

			// see which buttons are checked
			for (i = 0; g_lpFilterList[i].m_dwFilterType; i++)
				if (Button_GetCheck(GetDlgItem(hDlg, g_lpFilterList[i].m_dwCtrlID)))
					dwFilters |= g_lpFilterList[i].m_dwFilterType;

			// Mask out invalid filters
			dwFilters = ValidateFilters(lpFilterRecord, dwFilters);

			// Keep non filter flags
			folder->m_dwFlags &= ~F_MASK;

			// put in the set filters
			folder->m_dwFlags |= dwFilters;

			EndDialog(hDlg, 1);
			return true;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			return true;

		default:
			// Handle unchecking mutually exclusive filters
			if (wNotifyCode == BN_CLICKED)
				EnableFilterExclusions(hDlg, wID);
		}
	}
	break;
	}
	return 0;
}

INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
		{
			HBITMAP hBmp;
			hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ABOUT), IMAGE_BITMAP, 0, 0, LR_SHARED);
			SendDlgItemMessage(hDlg, IDC_ABOUT, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBmp);
			win_set_window_text_utf8(GetDlgItem(hDlg, IDC_VERSION), GetVersionString());
		}
		return 1;

	case WM_COMMAND:
		EndDialog(hDlg, 0);
		return 1;
	}
	return 0;
}

INT_PTR CALLBACK AddCustomFileDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static LPTREEFOLDER default_selection = NULL;
	static int driver_index = 0;
	BOOL res = 0;

	switch (Msg)
	{
	case WM_INITDIALOG:
	{
		TREEFOLDER **folders;
		int num_folders = 0;
		int i = 0;
		TVINSERTSTRUCT tvis;
		TVITEM tvi;
		BOOL first_entry = true;
		HIMAGELIST treeview_icons = GetTreeViewIconList();

		// current game passed in using DialogBoxParam()
		driver_index = lParam;

		(void)TreeView_SetImageList(GetDlgItem(hDlg,IDC_CUSTOM_TREE), treeview_icons, LVSIL_NORMAL);

		GetFolders(&folders,&num_folders);

		// should add "New..."

		// insert custom folders into our tree view
		for (i=0;i<num_folders;i++)
		{
			if (folders[i]->m_dwFlags & F_CUSTOM)
			{
				HTREEITEM hti;
				int jj = 0;

				if (folders[i]->m_nParent == -1)
				{
					memset(&tvi, '\0', sizeof(tvi));
					tvis.hParent = TVI_ROOT;
					tvis.hInsertAfter = TVI_SORT;
					tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
					tvi.pszText = folders[i]->m_lptTitle;
					tvi.lParam = (LPARAM)folders[i];
					tvi.iImage = GetTreeViewIconIndex(folders[i]->m_nIconId);
					tvi.iSelectedImage = 0;
#if !defined(NONAMELESSUNION)
					tvis.item = tvi;
#else
					tvis.DUMMYUNIONNAME.item = tvi;
#endif

					hti = TreeView_InsertItem(GetDlgItem(hDlg,IDC_CUSTOM_TREE),&tvis);

					/* look for children of this custom folder */
					for (jj=0; jj<num_folders; jj++)
					{
						if (folders[jj]->m_nParent == i)
						{
							HTREEITEM hti_child;
							tvis.hParent = hti;
							tvis.hInsertAfter = TVI_SORT;
							tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
							tvi.pszText = folders[jj]->m_lptTitle;
							tvi.lParam = (LPARAM)folders[jj];
							tvi.iImage = GetTreeViewIconIndex(folders[jj]->m_nIconId);
							tvi.iSelectedImage = 0;
#if !defined(NONAMELESSUNION)
							tvis.item = tvi;
#else
							tvis.DUMMYUNIONNAME.item = tvi;
#endif
							hti_child = TreeView_InsertItem(GetDlgItem(hDlg,IDC_CUSTOM_TREE),&tvis);
							if (folders[jj] == default_selection)
								res = TreeView_SelectItem(GetDlgItem(hDlg,IDC_CUSTOM_TREE),hti_child);
						}
					}

					/*TreeView_Expand(GetDlgItem(hDlg,IDC_CUSTOM_TREE),hti,TVE_EXPAND);*/
					if (first_entry || folders[i] == default_selection)
					{
						res = TreeView_SelectItem(GetDlgItem(hDlg,IDC_CUSTOM_TREE),hti);
						first_entry = false;
					}
				}
			}
		}

		win_set_window_text_utf8(GetDlgItem(hDlg,IDC_CUSTOMFILE_GAME), ModifyThe(driver_list::driver(driver_index).type.fullname()));

		res++;
		return true;
	}
	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			{
				TVITEM tvi;
				tvi.hItem = TreeView_GetSelection(GetDlgItem(hDlg,IDC_CUSTOM_TREE));
				tvi.mask = TVIF_PARAM;
				if (TreeView_GetItem(GetDlgItem(hDlg,IDC_CUSTOM_TREE),&tvi) == true)
				{
					/* should look for New... */
					default_selection = (LPTREEFOLDER)tvi.lParam; /* start here next time */
					AddToCustomFolder((LPTREEFOLDER)tvi.lParam,driver_index);
				}

				EndDialog(hDlg, 0);
				return true;
			}
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return true;

		}
		break;
	}
	return 0;
}

INT_PTR CALLBACK DirectXDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HWND hEdit;

	const char *directx_help = MAMEUINAME " requires DirectX version 9 or later.\r\n";

	switch (Msg)
	{
	case WM_INITDIALOG:
		hEdit = GetDlgItem(hDlg, IDC_DIRECTX_HELP);
		Edit_SetSel(hEdit, Edit_GetTextLength(hEdit), Edit_GetTextLength(hEdit));
		Edit_ReplaceSel(hEdit, directx_help);
		return 1;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDB_WEB_PAGE)
			ShellExecute(GetMainWindow(), NULL, TEXT("http://www.microsoft.com/directx"), NULL, NULL, SW_SHOWNORMAL);

		if (LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDB_WEB_PAGE)
			EndDialog(hDlg, 0);
		return 1;
	}
	return 0;
}

/***************************************************************************
    private functions
 ***************************************************************************/

static void DisableFilterControls(HWND hWnd, LPCFOLDERDATA lpFilterRecord, LPCFILTER_ITEM lpFilterItem, DWORD dwFlags)
{
	HWND hWndCtrl = GetDlgItem(hWnd, lpFilterItem->m_dwCtrlID);
	DWORD dwFilterType = lpFilterItem->m_dwFilterType;

	/* Check the appropriate control */
	if (dwFilterType & dwFlags)
		Button_SetCheck(hWndCtrl, MF_CHECKED);

	/* No special rules for this folder? */
	if (!lpFilterRecord)
		return;

	/* If this is an excluded filter */
	if (lpFilterRecord->m_dwUnset & dwFilterType)
	{
		/* uncheck it and disable the control */
		Button_SetCheck(hWndCtrl, MF_UNCHECKED);
		EnableWindow(hWndCtrl, false);
	}

	/* If this is an implied filter, check it and disable the control */
	if (lpFilterRecord->m_dwSet & dwFilterType)
	{
		Button_SetCheck(hWndCtrl, MF_CHECKED);
		EnableWindow(hWndCtrl, false);
	}
}

// Handle disabling mutually exclusive controls
static void EnableFilterExclusions(HWND hWnd, DWORD dwCtrlID)
{
	int i;

	for (i = 0; i < NUM_EXCLUSIONS; i++)
	{
		// is this control in the list?
		if (filterExclusion[i] == dwCtrlID)
		{
			// found the control id
			break;
		}
	}

	// if the control was found
	if (i < NUM_EXCLUSIONS)
	{
		DWORD id;
		// find the opposing control id
		if (i % 2)
			id = filterExclusion[i - 1];
		else
			id = filterExclusion[i + 1];

		// Uncheck the other control
		Button_SetCheck(GetDlgItem(hWnd, id), MF_UNCHECKED);
	}
}

// Validate filter setting, mask out inappropriate filters for this folder
static DWORD ValidateFilters(LPCFOLDERDATA lpFilterRecord, DWORD dwFlags)
{
	DWORD dwFilters = 0;

	if (lpFilterRecord != (LPFOLDERDATA)0)
	{
		// Mask out implied and excluded filters
		dwFilters = lpFilterRecord->m_dwSet | lpFilterRecord->m_dwUnset;
		return dwFlags & ~dwFilters;
	}

	// No special cases - all filters apply
	return dwFlags;
}

static void OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	int value = 0;
	TCHAR tmp[4];
	if (hwndCtl == GetDlgItem(hwnd, IDC_CYCLETIMESEC))
	{
		value = SendDlgItemMessage(hwnd,IDC_CYCLETIMESEC, TBM_GETPOS, 0, 0);
		_itot(value,tmp,10);
		SendDlgItemMessage(hwnd,IDC_CYCLETIMESECTXT,WM_SETTEXT,0, (WPARAM)tmp);
	}
	else
	if (hwndCtl == GetDlgItem(hwnd, IDC_SCREENSHOT_BORDERSIZE))
	{
		value = SendDlgItemMessage(hwnd,IDC_SCREENSHOT_BORDERSIZE, TBM_GETPOS, 0, 0);
		_itot(value,tmp,10);
		SendDlgItemMessage(hwnd,IDC_SCREENSHOT_BORDERSIZETXT,WM_SETTEXT,0, (WPARAM)tmp);
	}
}
