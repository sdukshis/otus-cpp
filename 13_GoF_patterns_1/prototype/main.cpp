#include <iostream>

#include "wysiwyg.h"
#include <list>

int main() {
    std::list<std::unique_ptr<Element>> elements;
    auto active_element = elements.end();
    active_element = elements.emplace(
        active_element,
        std::make_unique<TextBox>("Prototype", TextBox::Style::Bold));
    active_element =
        elements.emplace(std::next(active_element), std::make_unique<TextBox>("Props"));
    active_element = elements.emplace(
        std::next(active_element),
        std::make_unique<TextBox>(
            "You can clone objects without coupling to their concrete classes",
            TextBox::Style::Italic));
    // user copies active element two times
    active_element = elements.emplace(std::next(active_element), active_element->get()->clone());
    active_element = elements.emplace(std::next(active_element), active_element->get()->clone());

    for (auto &elem : elements) {
        elem->draw(std::cout);
    }
}
