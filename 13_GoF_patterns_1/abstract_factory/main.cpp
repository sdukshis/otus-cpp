#include <iostream>
#include <list>

#include "slides.h"

void draw_slide_with_style(const std::unique_ptr<SlidesFactory> &factory) {
    auto header = factory->create_header("Header");
    auto footer = factory->create_footer("Footer");

    header->draw(std::cout);
    std::cout << "* Bullet 1\n"
                 "* Bullet 2\n"
                 "* Bullet 3\n";
    footer->draw(std::cout);
}

int main() {
    std::unique_ptr<SlidesFactory> factory =
        std::make_unique<ModerSlidesFactory>();
    draw_slide_with_style(factory);
}