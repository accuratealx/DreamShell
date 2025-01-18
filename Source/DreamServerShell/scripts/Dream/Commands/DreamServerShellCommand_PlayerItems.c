class TDreamServerShellCommand_PlayerItems: TDreamServerShellCommand
{
	void TDreamServerShellCommand_PlayerItems()
	{
		Name = "PlayerItems";
		Description = "Show player items";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: PLayerItems [ID]");
		result.Insert("Parameters:");
		result.Insert("  ID - Player id");
		return result;
	}
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		string id = data.Command.Parameters()[0];
		PlayerBase player = GetPlayerByID(id);
		if (!player)
			result.Error = string.Format("player id %1 not found", id);
		else {
			//Получим полный список объектов
			array<EntityAI> items = new array<EntityAI>;
			player.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, items);

			//Вывод
			result.Result.Insert(player.GetIdentity().GetName() + " inventory:");
			for (int i = 0; i < items.Count(); i++)
			{
				EntityAI item = items.Get(i);
				if (item.IsKindOf("SurvivorBase")) 
					continue;
				
				result.Result.Insert("  " + GetItemInfo(item));
			}
			int cnt = items.Count() - 1;
			result.Result.Insert("count: " + cnt);
		};
		
		return result;
	}
	
	private string GetItemInfo(EntityAI item)
	{
		string name = item.ClassName();
		string health = GetItemHealth(item);
		string quant = GetQuantity(item);
		return string.Format("%1 (%2, %3)", name, health, quant);
	}
	
	private string GetQuantity(EntityAI item)
	{
		if (item.HasQuantity())
			return  item.GetQuantity().ToString() + "/" + item.GetQuantityMax().ToString();
		return "1/1";
	}
	
	private string GetItemHealth(EntityAI item)
	{
		float h = item.GetHealth01("", "");
		if (h == GameConstants.DAMAGE_PRISTINE_VALUE)
			return "Pristine";
		if (h < GameConstants.DAMAGE_PRISTINE_VALUE && h >= GameConstants.DAMAGE_WORN_VALUE)
			return "Worn";
		if (h < GameConstants.DAMAGE_WORN_VALUE && h >= GameConstants.DAMAGE_DAMAGED_VALUE)
			return "Damage";
		if (h < GameConstants.DAMAGE_DAMAGED_VALUE && h >= GameConstants.DAMAGE_RUINED_VALUE)
			return "Badly";
		return "Ruined";
	}
}
