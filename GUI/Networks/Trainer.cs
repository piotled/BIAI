using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI.Model;

namespace GUI.Networks
{
	/// <summary>
	/// Trains network
	/// </summary>
	public class Trainer
	{
		/// <summary>
		/// Network to train
		/// </summary>
		Perceptron network;
		/// <summary>
		/// Learn rate provided by user
		/// </summary>
		float learnRate;

		/// <summary>
		/// Saves learn rate and network to test
		/// </summary>
		public Trainer(Perceptron network, float learnRate)
		{
			this.network = network;
			this.learnRate = learnRate;
		}

		/// <summary>
		/// Trains network with use of provided digit
		/// </summary>
		/// <returns></returns>
		public TrainingResult Train(Digit digit)
		{
			List<float> expectedOutput = GetExpectedOutput(digit.Label);
			List<float> actualOutput = network.Run(digit.DigitPixels);
			List<float> nextLayerDeltas, currentLayerDeltas;

			List<Layer> layers = network.GetLayers();

			nextLayerDeltas = GetLastLayerDeltas(expectedOutput, actualOutput, layers.Last());

			for(int i = layers.Count - 2; i >= 0; i--)
			{
				currentLayerDeltas = GetCurrentDeltas(layers[i], layers[i + 1], nextLayerDeltas);
				UpdateWeights(layers[i + 1], nextLayerDeltas);
				nextLayerDeltas = currentLayerDeltas;
			}
			UpdateWeights(layers[0], nextLayerDeltas);

			return new TrainingResult(expectedOutput, actualOutput);
		}

		/// <summary>
		/// Updates weights in provided layer
		/// </summary>
		/// <param name="layer">Layer reference</param>
		/// <param name="layerDeltas">Deltas for layer</param>
		private void UpdateWeights(Layer layer, List<float> layerDeltas)
		{
			Action<int> action = (int index) =>
			{
				layer.Neurons[index].ModifyWeights(layerDeltas[index] * learnRate);
			};
			Parallel.For(0, layer.Neurons.Count, action);
		}

		/// <summary>
		/// Calculates deltas for any hidden layer
		/// </summary>
		/// <param name="currentLayer"></param>
		/// <param name="nextLayer"></param>
		/// <param name="nextLayerDeltas"></param>
		/// <returns>Deltas for current layer</returns>
		private List<float> GetCurrentDeltas(Layer currentLayer, Layer nextLayer, List<float> nextLayerDeltas)
		{
			List<float> deltas = new List<float>();
			for (int i = 0; i < currentLayer.Neurons.Count; i++)
			{
				deltas.Add(0f);
			}
			Action<int> action = (int index) =>
			{
				float delta = currentLayer.Neurons[index].ActivationFunctionDerivativeValue();
				float tmp = 0;
				for (int j = 0; j < nextLayer.Neurons.Count; j++)
				{
					tmp += nextLayerDeltas[j] * nextLayer.Neurons[j].Weights[index];
				}
				delta *= tmp;
				deltas[index] = delta;
			};
			Parallel.For(0, deltas.Count, action);
			return deltas;
		}

		/// <summary>
		/// Calculates deltas for last layer
		/// </summary>
		/// <param name="expectedOutput"></param>
		/// <param name="actualOutput"></param>
		/// <param name="lastLayer"></param>
		/// <returns>Deltas for last layer</returns>
		private List<float> GetLastLayerDeltas(List<float> expectedOutput, List<float> actualOutput, Layer lastLayer)
		{
			List<float> deltas = new List<float>();
			float derivativeValue;
			for(int i = 0; i < actualOutput.Count; i++)
			{
				derivativeValue = lastLayer.Neuron(i).ActivationFunctionDerivativeValue();
				deltas.Add((expectedOutput[i] - actualOutput[i]) * derivativeValue);
			}
			return deltas;
		}

		/// <summary>
		/// Returns expected output vector for provided digit label
		/// </summary>
		/// <param name="label">Digit label</param>
		/// <returns>Expected output vector</returns>
		private List<float> GetExpectedOutput(byte label)
		{
			List<float> expectedOutput = new List<float>();
			for(int i = 0; i < 10; i++)
			{
				expectedOutput.Add(i == label ? 1f : 0f);
			}
			return expectedOutput;
		}
	}
}
