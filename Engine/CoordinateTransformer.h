#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Drawable.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer( Graphics& gfx )
		:
		gfx( gfx )
	{}
	void Draw( Drawable& drawable ) const
	{
		float halfwidth = (float)gfx.ScreenWidth / 2;
		float halfheight = (float)gfx.ScreenHeight / 2;

		const Vec2 offset = { halfwidth, halfheight };
		drawable.ScaleIndependent( 1.0f,-1.0f );
		drawable.Translate( offset );
		drawable.ReadyToRender();
		
		if (std::any_of(drawable.GetModel().begin(), drawable.GetModel().end(), [&](const Vec2& p)
		{ return p.x >= 0.0f && p.x <= 0.0f + (halfwidth  * 2) &&
			p.y >= 0.0f && p.y <= 0.0f + (halfheight * 2); }))
		{
			
			drawable.Render(gfx);
		}
	}
private:
	Graphics& gfx;
};