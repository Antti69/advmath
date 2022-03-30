#pragma once

#include "CoordinateTransformer.h"
#include "RectF.h"
#include "Graphics.h"
#include "ChiliMath.h"

class Camera
{
public:
	Camera( CoordinateTransformer& ct )
		:
		ct( ct )
	{}
	Vec2 GetPos() const
	{
		return pos;
	}
	void MoveBy( const Vec2& offset )
	{
		pos += offset;
	}
	void MoveTo( const Vec2& pos_in )
	{
		pos = pos_in;
	}
	void Draw( Drawable& drawable ) const
	{
		
		drawable.Rotate(rot);
		drawable.Translate( -pos );
		drawable.Scale(scale);
	
		ct.Draw( drawable );
	}
	void SetScale( float s )
	{
		scale = s;
	}
	float GetScale() const
	{
		return scale;
	}
	void Rotate(float r_in)
	{
		rot = r_in;
		if (rot <= -2.0f * PI)
		{
			rot = 0.0f;
		}
		if (rot >= 2.0f * PI)
		{
			rot = 0.0f;
		}
	}
	float GetRot() const
	{
		return rot;
	}
	RectF GetViewportRect() const
	{
		const float zoom = 1.0f / scale;

		return RectF::FromCenter( 
			pos,
			float( Graphics::ScreenWidth / 2 ) * zoom,
			float( Graphics::ScreenHeight / 2 ) * zoom
		);
	}

private:
	Vec2 pos = {0.0f,0.0f};
	float scale = 1.0f;
	float rot = 0.0f;
	CoordinateTransformer& ct;
};