/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Rendering/GL/myGL.h"

#ifdef _MSC_VER
#pragma warning(disable:4291)
#endif

class CProjectileHandler;
class CBuilding;

#include "ExplosionGenerator.h"
#include "Sim/Units/UnitHandler.h"

class CUnit;
class CFeature;
class CVertexArray;

#define COLLISION_NOFRIENDLY	1
#define COLLISION_NOFEATURE		2
#define COLLISION_NONEUTRAL		4

class CProjectile: public CExpGenSpawnable
{
public:
	CR_DECLARE(CProjectile);

	static bool inArray;
	static CVertexArray* va;
	static int DrawArray();

	virtual void Draw();
	virtual void DrawOnMinimap(CVertexArray& lines, CVertexArray& points);
	CProjectile(); // default constructor is needed for creg
	CProjectile(const float3& pos, const float3& speed, CUnit* owner, bool isSynced, bool isWeapon, bool isPiece);
	virtual void Collision();
	virtual void Collision(CUnit* unit);
	virtual void Collision(CFeature* feature);
	virtual ~CProjectile();
	virtual void Update();
	virtual void Init(const float3& pos, CUnit* owner);

	bool synced; //! is this projectile part of the simulation?
	bool weapon; //! is this a weapon projectile? (true implies synced true)
	bool piece;  //! is this a piece projectile? (true implies synced true)

	bool checkCol;
	bool deleteMe;
	bool castShadow;
	unsigned int collisionFlags;

	float3 drawPos;
#if defined(USE_GML) && GML_ENABLE_SIM
	unsigned lastProjUpdate;
#endif

	inline CUnit* owner() const {
		return uh->units[ownerId];
	}

	float3 speed;
	float mygravity;

	virtual void DrawCallback(void) {}
	virtual void DrawUnitPart(void) {}
	virtual void DrawS3O() { DrawUnitPart(); }

	float tempdist; // temp distance used for sorting when rendering
	
private:
	int ownerId;
};

#endif /* PROJECTILE_H */
