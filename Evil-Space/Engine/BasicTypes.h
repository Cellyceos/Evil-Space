//
//  BasicTypes.h
//  Basic types for project.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include <memory>

#include <string>
#include <string_view>

#include <array>
#include <vector>

#include <map>
#include <unordered_map>

#include <functional>

#include <fstream>
#include <filesystem>

#include <glm/glm.hpp>


#ifdef _DEBUG
#define unimplemented() \
	LOG_CRITICAL("unimplemented")

#ifdef assert
#undef assert
#endif // assert

#define assert(expression) \
	if(!(expression)) { LOG_CRITICAL((#expression)); }
#else
#define unimplemented() ((void)0)
#endif // _DEBUG


using int8 = glm::int8_t;
using int16 = glm::int16_t;
using int32 = glm::int32_t;
using int64 = glm::int64_t;
using uint8 = glm::uint8_t;
using uint16 = glm::uint16_t;
using uint32 = glm::uint32_t;
using uint64 = glm::uint64_t;

template<class T> using TUniquePtr = std::unique_ptr<T>;
template<class T> using TSharedPtr = std::shared_ptr<T>;
template<class T> using TWeakPtr = std::weak_ptr<T>;

using FString = std::string;
using FStringView = std::string_view;

using FPath = std::filesystem::path;

template<class Key, class T> using TMap = std::map<Key, T>;
template<class Key, class T> using TUnorderedMap = std::unordered_map<Key, T>;

template<typename T> using TArray = std::vector<T>;
template<typename T, uint64 Size> using TFixedArray = std::array<T, Size>;

template<typename T> using TNumericLimits = std::numeric_limits<T>;

using namespace std::placeholders;
template<typename T> using TFunction = std::function<T>;

enum class EPixelFormatType : uint32
{
	Unknown,
	Mono,
	MonoLSB,
	Indexed8,
	RGB32,
	ARGB32,
	RGB16,
	RGB555,
	RGB888,
	RGB444,
	ARGB4444,
	RGBX8888,
	RGBA8888,
	BGR24,
	RGB24,
};

using FColor = glm::u8vec4;
using FPoint = glm::fvec2;

struct FSize
{
	float width = 0.0f;
	float height = 0.0f;
};

struct FRect
{
	union { 
		FPoint point{};
		struct 
		{  
			float x;
			float y;
		};
	};

	union 
	{
		FSize size{};
		struct
		{
			float width;
			float height;
		};
	};

	FRect() = default;
	FRect(const float InX, const float InY, const float InWidth, const float InHeight) : x(InX), y(InY), width(InWidth), height(InHeight) { }
	FRect(const FPoint& Point, const FSize& Size) : point(Point), size(Size) { }

	float GetLeft() const { return x; }
	float GetTop() const { return y; }
	float GetRight() const { return x + width; }
	float GetBottom() const { return y + height; }

	bool IntersectsWith(const FRect& rect) const
	{
		return (GetLeft() < rect.GetRight() && GetTop() < rect.GetBottom() && GetRight() > rect.GetLeft() && GetBottom() > rect.GetTop());
	}
};

struct FAABB
{
	FPoint Center;
	TFixedArray<float, 2> Radius{ 0.0f, 0.0f };

	bool Test(const FAABB& Other) const
	{
		if (std::fabsf(Center.x - Other.Center.x) > (Radius[0] + Other.Radius[0])) return false;
		if (std::fabsf(Center.y - Other.Center.y) > (Radius[1] + Other.Radius[1])) return false;
		return true;
	}
};
