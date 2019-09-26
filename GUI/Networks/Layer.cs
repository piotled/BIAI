using GUI.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Networks
{
	/// <summary>
	/// Represents layer.
	/// </summary>
	public class Layer
	{
		List<Neuron> neurons;

		/// <summary>
		/// List of neurons in layer
		/// </summary>
		public List<Neuron> Neurons
		{
			get
			{
				return neurons;
			}
		}

		/// <summary>
		/// Constructs layer
		/// </summary>
		/// <param name="neuronCount">Number of neurons in layer</param>
		/// <param name="weightSource">Source of weight values for neurons, either file or random number generator</param>
		public Layer(uint neuronCount, IWeightSource weightSource)
		{
			neurons = new List<Neuron>();
			for(int i = 0; i < neuronCount; i++)
			{
				neurons.Add(new Neuron(weightSource));
			}
		}

		/// <summary>
		/// Connects neurons from pravous layer to this layer neurons
		/// </summary>
		/// <param name="previousLayerNeurons"></param>
		public void ConnectInputs(List<Neuron> previousLayerNeurons)
		{
			foreach(Neuron neuron in neurons)
			{
				neuron.ConnectInputs(previousLayerNeurons);
			}
		}

		/// <summary>
		/// Connects first layer to this layer. FIrst layer is actually a vector of values.
		/// </summary>
		/// <param name="firstLayer"></param>
		public void ConnectInputs(List<float> firstLayer)
		{
			foreach (Neuron neuron in neurons)
			{
				neuron.ConnectInputs(firstLayer);
			}
		}

		/// <summary>
		/// Gets neuron at specified index
		/// </summary>
		internal Neuron Neuron(int i)
		{
			return neurons[i];
		}

		/// <summary>
		/// Calculates output for every neuron in layer
		/// </summary>
		internal void Calculate()
		{
			Parallel.For(0, neurons.Count, (int index) =>
			{
				neurons[index].CalculateOutput();
			});
		}
	}
}
