using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class MyGameObject : MonoBehaviour
{
	private List<string> kkE; //Список строк Scores для легкого уровня
	private List<string> kkH; //Список строк Scores для сложного уровня
	public int ScoreNow; //Поле в котором записываются очки текущего уровня
	public int lvlNum; //номер уровня
	public string[] filename; //файлы assest\resourses
	public string[] dest; //промежуточные файлы для обновления scores

	// Use this for initialization
	void Start()
	{
		kkE = new List<string>();
		kkH = new List<string>();
		filename = new string[2];
		filename[0] = @"C:\\Users\Public\Documents\Unity Projects\BoxPusher\Assets\Resources\ScoresEasy.txt";

			filename[1] = @"C:\\Users\Public\Documents\Unity Projects\BoxPusher\Assets\Resources\ScoresHard.txt";
			dest = new string[2];
		dest[0] = @"C:\\Users\Public\Documents\Unity Projects\BoxPusher\scE.txt";
			dest[1] = @"C:\\Users\Public\Documents\Unity Projects\BoxPusher\scH.txt";
			try
		{
			using (StreamReader sr = new StreamReader(filename[0]))
			{
				using (StreamReader sr1 = new StreamReader(filename[1]))
				{
					for (int j = 0; j < 4; j++)
					{
						kkE.Add(sr.ReadLine()); kkH.Add(sr1.ReadLine());
					}
					sr.Close(); sr1.Close();
				}
			}
		}
		catch (System.Exception e)
		{
			Debug.Log(e.Message);
		}
		for (int i = 0; i < 2; i++)
		{
			if (File.Exists(dest[i])) File.Create(dest[i]);
		}
	}

	public void Save()
	{
		int i;
		if (lvlNum < 4)
		{
			i = 0;
			string[] del = kkE[lvlNum].Split(new string[]{ " " }, System.StringSplitOptions.None);
			int.TryParse(del[2], out i);
			if (ScoreNow < i && ScoreNow != 0)
			{
				kkE[lvlNum] = (lvlNum + 1).ToString() + " lvl " + ScoreNow.ToString();
			};
		}
		else
		{
			string[] del = kkH[lvlNum - 4].Split(new string[]{ " " }, System.StringSplitOptions.None);
			int.TryParse(del[2], out i);
			if (ScoreNow < i && ScoreNow != 0)
			{
				kkH[lvlNum - 4] = (lvlNum - 3).ToString() + " lvl " + ScoreNow.ToString();
			};

		}
	}

	public void Refresh()
	{
		try
		{
			using (StreamWriter sw = new StreamWriter(dest[0]))
			{
				using (StreamWriter sw1 = new StreamWriter(dest[1]))
				{
					for (int j = 0; j < 4; j++)
					{
						sw.WriteLine(kkE[j]);
						sw1.WriteLine(kkH[j]);
					}
					sw.Close(); sw1.Close();
				}
			}
			for (int i = 0; i < 2; i++)
			{
				if (File.Exists(filename[i])) File.Delete(filename[i]);
				File.Copy(dest[i], filename[i]);
				File.Delete(dest[i]);
			}
		}
		catch (System.Exception e)
		{
			Debug.Log(e.Message);
		}


	}
}







