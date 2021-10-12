using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;

[System.Serializable]
public class LevelElement
{
	public string m_Character;
	public GameObject m_Prefab;
}


public class LevelBuilder : MonoBehaviour {
	public int m_CurrentLevel;
	public int MaxCout;
	public List<LevelElement> m_LevelElements;
	private Level m_Level;

	GameObject GetPrefab(char c)
	{
		LevelElement levelElement = m_LevelElements.Find(le = > le.m_Character == c.ToString());
		if (levelElement != null)
		{
			return levelElement.m_Prefab;
		}
		else
		{
			return null;
		}
	}

	public void NextLevel()
	{
		m_CurrentLevel++;
		if (m_CurrentLevel > MaxCout) //GetComponent<Levels>().m_Levels.Count)
		{
			m_CurrentLevel = -1;
		}
	}

	public bool Build()
	{

		//if (m_CurrentLevel==-1)
		//  {
		//      return false;
		//  };
		try
		{
			m_Level = GetComponent<Levels>().m_Levels[m_CurrentLevel];
		}
		catch
		{
			return false;
		};
		//m_Level = GetComponent<Levels>().m_Levels[m_CurrentLevel];
		int startx = -m_Level.Widht / 2;
		int x = startx;
		int y = -m_Level.Height / 2;
		foreach(var row in m_Level.m_Rows)
		{
			foreach(var ch in row)
			{
				Debug.Log(ch);
				GameObject prefab = GetPrefab(ch);
				if (prefab)
				{
					Debug.Log(prefab.name);
					Instantiate(prefab, new Vector3(x, y, 0), Quaternion.identity);
				}
				x++;
			}
			y++;
			x = startx;
		}
		return true;


	}

}
