using GUI.Networks;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Utils
{
	/// <summary>
	/// Writes network to file
	/// </summary>
	public class NetworkFileWriter
	{
		FileStream fileStream;
		byte[] buffer32 = new byte[4]; 

		public NetworkFileWriter(string filePath)
		{
			fileStream = new FileStream(filePath, FileMode.Create);
		}

		/// <summary>
		/// Writes file header containing network structure
		/// </summary>
		/// <param name="firstLayer"></param>
		/// <param name="layers"></param>
		public void WriteNetworkStructure(List<float> firstLayer, List<Layer> layers)
		{
			buffer32 = BitConverter.GetBytes((uint)(layers.Count + 1));
			fileStream.Write(buffer32, 0, 4);
			buffer32 = BitConverter.GetBytes((uint)firstLayer.Capacity);
			fileStream.Write(buffer32, 0, 4);
			foreach(Layer layer in layers)
			{
				buffer32 = BitConverter.GetBytes((uint)layer.Neurons.Count);
				fileStream.Write(buffer32, 0, 4);
			}
		}

		/// <summary>
		/// Writes weights, starting from first neuron in last layer to last neuron in first hidden layer
		/// </summary>
		/// <param name="layers"></param>
		public void WriteWeights(List<Layer> layers)
		{
			for (int i = layers.Count - 1; i >= 0; i--)
			{
				foreach(Neuron neuron in layers[i].Neurons)
				{
					foreach(float weight in neuron.Weights)
					{
						buffer32 = BitConverter.GetBytes(weight);
						fileStream.Write(buffer32, 0, 4);
					}
				}
			}
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
