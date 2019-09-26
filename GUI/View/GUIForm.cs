using GUI.Controller;
using GUI.Model;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
	/// <summary>
	/// Main GUI form
	/// </summary>
	public partial class GUIForm : System.Windows.Forms.Form
	{
		AppController appController;

		#region ctors

		public GUIForm()
		{
			appController = new AppController(this);
			InitializeComponent();
			neuralNetworkControl.LoadNetwork = LoadNetwork;
			neuralNetworkControl.CreateNetwork = CreateNetwork;
			neuralNetworkControl.SaveNetwork = SaveNetwork;
			neuralNetworkControl.ClearNetwork = ClearNetwork;
			digitSetControl.LoadDigitSet = LoadDigitSet;
		}

		#endregion

		#region methods

		/// <summary>
		/// Use appController to load network
		/// </summary>
		private void LoadNetwork(string filePath)
		{
			if (appController.LoadNetwork(filePath))
			{
				neuralNetworkControl.NetworkDescription = appController.NetworkDescription();
			}
			else
			{
				MessageBox.Show(appController.LastErrorMessage, "Load failed");
			}
		}

		/// <summary>
		/// Use appController to create network
		/// </summary>
		private void CreateNetwork(uint[] networkFormat)
		{
			if (appController.CreateNetwork(networkFormat))
			{
				neuralNetworkControl.NetworkDescription = appController.NetworkDescription();
			}
			else
			{
				MessageBox.Show(appController.LastErrorMessage, "Creation failed");
			}
		}

		/// <summary>
		/// Use appController to save network
		/// </summary>
		private void SaveNetwork(string filePath)
		{
			if (appController.SaveNetwork(filePath))
			{
				MessageBox.Show("Save successful");
			}
			else
			{
				MessageBox.Show(appController.LastErrorMessage, "Save failed");
			}
		}

		/// <summary>
		/// Use appController to load digit set
		/// </summary>
		private void LoadDigitSet(string digitFilePath, string labelFilePath)
		{
			if (appController.LoadDigitSet(digitFilePath, labelFilePath))
			{
				digitSetControl.DigitSetSize = appController.DigitSetSize;
			}
			else
			{
				MessageBox.Show(appController.LastErrorMessage, "Save failed");
			}
		}

		/// <summary>
		/// Remove network from appController
		/// </summary>
		private void ClearNetwork()
		{
			appController.ClearNetwork();
		}

		/// <summary>
		/// Allows to show training iteration in form
		/// </summary>
		internal void ShowIteration(uint iteration)
		{
			iterationLabel.Text = "Iteration " + (iteration + 1);
		}

		/// <summary>
		/// Allows to show test iteration in form
		/// </summary>
		internal void ShowTestIteration(uint iteration)
		{
			correctAmountLabel.Text = "Iteration " + (iteration + 1);
		}

		/// <summary>
		/// Allows to show results of test with digit set
		/// </summary>
		internal void ShowFileTestResults(uint correctCount, uint incorrectCount)
		{
			correctAmountLabel.Text = "Correctly classifed " + correctCount;
			incorrectAmountLabel.Text = "Incorrectly classifed " + incorrectCount;
			float percentage = 100f * ((float)incorrectCount / (correctCount + incorrectCount));
			percentageLabel.Text = "Error percentage: " + percentage.ToString() + " %";
		}

		/// <summary>
		/// Total mean error of network during training
		/// </summary>
		internal void ShowTotalError(float totalError)
		{
			networkErrorLabel.Text = "Total mean error: " + totalError.ToString();
		}

		#endregion

		#region event handlers

		/// <summary>
		/// Event handler for start of network training
		/// </summary>
		private void TrainButtonClick(object sender, EventArgs eventArgs)
		{
			uint startingIndex = (uint)startingIndexNumericUpDown.Value;
			uint endingIndex = (uint)endingIndexNumericUpDown.Value;
			if(endingIndex > startingIndex)
			{
				if(!appController.TrainNetwork(startingIndex, endingIndex, (float)learnRateUpDown.Value))
				{
					MessageBox.Show(appController.LastErrorMessage);
				}
			}
			else
			{
				MessageBox.Show("Ending index must be greater than starting index");
			}
		}

		/// <summary>
		/// Event handler for start of network testing, with use of digit set
		/// </summary>
		private void TestButtonClick(object sender, EventArgs eventArgs)
		{
			uint startingIndex = (uint)testStartingIndexNumericUpDown.Value;
			uint endingIndex = (uint)testEndingIndexNumericUpDown.Value;
			if (endingIndex > startingIndex)
			{
				if (!appController.TestNetwork(startingIndex, endingIndex))
				{
					MessageBox.Show(appController.LastErrorMessage);
				}
			}
			else
			{
				MessageBox.Show("Ending index must be greater than starting index");
			}
		}

		/// <summary>
		/// Event handler for testing network with use of a drawn digit
		/// </summary>
		private void TestSingleButtonClick(object sender, EventArgs eventArgs)
		{
			TestResult testResult = appController.TestSingle(digitDraw.DigitPixels);
			if (testResult != null)
			{
				singleTestResultLabel.Text = "Classified as " + testResult.ClassifiedAs;
			}
			else
			{
				MessageBox.Show(appController.LastErrorMessage);
			}
		}

		/// <summary>
		/// Clear image event handler
		/// </summary>
		private void ClearImageButtonClick(object sender, EventArgs e)
		{
			digitDraw.ClearImage();
		}

		#endregion


	}
}
