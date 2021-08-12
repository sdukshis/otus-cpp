#pragma once

#include <memory>
#include <ostream>
#include <string>

#include <fmt/color.h>
#include <fmt/core.h>

class Element {
  public:
    virtual std::unique_ptr<Element> clone() const = 0;

    virtual void draw(std::ostream &) const = 0;

    virtual ~Element() = default;
};

class TextBox : public Element {
  public:
    enum class Style {
        Normal,
        Bold,
        Italic,
    };

    TextBox() : text_{}, style_{Style::Normal} {}

    explicit TextBox(const std::string &text, Style style = Style::Normal)
        : text_{text}, style_{style} {}

    TextBox(const TextBox &other) = default;

    TextBox &operator=(const TextBox &other) = default;

    std::unique_ptr<Element> clone() const override {
        return std::make_unique<TextBox>(text_, style_);
    }

    void draw(std::ostream &stream) const override {
        stream << fmt::format(to_fmt_style(style_), text_) << '\n';
    }

    void set_text(const std::string &text) { text_ = text; }

    const std::string &get_text() const { return text_; }

    void set_style(const Style style) { style_ = style; }

    Style get_style() const { return style_; }

  protected:
    static fmt::text_style to_fmt_style(const Style style) {
        switch (style) {
        case Style::Normal:
            return {};
        case Style::Bold:
            return fmt::emphasis::bold;
        case Style::Italic:
            return fmt::emphasis::italic;
        }
    }

  private:
    std::string text_;
    Style style_;
};
