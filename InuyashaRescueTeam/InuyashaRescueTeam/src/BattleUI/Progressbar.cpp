#include "BattleUI/Progressbar.h"

void Progressbar::Draw()
{
	if (_Is_ValueSet == false) {
		std::cout << "Value값을 설정해주세요.";
		return;
	}

	int end = _width - 9;
	float ratio = _Value / _MaxValue;
	int fill_count = ratio * end;

	tbColor(_Color_Font, _Color_Background);
	GoToXY(_spawnX, _spawnY);
	std::cout << " ";
	if (!_opposite)
	{
		for (size_t i = 0; i < end; i++)
		{
			if (i < fill_count)
			{
				tbColor(_Color_Font, _Color_Background);
			}
			else {
				tbColor(BLACK, _Color_Background);
			}
			std::cout << _Fillchar;
		}

		tbColor(BLACK, _Color_Background);
		std::cout << " " << ValueToString() << "/" << MaxValueToString();
	}
	else {
		tbColor(BLACK, _Color_Background);
		std::cout << ValueToString() << "/" << MaxValueToString() << " ";
		for (size_t i = 0; i < end; i++)
		{
			if (i < (end - fill_count))
			{
				tbColor(BLACK, _Color_Background);
			}
			else {
				tbColor(_Color_Font, _Color_Background);
			}
			std::cout << _Fillchar;
		}
	}
	std::cout << " ";

	tbColor();
	_Is_ValueSet = false;
}

std::string Progressbar::ValueToString()
{
	_Value = _Value > 999 ? 999 : _Value;
	std::string s = std::to_string((int)_Value);
	std::string result = "000";

	int size = s.size();
	int count = 3 - size;
	for (size_t i = 0; i < size; i++)
	{
		result[count + i] = s[i];
	}

	return result;
}

std::string Progressbar::MaxValueToString()
{
	_MaxValue = _MaxValue > 999 ? 999 : _MaxValue;
	std::string s = std::to_string((int)_MaxValue);
	std::string result = "000";

	int size = s.size();
	int count = 3 - size;
	for (size_t i = 0; i < size; i++)
	{
		result[count + i] = s[i];
	}

	return result;
}
