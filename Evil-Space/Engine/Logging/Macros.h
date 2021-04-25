//
//  Macros.h
//  Logging macros.
//
//  Created by Kirill Bravichev on 03/12/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include <fmt/core.h>
#include <fmt/color.h>

struct ADebugLogging
{
	template<typename FormatType, typename ...Args>
	static std::string format(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
		return fmt::format("{}:{} - {} - {}\n", file, line, function, fmt::format(str, args...));
	}

	template<typename FormatType, typename ...Args>
	static constexpr void print(FormatType str, Args... args)
	{
#if defined(_DEBUG)
		fmt::print(fmt::format("{}\n", fmt::format(str, args...)));
#endif
	}

	template<typename FormatType, typename ...Args>
	static constexpr void warning(FormatType str, Args... args)
	{
		fmt::print(fg(fmt::color::yellow), fmt::format("{}\n", fmt::format(str, args...)));
	}

	template<typename FormatType, typename ...Args>
	static constexpr void error(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
		fmt::print(fg(fmt::color::red), format(file, line, function, str, args...));
	}

	template<typename FormatType, typename ...Args>
	static constexpr void exception(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
		const auto& text = format(file, line, function, str, args...);
		fmt::print(fg(fmt::color::red), text);
		throw std::runtime_error(text);
	}
};

#define LOG(str, ...)			ADebugLogging::print(str, ##__VA_ARGS__)
#define LOG_WARNING(str, ...)	ADebugLogging::warning(str, ##__VA_ARGS__)
#define LOG_ERROR(str, ...)		ADebugLogging::error(__FILE__, __LINE__, __FUNCTION__, str, ##__VA_ARGS__)
#define LOG_CRITICAL(str, ...)	ADebugLogging::exception(__FILE__, __LINE__, __FUNCTION__, str, ##__VA_ARGS__)
