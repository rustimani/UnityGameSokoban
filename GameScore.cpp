using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;



public class GameScore : MonoBehaviour {

	public string filename;
	public Text text;

	public void Awake()
	{
		text = GetComponent<Text>();

	}
	public void ShowText()
	{
		string stt;
		TextAsset textAsset = (TextAsset)Resources.Load(filename);
		if (!textAsset)
		{
			Debug.Log("Score doesn't exist!");
			return;
		}
		else
		{
			Debug.Log("Import success!");
		}
		stt = textAsset.text;
		if (filename == "ScoresHard")
		{
			text.text = "Hard Mode:\n" + stt;
		}
		else
			text.text = "Easy Mode:\n" + stt;

	}

	public void CloseScore()
	{
		text.text = "";
	}

}
