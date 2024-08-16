#pragma once
#include "CSendBuffer.h"
#include "CRecvBuffer.h"
#include "MyStlContainer.h"
class WWVector2D
{
public:
	float _x=0;
	float _y=0;
	void Normalize();
	float Length();
	std::pair<float, float> TransferToPair();
	WWVector2D(float x = 0, float y = 0) :_x(x), _y(y) {}
	friend CSendBuffer& operator<<(CSendBuffer& buf, const WWVector2D& vec);
	friend CRecvBuffer& operator>>(CRecvBuffer& buf, WWVector2D& vec);
	friend CSendBuffer& operator<<(CSendBuffer& buf, const Vector<WWVector2D>& vectors);
	friend CRecvBuffer& operator>>(CRecvBuffer& buf, Vector<WWVector2D>& vectors);
	friend WWVector2D operator-(WWVector2D vec1, WWVector2D vec2);
};