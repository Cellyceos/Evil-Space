#pragma once

class ShipType
{
public:
	enum shiptype
	{
		Batteleship = 1,
		Battlecruiser,
		Cruiser,
		Frigates
	};

	std::wstring ToString(shiptype ship)
	{
		std::wstring str;
		switch(ship)
		{
		case Batteleship:
			str = L"Batteleship";
			break;
		case Battlecruiser:
			str = L"Battlecruiser";
			break;
		case Cruiser:
			str = L"Cruiser";
			break;
		case Frigates:
			str = L"Frigates";
			break;
		}

		return str;
	}
};