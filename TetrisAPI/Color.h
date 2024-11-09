#pragma once
class Color
{
public:
	Color(int r, int g, int b, int a = MAX_COLOR);
	int GetR()const;
	int GetG()const;
	int GetB()const;
	int GetA()const;

	bool operator==(const Color& other) const;
private:
	int GetValidColorValue(int value);
private:
	int m_r;
	int m_g;
	int m_b;
	int m_a;
	
	static inline const int MIN_COLOR = 0;
	static inline const int MAX_COLOR = 255;
};

