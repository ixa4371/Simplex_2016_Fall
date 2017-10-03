#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Israel Anthony - ixa4371@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));
	
	// Init the 46 meshes in the vector collection to create the image
	for (int i = 0; i < 46; i++)
	{
		MyMesh* mesh = new MyMesh();
		cubes.push_back(mesh);
	}

	// Generate the cubes for each of the meshes
	for (int i = 0; i < 46; i++)
	{
		cubes[i]->GenerateCube(1.0f, C_BLACK);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Calculate view and projection matricies
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	// Calculate the scale for the cubes (all the same size)
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(1.0f,1.0f,1.0f));

	// Calculate the translations of the cubes by row
	static float value = 0.0f;
	std::vector<matrix4> translations;
	
	for (int i = -5; i <= 5; i++) // row1
	{
		if (i == -3 || i == 3)
		{
			translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, 4.0f, -20.0f)));
		}
	}

	for (int i = -5; i <= 5; i++) // row2
	{
		if (i == -2 || i == 2)
		{
			translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, 3.0f, -20.0f)));
		}
	}

	for (int i = -5; i <= 5; i++) // row3
	{
		if (i > -4 && i < 4)
		{
			translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, 2.0f, -20.0f)));
		}
	}

	for (int i = -5; i <= 5; i++) // row4
	{
		if (i != -5 && i != -2 && i != 2 && i != 5)
		{
			translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, 1.0f, -20.0f)));
		}
	}

	for (int i = -5; i <= 5; i++) // row5
	{
		translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, 0.0f, -20.0f)));
	}

	for (int i = -5; i <= 5; i++) // row6
	{
		if (i != -4 && i != 4)
		{
			translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, -1.0f, -20.0f)));
		}
	}

	for (int i = -5; i <= 5; i++) // row7
	{
		if (i == -5 || i == -3 || i == 3 || i == 5)
		{
			translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, -2.0f, -20.0f)));
		}
	}

	for (int i = -5; i <= 5; i++) // row8
	{
		if (i == -2 || i == -1 || i == 1 || i == 2)
		{
			translations.push_back(glm::translate(IDENTITY_M4, vector3(i + value, -3.0f, -20.0f)));
		}
	}

	value += 0.01f; // move cubes across screen

	// Render Cubes
	for (int i = 0; i < 46; i++)
	{
		cubes[i]->Render(m4Projection, m4View, (m4Scale * translations[i]));
	}

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	// Delete Cubes
	for (int i = 0; i < 46; i++)
	{
		SafeDelete(cubes[i]);
	}

	//release GUI
	ShutdownGUI();
}