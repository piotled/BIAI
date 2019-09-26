using GUI.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Networks
{
	/// <summary>
	/// Perceptron neural network
	/// </summary>
	public class Perceptron
	{
		/// <summary>
		/// Network hidden and last layers
		/// </summary>
		List<Layer> layers;
		/// <summary>
		/// Network input layer
		/// </summary>
		List<float> inputLayer;

		/// <summary>
		/// Returns network structure description
		/// </summary>
		public string Description
		{
			get
			{
				string description = (layers.Count + 1) + " layered perceptron \r\n";
				description += "1: " + inputLayer.Capacity + "\r\n";
				for(int i = 0; i < layers.Count; i++)
				{
					description += (i + 2) + ": " + (layers[i].Neurons.Count) + "\r\n";
				}
				return description;
			}
		}

		/// <summary>
		/// Constructs network from file
		/// </summary>
		/// <param name="filePath"></param>
		public Perceptron(string filePath)
		{
			NetworkFileReader reader = null;
			try
			{
				reader = new NetworkFileReader(filePath);
				List<uint> layerElementCountArray = reader.ReadNetworkStructure();
				IWeightSource weightSource = reader.GetWeightSource();
				Construct(layerElementCountArray, weightSource);
			}
			catch
			{
				throw;
			}
			finally
			{
				reader?.Close();
			}
		}

		/// <summary>
		/// Constructs network from structure description
		/// </summary>
		/// <param name="layerElementCountArray">List in which every element describes corresponding layer neuron count</param>
		public Perceptron(List<uint> layerElementCountArray)
		{
			Construct(layerElementCountArray, new RandomWeightSource());
		}

		/// <summary>
		/// Calculates output for provided input
		/// </summary>
		/// <param name="digitPixels">Network input</param>
		/// <returns>Network output</returns>
		public List<float> Run(List<float> digitPixels)
		{
			if(digitPixels.Count == inputLayer.Capacity)
			{
				inputLayer.Clear();
				for(int i = 0; i < digitPixels.Count; i++)
				{
					inputLayer.Add(digitPixels[i]);
				}
				foreach(Layer layer in layers)
				{
					layer.Calculate();
				}
				return GetOutput();
			}
			else
			{
				throw new Exception("Provided input doesn't match in length with input layer");
			}
		}

		/// <summary>
		/// Returns output from last layer
		/// </summary>
		private List<float> GetOutput()
		{
			List<float> output = new List<float>();
			foreach(Neuron neuron in layers.Last().Neurons)
			{
				output.Add(neuron.Output);
			}
			return output;
		}

		/// <summary>
		/// Accesses layers
		/// </summary>
		internal List<Layer> GetLayers()
		{
			return layers;
		}

		/// <summary>
		/// Saves network to specified file
		/// </summary>
		/// <param name="filePath">File to which network will be saved</param>
		public void Save(string filePath)
		{
			NetworkFileWriter writer = null;
			try
			{
				writer = new NetworkFileWriter(filePath);
				writer.WriteNetworkStructure(inputLayer, layers);
				writer.WriteWeights(layers);
			}
			catch
			{
				throw;
			}
			finally
			{
				writer?.Close();
			}
		}

		/// <summary>
		/// Creates layers
		/// </summary>
		/// <param name="layerElementCountArray">Network format description</param>
		/// <param name="weightSource">Weight source, either file or random number generator</param>
		private void Construct(List<uint> layerElementCountArray, IWeightSource weightSource)
		{
			if(ValidateStructure(layerElementCountArray))
			{
				inputLayer = new List<float>((int)layerElementCountArray[0]);
				layers = new List<Layer>();
				for(int i = 1; i < layerElementCountArray.Count; i++)
				{
					layers.Add(new Layer(layerElementCountArray[i], weightSource));
				}
				Connect();
			}
			else
			{
				throw new Exception("Invalid network structure");
			}
		}

		/// <summary>
		/// Connects layers
		/// </summary>
		private void Connect()
		{
			for(int i = layers.Count - 1; i > 0; i--)
			{
				layers[i].ConnectInputs(layers[i - 1].Neurons);
			}
			layers[0].ConnectInputs(inputLayer);
		}

		/// <summary>
		/// Checks if provided network format description is correct. Atl least 3 layers
		/// </summary>
		/// <param name="layerElementCountArray">Network format description</param>
		/// <returns>true if correct, false otherwise</returns>
		private bool ValidateStructure(List<uint> layerElementCountArray)
		{
			if (layerElementCountArray != null && layerElementCountArray.Count >= 3)
			{
				foreach(uint count in layerElementCountArray)
				{
					if (count == 0)
						return false;
				}
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
