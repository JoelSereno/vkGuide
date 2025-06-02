
#include <vk_types.h>
#include <SDL_events.h>

class Camera {
public:
	bool locked{ false };

	glm::vec3 velocity[2];
	glm::vec3 position;
	// vertical rotation
	float pitch{ 0.f };
	// horizontal rotation;
	float yaw{ 0.f };

	glm::mat4 getViewMatrix();
	glm::mat4 getRotationMatrix();

	void processSDLEvent(SDL_Event& e);

	void update();
};
