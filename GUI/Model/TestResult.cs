using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Model
{
	/// <summary>
	/// Digit set test result
	/// </summary>
	public class TestResult
	{
		/// <summary>
		/// Test was correct
		/// </summary>
		public bool Correct { get; set; }
		/// <summary>
		/// Tested digit label
		/// </summary>
		public string Label { get; set; }
		/// <summary>
		/// Label indicated by network
		/// </summary>
		public string ClassifiedAs { get; set; }
	}
}
