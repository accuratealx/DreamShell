class TDreamServerShellCommand_DeletePlayerItem: TDreamServerShellCommand
{
	void TDreamServerShellCommand_DeletePlayerItem()
	{
		Name = "DeletePlayerItem";
		Description = "Delete player item";
		MinimalParamCount = 2;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: DeletePlayerItem [UserID] [ItemID]");
		result.Insert("Parameters:");
		result.Insert("  UserID - ID item from PlayerList");
		result.Insert("  ItemID - ID item from PlayerItems");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		//Найдем пользователя
		string id = data.Command.GetStrParamByIndex(0);
		PlayerBase player = GetPlayerByID(id);
		if (!player)
			result.Error = string.Format(ERROR_PLAYER_NOT_FOUND_FMT, id);
		else {
			//ID предмета
			int iid = data.Command.GetIntParamByIndex(1);
			
			GameInventory inv = player.GetInventory();
			if (inv)
			{
				//Получим полный список объектов
				array<EntityAI> items = new array<EntityAI>;
				inv.EnumerateInventory(InventoryTraversalType.INORDER, items);
				
				//Проверим диапазон
				if (iid < 0 || iid >= items.Count())
					result.Error = string.Format(ERROR_ITEM_NOT_FOUND_FMT, iid);
				else {
					EntityAI item = items.Get(iid);
					item.DeleteSave();
				}
			} else {
				result.Error = ERROR_CANT_GET_INVENTORY;
			}
		};
		
		return result;
	}
}