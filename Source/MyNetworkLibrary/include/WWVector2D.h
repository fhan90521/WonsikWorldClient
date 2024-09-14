#pragma once
#include "Buffer/CSendBuffer.h"
#include "Buffer/CRecvBuffer.h"
#include "Container/MyStlContainer.h"
class WWVector2D
{
public:
	float _x;
	float _y;
	void Normalize();
	float Length();
	std::pair<float, float> TransferToPair();
	WWVector2D(float x = 0, float y = 0) :_x(x), _y(y) {}
	friend CSendBuffer& operator<<(CSendBuffer& buf, const WWVector2D& vec);
	friend CRecvBuffer& operator>>(CRecvBuffer& buf, WWVector2D& vec);
	friend CSendBuffer& operator<<(CSendBuffer& buf, const Vector<WWVector2D>& vectors);
	friend CRecvBuffer& operator>>(CRecvBuffer& buf, Vector<WWVector2D>& vectors);
	friend WWVector2D operator-(const WWVector2D& vec1,const WWVector2D& vec2);
};