#pragma once

template <typename T>
class ShapeGo : public GameObject
{

	bool active = true;
public:
	ShapeGo(const std::string name) : GameObject(name)
	{

	}
	
	~ShapeGo()
	{

	}

	ShapeGo(const ShapeGo&) = delete;
	ShapeGo(ShapeGo&&) = delete;
	ShapeGo& operator=(const ShapeGo&) = delete;
	ShapeGo& operator=(ShapeGo&&) = delete;

	void Init() override
	{

	}
	void Release() override
	{

	}

	void Reset() override
	{

	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	void SetPosition(const sf::Vector2f& pos) override
	{
		GameObject::SetPosition(pos);
		shape.setPosition(pos);
	}

	void SetScale(const sf::Vector2f& scale) override
	{
		GameObject::SetScale(scale);
		shape.setScale(scale);
	}

	void SetOrigin(Origins preset) override
	{
		GameObject::SetOrigin(preset);
		Utils::SetOrigin(shape, preset);
	}

	void SetOrigin(const sf::Vector2f& newOrigin) override
	{
		GameObject::SetOrigin(newOrigin);
		shape.setOrigin(newOrigin);
	}

	void SetOutlineThickness(float thickness)
	{
		shape.setOutlineThickness(thickness);
	}
	void SetOutlineColor(sf::Color color)
	{
		shape.setOutlineColor(color);
	}

	void SetSize(const sf::Vector2f& size)
	{
		if constexpr (std::is_same_v<T, sf::CircleShape>)
		{
			shape.setRadius(size.x);
		}
		else
		{
			shape.setSize(size);
		}
	}

	sf::Vector2f GetSize()
	{
		return shape.getSize();
	}

	void SetColor(sf::Color color)
	{
		shape.setFillColor(color);
	}

	sf::FloatRect GetGlobalBounds()
	{
		return shape.getGlobalBounds();
	}

protected:
	T shape;

};

