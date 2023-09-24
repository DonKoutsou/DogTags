modded class SCR_InventoryMenuUI : UIInfo
{
	string m_sCharName;
	override void ShowItemInfo( string sName = "", string sDescr = "", float sWeight = 0.0, SCR_InventoryUIInfo uiInfo = null )
	{
		if ( !m_pItemInfo )
		{
			//Widget parent = m_widget.FindAnyWidget( "SoldierInfo" );
			Widget infoWidget = GetGame().GetWorkspace().CreateWidgets(ITEM_INFO, m_widget);
			if ( !infoWidget )
				return;

			infoWidget.AddHandler( new SCR_InventoryItemInfoUI() );
			m_pItemInfo = SCR_InventoryItemInfoUI.Cast( infoWidget.FindHandler( SCR_InventoryItemInfoUI ) );
		}

		if( !m_pItemInfo )
			return;

		Widget w = WidgetManager.GetWidgetUnderCursor();
		if (!w)
		{
			w = m_pFocusedSlotUI.GetButtonWidget();
		}

		m_pItemInfo.Show( 0.6, w, m_bIsUsingGamepad );
		m_pItemInfo.SetName( sName );
		m_pItemInfo.SetDescription( sDescr );
		m_pItemInfo.SetCharName(m_sCharName);
		m_pItemInfo.SetWeight( sWeight );
		if (uiInfo && uiInfo.IsIconVisible())
			m_pItemInfo.SetIcon(uiInfo.GetIconPath(), uiInfo.GetIconColor());

		int iMouseX, iMouseY;

		float x, y;
		w.GetScreenPos(x, y);

		float width, height;
		w.GetScreenSize(width, height);

		float screenSizeX, screenSizeY;
		GetGame().GetWorkspace().GetScreenSize(screenSizeX, screenSizeY);

		float infoWidth, infoHeight;
		m_pItemInfo.GetInfoWidget().GetScreenSize(infoWidth, infoHeight);

		iMouseX = x;
		iMouseY = y + height;
		if (x + infoWidth > screenSizeX)
			iMouseX = screenSizeX - infoWidth - width / 2; // offset info if it would go outside of the screen

		m_pItemInfo.Move( GetGame().GetWorkspace().DPIUnscale( iMouseX ), GetGame().GetWorkspace().DPIUnscale( iMouseY ) );
	}
	override protected void SetFocusedSlotEffects()
	{
		if( !m_pFocusedSlotUI )
		{
			if( m_wProgressBarWeightItem )
				m_wProgressBarWeightItem.SetCurrent( 0.0 );
			return;
		}

		//show info about the item
		InventoryItemComponent invItemComp = m_pFocusedSlotUI.GetInventoryItemComponent();
		if ( !invItemComp )
			return;
		auto attribs = SCR_ItemAttributeCollection.Cast( invItemComp.GetAttributes() );

		if ( !attribs )
			return;
		UIInfo itemInfo = attribs.GetUIInfo();
		DogTagEntity tag = DogTagEntity.Cast(invItemComp.GetOwner());
		if(tag)
		{
			tag.GetCname(m_sCharName);
			m_sCharName = "TagOwner: " + m_sCharName
		}
		if ( !itemInfo )
			HideItemInfo();
		else
		{
			SCR_InventoryUIInfo inventoryInfo = SCR_InventoryUIInfo.Cast(itemInfo);
			
			if (inventoryInfo)
				ShowItemInfo( inventoryInfo.GetInventoryItemName(invItemComp), inventoryInfo.GetInventoryItemDescription(invItemComp), invItemComp.GetTotalWeight(), inventoryInfo);
			else 
				ShowItemInfo( itemInfo.GetName(), itemInfo.GetDescription(), invItemComp.GetTotalWeight(), null);
		}
	
		//show the weight on the progressbar
		//TODO: overlap or add on the end, depending on if the item is already in the storage or is going to be added
		if( m_wProgressBarWeightItem )
		{
			float weight = invItemComp.GetTotalWeight();
			m_wProgressBarWeightItem.SetCurrent( weight );
		};

		NavigationBarUpdate();
	}
}
modded class SCR_InventoryItemInfoUI
{
	private TextWidget						m_wTextCharName;
	
//------------------------------------------------------------------------------------------------
	void SetCharName( string name )
	{
		if( name != "" )
		{
			m_wTextCharName.SetEnabled( true );
			m_wTextCharName.SetVisible( true );
			m_wTextCharName.SetText( name );
		}
		else
		{
			m_wTextCharName.SetEnabled( false );
			m_wTextCharName.SetVisible( false );
		}
	}
	override void HandlerAttached( Widget w )
	{
		if( !w )
			return;
		super.HandlerAttached(w);
		m_wTextCharName		= TextWidget.Cast( w.FindAnyWidget( "ItemInfo_CharName" ) );
	}
}