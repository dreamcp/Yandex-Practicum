#pragma once

#include <chrono>
#include <iostream>

#define PROFILE_CONCAT_INTERNAL(X, Y) X ## Y
#define PROFILE_CONCAT(X, Y) PROFILE_CONCAT_INTERNAL(X, Y)
#define UNIQUE_VAR_NAME_PROFILE PROFILE_CONCAT(profileGuard, __LINE__)
#define LOG_DURATION(x) LogDuration UNIQUE_VAR_NAME_PROFILE(x) 

class LogDuration {
public:
    using Clock = std::chrono::steady_clock;

    LogDuration(const std::string& func_name) :
    func_name_(func_name)
    {
    }

    ~LogDuration() {
        using namespace std::chrono;
        using namespace std::literals;
        // эта переменная сохранит время уничтожения объекта:
        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        std::cerr << func_name_<< ": " << duration_cast<milliseconds>(dur).count() << " ms"s << std::endl;
    }

private:
    // Переменная будет инициализирована текущим моментом времени при
    // создании объекта класса.
    // Таким образом, она хранит время создания объекта.
    const Clock::time_point start_time_ = Clock::now();
    std::string func_name_;
};
