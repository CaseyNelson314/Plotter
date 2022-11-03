#pragma once

class Plotter {

	std::list<double> points;
	RectF             parent;      /// グラフを描画する四角形
	const int         resolution;  /// 分解能

public:

	Plotter(const int resolution = 1000, RectF&& parent = {}) noexcept
		: points{}
		, parent(std::move(parent))
		, resolution(resolution ? resolution : 1)
	{}

	Plotter& resize(const RectF& r) {
		parent = r;
		return *this;
	}

	Plotter& put(double r) {
		points.push_front(r);
		if (points.size() > resolution) {
			points.pop_back();
		}
		return *this;
	}

	Plotter& draw(const ColorF& color = Palette::White) {

		const RectF plotArea = parent.stretched(-20, -20);

		if (plotArea.h >= 0 && plotArea.w >= 0) {

			/// @brief グリッド描画
			for (auto i : step(5 + 1)) {
				plotArea.top().movedBy(0, plotArea.h / 5 * i).draw(Palette::Gray);
			}
			for (auto i : step(5 + 1)) {
				plotArea.left().movedBy(plotArea.w / 5 * i, 0).draw(Palette::Gray);
			}


			/// @brief 最小最大値取得
			double max = std::numeric_limits<double>::min();
			double min = std::numeric_limits<double>::max();
			for (const auto& it : points) {
				max = std::max(abs(it), max);
				min = std::min(it, min);
			}

			/// @brief 点の高さを求める
			const auto dataToPointHeight = [&](double data) ->double {
				const double ratio = plotArea.h / (max - min) * 0.9/*margin top*/;  /// オートスケーリング用比率
				return plotArea.right().end.y - (data - min) * ratio;
			};

			/// @brief 線分開始位置
			Vec2 holdPoint = {
				plotArea.right().end.x,          
				dataToPointHeight(points.front())
			};

			const double plotInterval = plotArea.w / (resolution - 1);

			for (auto it = points.begin()++; it != points.end(); ++it) {
				const Vec2 begin = holdPoint;

				holdPoint.x -= plotInterval;
				holdPoint.y  = dataToPointHeight(*it);

				const Vec2 end = holdPoint;

				Line{ begin, end }.draw(2, color);  /// 前回の点とを線分で結ぶ
			}

			plotArea.drawFrame(2, Palette::White);
		}

		parent.drawFrame(2, Palette::White);
		return *this;
	}
};
