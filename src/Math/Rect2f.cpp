#include "Rect2f.h"

namespace Math
{


	Rect2f::Rect2f()
	{

	}

	Rect2f::Rect2f( float x,float y, float w, float h )
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	bool Rect2f::Intersect( Math::Vector2f vec2f )const
	{
		return Intersect(vec2f.x,vec2f.y);
	}
	bool Rect2f::Intersect( float px, float py )const
	{
		if( (px>=x) && (px < (x+w)) && (py>=y) && (py < (y+h)) )
		{
			return true;
		}
		return false;
	}

	bool Rect2f::Intersect( Rect2f rhs ) const
	{
		float xa1 = x;
		float xa2 = x+w;
		float ya1 = y;
		float ya2 = y+h;
		float xb1 = rhs.x;
		float xb2 = rhs.x+rhs.w;
		float yb1 = rhs.y;
		float yb2 = rhs.y+rhs.h;
		bool xOverlap = false;
		bool yOverlap = false;
		if(xa1>=xb1 && xa1<=xb2){xOverlap=true;}
		if(xb1>=xa1 && xb1<=xa2){xOverlap=true;}
		if(ya1>=yb1 && ya1<=yb2){yOverlap=true;}
		if(yb1>=ya1 && yb1<=ya2){yOverlap=true;}
		return xOverlap&&yOverlap;
	}

	Rect2f::~Rect2f()
	{

	}

}