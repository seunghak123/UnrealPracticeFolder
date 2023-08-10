#pragma once
template <typename T>
class ManagerSingleton
{
public:
    ManagerSingleton() {}
    ManagerSingleton(const ManagerSingleton& ref) {}
    ManagerSingleton& operator=(const ManagerSingleton& ref) {}
    ~ManagerSingleton() {}
    static T& getInstance()
    {
        static T instance;
        return instance;
    }
};

