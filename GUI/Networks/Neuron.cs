using GUI.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.Networks
{
	/// <summary>
	/// Class representing neuron
	/// </summary>
	public class Neuron
	{
		/// <summary>
		/// Inputs if prevoius layer is hidden layer
		/// </summary>
		List<Neuron> inputs;
		/// <summary>
		/// Inputs if previous layer is input layer
		/// </summary>
		List<float> firstLayer;
		/// <summary>
		/// List of weights
		/// </summary>
		List<float> weights;
		/// <summary>
		/// Weight source used to create neuron
		/// </summary>
		IWeightSource weightSource;
		/// <summary>
		/// Output value holder
		/// </summary>
		float outputValue = 0;

		/// <summary>
		/// Accesses weights
		/// </summary>
		public List<float> Weights
		{
			get
			{
				return weights;
			}
		}

		/// <summary>
		/// Accesses output value
		/// </summary>
		public float Output
		{
			get
			{
				return outputValue;
			}
		}

		/// <summary>
		/// Constructs neuron
		/// </summary>
		/// <param name="weightSource"></param>
		public Neuron(IWeightSource weightSource)
		{
			weights = new List<float>();
			this.weightSource = weightSource;
		}

		/// <summary>
		/// Connects hidden layer neurons to this neuron
		/// </summary>
		/// <param name="inputNeurons">Previous layer neurons</param>
		public void ConnectInputs(List<Neuron> inputNeurons)
		{
			inputs = inputNeurons;
			for(int i = 0; i < inputNeurons.Count + 1; i++)
			{
				weights.Add(weightSource.GetWeight());
			}
		}

		/// <summary>
		/// Connects first layer to this neuron
		/// </summary>
		/// <param name="firstLayer"></param>
		public void ConnectInputs(List<float> firstLayer)
		{
			this.firstLayer = firstLayer; 
			for (int i = 0; i < firstLayer.Capacity + 1; i++)
			{
				weights.Add(weightSource.GetWeight());
			}
		}

		/// <summary>
		/// Activation function derivative : in this case sigmoid derivative
		/// </summary>
		/// <returns></returns>
		internal float ActivationFunctionDerivativeValue()
		{
			return outputValue * (1 - outputValue);
		}

		/// <summary>
		/// Calculates output of neuron
		/// </summary>
		internal void CalculateOutput()
		{
			outputValue = 0;
			if(firstLayer == null)
			{
				for (int i = 0; i < inputs.Count; i++)
				{
					outputValue += inputs[i].outputValue * weights[i];
				}
			}
			else
			{
				for (int i = 0; i < firstLayer.Count; i++)
				{
					outputValue += firstLayer[i] * weights[i];
				}
			}
			outputValue += weights.Last();
			outputValue = Sigmoid.Calc(outputValue);
		}

		/// <summary>
		/// Modifies all weights with provided factor
		/// </summary>
		internal void ModifyWeights(float modifyFactor)
		{
			int i = 0;
			for (; i < weights.Count - 1; i++)
			{
				weights[i] += modifyFactor * (firstLayer == null ? inputs[i].outputValue : firstLayer[i]);
			}
			weights[i] += modifyFactor;
		}
	}
}
