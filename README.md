# Plotter

## OpenSiv3D Simple Graph Plotter

![image](https://user-images.githubusercontent.com/91818705/199765950-85d84e68-c955-4ca1-b958-7ccaeaea2dfd.png)

## What you can

- plot and graph easily

- auto resizing

- auto scaling

## APIs

- `Plotter(RectF&& parent, int resolution)`

  Generate plotter object
  
  `@param resolution` Number of points to plot (defalt 100)
  
  `@param parent` Rectangle to be drawn (defalt null)

- `resize(RectF& r)`

  Graph resize

- `resize(Plotter& r)`

  Graph resize

- `plot(double r)`

  Add data to be plotted

- `draw(ColorF& color)`

  Plotting graphs
  
- `drawGrid(int horizontal, int vertical, ColorF& color)`

  Drawing a grid of graphs
  
- `getPlotArea()`

  Gets the area where the graph will be drawn.

## sample

```cpp
#include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include "Plotter.h"

void Main() {
	Window::SetStyle(WindowStyle::Sizable);

	Plotter plotter;

	while (System::Update()) {
		const auto plotterArea
			= RectF{ Arg::center = Scene::Center(), Scene::Size() - Vec2{100, 100} };
		plotter
			.resize(plotterArea)
			.plot(Periodic::Sawtooth0_1(5s))
			.drawGrid(5, 4, Palette::Gray)
			.draw(Palette::Blue);
	}
}

```

# Version

OpenSiv3D v0.6.5

Microsoft Visual Studio Community 2022 Version 17.3.6
