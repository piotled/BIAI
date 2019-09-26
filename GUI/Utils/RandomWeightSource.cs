using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Utils
{
	public class RandomWeightSource : IWeightSource
	{
		Random random = new Random();

		/// <summary>
		/// Generates random float from range -1 to 1 
		/// </summary>
		/// <returns>Randow float from range -1;1</returns>
		public float GetWeight()
		{
			return (float)random.NextDouble() * 2f - 1f;
		}
	}
}
