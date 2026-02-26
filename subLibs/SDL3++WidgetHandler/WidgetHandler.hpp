//
// Created by lr6549 on 2/1/26.
//

#ifndef SDL3_WIDGETS_SDLW_HPP
#define SDL3_WIDGETS_SDLW_HPP

#define SDL3PP_WidgetHandler
#include "SDL3++.hpp"

#include "widget/Widget.hpp"


#include <string>
#include <vector>
#include <unordered_map>

namespace JFLX::sdl3PP {
    class WidgetHandler {
        private:
            std::vector<Widget*> widgets;
            std::unordered_map<std::string, int> identifiers;

        public:

        WidgetHandler();
        ~WidgetHandler();

        void addWidget(Widget* widget);

        void removeWidget(int index);
        void removeWidget(Widget* widget);
        void removeWidget(std::string identifier);

        void renderWidgets();
        void updateWidgets();

        void renderWidget(int index);
        void renderWidget(std::string identifier);
    };
} // JFLX

#endif //SDL3_WIDGETS_SDLW_HPP