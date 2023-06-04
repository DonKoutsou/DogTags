class DogTagEntityClass: GameEntityClass
{

}
class DogTagEntity: GameEntity
{
	private string charname;
	
	void GetCname(out string name)
	{
		name = charname;	
	}
	
	override event protected void EOnActivate(IEntity owner)
	{
		IEntity parent = owner.GetParent();
		if(parent && EntityUtils.IsPlayer(parent))
		{
			PlayerManager mngr = GetGame().GetPlayerManager();
			int pid = mngr.GetPlayerIdFromControlledEntity(parent);
			charname = mngr.GetPlayerName(pid);
		}
		parent = ChimeraCharacter.Cast(parent);
		if(parent)
		{
			SCR_CharacterIdentityComponent CharID = SCR_CharacterIdentityComponent.Cast(parent.FindComponent(SCR_CharacterIdentityComponent));
			//SCR_CharacterRankComponent RankC = SCR_CharacterRankComponent.Cast(parent.FindComponent(SCR_CharacterRankComponent));
			charname = CharID.GetIdentity().GetFullName();
		}
		
	};
}