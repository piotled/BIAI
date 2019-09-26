using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Networks
{
	/// <summary>
	/// Mathematical sigmoid function
	/// </summary>
	public class Sigmoid
	{
		public static float Calc(float input) 
		{
			float e = 2.71828182846f;
			return 1.0f / (1.0f + (float)Math.Pow(e, -input));
		}
	}
}

