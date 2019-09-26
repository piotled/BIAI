using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI.Controls
{
	/// <summary>
	/// Control used to manage neural network
	/// </summary>
	public partial class NeuralNetworkControl : UserControl
	{
		/// <summary>
		/// Invoked when user decides to load network from file
		/// </summary>
		public delegate void LoadNetworkDelegate(string filePath);
		/// <summary>
		/// Invoked when user decides to create new network 
		/// </summary>
		public delegate void CreateNetworkDelegate(uint[] networkFormat);
		/// <summary>
		/// Invoked when user decides to save network
		/// </summary>
		public delegate void SaveNetworkDelegate(string filePath);
		/// <summary>
		/// Invoked when user decides to delete network
		/// </summary>
		public delegate void ClearNetworkDelegate();

		public LoadNetworkDelegate LoadNetwork;
		public CreateNetworkDelegate CreateNetwork;
		public SaveNetworkDelegate SaveNetwork;
		public ClearNetworkDelegate ClearNetwork;

		public NeuralNetworkControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Network description is written into control.
		/// </summary>
		public string NetworkDescription
		{
			set
			{
				networkFormatTextBox.Text = value;
				networkFormatTextBox.ReadOnly = true;
				saveNetworkButton.Visible = true;
				clearButton.Visible = true;
				createNetworkButton.Visible = false;
			}
		}

		/// <summary>
		/// Changes appearance of controls
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="eventArgs"></param>
		public void ClearButtonClick(object sender,	EventArgs eventArgs)
		{
			networkFormatTextBox.Clear();
			networkFormatTextBox.ReadOnly = false;
			clearButton.Visible = false;
			saveNetworkButton.Visible = false;
			createNetworkButton.Visible = true;
			ClearNetwork?.Invoke();
		}

		/// <summary>
		/// Event handler for loading network
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="eventArgs"></param>
		private void LoadNetworkButtonCLick(object sender, EventArgs eventArgs)
		{
			if (networkOpenFileDialog.ShowDialog() == DialogResult.OK)
			{
				LoadNetwork?.Invoke(networkOpenFileDialog.FileName);
			}
		}

		/// <summary>
		/// Event handler for saving network
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="eventArgs"></param>
		private void SaveNetworkButtonCLick(object sender, EventArgs eventArgs)
		{
			if(networkSaveFileDialog.ShowDialog() == DialogResult.OK)
			{
				SaveNetwork?.Invoke(networkSaveFileDialog.FileName);
			}
		}

		/// <summary>
		/// Event handler for creating new network
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="eventArgs"></param>
		private void CreateNetworkButtonCLick(object sender, EventArgs eventArgs)
		{
			uint[] networkFormat = ValidateNetworkFormat();
			if(networkFormat != null)
			{
				CreateNetwork?.Invoke(networkFormat);
			}
			else
			{
				MessageBox.Show("Incorrect format in text field. Correct format: x1;x2;x3;... where x is number if neurons in corresponding layer. At least 3 values", "Could not create neural network");
			}
		}

		/// <summary>
		/// Validates network description provided by user
		/// </summary>
		/// <returns>null if incorrect, array of neuron count in layers if correct</returns>
		private uint[] ValidateNetworkFormat()
		{
			if (networkFormatTextBox.Text != "")
			{
				string[] splitFormat = networkFormatTextBox.Text.Split(new char[] { ';' });
				if (splitFormat.Length >= 3)
				{
					return ConvertFormatToNumbers(splitFormat);
				}
			}
			return null;
		}

		/// <summary>
		/// Converts string format to neuron counts in layers
		/// </summary>
		/// <param name="splitFormat">Array of strings. Every string should contain a number</param>
		/// <returns>null on error, array of neuron count in layers if correct</returns>
		private uint[] ConvertFormatToNumbers(string[] splitFormat)
		{
			uint[] splitIntFormat = new uint[splitFormat.Length];
			for (int i = 0; i < splitFormat.Length; i++)
			{
				if (!uint.TryParse(splitFormat[i], out splitIntFormat[i]) && splitIntFormat[i] != 0)
				{
					MessageBox.Show("Error during parsing numbers in format. Check if entered format text is correct");
					return null;
				}
			}
			return splitIntFormat;
		}

	}
}
