using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Model
{
	/// <summary>
	/// Result of training
	/// </summary>
	public class TrainingResult
	{
		/// <summary>
		/// Calculates error
		/// </summary>
		/// <param name="expectedOutput"></param>
		/// <param name="actualOutput"></param>
		public TrainingResult(List<float> expectedOutput, List<float> actualOutput)
		{
			MeanSquareError = 0;
			for(int i = 0; i < expectedOutput.Count; i++)
			{
				float difference = expectedOutput[i] - actualOutput[i];
				MeanSquareError += difference * difference;
			}
			MeanSquareError /= 10f;
		}

		public float MeanSquareError { get; set; }
	}
}
