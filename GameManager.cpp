using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class GameManager : MonoBehaviour {

	public LevelBuilder m_LevelBuilder; //сборщик уровней

	public GameObject m_NextButton;
	public GameObject m_ResetButton;
	public GameObject m_EasyButton;
	public GameObject m_HardButton;
	public GameObject m_UndoButton;
	public GameObject m_MenuButton;

	public MyGameObject my; //объект со скриптом для сохранения и обновления Scores

	public Text text;  // Текс подсчета очков
	public Vector2 save;  //вектор для сохранения координат для отмены хода

	private bool m_ReadyForInput;
	private Player m_Player;

	void Start()
	{
		m_NextButton.SetActive(false);
		m_ResetButton.SetActive(false);
		m_UndoButton.SetActive(false);
		m_MenuButton.SetActive(false);
	}

	private void Update()
	{

		Vector2 moveInput = new Vector2(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"));
		moveInput.Normalize();
		if (moveInput.sqrMagnitude > 0.5)
		{
			if (m_ReadyForInput)
			{
				m_ReadyForInput = false;
				if (m_Player.Move(moveInput))
				{
					save = moveInput;
					if (!IsLevelComplete())
						m_UndoButton.SetActive(true);
					my.ScoreNow++;
					//textUpdate(my.Score);
				};
				m_NextButton.SetActive(true);// IsLevelComplete());
				if (!IsLevelComplete())
					TextUpdate(my.ScoreNow);
				if (IsLevelComplete())
				{
					m_UndoButton.SetActive(false);
				};
			}
		}
		else
		{
			m_ReadyForInput = true;
		}
		if (Input.GetKey(KeyCode.Escape))
		{
			ExitMenu();

		}

	}

	//обновление очков
	public void TextUpdate(int num)
	{
		text.fontSize = 14;
		text.alignment = TextAnchor.LowerLeft;
		text.text = "Score: " + num.ToString();
	}

	//кнопка Main Menu
	public void ExitMenu()
	{
		my.Refresh();
		SceneManager.UnloadSceneAsync("MainScene");
		SceneManager.LoadSceneAsync("Main_Menu");
	}

	//легкий режим
	public void EasyMode()
	{
		m_LevelBuilder.m_CurrentLevel = 0;
		m_LevelBuilder.MaxCout = 3;
		text.text = "";
		ResetScene();
	}

	//сложный режим
	public void HardMode()
	{
		m_LevelBuilder.m_CurrentLevel = 4;
		m_LevelBuilder.MaxCout = 7;
		text.text = "";
		ResetScene();
	}

	//кнопка undo
	public void Undo()
	{
		Vector2 moveUndo = new Vector2();
		moveUndo.x = save.x;
		moveUndo.y = save.y;
		save.x = m_Player.transform.position.x;
		save.y = m_Player.transform.position.y;

		Box[] boxes = FindObjectsOfType<Box>();
		foreach(var box in boxes)
		{

			if (box.transform.position.x == save.x + moveUndo.x && box.transform.position.y == save.y + moveUndo.y)
			{
				if (box.m_OnCross)
				{
					box.GetComponent<SpriteRenderer>().color = Color.white;
				}
				moveUndo.x = -moveUndo.x; moveUndo.y = -moveUndo.y;
				m_Player.Move(moveUndo);
				m_UndoButton.SetActive(false);
				box.Move(moveUndo);
				my.ScoreNow--;
				TextUpdate(my.ScoreNow);
				return;
			};

		}
		moveUndo.x = -moveUndo.x; moveUndo.y = -moveUndo.y;
		m_Player.Move(moveUndo);
		m_UndoButton.SetActive(false);
		if (!IsLevelComplete())
		{
			my.ScoreNow--;
			TextUpdate(my.ScoreNow);
		}
	}

	//кнопка nextlvl
	public void NextLevel()
	{
		my.Save();
		m_NextButton.SetActive(false);
		m_UndoButton.SetActive(false);
		m_LevelBuilder.NextLevel();
		StartCoroutine(ResetSceneAsync());
	}

	//сброс сцены (reset)
	public void ResetScene()
	{
		my.ScoreNow = 0;
		m_ResetButton.SetActive(true);
		m_HardButton.SetActive(false);
		m_EasyButton.SetActive(false);
		m_NextButton.SetActive(false);
		m_MenuButton.SetActive(true);
		StartCoroutine(ResetSceneAsync());
	}

	//проверка того пройден ли уровень
	bool IsLevelComplete()
	{
		Box[] boxes = FindObjectsOfType<Box>();
		foreach(var box in boxes)
		{
			if (!box.m_OnCross) return false;
		}
		return true;
	}

	//завершение игрового процесса
	public void FinishGame()
	{
		SceneManager.SetActiveScene(SceneManager.GetSceneByName("MainScene"));
		m_ResetButton.SetActive(false);
		m_HardButton.SetActive(false);
		m_EasyButton.SetActive(false);
		m_NextButton.SetActive(false);
		m_UndoButton.SetActive(false);

	}

	//перезагрузка уровня
	IEnumerator ResetSceneAsync()
	{
		if (SceneManager.sceneCount > 1)
		{
			AsyncOperation asyncUnload = SceneManager.UnloadSceneAsync("lvl");
			while (!asyncUnload.isDone)
			{
				yield return null;
				Debug.Log("Unloading...");
			}
			Debug.Log("Done");
			Resources.UnloadUnusedAssets();
		}

		AsyncOperation asyncLoad = SceneManager.LoadSceneAsync("lvl", LoadSceneMode.Additive);
		while (!asyncLoad.isDone)
		{
			yield return null;
			Debug.Log("Loading...");
		}
		SceneManager.SetActiveScene(SceneManager.GetSceneByName("lvl"));
		if (m_LevelBuilder.Build())
		{
			m_Player = FindObjectOfType<Player>(); Debug.Log("Load complited!");
			my.lvlNum = m_LevelBuilder.m_CurrentLevel; my.ScoreNow = 0; TextUpdate(my.ScoreNow);
		}
		else
		{
			if (m_LevelBuilder.m_CurrentLevel == -1)
			{
				my.Refresh();
				text.fontSize = 50;
				text.alignment = TextAnchor.LowerCenter;
				text.text = "U WIN THE GAME";
			}
			else { text.fontSize = 50; text.alignment = TextAnchor.LowerCenter; text.text = "ERROR LOAD LEVELS!"; }
			FinishGame();
		}


	}
}
