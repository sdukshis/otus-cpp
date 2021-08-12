#pragma once

#include <fmt/color.h>
#include <fmt/core.h>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

const size_t max_width = 40;

class Header {
  public:
    virtual void draw(std::ostream &) const = 0;
    virtual ~Header() = default;
};

class Footer {
  public:
    virtual void draw(std::ostream &) const = 0;
    virtual ~Footer() = default;
};

class SlidesFactory {
  public:
    virtual std::unique_ptr<Header>
    create_header(const std::string_view text) const = 0;
    virtual std::unique_ptr<Footer>
    create_footer(const std::string_view text) const = 0;
    virtual ~SlidesFactory() = default;
};

class CenteredHeader : public Header {
  public:
    CenteredHeader(const std::string_view text) : text_{text} {}

    ~CenteredHeader() override = default;

    void draw(std::ostream &stream) const override {
        stream << fmt::format("{:^{}}\n\n", text_, max_width);
    }

  private:
    std::string text_;
};

class LeftAlignedHeader : public Header {
  public:
    LeftAlignedHeader(const std::string_view text) : text_{text} {}

    ~LeftAlignedHeader() override = default;

    void draw(std::ostream &stream) const override {
        stream << fmt::format("{:<{}}\n\n", text_, max_width);
    }

  private:
    std::string text_;
};

class LeftAlignedFooter : public Footer {
  public:
    LeftAlignedFooter(const std::string_view text) : text_{text} {}

    ~LeftAlignedFooter() override = default;

    void draw(std::ostream &stream) const override {
        stream << fmt::format("\n{:<{}}\n", text_, max_width);
    }

  private:
    std::string text_;
};

class RightAlignedFooter : public Footer {
  public:
    RightAlignedFooter(const std::string_view text) : text_{text} {}

    ~RightAlignedFooter() override = default;

    void draw(std::ostream &stream) const override {
        stream << fmt::format("\n{:>{}}\n", text_, max_width);
    }

  private:
    std::string text_;
};

class ClassicSlidesFactory : public SlidesFactory {
  public:
    std::unique_ptr<Header>
    create_header(const std::string_view text) const override {
        return std::make_unique<LeftAlignedHeader>(text);
    }
    std::unique_ptr<Footer>
    create_footer(const std::string_view text) const override {
        return std::make_unique<LeftAlignedFooter>(text);
    }

    ~ClassicSlidesFactory() override = default;
};

class ModerSlidesFactory : public SlidesFactory {
  public:
    std::unique_ptr<Header>
    create_header(const std::string_view text) const override {
        return std::make_unique<CenteredHeader>(text);
    }
    std::unique_ptr<Footer>
    create_footer(const std::string_view text) const override {
        return std::make_unique<RightAlignedFooter>(text);
    }

    ~ModerSlidesFactory() override = default;
};