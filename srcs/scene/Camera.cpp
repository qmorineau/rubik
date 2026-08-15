#include "Camera.hpp"

Camera::Camera(int width, int height, vec3 position, vec3 up, float yaw, float pitch) : 
	_front(vec3(0.0f, 0.0f, -1.0f)), 
	_width(width), 
	_height(height),
	_target(0, 0, 0),
	_baseFront(_front),
	_baseUp(up),
	_basePosition(position)
{
	_mode = CameraMode::ORBITAL;
	_aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
	_position = position;
	_worldUp = up;
	_yaw = yaw;
	_pitch = pitch;
	updateCameraVectors();
	updateOrientation();
}

void Camera::resize(int width, int height)
{
	_width = width;
	_height = height;
	_aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
}

void Camera::moveOrbitalMode(CameraMovement dir, float deltaTime)
{
	int radius = 10;
	float angle = _movementSpeed * deltaTime;

	angle = math::degrees(angle);
    if (dir == LEFT)
		_yaw -= angle;
    if (dir == RIGHT)
		_yaw += angle;
    if (dir == FORWARD)
		_pitch += angle;
    if (dir == BACKWARD)
		_pitch -= angle;

	float clamp = 89.f;
    _pitch = _pitch < -clamp ? -clamp : _pitch > clamp ? clamp : _pitch;

	float yawRad = math::radians(_yaw);
	float pitchRad = math::radians(_pitch);

	vec3 newPos;
    newPos.x = _target.x + radius * cos(pitchRad) * cos(yawRad);
    newPos.y = _target.y + radius * sin(pitchRad);
    newPos.z = _target.z + radius * cos(pitchRad) * sin(yawRad);

	changePosition(newPos);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
	switch (_mode)
	{
		case CameraMode::ORBITAL:
			moveOrbitalMode(direction, deltaTime);
			break;
	}

}

void Camera::onMouseMove(const vec2& posIn)
{
	if (_mode != Camera::ORBITAL)
	{
		float xpos = static_cast<float>(posIn.x);
		float ypos = static_cast<float>(posIn.y);

		if (_firstMouse)
		{
			_lastX = xpos;
			_lastY = ypos;
			_firstMouse = false;
		}

		float xoffset = xpos - _lastX;
		float yoffset = _lastY - ypos;
		_lastX = xpos;
		_lastY = ypos;

		xoffset *= _mouseSensitivity;
		yoffset *= _mouseSensitivity;

		_yaw += xoffset;
		_pitch += yoffset;

		float clamp = 89.f;
    	_pitch = _pitch < -clamp ? -clamp : _pitch > clamp ? clamp : _pitch;

		updateCameraVectors();
	}
}

void Camera::onMouseScroll(const vec2& offset)
{
	_zoom -= (float)static_cast<float>(offset.y);
	if (_zoom < 1.0f)
		_zoom = 1.0f;
	if (_zoom > 45.0f)
		_zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	vec3 front;
	front.x = cos(math::radians(_yaw)) * cos(math::radians(_pitch));
	front.y = sin(math::radians(_pitch));
	front.z = sin(math::radians(_yaw)) * cos(math::radians(_pitch));
	_front = math::normalize(front);
	// also re-calculate the Right and Up vector
	_right = math::normalize(math::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	_up    = math::normalize(math::cross(_right, _front));
}

void Camera::resetPosition()
{
	changePosition(_basePosition);
	_firstMouse = true;
	updateOrientation();
}

void Camera::updateOrientation()
{
	switch (_mode)
	{
		case CameraMode::ORBITAL:
		{
			vec3 rel = math::normalize(_position - _target);
			_yaw   = math::degrees(atan2(rel.z, rel.x));
			_pitch = math::degrees(asin(rel.y));
			break;
		}
	}
}

void Camera::changePosition(const vec3& pos)
{
    _position = pos;
    _front = math::normalize(_target - _position);
    _right = math::normalize(math::cross(_front, _worldUp));
    _up    = math::normalize(math::cross(_right, _front));
}
