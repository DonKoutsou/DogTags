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
	
	override event protected void EOnInit(IEntity owner)
	{
		SetEventMask(EntityEvent.FRAME);
	}
	override event protected void EOnFrame(IEntity owner, float timeSlice)
	{
		if(!charname)
		{
			IEntity parent = owner.GetParent();
			if(parent && EntityUtils.IsPlayer(parent))
			{
				PlayerManager mngr = GetGame().GetPlayerManager();
				int pid = mngr.GetPlayerIdFromControlledEntity(parent);
				charname = mngr.GetPlayerName(pid);
				return;
			}
			parent = ChimeraCharacter.Cast(parent);
			if(parent)
			{
				SCR_CharacterIdentityComponent CharID = SCR_CharacterIdentityComponent.Cast(parent.FindComponent(SCR_CharacterIdentityComponent));
				SCR_CharacterRankComponent RankC = SCR_CharacterRankComponent.Cast(parent.FindComponent(SCR_CharacterRankComponent));
				charname = RankC.GetCharacterRankName(parent) + " " + CharID.GetIdentity().GetName() + " " + CharID.GetIdentity().GetSurname();
			}
		}
		if (charname)
		{
			ClearEventMask(EntityEvent.FRAME);
		}
	};
}
class SP_DogtagPredicate : InventorySearchPredicate
{

	override protected bool IsMatch(BaseInventoryStorageComponent storage, IEntity item, array<GenericComponent> queriedComponents, array<BaseItemAttributeData> queriedAttributes)
	{
		DogTagEntity tag = DogTagEntity.Cast(item);
		if(tag)
		{
			return true;
		}
		return false;
	}
}
modded enum ECommonItemType
{
	DogTag
};