#include <Siv3D.hpp> // OpenSiv3D v0.6.5

class Plotter {

	std::list<double> points;
	RectF             parent;      /// グラフを描画する四角形
	const int         resolution;  /// 分解能

public:

	Plotter(const int resolution = 500, RectF&& parent = {}) noexcept
		: points{}
		, parent(std::move(parent))
		, resolution(resolution ? resolution : 1)
	{}

	Plotter& resize(const RectF& r) {
		parent = r;
		return *this;
	}

	Plotter& set(double r) {
		points.push_front(r);
		if (points.size() > resolution) {
			points.pop_back();
		}
		return *this;
	}

	Plotter& draw(const ColorF& color = Palette::White) {

		const RectF plotArea = parent.stretched(-10, -10);

		/// @brief グリッド描画
		for (auto i : step(5 + 1)) {
			plotArea.top().movedBy(0, plotArea.h / 5 * i).draw(Palette::Gray);
		}
		for (auto i : step(5 + 1)) {
			plotArea.left().movedBy(plotArea.w / 5 * i, 0).draw(Palette::Gray);
		}


		const double plotInterval = plotArea.w / (resolution - 1);

		/// @brief 最小最大値取得
		const auto [min, max] = [&]() {
			double max = std::numeric_limits<double>::min();
			double min = std::numeric_limits<double>::max();
			for (const auto& it : points) {
				max = std::max(+abs(it), max);
				min = std::min(it, min);
			}
			return std::make_pair(min, max);
		}();

		const double ratio = plotArea.h / (max - min);  /// オートスケーリング用比率

		Vec2 prevValue = { plotArea.right().end - Vec2{  0, (points.front() - min) * ratio } };

		for (auto [index, value] : Indexed(points)) {
			if (index > resolution)
				break;

			Vec2 currPoint = { plotArea.right().end - Vec2{  index * plotInterval, (value - min) * ratio } };

			Line{ prevValue, currPoint }.draw(2, color);  /// 前回の点とを線分で結ぶ
			prevValue = currPoint;
		}

		parent.drawFrame(2, Palette::Wheat);
		return *this;
	}
};

void Main() {
	Window::SetStyle(WindowStyle::Sizable);

	Plotter plotter1;
	Plotter plotter2;

	while (System::Update()) {
		const auto plotterArea = RectF{ Arg::center(Scene::Size() / 2), Scene::Size() - Vec2{100, 100} };

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
