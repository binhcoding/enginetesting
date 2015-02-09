#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "Bullet.h"

class Gun
{
	public:
	Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed);
	~Gun();
	void Update(bool isMouseDown, const glm::vec2& position, glm::vec2 direction, std::vector<Bullet>& bullets);
	private:
	void Fire(glm::vec2 direction, const glm::vec2& position, std::vector<Bullet>& bullets);


	std::string _name;
	int _fireRate; // fire rate in frames
	int _bulletsPerShot; // how many bullets are fired at a time
	int _frameCounter;
	float _spread; // accuracy
	float _bulletSpeed; 
	float _bulletDamage;


};

