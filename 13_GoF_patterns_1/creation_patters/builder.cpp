// Строитель (Builder)

#include <string>

class Car {
  public:
    Car(const std::string &model, const std::string &year,
        const std::string &type)
        : m_model(model), m_year(year), m_type(type) {}

    Car(const std::string &model, const std::string &year,
        const std::string &type, const std::string &additional)
        : m_model(model), m_year(year), m_type(type), m_additional(additional) {

    }

  private:
    std::string m_model;
    std::string m_year;
    std::string m_type;
    std::string m_additional = "None";
};

void testCar() {
    Car car1("tesla", "2018", "S");

    Car car2("2018", "tesla", "S");
}

class CarWithSetters {
  public:
    CarWithSetters() {}
    void setModel(const std::string &model) { m_model = model; }

    void setYear(const std::string &year) { m_year = year; }

    void setType(const std::string &type) { m_type = type; }

    void setAdditional(const std::string &additional) {
        m_additional = additional;
    }

  private:
    std::string m_model;
    std::string m_year;
    std::string m_type;
    std::string m_additional = "None";
};

void testCarWithSetters() {
    CarWithSetters car;
    car.setModel("Tesla");
    car.setYear("2018");
    car.setType("S");

    // work with car
}

class CarBuilder {
  public:
    CarBuilder() = default;
    ~CarBuilder() = default;

    CarBuilder &withModel(const std::string &model) {
        m_model = model;
        return *this;
    }

    CarBuilder &withYear(const std::string &year) {
        m_year = year;
        return *this;
    }

    CarBuilder &withType(const std::string &type) {
        m_type = type;
        return *this;
    }

    CarBuilder &withAdditional(const std::string &additional) {
        m_additional = additional;
        return *this;
    }

    Car build() { return Car{m_model, m_year, m_type, m_additional}; }

  private:
    std::string m_model = "model";
    std::string m_year = "year";
    std::string m_type = "type";
    std::string m_additional = "None";
};

void testBuilder() {
    CarBuilder builder;

    Car car = builder.withType("S").withModel("Tesla").withYear("2018").build();
}

int main() {

    testBuilder();

    return 0;
}
