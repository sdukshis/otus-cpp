// Фабричный метод (Factory method)

#include <iostream>
#include <memory>
#include <vector>

struct Button {};

struct Edit {};

class UIForm {
  public:
    void addButton(Button btn) {}

    void addEdit(Edit edit) {}

    void show() {}

    void close() {}

  private:
    std::vector<Button> m_buttons;
    std::vector<Edit> m_edits;
};

class NewSuperButton : public Button {
    // Ooooops...
};

class IButton {};
class IEdit {};

class IUIForm {
  public:
    virtual std::unique_ptr<IButton> makeButton() = 0;

    virtual std::unique_ptr<IEdit> makeEdit() = 0;
};

class BaseButton : public IButton {};

class BaseEdit : public IEdit {};

class BaseUIForm : public IUIForm {
  public:
    void addButton() {}

    void addEdit() {}

    void show() {}

    void close() {}

    std::unique_ptr<IButton> makeButton() override {
        return std::make_unique<BaseButton>();
    }

    std::unique_ptr<IEdit> makeEdit() override {
        return std::make_unique<BaseEdit>();
    }

  private:
    std::vector<std::unique_ptr<IButton>> m_buttons;
    std::vector<std::unique_ptr<IEdit>> m_edits;
};

class ModernButton : public IButton {};

class ModernEdit : public IEdit {};

class ModernUIForm : public IUIForm {
  public:
    void addButton() {}

    void addEdit() {}

    void show() {}

    void close() {}

    std::unique_ptr<IButton> makeButton() override {
        return std::make_unique<ModernButton>();
    }

    std::unique_ptr<IEdit> makeEdit() override {
        return std::make_unique<ModernEdit>();
    }

  private:
    std::vector<std::unique_ptr<IButton>> m_buttons;
    std::vector<std::unique_ptr<IEdit>> m_edits;
};

int main() { return 0; };
