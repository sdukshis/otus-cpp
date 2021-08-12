// Абстрактная фабрика (Abstract factory)

#include <iostream>
#include <memory>

struct IEngine {
    virtual void start() = 0;
};

struct IVehicle {
    virtual void run() = 0;
};

struct ISPoiler() {
    virtual void apply() = 0;
}

struct IFactory {
    virtual std::unique_ptr<IEngine> makeEngine() = 0;
    virtual std::unique_ptr<IVehicle> makeVehicle() = 0;
    virtual std::unique_ptr<ISPoiler> makeSpoiler() = 0;
};

enum class Type { Sport, Business, Home };

struct SportVehicle : IVehicle {
    void run() override { std::cout << "Sport vehicle!" << std::endl; }
};
struct SportEngine : IEngine {
    void start() override {
        std::cout << "Sport engine! Grrrrr-grrrr!" << std::endl;
    }
};
struct SportFactory : IFactory {
    std::unique_ptr<IEngine> makeEngine() override {
        return std::unique_ptr<IEngine>(new SportEngine{});
    }
    std::unique_ptr<IVehicle> makeVehicle() override {
        return std::unique_ptr<IVehicle>(new SportVehicle{});
    }
};

struct BusinessDoor {
    virtual void run() = 0;
};

struct BusinessVehicle : IVehicle {
    void run() override { std::cout << "Business vehicle!" << std::endl; }
};
struct BusinessEngine : IEngine {
    void start() override {
        std::cout << "Business engine! Shhhhh." << std::endl;
    }
};
struct BusinessFactory : IFactory {
    std::unique_ptr<IEngine> makeEngine() override {
        return std::unique_ptr<IEngine>(new BusinessEngine{});
    }
    std::unique_ptr<IVehicle> makeVehicle() override {
        return std::unique_ptr<IVehicle>(new BusinessVehicle{});
    }
};

struct HomeVehicle : IVehicle {
    void run() override { std::cout << "Home vehicle!" << std::endl; }
};
struct HomeEngine : IEngine {
    void start() override {
        std::cout << "Home engine! Zzzzzzzzz!" << std::endl;
    }
};
struct HomeFactory : IFactory {
    std::unique_ptr<IEngine> makeEngine() override {
        return std::unique_ptr<IEngine>(new HomeEngine{});
    }
    std::unique_ptr<IVehicle> makeVehicle() override {
        return std::unique_ptr<IVehicle>(new HomeVehicle{});
    }
};

std::unique_ptr<IFactory> makeFactory(Type type) {
    switch (type) {
    case Type::Sport:
        return std::unique_ptr<IFactory>(new SportFactory{});
    case Type::Business:
        return std::unique_ptr<IFactory>(new BusinessFactory{});
    case Type::Home:
        return std::unique_ptr<IFactory>(new HomeFactory{});
    }
    return nullptr;
}

int main() {
    // IFactory ------------------------------
    //           |             |             |
    //   SportFactory  BusinessFactory     HomeFactory
    //
    // IEngine -------------------------------
    //           |             |             |
    //     SportEngine    BusinessEngine   HomeEngine
    //
    // IVehicle -------------------------------
    //           |             |             |
    //     SportVehicle    BusinessVehicle   HomeVehicle

    {
        std::unique_ptr<IFactory> factoryPtr = makeFactory(Type::Sport);

        auto enginePtr = factoryPtr->makeEngine();
        auto vehiclePtr = factoryPtr->makeVehicle();

        enginePtr->start();
        vehiclePtr->run();
    }

    {
        std::unique_ptr<IFactory> factoryPtr = makeFactory(Type::Business);

        auto enginePtr = factoryPtr->makeEngine();
        auto vehiclePtr = factoryPtr->makeVehicle();

        enginePtr->start();
        vehiclePtr->run();
    }

    {
        std::unique_ptr<IFactory> factoryPtr = makeFactory(Type::Home);

        auto enginePtr = factoryPtr->makeEngine();
        auto vehiclePtr = factoryPtr->makeVehicle();

        enginePtr->start();
        vehiclePtr->run();
    }

    return 0;
}
