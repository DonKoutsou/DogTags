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
	void SetCname(string name)
	{
		charname = name;
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

			PlayerManager mngr = GetGame().GetPlayerManager();
			int pid = mngr.GetPlayerIdFromControlledEntity(parent);
			if (pid == 0)
			{
				SCR_PossessingManagerComponent m_PossessingManager = SCR_PossessingManagerComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_PossessingManagerComponent));
				if (m_PossessingManager)
				{
					pid = m_PossessingManager.GetIdFromMainEntity(parent);	// in case this is a main entity of someone whos currently possessing, consider it that player
				}
			}
			else
			{
				charname = mngr.GetPlayerName(pid);
			}
			if (charname)
				return;
			parent = ChimeraCharacter.Cast(parent);
			if(parent)
			{
				SCR_CharacterIdentityComponent IdentityComponent = SCR_CharacterIdentityComponent.Cast(parent.FindComponent(SCR_CharacterIdentityComponent));
				SCR_CharacterRankComponent RankComponent = SCR_CharacterRankComponent.Cast(parent.FindComponent(SCR_CharacterRankComponent));
				if(IdentityComponent && RankComponent)
				{
					Identity ID = IdentityComponent.GetIdentity();
					if(ID)
					{
						charname = RankComponent.GetCharacterRankNameShort(parent) + " " + ID.GetFullName();
					}
				}
			}
		}
		if (charname)
		{
			ClearEventMask(EntityEvent.FRAME);
		}
	};
	void UpdateNameToPL()
	{
		
	}
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