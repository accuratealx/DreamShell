class TDreamServerShellCommand_DeletePlayerItems: TDreamServerShellCommand
{
	void TDreamServerShellCommand_DeletePlayerItems()
	{
		Name = "DeletePlayerItems";
		Description = "Delete player items";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: DeletePlayerItems [PlayerID]");
		result.Insert("Parameters:");
		result.Insert("  PlayerID - ID player from PlayerList");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		string id = data.Command.GetStrParamByIndex(0);
		PlayerBase player = GetPlayerByID(id);
		if (!player)
			result.Error = string.Format(ERROR_PLAYER_NOT_FOUND_FMT, id);
		else {
			GameInventory inv = player.GetInventory();
			if (inv)
			{
				array<EntityAI> items = new array<EntityAI>();
				inv.EnumerateInventory(InventoryTraversalType.PREORDER, items);
				for (int i = 0; i < items.Count(); i++)
				{
					//Пропустим игрока
					EntityAI item = items.Get(i);
					if (item == player)
						continue;
					
					//Удалим предмет
					item.DeleteSafe();
				}
			} else
				result.Error = ERROR_CANT_GET_INVENTORY;
		};
		
		return result;
	}
}