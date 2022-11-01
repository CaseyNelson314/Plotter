#include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include "Plotter.h"

void Main() {
	Window::SetStyle(WindowStyle::Sizable);

	Plotter plotter1;
	Plotter plotter2;

	while (System::Update()) {
		const auto plotterArea = RectF{ Arg::center(Scene::Center()), Scene::Size() - Vec2{100, 100} };

		plotter1
			.resize(plotterArea)
			.set(Periodic::Sine0_1(5s) - 0.5)
			.draw(Palette::Blue);

		plotter2
			.resize(plotterArea)
			.set(Periodic::Sine0_1(7s) + Random() / 10)
			.draw(Palette::Red);
	}
}
