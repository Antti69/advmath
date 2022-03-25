#pragma once

#include "Graphics.h"
#include <vector>
#include "Vec2.h"
#include <algorithm>

class Drawable
{
public:
	Drawable( std::vector<Vec2> model,Color c )
		:
		c( c ),
		model( std::move( model ) )
	{}
	void Translate( const Vec2& translation_in )
	{
		translation += translation_in;
	}
	void Scale( float scale_in )
	{
		scale_x *= scale_in;
		scale_y *= scale_in;
		translation *= scale_in;
	}
	void ScaleIndependent( float scale_in_x,float scale_in_y )
	{
		scale_x *= scale_in_x;
		scale_y *= scale_in_y;
		translation.x *= scale_in_x;
		translation.y *= scale_in_y;
	}
	void ReadyToRender()
	{
		for (auto& v : model)
		{
			v.x *= scale_x;
			v.y *= scale_y;
			v += translation;
		}
	}
	void Render( Graphics& gfx )
	{
		gfx.DrawClosedPolyline(model, c);
		//const float halfwidth = (float)gfx.ScreenWidth / 2;
		//const float halfheight = (float)gfx.ScreenHeight / 2;

		//if (std::any_of(model.begin(), model.end(), [&](const Vec2& p)
		//{ return p.x >= translation.x - halfwidth + 100 && p.x <= translation.x + halfwidth &&
		//	p.y >= translation.y - halfheight && p.y <= translation.y + halfheight; }))
		//{
		//	
		//}
		
	}
	const std::vector<Vec2>& GetModel() const
	{
		return model;
	}
	const Vec2& GetTranslation() const
	{
		return translation;
	}
private:
	Color c;
	std::vector<Vec2> model;
	Vec2 translation = {0.0f,0.0f};
	float scale_x = 1.0f;
	float scale_y = 1.0f;
};