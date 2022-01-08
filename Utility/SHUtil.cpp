#include "SHUtil.h"

namespace sh
{
	double basisSH00(const cv::Vec3d& d) {
		// 0.5 * sqrt(1/pi)
		return 0.282095;
	}

	double basisSH1n1(const cv::Vec3d& d) {
		// -sqrt(3/(4pi)) * y
		return -0.488603 * d[1];
	}

	double basisSH10(const cv::Vec3d& d) {
		// sqrt(3/(4pi)) * z
		return 0.488603 * d[2];
	}

	double basisSH1p1(const cv::Vec3d& d) {
		// -sqrt(3/(4pi)) * x
		return -0.488603 * d[0];
	}

	double basisSH2n2(const cv::Vec3d& d) {
		// 0.5 * sqrt(15/pi) * x * y
		return 1.092548 * d[0] * d[1];
	}

	double basisSH2n1(const cv::Vec3d& d) {
		// -0.5 * sqrt(15/pi) * y * z
		return -1.092548 * d[1] * d[2];
	}

	double basisSH20(const cv::Vec3d& d) {
		// 0.25 * sqrt(5/pi) * (-x^2-y^2+2z^2)
		return 0.315392 * (-d[0] * d[0] - d[1] * d[1] + 2.0 * d[2] * d[2]);
	}

	double basisSH2p1(const cv::Vec3d& d) {
		// -0.5 * sqrt(15/pi) * x * z
		return -1.092548 * d[0] * d[2];
	}

	double basisSH2p2(const cv::Vec3d& d) {
		// 0.25 * sqrt(15/pi) * (x^2 - y^2)
		return 0.546274 * (d[0] * d[0] - d[1] * d[1]);
	}

	std::array<std::function<double(const cv::Vec3d&)>, 9> SHUtil::SHB = {
		basisSH00,
		basisSH1n1,basisSH10,basisSH1p1,
		basisSH2n2,basisSH2n1,basisSH20,basisSH2p1,basisSH2p2
	};

	cv::Vec3d SHUtil::toVector(double phi, double theta)
	{
		double r = std::sin(theta);
		return cv::Vec3d(-r * std::sin(phi), std::cos(theta), r * std::cos(phi));
	}

	std::unique_ptr<std::array<double, 9> > SHUtil::getFloatCoeffSH(const FloatSphericalFunction& func, int sampleCount)
	{
		std::unique_ptr<std::array<double, 9> > coeffSH(new std::array<double, 9>({ 0,0,0,0,0,0,0,0,0 }));

		sampleCount = std::max(sampleCount, 10000);
		cv::RNG rng(0);
		for (int i = 0; i < sampleCount; i++)
		{
			double phi = PI2 * rng.uniform(0.0, 1.0);
			double theta = std::acos(2 * rng.uniform(0.0, 1.0) - 1);
			cv::Vec3d direction = toVector(phi, theta);
			double value = func(direction);
			for (size_t k = 0; k < coeffSH->size(); k++)
				(*coeffSH)[k] += (SHB[k](direction) * value);
		}

		double weight = PI4 / sampleCount;
		for (size_t k = 0; k < coeffSH->size(); k++)
			(*coeffSH)[k] *= weight;

		return coeffSH;
	}

	std::unique_ptr<std::array<cv::Vec3d, 9> > SHUtil::getVectorCoeffSH(const VectorSphericalFunction& func, int sampleCount)
	{
		std::unique_ptr<std::array<cv::Vec3d, 9> > coeffSH(new std::array<cv::Vec3d, 9>());

		cv::Vec3d zero(0, 0, 0);
		std::fill(coeffSH->begin(), coeffSH->end(), zero);

		sampleCount = std::max(sampleCount, 10000);
		cv::RNG rng(0);
		for (int i = 0; i < sampleCount; i++)
		{
			double phi = PI2 * rng.uniform(0.0, 1.0);
			double theta = std::acos(2 * rng.uniform(0.0, 1.0) - 1);
			cv::Vec3d direction = toVector(phi, theta);
			cv::Vec3d value = func(direction);
			for (size_t k = 0; k < coeffSH->size(); k++)
				(*coeffSH)[k] += (SHB[k](direction) * value);
		}

		double weight = PI4 / sampleCount;
		for (size_t k = 0; k < coeffSH->size(); k++)
			(*coeffSH)[k] *= weight;

		return coeffSH;
	}
	std::unique_ptr<std::vector<cv::Vec3d> > SHUtil::getSampleVectors(int sampleCount)
	{
		sampleCount = std::max(sampleCount, 10000);
		std::unique_ptr<std::vector<cv::Vec3d> > samples(new std::vector<cv::Vec3d>());
		cv::RNG rng(0);
		for (int i = 0; i < sampleCount; i++)
		{
			double phi = PI2 * rng.uniform(0.0, 1.0);
			double theta = std::acos(2 * rng.uniform(0.0, 1.0) - 1);
			cv::Vec3d direction = toVector(phi, theta);
			samples->push_back(direction);
		}
		return samples;
	}
}