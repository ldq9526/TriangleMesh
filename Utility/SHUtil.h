#ifndef SH_UTIL_H
#define SH_UTIL_H

#include <opencv2/opencv.hpp>

#include <array>
#include <vector>
#include <functional>
#include <memory>

namespace sh
{
	const double PI = 3.14159265;
	const double PI2 = 6.2831853;
	const double PI4 = 12.5663706;

	typedef std::function<double(const cv::Vec3d&)> FloatSphericalFunction;
	typedef std::function<cv::Vec3d(const cv::Vec3d&)> VectorSphericalFunction;

	class SHUtil
	{
	private:
		static std::array<std::function<double(const cv::Vec3d&)>, 9> SHB;

	private:
		/// <summary>
		/// 球坐标转 OpenGL 坐标系坐标
		/// </summary>
		/// <param name="phi">[0, 2*pi]</param>
		/// <param name="theta">[0, pi]</param>
		/// <returns></returns>
		static cv::Vec3d toVector(double phi, double theta);

	public:
		/// <summary>
		/// 估计2阶(9个)球谐系数
		/// </summary>
		/// <param name="func"></param>
		/// <param name="sampleCount"></param>
		/// <returns></returns>
		static std::unique_ptr<std::array<double, 9> > getFloatCoeffSH(const FloatSphericalFunction& func, int sampleCount = 10000);

		/// <summary>
		/// 估计2阶(9个)球谐系数
		/// </summary>
		/// <param name="func"></param>
		/// <param name="sampleCount"></param>
		/// <returns></returns>
		static std::unique_ptr<std::array<cv::Vec3d, 9> > getVectorCoeffSH(const VectorSphericalFunction& func, int sampleCount = 10000);

		/// <summary>
		/// 获取采样方向数组
		/// </summary>
		static std::unique_ptr<std::vector<cv::Vec3d> > getSampleVectors(int sampleCount = 10000);
	};
}

#endif