/*
* Mirage Game Engine Unit Tests
* Tests for Camera class
* Author: Harha
* (c) 2016-
*/

// gtest includes
#include <gtest/gtest.h>

// mirage includes
#include "graphics/camera.h"

TEST(test_camera, create)
{
	Camera camera;

	EXPECT_NEAR(camera.getExposure(), 1.0f, 0.001f);
}

TEST(test_camera, set_exposure)
{
	Camera camera;

	camera.setExposure(5.1256f);

	EXPECT_GT(camera.getExposure(), 5.1256f);
}