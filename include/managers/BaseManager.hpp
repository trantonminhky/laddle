#pragma once

template <typename T>
class BaseManager
{
public:
	static T& getInstance()
	{
		static T instance;
		return instance;
	}

private:
	BaseManager() = default;
	virtual ~BaseManager() = default;
};