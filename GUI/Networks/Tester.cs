using GUI.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Networks
{
	/// <summary>
	/// Tests network
	/// </summary>
	public class Tester
	{
		/// <summary>
		/// Network to test
		/// </summary>
		private Perceptron network;

		/// <summary>
		/// Creates tester with network to test
		/// </summary>
		/// <param name="perceptron">Network to test</param>
		public Tester(Perceptron perceptron)
		{
			network = perceptron;
		}

		/// <summary>
		/// Test for provided digit
		/// </summary>
		/// <returns>Object containing test results</returns>
		public TestResult Test(Digit digit)
		{
			List<float> networkOutput = network.Run(digit.DigitPixels);
			float max = networkOutput.Max();
			int indexOfMax = networkOutput.IndexOf(max);
			return new TestResult { Label = digit.Label.ToString(), ClassifiedAs = indexOfMax.ToString(), Correct = digit.Label == indexOfMax};
		}

		/// <summary>
		/// Tests for network input
		/// </summary>
		/// <param name="digitPixels">Network input</param>
		/// <returns>Object containing test results</returns>
		public TestResult Test(List<float> digitPixels)
		{
			List<float> networkOutput = network.Run(digitPixels);
			float max = networkOutput.Max();
			int indexOfMax = networkOutput.IndexOf(max);
			return new TestResult { ClassifiedAs = indexOfMax.ToString()};
		}
	}
}
