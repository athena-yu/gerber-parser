#pragma once

#include <math.h>
#include <vector>
#include <memory>

#include "bound_box.h"


class RenderCommand;

class Aperture {
protected:
	std::vector<std::shared_ptr<RenderCommand>> render_commands_{};

	void RenderHole();

	void HoleCircle(double d);
	void HoleRectangle(double w, double h);

	virtual void RenderAperture() = 0;

	double dimension_x_; // Also used for outside diameter of circles
	double dimension_y_;
	double hole_x_; // For no hole, make this negative
	double hole_y_; // For a round hole make this negative

	// Regular Polygon additional modifiers
	double rotation_;  // Degrees of rotaion (rotate the whole thing CCW)
	int code_; // The code to use in the D-Code to load this tool

public:
	Aperture(int code);
	~Aperture();

	BoundBox bound_box_{ 0.0, 0.0, 0.0, 0.0 };

	int Code() const {
		return code_;
	}

	// Used to determine if it is a basic shape or not
	virtual bool SolidCircle() = 0;
	virtual bool SolidRectangle() = 0;

	std::vector<std::shared_ptr<RenderCommand>> Render();
};
