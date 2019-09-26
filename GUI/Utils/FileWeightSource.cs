using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Utils
{
	/// <summary>
	/// Source of neuron weights. Weights read from file.
	/// </summary>
	public class FileWeightSource : IWeightSource
	{
		FileStream fileStream;
		byte[] floatBuffer = new byte[sizeof(float)]; 

		/// <summary>
		/// Saves provided file stream
		/// </summary>
		/// <param name="openedFileStream">Opened file stream</param>
		public FileWeightSource(FileStream openedFileStream)
		{
			fileStream = openedFileStream;
		}

		/// <summary>
		/// Reads 4 bytes from file, converts it into float and returns converted number
		/// </summary>
		/// <returns>Read float</returns>
		public float GetWeight()
		{
			fileStream.Read(floatBuffer, 0, floatBuffer.Length);
			return BitConverter.ToSingle(floatBuffer, 0);
		}
	}
}
