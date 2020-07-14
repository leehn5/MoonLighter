#pragma once
#include "Component.h"
#include <vector>
#include <list>
class Transform;
class Sprite;
class DrawComponent;

class Object
{
protected:
	Object();

	Transform* _trans;
	vector<DrawComponent*> _draw;
	vector <Component*> _components;
	string _name;
	string _tag;
	bool _isActive = true;
	bool _allowsUpdate = true;
	bool _allowInit = true;
	bool _allowRender = true;
	bool _cameraAffect = true;
	Object* _parent;
	vector<Object*> _children;

public:
	~Object() {};
	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();

	template<typename T>
	static T* CreateObject(Object* parant = nullptr);


	virtual inline Transform* GetTrans() { return _trans; }
	inline vector<DrawComponent*> GetDraw() { return _draw; }

	inline string GetName() { return _name; }
	inline void SetName(string name) { _name = name; }

	inline string GetTag() { return _tag; }
	inline void SetTag(string tag) { _tag = tag; }

	inline void SetIsActive() { _isActive = !_isActive; }
	inline void SetIsActive(bool active) { _isActive = active; }

	inline bool GetIsActive() { return _isActive; }

	inline bool GetAllowsUpdate() { return _allowsUpdate; }
	inline void SetAllowsUpdate() { _allowsUpdate = !_allowsUpdate; }
	inline void SetAllowsUpdate(bool active) { _allowsUpdate = active; }

	inline bool GetAllowsRender() { return _allowRender; }
	inline void SetAllowsRender() { _allowRender = !_allowRender; }
	inline void SetAllowsRender(bool active) { _allowRender = active; }


	inline bool GetAllowInit() { return _allowInit; }
	
	inline void SetCameraAffect(bool active) { _cameraAffect = active; }
	inline bool GetCameraAffect() { return _cameraAffect; }

	void AddChild(Object* child);
	void RemoveComponent(Component* component);
	void RemoveChild(Object* child);

	Object* GetChildFromName(string name);
	vector<Object*>GetChildrenFromTag(string tag);
	inline vector<Object*>GetChildren() { return _children; }
	inline Object* GetParent() { return _parent; }

	void SetParent(Object* parent);

	template<typename T>
	T* AddComponent();

	template<typename T>
	T* GetComponent();

	template<typename T>
	vector<T*> GetComponents();
};

#include "Object.hpp"