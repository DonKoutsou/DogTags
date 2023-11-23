[BaseContainerProps()]
class SCR_DogaTagInventoryItemHintUIInfo : SCR_InventoryItemHintUIInfo
{
	//------------------------------------------------------------------------------------------------
	override bool SetItemHintNameTo(InventoryItemComponent item, TextWidget textWidget)
	{
		if (!textWidget)
			return false;
		DogTagEntity Dogtag = DogTagEntity.Cast(item.GetOwner());
		string name;
		Dogtag.GetCname(name);
		Name = string.Format("Tag Owner: %1", name);
		textWidget.SetText(GetItemHintName(item));
		return true;
	}
}