using System;

[System.Serializable]
public record JUnitData : JBaseData
{
	public int index;
	public string unitName;
	public int unitHp;
}