using System;

[System.Serializable]
public record JShopData : JBaseData
{
	public int index;
	public int shop_id;
	public int shop_price;
	public string shop_id_string;
}