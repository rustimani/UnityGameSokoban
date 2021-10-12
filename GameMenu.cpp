using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameMenu : MonoBehaviour {

	public GameObject m_ScoreButton;
	public GameObject m_StartButton;
	public GameObject m_ReturnButton;


	// Use this for initialization
	void Start() {

		m_ReturnButton.SetActive(false);
		Resources.UnloadUnusedAssets();
	}

	// Update is called once per frame
	void Update() {
		if (Input.GetKey(KeyCode.Escape))
		{
			if (m_ReturnButton.activeSelf)
			{
				SceneManager.LoadSceneAsync("Main_Menu", LoadSceneMode.Single);
			}
			else
			{
				Application.Quit();
				SceneManager.UnloadSceneAsync("Main_Menu");
			}

		}
	}

	public void StartGame()
	{
		SceneManager.LoadSceneAsync("MainScene");
	}

	public void ShowScores()  ///активация exit
	{
		m_ReturnButton.SetActive(true);
		m_ScoreButton.SetActive(false);
		m_StartButton.SetActive(false);
		Resources.UnloadUnusedAssets();
	}

	public void ToMain() //return
	{
		m_ReturnButton.SetActive(false);
		m_ScoreButton.SetActive(true);
		m_StartButton.SetActive(true);
		Resources.UnloadUnusedAssets();
	}

}
