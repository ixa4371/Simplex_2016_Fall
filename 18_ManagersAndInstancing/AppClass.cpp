#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//init the camera
	m_pCamera = new MyCamera();
	m_pCamera->SetPositionTargetAndUp(
		vector3(0.0f, 3.0f, 20.0f), //Where my eyes are
		vector3(0.0f, 3.0f, 19.0f), //where what I'm looking at is
		AXIS_Y);					//what is up

	//Get the singleton
	m_pMyMeshMngr = MyMeshManager::GetInstance();
	m_pMyMeshMngr->SetCamera(m_pCamera);
	
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCylinder(1.0f, 2.0f, 6, C_PURPLE);

	//Instance rendering
	for (uint i = 0; i < 1; i++)
	{
		matrix4* pMatrix = new matrix4();
		*pMatrix = glm::translate(IDENTITY_M4, vector3(i * 2, 0, 0));
		m_m4List.push_back(pMatrix);
	}
	
	m_pRB = new MyRigidBody(m_pMesh);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Add objects to the Manager
	//uint nCount = 0;
	//for (int j = -420; j < 420; j += 2)
	//{
	//	for (int i = -420; i < 420; i += 2)
	//	{
	//		m_pMyMeshMngr->AddConeToRenderList(glm::translate(vector3(i, 0.0f, j)));
	//		nCount++;
	//	}
	//}
	//m_pMeshMngr->Print("Objects: " + std::to_string(nCount) + "\n", C_BLUE);
}
void Application::Display(void)
{
	//Clear the screen
	ClearScreen();

	//Render call per object (slow performance with high number objects)
	/*
	for (uint i = 0; i < 500; i++)
	{
		m_pMesh->Render(m_pCamera, glm::translate(IDENTITY_M4, vector3(i * 2, 0, 0)) * ToMatrix4(m_qArcBall));
	}
		m_pMesh->Render(m_pCamera, m_m4List);
	*/

	//Instance rendering with list. Has drawbacks with transformations, but runs way better.
	for (uint i = 0; i < 1; i++)
	{
		*m_m4List[i] = ToMatrix4(m_qArcBall);
	}

	m_pMesh->Render(m_pCamera, m_m4List);
	m_pRB->Render(m_pCamera, *m_m4List[0]);

	//Render the list of MyMeshManager
	m_pMyMeshMngr->Render();

	//clear the MyMeshManager list
	m_pMyMeshMngr->ClearRenderList();

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
	//release the singleton
	MyMeshManager::ReleaseInstance();


	for (uint i = 0; i < i; i++)
	{
		SafeDelete(m_m4List[i]);
	}

	//release the camera
	SafeDelete(m_pCamera);

	SafeDelete(m_pRB);
	/* Below is the logical equivalent of SafeDelete
	if (m_pRB)
	{
		delete m_pRB;
		m_pRB = nullptr;
	}
	*/

	//release GUI
	ShutdownGUI();
}
