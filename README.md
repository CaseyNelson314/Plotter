# Plotter

## OpenSiv3D Simple Graph Plotter

![image](https://user-images.githubusercontent.com/91818705/199291825-11d5247d-8d80-47d7-93c8-9bb55a530bb8.png)

## What you can

- plot and graph easily

- auto resizing

- auto scaling

## APIs

- `Plotter(int resolution, RectF&& parent)`

  Generate plotter object
  
  `@param resolution` Number of points to plot (defalt 100)
  
  `@param parent` Rectangle to be drawn (defalt null)

- `Plotter& resize(RectF& r)`

  Graph resize
  
  `@param r` Rectangle to be drawn

- `Plotter& set(double r)`

  Add data to be plotted
  
  `@param r` data

- `Plotter& draw(const ColorF& color = Palette::White)`

  Plotting graphs
  
  `@param color` Graph color

## sample

```cpp
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

```

# Version

OpenSiv3D v0.6.5

Microsoft Visual Studio Community 2022 Version 17.3.6
