#pragma once

class Vertex
{
public:
	int index, degree, nebDeg;
	int core;

	Vertex() { index = degree = nebDeg = core = 0; }
	Vertex(int index, int degree)
	{
		this->index = index;
		this->degree = degree;
		nebDeg = core = 0;
	}
	Vertex(int index, int degree, int core)
	{
		this->index = index;
		this->degree = degree;
		this->core = core;
		nebDeg = 0;
	}
	Vertex(const Vertex &obj) 
	{ 
		index = obj.index; degree = obj.degree; nebDeg = obj.nebDeg;
		core = obj.core;
	}

	bool operator ==(const Vertex &p)
	{
		if (this->index == p.index)
			return true;
		return false;
	}
};
