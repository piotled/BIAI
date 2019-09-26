using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Utils
{
	/// <summary>
	/// Class used to read network from file
	/// </summary>
	public class NetworkFileReader
	{
		FileStream fileStream;
		byte[] buffer32 = new byte[4]; 

		public NetworkFileReader(string filePath)
		{
			fileStream = new FileStream(filePath, FileMode.Open);
		}

		/// <summary>
		/// Reads file headers
		/// </summary>
		/// <returns>Network format description</returns>
		public List<uint> ReadNetworkStructure()
		{
			fileStream.Read(buffer32, 0, 4);
			uint numberOfLayers = BitConverter.ToUInt32(buffer32, 0);
			List<uint> layerElementCountArray = new List<uint>();
			for(int i = 0; i < numberOfLayers; i++)
			{
				fileStream.Read(buffer32, 0, 4);
				layerElementCountArray.Add(BitConverter.ToUInt32(buffer32, 0));
			}
			return layerElementCountArray;
		}

		/// <summary>
		/// Returns weight source associated with current file
		/// </summary>
		public IWeightSource GetWeightSource()
		{
			return new FileWeightSource(fileStream);
		}

		/// <summary>
		/// Closes file stream
		/// </summary>
		public void Close()
		{
			fileStream.Close();
		}
	}
}
