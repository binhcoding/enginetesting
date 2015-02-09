#include "Gun.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed) :
_name(name), _fireRate(fireRate), _bulletsPerShot(bulletsPerShot), _spread(spread), _bulletDamage(bulletDamage), _bulletSpeed(bulletSpeed),
_frameCounter(0)
{
}


Gun::~Gun()
{
}

void Gun::Update(bool isMouseDown, const glm::vec2& position, glm::vec2 direction, std::vector<Bullet>& bullets)
{
	_frameCounter++;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		Fire(direction, position, bullets);
		_frameCounter = 0;
	}
}

void Gun::Fire(glm::vec2 direction, const glm::vec2& position, std::vector<Bullet>& bullets)
{
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomRotate(-_spread, _spread);


	for (int i = 0; i < _bulletsPerShot; i++)
	{
		//std::cout << "Value of glm rotate: " << glm::degrees(glm::rotate(direction, randomRotate(randomEngine))).x << glm::degrees(glm::rotate(direction, randomRotate(randomEngine))).y;

		glm::vec2 randomRotationVector = glm::rotate(direction, randomRotate(randomEngine)); // returns results in radians
		bullets.emplace_back(position, randomRotationVector, _bulletDamage, _bulletSpeed);
		
	}
}