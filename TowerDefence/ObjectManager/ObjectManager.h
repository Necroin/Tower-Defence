#pragma once
#ifndef _OBJECTMANAGER_H
#define _OBJECTMANAGER_H
#include <vector>

template <class _Ty>
class ObjectManager {
private:
	inline static std::vector<_Ty> _objects;
public:
	ObjectManager() {}
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager(ObjectManager&&) = delete;

	ObjectManager& operator= (const ObjectManager&) = delete;
	ObjectManager& operator= (ObjectManager&&) = delete;

	void* operator new(size_t) = delete;
	void operator delete(void*) = delete;

	void* operator new[](size_t) = delete;
	void operator delete[](void*) = delete;

	void erase(size_t index);
public:
	void update();
	void action();
	void push(_Ty&& object);
	const std::vector<_Ty>& data() const;
};

template <class _Ty>
class ObjectManager<_Ty*> {
private:
	inline static std::vector<_Ty*> _objects;
public:
	ObjectManager() {}
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager(ObjectManager&&) = delete;

	ObjectManager& operator= (const ObjectManager&) = delete;
	ObjectManager& operator= (ObjectManager&&) = delete;

	void* operator new(size_t) = delete;
	void operator delete(void*) = delete;

	void* operator new[](size_t) = delete;
	void operator delete[](void*) = delete;

	void erase(size_t index);
public:
	void update();
	void action();
	void push(_Ty* object_pointer);
	const std::vector<_Ty*>& data() const;
	static void destroy_data();
};
#endif

template<class _Ty>
inline void ObjectManager<_Ty>::erase(size_t index)
{
	_objects.erase(_objects.begin() + index);
}

template<class _Ty>
inline void ObjectManager<_Ty>::update()
{
	for (size_t i = 0; i < _objects.size(); ++i) {
		if (!_objects[i].update()) {
			erase(i);
		}
	}
}

template<class _Ty>
inline void ObjectManager<_Ty>::action()
{
	for (auto&& object : _objects) object.action();
}

template<class _Ty>
inline void ObjectManager<_Ty>::push(_Ty&& object)
{
	_objects.push_back(std::move(object));
}

template<class _Ty>
inline const std::vector<_Ty>& ObjectManager<_Ty>::data() const
{
	return _objects;
}

///////////// FOR POINTER /////////////
template<class _Ty>
inline void ObjectManager<_Ty*>::erase(size_t index)
{
	_objects.erase(_objects.begin() + index);
}

template<class _Ty>
inline void ObjectManager<_Ty*>::update()
{
	for (size_t i = 0; i < _objects.size(); ++i) {
		if (!_objects[i]->update()) {
			delete _objects[i];
			erase(i);
		}
	}
}

template<class _Ty>
inline void ObjectManager<_Ty*>::action()
{
	for (auto&& object : _objects) object->action();
}

template<class _Ty>
inline void ObjectManager<_Ty*>::push(_Ty* object_pointer)
{
	_objects.emplace_back(object_pointer);
}

template<class _Ty>
inline const std::vector<_Ty*>& ObjectManager<_Ty*>::data() const
{
	return _objects;
}

template<class _Ty>
inline void ObjectManager<_Ty*>::destroy_data()
{
	for (auto&& p : _objects) {
		delete p;
	}
}