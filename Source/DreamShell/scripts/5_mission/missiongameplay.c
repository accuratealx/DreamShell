modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		//Только на клиенте
		if (!GetGame().IsServer())
		{
			//Обработать кнопки только если не открыто меню
			UIScriptedMenu menu;
			menu = GetGame().GetUIManager().GetMenu();
			
			if (menu == null)
			{
				//Если действие открыть меню
				if (GetGame().GetInput().LocalPress("DreamShellOpenMenu"))
				{
					PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
					if (player)
						player.DreamShellMenuOpen();
				}
			}
		}
	}
	
	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		
		if (key == KeyCode.KC_ESCAPE)
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if (player)
				player.DreamShellMenuClose();
		}
	}
}