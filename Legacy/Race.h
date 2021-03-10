#pragma once

class Race
{
public:
	enum race
	{
		Blazer,
		Keller,
		Terron,
	};

	std::wstring ToString(race obj)
	{
		std::wstring str;

		switch(obj)
		{
		case Blazer:
			str = L"Blazer";
			break;
		case Keller:
			str = L"Keller";
			break;
		case Terron:
			str = L"Terron";
			break;
		}

		return str;
	}
};