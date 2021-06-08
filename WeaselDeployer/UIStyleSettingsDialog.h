#pragma once

#include "resource.h"
#include "UIStyleSettings.h"


class UIStyleSettingsDialog : public CDialogImpl<UIStyleSettingsDialog> {
public:
	enum { IDD = IDD_STYLE_SETTING };

	UIStyleSettingsDialog(UIStyleSettings* settings);
	~UIStyleSettingsDialog();

	static bool open(const std::wstring &path)
	{
		return (int)ShellExecuteW(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL) > 32;
	}

	static std::wstring install_dir()
	{
		WCHAR exe_path[MAX_PATH] = { 0 };
		GetModuleFileNameW(GetModuleHandle(NULL), exe_path, _countof(exe_path));
		std::wstring dir(exe_path);
		size_t pos = dir.find_last_of(L"\\");
		dir.resize(pos);
		return dir;
	}

protected:
	BEGIN_MSG_MAP(UIStyleSettingsDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDC_SELECT_FONT, OnOpenConfig)
		COMMAND_HANDLER(IDC_COLOR_SCHEME, LBN_SELCHANGE, OnColorSchemeSelChange)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnClose(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnOK(WORD, WORD code, HWND, BOOL&);
	LRESULT OnOpenConfig(WORD, WORD code, HWND, BOOL&);
	LRESULT OnColorSchemeSelChange(WORD, WORD, HWND, BOOL&);

	void Populate();
	void Preview(int index);

	UIStyleSettings* settings_;
	bool loaded_;
	std::vector<ColorSchemeInfo> preset_;

	CListBox color_schemes_;
	CStatic preview_;
	CImage image_;
	CButton select_font_;
};

