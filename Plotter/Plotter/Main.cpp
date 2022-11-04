#include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include "Plotter.h"

void Main() {
	Window::SetStyle(WindowStyle::Sizable);

	Plotter plotter1;
	Plotter plotter2;

	while (System::Update()) {
		const auto plotterArea
			= RectF{ Arg::center = Scene::Center(), Scene::Size() - Vec2{100, 100} };

		plotter1
			.resize(plotterArea)
			.plot(Periodic::Sawtooth0_1(5s))
			.drawGrid(5, 4, Palette::Gray)
			.draw(Palette::Blue);

		plotter2
			.resize(plotter1)
			.plot(Periodic::Sine0_1(2s))
			.draw(Palette::Red);
	}
}
