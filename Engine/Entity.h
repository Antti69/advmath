#pragma once

#include <vector>
#include "Vec2.h"
#include "Drawable.h"

class Entity
{
public:
	Entity( std::vector<Vec2> model, float pulsingspeed, const Vec2& pos = { 0.0f,0.0f },Color c = Colors::Yellow )
		:
		c( c ),
		pulsingspeed ( pulsingspeed ),
		pos( pos ),
		model( std::move( model ) )
	{}
	const Vec2& GetPos() const
	{
		return pos;
	}
	void SetPos( const Vec2& newPos )
	{
		pos = newPos;
	}
	void TranslateBy( const Vec2& offset )
	{
		pos += offset;
	}
	void SetScale( float s )
	{
		scale = s;
	}
	float GetScale() const
	{
		return scale;
	}
	Drawable GetDrawable() const
	{
		Drawable d( model,c );
		d.Scale( scale );
		d.Translate( pos );
		return d;
	}
	void Pulsar(float minscale, float maxscale)
	{
		pulsarStart += pulsingspeed;
		if (pulsarStart >= counter)
		{
			scale += scaledir;
			
			b += colordir;
			c.SetB(b);
			if (scale >= maxscale)
			{
				scaledir = -0.1f;
			}
			if (scale <= minscale)
			{
				scaledir = 0.1f;
			}

			if (c.GetB() >= 240)
			{
				colordir = -5;
			}
			if (c.GetB() <= 20)
			{
				colordir = 5;
			}

			pulsarStart = 0.0f;
		}

	}
private:
	Color c;
	float scale = 1.0f;
	Vec2 pos = {0.0f,0.0f};
	std::vector<Vec2> model;
	float pulsingspeed;
	float counter = 4.0f;
	float pulsarStart = 0.0f;
	float scaledir = 0.1;
	int colordir = 1;
	unsigned char b = c.GetB();
};