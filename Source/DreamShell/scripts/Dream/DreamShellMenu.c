const int DREAM_SHELL_MENU_ID = 103;

class TDreamShellMenu: UIScriptedMenu
{
	private PlayerBase FPlayer;

	private ImageWidget FBackground;
	private ButtonWidget FClose;
	private EditBoxWidget FShellCommand;
	private TextListboxWidget FShellLog;
	private ButtonWidget FCopyButton;
	
	private const string HOSTORY_FILE = "CommandHistory.txt";
	private string FSettingsDir;
	private ref TDreamShellCommandHistory FCommandHistory = new TDreamShellCommandHistory();

	void TDreamShellMenu(PlayerBase player)
	{
		m_id = DREAM_SHELL_MENU_ID;
		FPlayer = player;
		
		FSettingsDir = DreamShell_GetProfileDir() + "Dream/Shell/";
		DreamShell_ForceDirectories(FSettingsDir);
		
		LoadCommandHistory();
	}
	
	void ~TDreamShellMenu()
	{
		SaveCommandHistory();
	}
	
	//Переопределить этот метод для замены фоновой картинки
	string GetBackgroundImage()
	{
		return "DreamShell/DreamShell/gui/images/background.edds";
	}
	
	//Переопределить этот метод для замены формы
	string GetLayoutFile()
	{
		return "DreamShell/DreamShell/gui/layout/DreamShellMenu.layout";
	}
	
	void Show()
	{
		GetGame().GetUIManager().ShowScriptedMenu(this, null);
		g_Game.SetKeyboardHandle(this);
	}
	
	void Hide()
	{
		g_Game.SetKeyboardHandle(null);
		if (IsVisible())
			GetGame().GetUIManager().Back();
	}	
	
	private void LoadCommandHistory()
	{
		string fn = GetHistoryFileName();
		if (FileExist(fn))
		{
			string err = FCommandHistory.LoadFromFile(fn);
			if (err != "")
				DreamShell_LogEror(err, "DreamShellMenu");
		}
	}
	
	private void SaveCommandHistory()
	{
		string err = FCommandHistory.SaveToFile(GetHistoryFileName());
		if (err != "")
			DreamShell_LogEror(err, "DreamShellMenu");
	}
	
	private string GetHistoryFileName()
	{
		return FSettingsDir + HOSTORY_FILE;
	}
	
	override void OnShow()
	{
		LockControls();
		GetGame().GetInput().ChangeGameFocus(1);
		FocusCommandEdit();
	}
	
	override void OnHide()
	{
		GetGame().GetInput().ResetGameFocus();
		UnlockControls();
	}
	
	
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets(GetLayoutFile());
		
		FBackground = ImageWidget.Cast(layoutRoot.FindAnyWidget("BGImage"));
		FClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CaptionButtonClose"));
		FShellCommand = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ShellCommand"));
		FShellLog = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ShellLog"));
		FCopyButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CopyButton"));
		
		//Установить фоновую картинку
		string bgImage = GetBackgroundImage();
		FBackground.LoadImageFile(0, bgImage);
		
		ExecuteCommand("welcome", true);
		
		return layoutRoot;
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		switch (w)
		{
			case FClose:
				CloseClick();
			break;

			case FCopyButton:
				CopyClick();
			break;
						
			default:
				return super.OnClick(w, x, y, button);
			break;
		}
		return true;
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		if (w == FShellLog)
		{
			int idx = FShellLog.GetSelectedRow();
			string line = "";
			FShellLog.GetItemText(idx, 0, line);
			GetGame().CopyToClipboard(line);
			return true;
		} else
			return super.OnDoubleClick(w, x, y, button);
	}
	
	private void CloseClick()
	{
		if (FPlayer)
			FPlayer.DreamShellMenuClose();
	}
	
	private void CopyClick()
	{
		string result = "";
		
		for (int i = 0; i < FShellLog.GetNumItems(); i++)
		{
			string line;
			FShellLog.GetItemText(i, 0, line);
			result += line + "\r\n";
		}
		GetGame().CopyToClipboard(result);
	}
	
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		string s = "";
		switch (key)
		{
			case KeyCode.KC_RETURN:
				ExecuteCommand(GetCommand(), false);
				return true;
			break;

			case KeyCode.KC_UP:
				s = FCommandHistory.GetPrevious();
				if (s != "")
					SetCommand(s);
				return true;
			break;
			
			case KeyCode.KC_DOWN:
				s = FCommandHistory.GetNext();
				if (s != "")
					SetCommand(s);
				return true;
			break;
						
			default:
				return super.OnKeyDown(w, x, y, key);
			break;
		}
		
		return true;
	}
	
	private void SetCommand(string cmd = "")
	{
		FShellCommand.SetText(cmd);
	}
	
	private string GetCommand()
	{
		return FShellCommand.GetText();
	}

	private void AddStringToLog(string log)
	{
		FShellLog.AddItem(log, null, 0);
		FShellLog.EnsureVisible(FShellLog.GetNumItems() - 1);
	}
	
	private void ClearLog()
	{
		FShellLog.ClearItems();
	}
	
	private void FocusCommandEdit()
	{
		SetFocus(FShellCommand);
	}
	
	private void ExecuteCommand(string cmd, bool init = false)
	{
		cmd.Trim();
		if (cmd == "")
			return;
		
		//Сохранить историю
		if (!init)
			FCommandHistory.Add(cmd);
		
		//Отослать команду на сервер
		FPlayer.RPCSingleParam(RPC_DREAM_SHELL_SEND_COMMAND, new Param1<string>(cmd), true, FPlayer.GetIdentity());
		
		//Очистить журнал от предыдущей команды
		ClearLog();
		
		//Очистить строку ввода
		SetCommand();
		
		//Активировать строку ввода команды
		FocusCommandEdit();
	}
	
	//Прием ответов от сервера
	void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		switch (rpc_type)
		{
			case RPC_DREAM_SHELL_SEND_RESULT:
				Param1<string> prm = new Param1<string>("");
				if (ctx.Read(prm))
					AddStringToLog(prm.param1);
			break;
		}
	}
}