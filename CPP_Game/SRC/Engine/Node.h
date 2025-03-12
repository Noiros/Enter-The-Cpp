#pragma once
#include "Logger.h"


class Node {
public:
	Node() {}
	virtual ~Node() {}

	virtual void Update(float deltaTime) = 0;
};