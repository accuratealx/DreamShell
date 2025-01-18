PlayerBase GetPlayerByID(string id)
{
	PlayerBase result = null;
	
	array<Man> players = new array<Man>();
	GetGame().GetPlayers(players);
	foreach (auto p: players)
	{
		PlayerIdentity identity = p.GetIdentity();
		if (!identity)
			continue;
		
		if (id == identity.GetPlayerId().ToString())
		{
			result = PlayerBase.Cast(p);
			break;
		}
	}
		return result;
}


string BoolToString(bool val, string trueStr = "On", string falseStr = "Off")
{
	if (val)
		return trueStr;
	else
		return falseStr;
}
