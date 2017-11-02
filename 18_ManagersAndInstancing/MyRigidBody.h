/*----------------------------------------------
Programmer: Israel Anthony (ixa4371@rit.edu)
Date: 2017/11
----------------------------------------------*/

#ifndef __MYRIGIDBODY_H_
#define __MYRIGIDBODY_H_

#include "MyMesh.h"

namespace Simplex
{

class MyRigidBody
{
public:
	Mesh* m_BS = nullptr; // Bounding sphere
	Mesh* m_BB = nullptr; // Bounding box
	vector3 m_v3Min;
	vector3 m_v3Max;
	vector3 m_v3Center;

	MyRigidBody(void);
	MyRigidBody(MyMesh* a_pObject);
	void Render(MyCamera* a_pCamera, matrix4 a_m4Model);
};

}

#endif //__MYRIGIDBODY_H_
