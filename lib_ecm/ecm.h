#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

class Component;

class Entity {
private:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;

	int _points;
	float _rotation;
	bool _alive;
	bool _visible;
	bool _forDeletion;

public:
	Entity();
	virtual ~Entity() = default;

	virtual void Update(const double dt);
	virtual void Render();

	sf::Vector2f& getPosition();
	void setPosition(const sf::Vector2f& pos);
	bool is_forDeletion() const;
	float getRotation()	const;
	void setRotation(float _rot);
	bool isAlive() const;
	void setAlive(bool _value);
	void setForDelete();
	bool isVisible() const;
	void setVisible(bool _value);
	void setPoints(int p);
	int getPoints();

	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

		template <typename T>
		const std::vector<std::shared_ptr<T>> get_components() const {
			static_assert(std::is_base_of<Component, T>::value, "T != component");
			std::vector<std::shared_ptr<T>> ret;
			for (const auto c : _components) {
				if (typeid(*c) == typeid(T)) {
					ret.push_back(std::dynamic_pointer_cast<T>(c));
				}
			}
			return std::move(ret);
		}

		template <typename T>
		const std::vector<std::shared_ptr<T>> GetCompatibleComponent() {
			static_assert(std::is_base_of<Component, T>::value, "T != component");
			std::vector<std::shared_ptr<T>> ret;
			for (auto c : _components) {
				auto dd = dynamic_cast<T*>(&(*c));
				if (dd) {
					ret.push_back(std::dynamic_pointer_cast<T>(c));
				}
			}
			return ret;
		}
};

class Component {
protected:
	Entity* _parent;
	bool _fordeletion; // should be removed
	explicit Component(Entity* p);

public:
	Component() = delete;
	bool is_fordeletion();
	void setfordeletion();
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual ~Component();

	Entity getParent();
};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void Update(double dt);
	void Render();
};