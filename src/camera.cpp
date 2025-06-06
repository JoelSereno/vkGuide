#include "camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

void Camera::update() {
	glm::mat4 cameraRotation = getRotationMatrix();
	position += glm::vec3(cameraRotation * glm::vec4((velocity[0]+velocity[1]) * 0.5f, 0.f));
}

void Camera::processSDLEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_w) { velocity[0].z = -1; }
		if (e.key.keysym.sym == SDLK_s) { velocity[1].z = 1; }
		if (e.key.keysym.sym == SDLK_a) { velocity[0].x = -1; }
		if (e.key.keysym.sym == SDLK_d) { velocity[1].x = 1; }
		if (e.key.keysym.sym == SDLK_LSHIFT) { velocity[0].y = -1; }
		if (e.key.keysym.sym == SDLK_SPACE) { velocity[1].y = 1; }
	}

	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_w:
			velocity[0].z = 0;
			break;
		case SDLK_s:
			velocity[1].z = 0;
			break;
		case SDLK_a:
			velocity[0].x = 0;
			break;
		case SDLK_d:
			velocity[1].x = 0;
			break;
		case SDLK_LSHIFT:
			velocity[0].y = 0;
			break;
		case SDLK_SPACE:
			velocity[1].y = 0;
			break;

		}
	}

	if (e.type == SDL_MOUSEMOTION && !locked) {
		yaw += (float)e.motion.xrel / 200.f;
		pitch -= (float)e.motion.yrel / 200.f;
	}
}

glm::mat4 Camera::getViewMatrix() {
	// to create a correct model view, we need to move the world in opposite
	// direction to the camera
	// so we will create the camera model matrix and invert
	glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.f), position);
	glm::mat4 cameraRotation = getRotationMatrix();
	return glm::inverse(cameraTranslation * cameraRotation);
}

glm::mat4 Camera::getRotationMatrix() {
	// fairly typical FPS style camera. we join the pitch and yaw rotations into
	// the final rotation matrix

	glm::quat pitchRotation = glm::angleAxis(pitch, glm::vec3{ 1.f, 0.f, 0.f });
	glm::quat yawRotation = glm::angleAxis(yaw, glm::vec3{ 0.f, -1.f, 0.f });

	return glm::toMat4(yawRotation) * glm::toMat4(pitchRotation);
}